/*
 * Opdracht 1 - Blink Once To Accept
 * 
 * Maarten Paauw <s1094220@student.hsleiden.nl>
 * s1094220
 * INF3C
 */

#include <avr/io.h>
#include <util/delay.h>

// Defineer de pinnen voor de leds.
#define LED_1 PD5
#define LED_2 PD7

// De main functie.
int main(void)
{

    // Defineer dat D5 + D7 een output pin is.
    DDRD = (1 << LED_1) | (1 << LED_2);

    while (1)
    {
        // Toggle de led op D5.
        PORTD ^= (1 << LED_1);

        // Wacht voor 1 seconden.
        _delay_ms(1000);

        // Toggle de led op D7.
        PORTD ^= (1 << LED_2);
    }

    return 0;
}
