/*
 * Opdracht 4.1 - Led There Be Light
 * 
 * Maarten Paauw <s1094220@student.hsleiden.nl>
 * s1094220
 * INF3C
 */

#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>

// LED pinnen.
#define LED_RED PB1
#define LED_GREEN PB2
#define LED_BLUE PB3

// RGB waardes.
int RGB[3] = {255, 0, 0};

// Rood als decrement.
int dec = 0;

// Groen als increment.
int inc = 1;

ISR(TIMER0_OVF_vect)
{
    // Trek R, G of B af.
    RGB[dec] -= 1;

    // Tel R, G of B af.
    RGB[inc] += 1;

    // Als de waarde van R, G of B helemaal terug is op 0.
    if (RGB[dec] <= 0)
    {
        // Tel op.
        dec++;
        inc++;

        // Als de decrement groter dan 2 wordt.
        if (dec > 2)
        {
            // Reset de opteller.
            dec = 0;
        }

        // Als de increment groter dan 2 wordt.
        if (inc > 2)
        {
            // Reset de opteller.
            inc = 0;
        }
    }

    else
    {
        // Rode led waarde.
        OCR1A = ~RGB[0];

        // Groene led waarde.
        OCR1B = ~RGB[1];

        // Blauwe led waarde.
        OCR2A = ~RGB[2];
    }
}

void initTimerOverflow()
{
    // Timer mask.
    TIMSK0 |= (1 << TOIE0);

    // Timer instellingen.
    TCCR0B |= (1 << CS02) | (1 << CS00);
    sei();
}

void intPWMTimerLED()
{
    // Timer 1 (Voor rood en groen).
    TCCR1A |= (1 << WGM10) | (1 << WGM12); // Fast PWM.
    TCCR1B |= (1 << CS11);                 // PWM freq.

    // Timer 2 (Voor blauw).
    TCCR2A |= (1 << WGM20) | (1 << WGM21); // Fast PWM.
    TCCR2B |= (1 << CS21);                 // PWM freq.

    // Rode led.
    TCCR1A |= (1 << COM1A1);

    // Groene led.
    TCCR1A |= (1 << COM1B1);

    // Blauwe led.
    TCCR2A |= (1 << COM2A1);
}

// Main fucntie.
int main(void)
{

    // Initialiseer de RGB LED pinnen.
    DDRB = ((1 << LED_RED) | (1 << LED_GREEN) | (1 << LED_BLUE));

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
