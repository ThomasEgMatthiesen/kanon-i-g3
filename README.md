# Kanon i G3
Lydinstallation i Kanonstilling G3 ved Dueodde, Bornholm.

[Læs mere](https://www.genhoer.dk/kanon-i-g3)

Ved knaptryk tænder Arduino og holder latch i gang. Når Bela Mini er bootet startes afspilning og signal sendes til Arduino. Arduino tænder forstærkerne (4xTPA3118 moduler). Når afspilningen er slut går Bela Mini GPIO LOW og Arduino slukker forstærkere og herefter power latch.

Anlægget forsynes via en 12V 25Ah AGM Super Cycle batteri som oplades via MPPT 75/10 og solcellepanel (12V 55W).

## Power latch til forsyning af Arduino + Bela Mini
![Power Latch Breadboard](images/power-latch-breadboard.png)
![Power Latch Circuit](images/power-latch-circuit.png)
![Power Latch Image](images/power-latch-image.JPG)

## Soft start (RC) til opstart af TPA3118 moduler
![Soft Start Breadboard](images/soft-start-breadboard.png)
![Soft Start Circuit](images/soft-start-circuit.png)
![Soft Start Image](images/soft-start-image.JPG)
