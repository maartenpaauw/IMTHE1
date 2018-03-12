# Opdracht 5.2

> ET Phone Home

Deze opdracht bestaat uit twee kleinere opdrachten:

1. Elke IMTHE-Box bevat unieke componenten. Zoek naar de datasheets van deze componenten en maak een kort verslag per component over de protocollen die gebruikt worden en hoe je dit moet gebruiken vanuit de AVR code.
2. **Zoek naar een library op internet om het HD44780 display te kunnen besturen en maak een programma dat jouw naam en studentnummer op het display laat zien.**

## Aanpak en Uitvoering

TODO

## Afbeelding

![Opdracht 5.2 - ET Phone Home - Afbeelding](assets/setup.jpg)

De afbeelding van de setup kan ook gedownload worden via de volgende link:

[https://raw.githubusercontent.com/maartenpaauw/IMTHE1/master/O5_2/assets/setup.jpg](https://raw.githubusercontent.com/maartenpaauw/IMTHE1/master/O5_2/assets/setup.jpg)

## Video

[![Opdracht 5.2 - ET Phone Home - Video](https://img.youtube.com/vi/XXX/maxresdefault.jpg)](https://www.youtube.com/)

Deze video is ook te vinden op **Youtube**:

[https://www.youtube.com/](https://www.youtube.com/)

## Breadboard Schema

[![Opdracht 5.2 - ET Phone Home - Schema](assets/fritzing/schema.png)](https://raw.githubusercontent.com/maartenpaauw/IMTHE1/master/O5_2/assets/fritzing/schema.png)

Het **Fritzing** schema kan ook gedownload worden via de volgende link:

[https://github.com/maartenpaauw/IMTHE1/raw/master/O5_2/assets/fritzing/schema.fzz](https://github.com/maartenpaauw/IMTHE1/raw/master/O5_2/assets/fritzing/schema.fzz)

### Hardware

| Onderdelen                 |
| -------------------------- |
| Arduino Nano (v3.0) - 1×   |

## Code

```c
/*
 * Opdracht 5.2 - ET Phone Home
 * 
 * Maarten Paauw <s1094220@student.hsleiden.nl>
 * s1094220
 * INF3C
 */

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{

    while (1)
    {
        
    }

    return 0;
}
```

De code kan ook gevonden worden in mijn **GitHub** *repository* via de volgende link:

[https://github.com/maartenpaauw/IMTHE1/blob/master/O5_2/src/main.c](https://github.com/maartenpaauw/IMTHE1/blob/master/O5_2/src/main.c)

## Datasheet

### Arduino Nano Pinout

![Arduino Nano Pinout](assets/data_sheets/nano.png)

De [Arduino Nano Pinout][1] is uitgedeeld tijdens de eerste les en terug te vinden via het volgende forum post:

[https://forum.arduino.cc/index.php?topic=147582.0][1]

## Bronvermelding

* [https://forum.arduino.cc/index.php?topic=147582.0][1] (Arduino Nano Pinout)

[1]: https://forum.arduino.cc/index.php?topic=147582.0 "Arduino Nano Pinout"
