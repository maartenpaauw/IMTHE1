/*
 * Opdracht 4.2 - Led There Be Light
 * 
 * Maarten Paauw <s1094220@student.hsleiden.nl>
 * s1094220
 * INF3C
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

    // Anders,
    else
    {
      // Geef aan dat het niet gelukt is.
      printString("Het is niet gelukt.\n");
    }
  }
}
