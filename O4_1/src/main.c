/*
 * Opdracht 4.1 - Led There Be Light
 * 
 * Maarten Paauw <s1094220@student.hsleiden.nl>
 * s1094220
 * INF3C
 */

#include <avr/io.h>
#include <avr/interrupt.h>

// LED pinnen.
#define LED_RED PB1
#define LED_GREEN PB2
#define LED_BLUE PB3

// RGB waardes.
int RGB[3] = {255, 0, 0};

// Count.
int count = 0;

// Bereken degene die opgeteld moet worden.
int increment(int count)
{
    return (count + 1) % 3;
}

// Bereken degene die afgetrokken moet worden.
int decrement(int count)
{
    return count % 3;
}

// Timer interrupt.
ISR(TIMER0_OVF_vect)
{
    // Deze variabele hebben we twee keer nodig.
    int dec = decrement(count);

    // Trek R, G of B af.
    RGB[dec] -= 1;

    // Tel R, G of B af.
    RGB[increment(count)] += 1;

    // Als de waarde van R, G of B helemaal terug is op 0.
    if (RGB[dec] <= 0)
    {
        // Tel op.
        count++;
    }

    else
    {
        OCR1A = ~RGB[0]; // Rode led waarde.
        OCR1B = ~RGB[1]; // Groene led waarde.
        OCR2A = ~RGB[2]; // Blauwe led waarde.
    }
}

// Overflow timers.
void initTimerOverflow()
{
    // Timer mask.
    TIMSK0 |= (1 << TOIE0);

    // Timer instellingen.
    TCCR0B |= (1 << CS02) | (1 << CS00);

    // Start de interrupt.
    sei();
}

// LED timers.
void intPWMTimerLED()
{
    // Timer 1 (Voor rood en groen).
    TCCR1A |= (1 << WGM10) | (1 << WGM12); // Fast PWM.
    TCCR1B |= (1 << CS11);                 // PWM freq.

    // Timer 2 (Voor blauw).
    TCCR2A |= (1 << WGM20) | (1 << WGM21); // Fast PWM.
    TCCR2B |= (1 << CS21);                 // PWM freq.

    // Rode en groene led.
    TCCR1A |= (1 << COM1A1) | (1 << COM1B1);

    // Blauwe led.
    TCCR2A |= (1 << COM2A1);
}

// Main functie.
int main(void)
{

    // Initialiseer de RGB LED pinnen.
    DDRB = (1 << LED_RED) | (1 << LED_GREEN) | (1 << LED_BLUE);

    // Initialiseer de overflow timer.
    initTimerOverflow();

    // Initialiseer de led timer.
    intPWMTimerLED();

    // Loop voor altijd.
    while (1)
    {
    }

    // Geef 0 terug.
    return 0;
}
