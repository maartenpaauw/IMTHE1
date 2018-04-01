# Opdracht 4.2

> Led There Be Light

Deze opdracht bestaat uit drie kleinere opdrachten:

1. Creëer een ‘Color changing light’ met het RGB-led op basis van PWM. De PWM moet in een Interrupt Service Routine (ISR) worden afgehandeld.
2. **Maak een programma waarin je via Serial communicatie een led aan of uit kan zetten. Dit mag door bijvoorbeeld het karakter ‘a’ of ‘u’ te sturen. Het programma geeft feedback over de seriële poort of het gelukt is ja of nee. Gebruik niet de gegeven usart.c en .h in je uitwerking, maar maak een oplossing in 1 source bestand.**
3. Verander deelopdracht 2 zodat binnenkomende data afgehandeld wordt in een interrupt (USART_RX_vect) zodat je programma (zoals in het voorbeeld van hoofdstuk 5) niet ‘eeuwig’ op input wacht. Toon aan dat het werkt door via seriële communicatie een ‘r’, ‘g’ of ‘b’ door te geven aan de AVR en dat dan de corresponderende kleur gaat pulseren (PWM op 1 kleur).

## Aanpak en Uitvoering

Tijdens de les ben ik op weg geholpen met seriële communicatie. Dit was code die de seriele verbinding uit leest en het karakter terug geeft wat verstuurd werd. Deze code die tijdens de les gemaakt is heb ik verder uitgewerkt voor deze opdracht. De code die gemaakt is controleert of er een 'a' of 'u' ontvangen wordt via de seriële communicatie. Als er een 'a' ontvangen wordt gaat de led aan en als er een 'u' ontvangen wordt gaat de led uit. Ook wordt er feedback gegeven via de seriële communicatie of het gelukt is of niet.

## Afbeelding

![Opdracht 4.2 - Led There Be Light - Afbeelding](https://raw.githubusercontent.com/maartenpaauw/IMTHE1/master/O4_2/assets/setup.jpg)

De afbeelding van de setup kan ook gedownload worden via de volgende link:

[https://raw.githubusercontent.com/maartenpaauw/IMTHE1/master/O4_2/assets/setup.jpg](https://raw.githubusercontent.com/maartenpaauw/IMTHE1/master/O4_2/assets/setup.jpg)

## Video

[![Opdracht 4.2 - Led There Be Light - Video](https://img.youtube.com/vi/a47dbYte-uk/maxresdefault.jpg)](https://www.youtube.com/watch?v=a47dbYte-uk)

Deze video is ook te vinden op **YouTube**:

[https://www.youtube.com/watch?v=a47dbYte-uk](https://www.youtube.com/watch?v=a47dbYte-uk)

## Breadboard Schema

[![Opdracht 4.2 - Led There Be Light - Schema](https://raw.githubusercontent.com/maartenpaauw/IMTHE1/master/O4_2/assets/fritzing/schema.png)](https://raw.githubusercontent.com/maartenpaauw/IMTHE1/master/O4_2/assets/fritzing/schema.png)

Het **Fritzing** schema kan ook gedownload worden via de volgende link:

[https://github.com/maartenpaauw/IMTHE1/raw/master/O4_2/assets/fritzing/schema.fzz](https://github.com/maartenpaauw/IMTHE1/raw/master/O4_2/assets/fritzing/schema.fzz)

### Hardware

| Onderdelen               |
| ------------------------ |
| Arduino Nano (v3.0) - 1× |
| LED - 1×                 |
| 220Ω Resistor - 1×       |
| Dupont Kabel - 3×        |

## Code

```c
/*
 * Opdracht 4.2 - Led There Be Light
 * 
 * Eigenaar:
 * Maarten Paauw <s1094220@student.hsleiden.nl>
 * s1094220
 * INF3C
 * 
 * Versie: 1
 * Aangemaakt: 12 maart 2018
 * Gewijzigd: 27 maart 2018
 */
#define BAUD 9600

#include <avr/io.h>
#include <util/setbaud.h>
#include <util/delay.h>

// Uit het bestand USART.
void initUSART(void)
{
  UBRR0H = UBRRH_VALUE;
  UBRR0L = UBRRL_VALUE;

  #if USE_2X
    UCSR0A |= (1 << U2X0);
  #else
    UCSR0A &= ~(1 << U2X0);
  #endif

  UCSR0B = (1 << TXEN0) | (1 << RXEN0);
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

// Uit het bestand USART.
uint8_t receiveByte(void)
{
  loop_until_bit_is_set(UCSR0A, RXC0);
  return UDR0;
}

// Uit het bestand USART.
void transmitByte(uint8_t data)
{
  loop_until_bit_is_set(UCSR0A, UDRE0);
  UDR0 = data;
}

// Uit het bestand USART.
void printString(const char myString[])
{
  uint8_t i = 0;
  while (myString[i])
  {
    transmitByte(myString[i]);
    i++;
  }
}

// Main functie.
int main(void)
{
  // Initialiseer de USART.
  initUSART();

  // Defineer de LED pin.
  DDRB = (1 << PB5);

  // Loop voor altijd.
  while (1)
  {
    // Lees de ontvangen byte via de seriele communicatie.
    uint8_t received = receiveByte();

    // Controleer of het een a is.
    if (received == 'a')
    {
      // Geef terug dat het gelukt is.
      printString("De LED is aan.\n");

      // Zet de LED aan.
      PORTB = (1 << PB5);
    }

    // Controller of het een u is.
    else if (received == 'u')
    {
      // Geef terug dat het gelukt is.
      printString("De LED is uit.\n");

      // Zet de LED aan.
      PORTB = (0 << PB5);
    }

    // Anders;
    else
    {
      // Geef aan dat het niet gelukt is.
      printString("Het is niet gelukt.\n");
    }
  }
}
```

De code kan ook gevonden worden in mijn **GitHub** *repository* via de volgende link:

[https://github.com/maartenpaauw/IMTHE1/blob/master/O4_2/src/main.c](https://github.com/maartenpaauw/IMTHE1/blob/master/O4_2/src/main.c)

## Datasheets

### Arduino Nano

![Arduino Nano Pinout](https://raw.githubusercontent.com/maartenpaauw/IMTHE1/master/O4_2/assets/data_sheets/nano.png)

De [Arduino Nano Pinout][1] is uitgedeeld tijdens de eerste les en terug te vinden via het volgende forum post:

[https://forum.arduino.cc/index.php?topic=147582.0][1]

### Led

![LED Pinout](https://raw.githubusercontent.com/maartenpaauw/IMTHE1/master/O4_2/assets/data_sheets/led.png)

De [Led Pinout](https://raw.githubusercontent.com/maartenpaauw/IMTHE1/master/O4_2/assets/data_sheets/led.png) heb ik gevonden in de datasheet van de led. Deze datasheet is terug te vinden via de volgende link:

[http://www1.futureelectronics.com/doc/EVERLIGHT%C2%A0/334-15__T1C1-4WYA.pdf][2]

## Bronvermelding

* [https://forum.arduino.cc/index.php?topic=147582.0][1] (Arduino Nano Pinout)
* [http://www1.futureelectronics.com/doc/EVERLIGHT%C2%A0/334-15__T1C1-4WYA.pdf][2] (Led Datasheet)

[1]: https://forum.arduino.cc/index.php?topic=147582.0 "Arduino Nano Pinout"
[2]: http://www1.futureelectronics.com/doc/EVERLIGHT%C2%A0/334-15__T1C1-4WYA.pdf "Led Datasheet"
