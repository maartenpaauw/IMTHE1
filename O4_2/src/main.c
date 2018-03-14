/*
 * Opdracht 4.2 - Led There Be Light
 * 
 * Maarten Paauw <s1094220@student.hsleiden.nl>
 * s1094220
 * INF3C
 */

#include <avr/io.h>
#include <util/setbaud.h>
#include <util/delay.h>

#include <USART.h>

uint8_t serData = 0;

ISR (USART_RX_vect) {
  serData = UDR0;
}

void initUSART(void) { 
    UBRR0H = UBRRH_VALUE; 
    UBRR0L = UBRRL_VALUE;
    
    #if USE_2X
        UCSR0A |= (1 << U2X0);
    #else
        UCSR0A &= ~(1 << U2X0);
    #endif
                    /* requires BAUD */
             /* defined in setbaud.h */
/* Enable USART transmitter/receiver */
    UCSR0B = (1 << TXEN0) | (1 << RXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); /* 8 data bits, 1 stop bit */
}


void transmitByte(uint8_t data) {
  loop_until_bit_is_set(UCSR0A, UDRE0);
  UDR0 = data;
}

uint8_t receiveByte(void) { 
    loop_until_bit_is_set(UCSR0A, RXC0); 
    return UDR0;
}

//  Example of a useful printing command
void printString(const char myString[]) { uint8_t i = 0;
    while (myString[i]) {
        transmitByte(myString[i]);
        i++; 
    }
}

int main (void) {

  initUSART();

  while (1) {
    transmitByte('h');
    _delay_ms(2000);
  }
}
