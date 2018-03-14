/*
 * Opdracht 3.2 - ADC Baby!
 * 
 * Maarten Paauw <s1094220@student.hsleiden.nl>
 * s1094220
 * INF3C
 */

#include <avr/io.h>
#include <util/delay.h>
#include <math.h>

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
        _delay_us(1);
    }
}

// Preciezere afronden.
// https://stackoverflow.com/questions/5731863/mapping-a-numeric-range-onto-another
double round (double d) {

    // Tel er 0.5 bij op en rond het getal af.
    return floor(d + 0.5);
}

// Map het getal van een range in een nieuwe range.
// https://stackoverflow.com/questions/5731863/mapping-a-numeric-range-onto-another
double map (int input, int input_start, int input_end, int output_start, int output_end) {
    
    // Defineer de slope.
    double slope = 1.0 * (output_end - output_start) / (input_end - input_start);

    // Geef het nieuwe getal terug.
    return output_start + round(slope * (input - input_start));
}

int main(void)
{
    // B Bank initialiseren.
    DDRB  = (1 << PB5);

    // Initialiseer de potential meter.
    initADC();

    // Loop voor altijd.
    while (1)
    {
        // Lees de waarde van de potential meter uit.
        uint16_t pwm = readADC();

        // Zet de B pin aan.
        PORTB = (1 << PB5);

        // Bereken de delay.
        double mapped = map(pwm, 1, 1024, 10000, 100) / 2;

        // Wacht voor een X aantal µs.
        delay(mapped);

        // Zet de B pin uit.
        PORTB = 0;

        // Wacht voor een X aantal µs.
        delay(mapped);
    }

    return 0;
}
