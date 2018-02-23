/*
 * Opdracht 3.2 - ADC Baby!
 * 
 * Maarten Paauw <s1094220@student.hsleiden.nl>
 * s1094220
 * INF3C
 */

#include <avr/io.h>
#include <util/delay.h>

// Initialiseer de potential meter.
void initADC () {
    
    // Zet op 5 volt.
    ADMUX  |= (1 << REFS0);
    
    // Divider op 128 voor 10 bit precisie.
    ADCSRA |= ((1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2));
    
    // AD enable.
    ADCSRA |= (1 << ADEN);
}

// Lees de potential meter.
uint16_t readADC () {
    
    // Starten met lezen.
    ADCSRA |= (1 << ADSC);
    
    // Loop totdat er een waarde is.
    loop_until_bit_is_clear(ADCSRA, ADSC);
    
    // Geef de waarde terug.
    return ADC;
}

// Dynamische timeout.
void delay (uint16_t time) {

    // For loop.
    for (uint16_t i = 0; i < time; i++) {

        // Wacht voor 1 ms.
        _delay_ms(1);
    }
}

int main(void)
{
    // B Bank initialiseren.
    DDRB  = (1 << PB5);

    // Zet de D pin aan.
    PORTD = (1 << PD2);

    // Initialiseer de potential meter.
    initADC();

    // Loop voor altijd.
    while (1)
    {
        // Lees de waarde van de potential meter uit.
        uint16_t pwm = readADC();

        // Zet de B pin aan.
        PORTB = (1 << PB5);

        // Wacht voor 2 ms.
        _delay_ms(2);

        // Zet de B pin uit.
        PORTB = 0;

        // Wacht voor een X aantal ms.
        delay(pwm / 100);
    }

    return 0;
}
