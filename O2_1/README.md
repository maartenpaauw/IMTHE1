# Opdracht 2.1

> Count Me In

Deze opdracht bestaat uit drie kleinere opdrachten:

1. **Maak een programma dat op het 7-segment LED display herhalend telt van 0 t/m 9. Gebruik het rechter display van de twee en verwerk functies en bit-shifting in je oplossing.**
2. Breidt de eerste deel-opdracht uit zodat de twee segmenten samen van 0 t/m 99 tellen.

## Aanpak & Uitvoering

### Vinden van de Datasheet

Op het internet had ik een [brochure][2] gevonden van het bedrijf Greegoo. In deze brochure stonden meerdere componenten met het daarbij behorende datasheet. Één pagina ging over het 7 segment display (D5621A/B). Deze is te vinden in het hoofdstuk **Datasheets**. Elke 7 segment heeft 9 pinnen. 7 daarvan voor elke *streepje*, 1 voor de punt en 1 voor de *ground* of de voltage. Deze aantal pinnen zijn 2 keer aanwezig omdat het een dubbel 7 segment display is.

Als het scherm gevoed wordt via de 5v5 pin op de Arduino heet dat **common anode** en als het scherm gevoed wordt via een data pin op de Arduino heet dat **common cathode**. Hoe mijn 7 Segment Display aangesloten moet worden is niet aangegeven op het component zelf. Dit moet achterhaald worden. Meer hierover in het volgende hoofdstuk.

### Common- Anode of Cathode

In het datasheet stond aangegeven dat pin 13 en 14 op de *ground* of op de 5v5 pin moeten. Om uit te zoeken of het een common anode of een cathode is heb ik eerst pin 13 en 14 op een *ground* pin aangesloten. Daarna had ik met de 5v5 pin, met een resistor ertussen, aan gesloten op een van de segment pinnen. Geen een van de segmenten ging aan. Hierdoor wist ik dat het geen common cathode is maar een common anode 7 segment display. Dus heb ik pin 13 en 14 aangesloten, met een resistor ertussen, op de 5v5 pin op de Arduino. De pinnen van elke segment heb ik aangesloten op de pinnen van de B en D bank. 

### Het Vormen van Getallen

Op de wikipedia pagina van het [7 Segment Display][3] was een lijst opgenomen hoe je met welke segmenten welk getal kan vormen. Voor het gemak heb ik deze waardes (**on** of **off**) omgezet naar binair (**1** of **0**). Dit heb ik gedaan voor elk getal en dit in een array gestopt.

## Afbeelding

