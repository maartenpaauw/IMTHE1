#include <avr/io.h>
#include <avr/interrupt.h>

#define LED PB3

uint8_t teller = 0;

ISR(TIMER0_OVF_vect)
{
  OCR2A = teller;
  teller++;
}

void initTimer0()
{
  TIMSK0 |= (1 << TOIE0);
  TCCR0B |= (1 << CS02) | (1 << CS00);
  sei();
}

void initTimer1()
{
  TCCR1B |= ((1 << CS10) | (1 << CS12));
}

void intPWMTimer2()
{
  TCCR2A |= ((1 << WGM20) | (1 << WGM21)); // Fast PWM
  TCCR2B |= (1 << CS21);                   // Devider van 8.
  TCCR2A |= (1 << COM2A1);                 // Output op pb3.
}

int main()
{
  DDRB = (1 << LED);

  initTimer0();
  // initTimer1();
  intPWMTimer2();

  while (1)
  {
    // TCNT1
    // PORTB = (TCNT1 > 32000) ? (1 << LED) : 0;
  }

  return 0;
}
