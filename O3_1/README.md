# Opdracht 3.1

> ADC Baby!

Deze opdracht bestaat uit twee kleinere opdrachten:

1. **Maak een digitale dobbelsteen met 9 leds (zie plaatje). Als je op een knop drukt geven de leds een random waarde tussen 1 en 6 weer op de leds zoals je dat kent op een echte dobbelsteen. Hou bij het programma rekening met dender-gedrag.** 
2. Maak een programma dat de waarde van een potentiometer vertaalt in een geluidssignaal tussen 100 en 10.000Hz. Laat dit signaal horen op de speaker.

![Opdracht 3.1 - ADC Baby! - Voorbeeld](assets/voorbeeld.png)

## Aanpak en Uitvoering

Pinnen die nodig zijn:

| Rijen | Kolommen |
| ----- | -------- |
| 9     | 13       |
| 14    | 3        |
| 4     | 10       |
| 5     | 6        |
| 7     | 15       |
| 8     | 16       |

## Afbeelding

![Opdracht 3.1 - ADC Baby! - Afbeelding](assets/setup.jpg)

De afbeelding van de setup kan ook gedownload worden via de volgende link:

[https://raw.githubusercontent.com/maartenpaauw/IMTHE1/master/O3_1/assets/setup.jpg](https://raw.githubusercontent.com/maartenpaauw/IMTHE1/master/O3_1/assets/setup.jpg)

## Video

[![Opdracht 3.1 - ADC Baby! - Video](https://img.youtube.com/vi/kApDEr8afI4/maxresdefault.jpg)](https://www.youtube.com/watch?v=kApDEr8afI4)

Deze video is ook te vinden op **Youtube**:

[https://www.youtube.com/watch?v=kApDEr8afI4](https://www.youtube.com/watch?v=kApDEr8afI4)

## Breadboard Schema

[![Opdracht 3.1 - ADC Baby! - Schema](assets/fritzing/schema.png)](https://raw.githubusercontent.com/maartenpaauw/IMTHE1/master/O3_1/assets/fritzing/schema.png)

Het **Fritzing** schema kan ook gedownload worden via de volgende link:

[https://github.com/maartenpaauw/IMTHE1/raw/master/O3_1/assets/fritzing/schema.fzz](https://github.com/maartenpaauw/IMTHE1/raw/master/O3_1/assets/fritzing/schema.fzz)

### Hardware

| Onderdelen                 |
| -------------------------- |
| Arduino Nano (v3.0) - 1×   |

## Code

```c
/*
 * Opdracht 3.1 - ADC Baby!
 * 
 * Maarten Paauw <s1094220@student.hsleiden.nl>
 * s1094220
 * INF3C
 */

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

// Genereer een random nummer tussen 1 en 6.
int dobbel () {
    return (rand() % 6) + 1;
}

// Regel de pinnen op de C bank.
void handleC (int number) {
    PORTC =~ number;
}

// Regel de pinnen op de D bank.
void handleD (int number) {

    // Door de RX en TX pinnen begin ik pas op pin D2.
    // Daarom wordt er even 2x naar links gebitshift.
    PORTD = (number << 2);
}

// Zet alle poorten uit.
void clear () {
    PORTC = 0b0000000;
    PORTD = 0b0000000;
}

void dot (int number) {
    number = number - 1;

    int dots[9][2] = {
        { 0b00000011, 0b00000011 },     // LINKS    BOVEN
        { 0b00001100, 0b00000011 },     // MIDDEN   BOVEN
        { 0b00110000, 0b00000011 },     // RECHTS   BOVEN
        { 0b00000011, 0b00001100 },     // LINKS    MIDDEN
        { 0b00001100, 0b00001100 },     // MIDDEN   MIDDEN
        { 0b00110000, 0b00001100 },     // RECHTS   MIDDEN
        { 0b00000011, 0b00110000 },     // LINKS    ONDER
        { 0b00001100, 0b00110000 },     // MIDDEN   ONDER
        { 0b00110000, 0b00110000 }      // RECHTS   ONDER
    };

    // Zet de C pinnen aan.
    handleC(dots[number][0]);

    // Zet de D pinnen aan.
    handleD(dots[number][1]);
}

void side (int number) {

    // Alle zijdes van een dobbelsteen met welke ogen er nodig zijn.
    int sides[6][6] = {
        { 5 },                  // 1
        { 1, 9 },               // 2
        { 1, 5, 9 },            // 3
        { 1, 3, 7, 9},          // 4
        { 1, 3, 5, 7, 9},       // 5
        { 1, 3, 4, 6, 7, 9 }    // 6
    };

    // Loop door de ogen heen.
    for (int i = 0; i < number; i++)
    {
        // Zet alle pinnen uit.
        clear();

        // Zet de dot aan.
        dot(sides[number - 1][i]);

        // Wacht voor 1 miliseconden.
        _delay_ms(1);
    }
}

int main(void)
{
    // Zet de B pinnen op input.
    PORTB = (1 << PB0);

    // Zet de C pinnen op output.
    DDRC = 0b00111111;

    // Zet de D pinnen op output.
    DDRD = 0b11111100;

    // Toon standaard 1.
    int res = 1;

    while (1)
    {
        // Controleer of de knop is ingedrukt.
        if (bit_is_clear(PINB, PB0)) {

            // Genereer een random getal.
            res = dobbel();

            // Leeg het display.
            clear();

            // Loop net zolang dat de button losgelaten is.
            loop_until_bit_is_set(PINB, PB0);
        }

        // Toon het resultaat.
        side(res);
    }

    return 0;
}
```

De code kan ook gevonden worden in mijn **GitHub** *repository* via de volgende link:

[https://github.com/maartenpaauw/IMTHE1/blob/master/O3_1/src/main.c](https://github.com/maartenpaauw/IMTHE1/blob/master/O3_1/src/main.c)

## Datasheet

### Arduino Nano Pinout

![Arduino Nano Pinout](assets/data_sheets/nano.png)

De [Arduino Nano Pinout][1] is uitgedeeld tijdens de eerste les en terug te vinden via het volgende forum post:

[https://forum.arduino.cc/index.php?topic=147582.0][1]

## Bronvermelding

* [https://forum.arduino.cc/index.php?topic=147582.0][1] (Arduino Nano Pinout)

[1]: https://forum.arduino.cc/index.php?topic=147582.0 "Arduino Nano Pinout"