/*
 * Opdracht 4.2 - Led There Be Light
 * 
 * Maarten Paauw <s1094220@student.hsleiden.nl>
 * s1094220
 * INF3C
 */

#include <avr/io.h>
#include <USART.h>
#include <util/setbaud.h>
#include <util/delay.h>

// Main functie.
int main (void)
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

    // Anders,
    else
    {
        // Geef aan dat het niet gelukt is.
        printString("Het is niet gelukt.\n");
    }
  }
}
