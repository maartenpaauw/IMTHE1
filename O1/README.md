# Opdracht 1

> Blink Once To Accept

Maak een "Blink led" programma, waar twee leds om en om aan en uit gaan. Het knipperen van de leds moet traag verlopen, zodat het knipper-effect zichtbaar is met het blote oog.

## Aanpak en Uitvoering

Omdat ik altijd de editor Visual Studio Code gebruik wilde ik daar ook mijn opdrachten in gaan maken. Om er voor te zorgen dat dit mogelijk is moet er gebruik worden gemaakt van Platform IO. Dit wordt gedaan door middel van Platform IO zelf te installeren en de plugin binnen Visual Studio Code te downloaden en te activeren. Platform IO heeft, net zoals in Arduino IDE, voorbeeld *sketches*. Een van de *sketches* is ["Native Blink"][2] (geschreven in C). Deze heb ik geopend, *gebuild* en geüpload naar mijn Arduino om Platform IO te testen. Deze code zorgt ervoor dat de *onboard* led aan en uit gaat. Dit is lukte. Om deze opdracht te voltooien heb ik de code omgeschreven om er voor te zorgen dat 2 leds om de beurt aan en uit gaan. Hoe de led aangesloten moest worden heb ik gevonden in de datasheet. Een afbeelding en een link naar de datasheet is opgenomen in het hoofdstuk **Datasheets**.

## Afbeelding

![Opdracht 1 - Blink Once To Accept - Afbeelding](https://raw.githubusercontent.com/maartenpaauw/IMTHE1/master/O1/assets/setup.jpg)

De afbeelding van de setup kan ook gedownload worden via de volgende link:

[https://raw.githubusercontent.com/maartenpaauw/IMTHE1/master/O1/assets/setup.jpg](https://raw.githubusercontent.com/maartenpaauw/IMTHE1/master/O1/assets/setup.jpg)

## Video

[![Opdracht 1 - Blink Once To Accept - Video](https://img.youtube.com/vi/_TIATMJMEbU/maxresdefault.jpg)](https://www.youtube.com/watch?v=_TIATMJMEbU)

Deze video is ook te vinden op **YouTube**:

[https://www.youtube.com/watch?v=_TIATMJMEbU](https://www.youtube.com/watch?v=_TIATMJMEbU)

## Breadboard Schema

[![Opdracht 1 - Blink Once To Accept - Schema](https://raw.githubusercontent.com/maartenpaauw/IMTHE1/master/O1/assets/fritzing/schema.png)](https://raw.githubusercontent.com/maartenpaauw/IMTHE1/master/O1/assets/fritzing/schema.png)

Het **Fritzing** schema kan ook gedownload worden via de volgende link:

[https://github.com/maartenpaauw/IMTHE1/raw/master/O1/assets/fritzing/schema.fzz](https://github.com/maartenpaauw/IMTHE1/raw/master/O1/assets/fritzing/schema.fzz)

### Hardware

| Onderdelen               |
| ------------------------ |
| Arduino Nano (v3.0) - 1× |
| 220Ω Resistor - 2×       |
| Dupont kabel - 5×        |
| LED - 2×                 |

## Code

```c
/*
 * Opdracht 1 - Blink Once To Accept
 * 
 * Eigenaar:
 * Maarten Paauw <s1094220@student.hsleiden.nl>
 * s1094220
 * INF3C
 * 
 * Versie: 1
 * Aangemaakt: 8 februari 2018
 * Gewijzigd: 27 maart 2018
 */

#include <avr/io.h>
#include <util/delay.h>

// Defineer de pinnen voor de leds.
#define LED_1 PD5
#define LED_2 PD7

// De main functie.
int main(void)
{

    // Defineer dat D5 + D7 een output pin is.
    DDRD = (1 << LED_1) | (1 << LED_2);

    // Loop voor altijd.
    while (1)
    {
        // Toggle de led op D5.
        PORTD ^= (1 << LED_1);

        // Wacht voor 1 seconden.
        _delay_ms(1000);

        // Toggle de led op D7.
        PORTD ^= (1 << LED_2);
    }

    // Geef 0 terug.
    return 0;
}
```

De code kan ook gevonden worden in mijn **GitHub** *repository* via de volgende link:

[https://github.com/maartenpaauw/IMTHE1/blob/master/O1/src/main.c](https://github.com/maartenpaauw/IMTHE1/blob/master/O1/src/main.c)

## Datasheets

### Arduino Nano

![Arduino Nano Pinout](https://raw.githubusercontent.com/maartenpaauw/IMTHE1/master/O1/assets/data_sheets/nano.png)

De [Arduino Nano Pinout](https://raw.githubusercontent.com/maartenpaauw/IMTHE1/master/O1/assets/data_sheets/nano.png) is uitgedeeld tijdens de eerste les en terug te vinden via het volgende forum post:

[https://forum.arduino.cc/index.php?topic=147582.0][1]

### Led

![LED Pinout](https://raw.githubusercontent.com/maartenpaauw/IMTHE1/master/O1/assets/data_sheets/led.png)

De [Led Pinout](https://raw.githubusercontent.com/maartenpaauw/IMTHE1/master/O1/assets/data_sheets/led.png) heb ik gevonden in de datasheet van de led. Deze datasheet is terug te vinden via de volgende link:

[http://www1.futureelectronics.com/doc/EVERLIGHT%C2%A0/334-15__T1C1-4WYA.pdf][3]

## Bronvermelding

* [https://forum.arduino.cc/index.php?topic=147582.0][1] (Arduino Nano Pinout)
* [https://github.com/platformio/platform-atmelavr/tree/develop/examples/native-blink][2] (Native Blink)
* [http://www1.futureelectronics.com/doc/EVERLIGHT%C2%A0/334-15__T1C1-4WYA.pdf][3] (Led Datasheet)

[1]: https://forum.arduino.cc/index.php?topic=147582.0 "Arduino Nano Pinout"
[2]: https://github.com/platformio/platform-atmelavr/tree/develop/examples/native-blink "Native Blink"
[3]: http://www1.futureelectronics.com/doc/EVERLIGHT%C2%A0/334-15__T1C1-4WYA.pdf "Led Datasheet"
