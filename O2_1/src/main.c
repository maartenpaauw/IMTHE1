/*
 * Opdracht 2.1 - Count Me In
 * 
 * Maarten Paauw <s1094220@student.hsleiden.nl>
 * s1094220
 * INF3C
 */

/*
 * RIGHT DIGIT
 *
 * PD2 = A
 * PD3 = B
 * PD4 = C
 * PD5 = D
 * 
 * PC0 = E
 * PC1 = F
 * PC2 = G
 */

#include <avr/io.h>
#include <util/delay.h>

// Regel de C pinnen.
void handleC (int number) {
    PORTC =~ ((number << 1) >> 5);
}

// Regel de D pinnen.
void handleD (int number) {
    PORTD =~ ((number << 4) >> 2);
}

int main(void)
{
    // Segmenten als binair getal voor de cijfers 0 t/m 9.
    int numbers[10] = {
        // GFEDCBA
        0b00111111, // 0
        0b00000110, // 1
        0b01011011, // 2
        0b01001111, // 3
        0b01100110, // 4
        0b01101101, // 5
        0b01111101, // 6
        0b00000111, // 7
        0b01111111, // 8
        0b01101111  // 9
    };

    // Count
    int a = 0;

    // Zet alle C pinnen op output.
    DDRC = 0xFF;

    // Zet alle D pinnen op output.
    DDRD = 0xFF;

    while (1)
    {
        // Regel de C pinnen.
        handleC(numbers[a % 10]);

        // Regel de D pinnen.
        handleD(numbers[a % 10]);

        // Wacht 1 seconden.
        _delay_ms(1000);

        // Tel de A op.
        a++;
    }

    return 0;
}
