#include <avr/io.h>
#include <avr/interrupt.h>

#define BUTTON PD2
#define LED    PB5

// ISR (INT0_vect) {
ISR (PCINT2_vect) {
  PORTB = (bit_is_clear(PIND, BUTTON) ? (1 << LED) : 0);
}

void initInterruptPCINT18 () {
  PCICR  |= (1 << PCIE2);          // Welke bank
  PCMSK2 |= (1 << PCINT18);       // Welke mask
  sei();
}

void initInterrupt0 () {
  EIMSK |= (1 << INT0);
  EICRA |= (1 << ISC00);
  sei();
}

int main (void) {

  DDRB  = (1 << LED);
  PORTD = (1 << BUTTON);

  // initInterrupt0();
  initInterruptPCINT18();

  // PORTB = (1 << LED);

  while (1) {

  }
}
