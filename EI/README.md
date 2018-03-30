# Eindopdracht

> Show Your Moves

In opdracht 5 heb je jouw unieke IMTHE-Box componenten uitgezocht. Het doel van de eindopdracht is dat je iets unieks gaat maken met die componenten. Wat je gaat maken is aan jou, zolang het maar voldoet aan de volgend isen:

* Je maakt correct gebruik van minimaal 1 uniek input en 1 uniek output component. Het staat je vrij om daarnaast elk ander onderdeel uit je IMTHE-Box te gebruiken in je oplossing.
* De afhandeling van je in- en output gebeurt asynchroon door bijvoorbeeld ISR toe te passen.
* Je maakt gebruik van de nauwkeurigheid van de gegeven componenten. Je probeert dus zoveel mogelijk uit je component te halen.

De eindopdracht wordt ook in het verslag opgenomen met alle eisen eraan die al genoemd zijn. Daarnaast geef je ook een beschrijving van het concept inclusief waar het toegepast zou kunnen worden en film je je uitwerking uitgebreid, waarin duidelijk wordt dat je de uitwerking getest hebt in verschillende situaties.

## Aanpak en Uitvoering

In opdracht 5.1 heb ik al eerder beschreven hoe de 8×8 Matrix werkt en in opdracht 3.1 heb ik de 8×8 Matrix al eerder toegepast. Ook heb ik al eerder in opdracht 5.1 beschreven hoe de DHT11 sensor werkt. Het aansluiten en programmeren van de DHT11 sensor ligt na het uitzoeken en uitleggen voor de hand. Dit ga ik niet behandelen in dit hoofdstuk. Dit kan de hoofdstukken teruggevonden worden van de eerder genoemde opdrachten.

### Het concept

TODO.

## Afbeelding

![Eindopdracht - Show Your Moves - Afbeelding](https://raw.githubusercontent.com/maartenpaauw/IMTHE1/master/EI/assets/setup.jpg)

De afbeelding van de setup kan ook gedownload worden via de volgende link:

[https://raw.githubusercontent.com/maartenpaauw/IMTHE1/master/EI/assets/setup.jpg](https://raw.githubusercontent.com/maartenpaauw/IMTHE1/master/EI/assets/setup.jpg)

## Video

[![Eindopdracht - Show Your Moves - Video](https://img.youtube.com/vi/XXX/maxresdefault.jpg)](https://www.youtube.com/)

Deze video is ook te vinden op **Youtube**:

[https://www.youtube.com/](https://www.youtube.com/)

## Breadboard Schema

[![Eindopdracht - Show Your Moves - Schema](https://raw.githubusercontent.com/maartenpaauw/IMTHE1/master/EI/assets/fritzing/schema.png)](https://raw.githubusercontent.com/maartenpaauw/IMTHE1/master/EI/assets/fritzing/schema.png)

***LET OP:*** *Het programma **Fritzing** had geen DHT11 component. Daarom heb ik een component gepak dat het meest in de buurt komt. Op het component, dat in mijn IMTHE-Box zit, is een resistor van de data pin naar de 5v5 pin gesoldeerd. Deze resistor heb ik weggelaten in mijn Fritzing schema.*

Het **Fritzing** schema kan ook gedownload worden via de volgende link:

[https://github.com/maartenpaauw/IMTHE1/raw/master/EI/assets/fritzing/schema.fzz](https://github.com/maartenpaauw/IMTHE1/raw/master/EI/assets/fritzing/schema.fzz)

### Hardware

| Onderdelen                 |
| -------------------------- |
| Arduino Nano (v3.0) - 1×   |

## Code

```c
/*
 * Eindopdracht - Show Your Moves
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

[https://github.com/maartenpaauw/IMTHE1/blob/master/EI/src/main.c](https://github.com/maartenpaauw/IMTHE1/blob/master/EI/src/main.c)

## Datasheet

### Arduino Nano Pinout

![Arduino Nano Pinout](https://raw.githubusercontent.com/maartenpaauw/IMTHE1/master/EI/assets/data_sheets/nano.png)

De [Arduino Nano Pinout][1] is uitgedeeld tijdens de eerste les en terug te vinden via het volgende forum post:

[https://forum.arduino.cc/index.php?topic=147582.0][1]

## Bronvermelding

* [https://forum.arduino.cc/index.php?topic=147582.0][1] (Arduino Nano Pinout)
* [https://protostack.com.au/2010/05/introduction-to-74hc595-shift-register-controlling-16-leds/][2] (Shift Register Controlling 16 Leds)

[1]: https://forum.arduino.cc/index.php?topic=147582.0 "Arduino Nano Pinout"
[2]: https://protostack.com.au/2010/05/introduction-to-74hc595-shift-register-controlling-16-leds/ "Shift Register Controlling 16 Leds"