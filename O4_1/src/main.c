/*
 * Opdracht 4.1 - Led There Be Light
 * 
 * Maarten Paauw <s1094220@student.hsleiden.nl>
 * s1094220
 * INF3C
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>

// LED pinnen.
#define LED_R PB1
#define LED_G PB2
#define LED_B PB3

// Random getal tussen de 0 en 255.
int waarde () {
    return (rand() % 255);
}

int main(void) {

    // Initialiseer de RGB LED pinnen.
    PORTB = ((1 << LED_R) | (1 << LED_G) | (1 << LED_B));

    while (1)
    {

    }

    return 0;
}
