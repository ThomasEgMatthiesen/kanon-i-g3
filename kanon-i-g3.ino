#include <EEPROM.h>
#include <Wire.h>
#include <RTClib.h>
#include <Bounce2.h>

// PINS
#define LATCH_POWER       2
#define AMP_POWER_1       3
#define AMP_POWER_2       4
#define BELA_STATUS       5

// OPENING TIME
#define START_HOUR        10
#define END_HOUR          21

// EEPROM LOG
#define BOOT_COUNT_ADDR    0
int bootCount;

RTC_DS3231 rtc;
Bounce bela = Bounce();
unsigned long bootTime = 0;
bool hasPlayed = false;
bool rtcOK = false;

bool openingHours() {
  if (!rtcOK) return true;  // fortsæt hvis RTC fejler eller er løbet tør for strøm
  DateTime now = rtc.now();
  int hour = now.hour();
  return hour >= START_HOUR && hour < END_HOUR;
}

void setup() {
  pinMode(LATCH_POWER, OUTPUT);
  digitalWrite(LATCH_POWER, HIGH);
  
  pinMode(AMP_POWER_1, OUTPUT);
  digitalWrite(AMP_POWER_1, LOW);

  pinMode(AMP_POWER_2, OUTPUT);
  digitalWrite(AMP_POWER_2, LOW);

  bela.attach(BELA_STATUS, INPUT);
  bela.interval(50);

  bootTime = millis();

  Wire.begin();
  rtcOK = rtc.begin() && !rtc.lostPower();

  // SLUK IGEN UDEN FOR ÅBNINGSTID
  if (!openingHours()) {
    digitalWrite(LATCH_POWER, LOW);
    while (true);
  }

  // LOG BOOT COUNT
  EEPROM.get(BOOT_COUNT_ADDR, bootCount);
  bootCount++;
  EEPROM.put(BOOT_COUNT_ADDR, bootCount);  

  // INDSTIL RTC TIDSPUNKT VED UPLOAD:
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  // LÆS EEPROM (BOOT_COUNT_ADDR)
  // Serial.begin(9600);
  // EEPROM.get(BOOT_COUNT_ADDR, bootCount);
  // Serial.println(bootCount);

  // NULSTIL EEPROM TOTALT:
  // for (int i = 0; i < EEPROM.length(); i++) {
  //   EEPROM.write(i, 0);
  // }
}

void loop() {
  bela.update();
  bool playing = bela.read() == HIGH;

  if (playing) {
    digitalWrite(AMP_POWER_1, HIGH);
    delay(1000);
    digitalWrite(AMP_POWER_2, HIGH);
    hasPlayed = true;
  }

  else if (hasPlayed) {
    digitalWrite(AMP_POWER_1, LOW);
    digitalWrite(AMP_POWER_2, LOW);
    delay(1000);
    digitalWrite(LATCH_POWER, LOW);
  }

  // TIMEOUT WATCHDOG (30 sek)
  else if (millis() - bootTime > 30000) {
    digitalWrite(LATCH_POWER, LOW);
  }
}