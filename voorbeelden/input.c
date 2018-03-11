/*
 * Opdracht 0 - X
 * 
 * Maarten Paauw <s1094220@student.hsleiden.nl>
 * s1094220
 * INF3C
 */

#include <avr/io.h>
#include <util/delay.h>
// #include <stdlib.h>

// Genereer een random nummer tussen 1 en 6.
// int dobbel () {
//     return rand() % 6 + 1;
// }

void initADC () {
    ADMUX  |= (1 << REFS0);                                                     // Zet op 5 volt.
    ADCSRA |= ((1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2));                     // Divider op 128 voor 10 bit precisie.
    ADCSRA |= (1 << ADEN);                                                      // AD enable.
}

uint16_t readADC () {
    ADCSRA |= (1 << ADSC);                                                      // Starten met lezen.
    loop_until_bit_is_clear(ADCSRA, ADSC);                                      // Loop totdat er een waarde is.
    return ADC;                                                                 // Geef de waarde terug.
}

void delay (uint16_t value) {
    for (uint16_t i = 0; i < value; i++) {
        _delay_ms(1);
    }
}

int main(void)
{
    DDRB  = (1 << PB5);
    PORTD = (1 << PD2);

    initADC();

    while (1)
    {
        // PORTB = bit_is_clear(PIND, PD2) ? (1 << PB5) : 0;
        // PORTB = (readADC() > 512) ? (1 << PB5) : 0;

        uint16_t pwm = readADC();

        PORTB = (1 << PB5);
        _delay_ms(2);
        PORTB = 0;
        delay(pwm / 100);
    }

    return 0;
}
