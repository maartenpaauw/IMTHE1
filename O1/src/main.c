/*
 * Opdracht 1 - Blink Once To Accept
 * 
 * Maarten Paauw <s1094220@student.hsleiden.nl>
 * s1094220
 * INF3C
 */

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{

    // Defineer dat D5 + D7 een output pin is.
    DDRD = 0b10100000;

    while (1)
    {
        // Toggle de led op D5.
        PORTD ^= 1 << 5;

        // Wacht voor 1 seconden.
        _delay_ms(1000);

        // Toggle de led op D7.
        PORTD ^= 1 << 7;
    }

    return 0;
}