![Opdracht 2.1 - Count Me In - Afbeelding](https://raw.githubusercontent.com/maartenpaauw/IMTHE1/master/O2_1/assets/setup.jpg)

De afbeelding van de setup kan ook gedownload worden via de volgende link:

[https://raw.githubusercontent.com/maartenpaauw/IMTHE1/master/O2_1/assets/setup.jpg](https://raw.githubusercontent.com/maartenpaauw/IMTHE1/master/O2_1/assets/setup.jpg)

## Video

[![Opdracht 2.1 - Count Me In - Video](https://img.youtube.com/vi/wHO4zX4rpPY/maxresdefault.jpg)](https://www.youtube.com/watch?v=wHO4zX4rpPY)

Deze video is te vinden op **YouTube**:

[https://www.youtube.com/watch?v=wHO4zX4rpPY](https://www.youtube.com/watch?v=wHO4zX4rpPY)

De video kan ook gedownload worden via de volgende **Google Drive** link:

[https://drive.google.com/file/d/1ph_m7KxTQp7U6tLeJVHFOjUYs3lxtdCl/view?usp=sharing](https://drive.google.com/file/d/1ph_m7KxTQp7U6tLeJVHFOjUYs3lxtdCl/view?usp=sharing)

## Breadboard Schema

[![Opdracht 2.1 - Count Me In - Schema](https://raw.githubusercontent.com/maartenpaauw/IMTHE1/master/O2_1/assets/fritzing/schema.png)](https://raw.githubusercontent.com/maartenpaauw/IMTHE1/master/O2_1/assets/fritzing/schema.png)

***LET OP:*** *Fritzing heeft geen dubbel 7 segment display. Daarom gebruik ik in het schema 2 enkele. Omdat ik 2 enkele gebruik zijn er wel meer pinnen in het schema. Van het rechter 7 segment display tel ik de rechter- boven en onder pin niet mee.*

Het **Fritzing** schema kan ook gedownload worden via de volgende link:

[https://github.com/maartenpaauw/IMTHE1/raw/master/O2_1/assets/fritzing/schema.fzz](https://github.com/maartenpaauw/IMTHE1/raw/master/O2_1/assets/fritzing/schema.fzz)

### Hardware

| Onderdelen                |
| ------------------------- |
| Arduino Nano (v3.0) - 1×  |
| 220Ω Resistor - 1×        |
| Dupont Kabel - 10×        |
| 7 Segment (D5621A/B) - 1× |


## Code

```c
/*
 * Opdracht 2.1 - Count Me In
 * 
 * Eigenaar:
 * Maarten Paauw <s1094220@student.hsleiden.nl>
 * s1094220
 * INF3C
 * 
 * Versie: 1
 * Aangemaakt: 15 februari 2018
 * Gewijzigd: 27 maart 2018
 */

/*
 * RIGHT DIGIT
 *
 * PD2 = A = 11
 * PD3 = B = 10
 * PD4 = C = 8
 * PD5 = D = 6
 * 
 * PC0 = E = 5
 * PC1 = F = 12
 * PC2 = G = 7
 */

#include <avr/io.h>
#include <util/delay.h>

// Regel de C pinnen.
void handleC(int number)
{
    // 0b00111111
    // 0b01111110
    // 0b00000011 <- uitkomst voor 0.
    PORTC = ~((number << 1) >> 5);
}

// Regel de D pinnen.
void handleD(int number)
{
    // 0b00111111
    // 0b11110000
    // 0b00111100 <- uitkomst voor 0.
    PORTD = ~((number << 4) >> 2);
}

// De main functie.
int main(void)
{
    // Segmenten als binair getal voor de cijfers 0 t/m 9.
    int numbers[10] = {
        // GFEDCBA
        0b00111111, // 0
        0b00000110, // 1
        0b01011011, // 2
        0b01001111, // 3
        0b01100110, // 4
        0b01101101, // 5
        0b01111101, // 6
        0b00000111, // 7
        0b01111111, // 8
        0b01101111  // 9
    };

    // Count
    int a = 0;

    // Zet de C pinnen op output.
    DDRC = 0b00111111;

    // Zet de D pinnen op output.
    DDRD = 0b00111100;

    // Loop voor altijd.
    while (1)
    {
        // Rechter digit.
        int right = numbers[a % 10];

        // Regel de C pinnen.
        handleC(right);

        // Regel de D pinnen.
        handleD(right);

        // Wacht 1 seconden.
        _delay_ms(1000);

        // Tel de A op.
        a++;

        // Als het getal groter is dan 9.
        if (a > 9)
        {
            // Reset de count.
            a = 0;
        }
    }

    // Geef 0 terug.
    return 0;
}
```

De code kan ook gevonden worden in mijn **GitHub** *repository* via de volgende link:

[https://github.com/maartenpaauw/IMTHE1/blob/master/O2_1/src/main.c](https://github.com/maartenpaauw/IMTHE1/blob/master/O2_1/src/main.c)

## Datasheets

### Arduino Nano

![Arduino Nano Pinout](https://raw.githubusercontent.com/maartenpaauw/IMTHE1/master/O2_1/assets/data_sheets/nano.png)

De [Arduino Nano Pinout](https://raw.githubusercontent.com/maartenpaauw/IMTHE1/master/O2_1/assets/data_sheets/nano.png) is uitgedeeld tijdens de eerste les en terug te vinden via het volgende forum post:

[https://forum.arduino.cc/index.php?topic=147582.0][1]

### 7 Segment Display

![D5621A_B](https://raw.githubusercontent.com/maartenpaauw/IMTHE1/master/O2_1/assets/data_sheets/D5621A_B.png)

De [7 Segment Display Pinout](https://raw.githubusercontent.com/maartenpaauw/IMTHE1/master/O2_1/assets/data_sheets/D5621A_B.png) heb ik gevonden in de datasheet van het 7 Segment Display. De datasheet is terug te vinden via de volgende link:

[http://datasheet.datasheetarchive.com/originals/library/Datasheets-SL3/DSASL0045733.pdf][2]

## Bronvermelding

* [https://forum.arduino.cc/index.php?topic=147582.0][1] (Arduino Nano Pinout)
* [http://datasheet.datasheetarchive.com/originals/library/Datasheets-SL3/DSASL0045733.pdf][2] (7 Segment Display (D5621A/B) Datasheet)
* [https://en.wikipedia.org/wiki/Seven-segment_display][3] (7 Segment Display)

[1]: https://forum.arduino.cc/index.php?topic=147582.0 "Arduino Nano Pinout"
[2]:  http://datasheet.datasheetarchive.com/originals/library/Datasheets-SL3/DSASL0045733.pdf "7 Segment Display (D5621A/B) Datasheet"
[3]: https://en.wikipedia.org/wiki/Seven-segment_display "7 Segment Display"
