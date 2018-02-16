/*
 * Opdracht 2.2 - Count Me In
 * 
 * Maarten Paauw <s1094220@student.hsleiden.nl>
 * s1094220
 * INF3C
 */

/*
 * LEFT DIGIT
 *
 * PB0 = A = 16
 * PB1 = B = 15
 * PB2 = C = 3
 * PB3 = D = 2
 * 
 * PC3 = E = 1
 * PC4 = F = 18
 * PC5 = G = 17
 */

/*
 * RIGHT DIGIT
 *
 * PD2 = A = 11
 * PD3 = B = 10
 * PD4 = C = 8
 * PD5 = D = 6
 * 
 * PC0 = E = 5
 * PC1 = F = 12
 * PC2 = G = 7
 */

#include <avr/io.h>
#include <util/delay.h>


// Regel de B pinnen.
void handleB (int right) {
    // 0b00111111
    // 0b11110000
    // 0b00001111 <- uitkomst voor 0.
    PORTB =~ ((right << 4) >> 4);
}

// Regel de C pinnen.
void handleC (int left, int right) {
    // Left
    // 0b00111111
    // 0b01111110
    // 0b00011000 <- uitkomst voor de linker 0.
    //
    // Right
    // 0b00111111
    // 0b01111110
    // 0b00000011 <- uitkomst voor de rechter 0.
    //
    // 0b00011000
    // 0b00000011 |
    // ----------
    // 0b00011011 <- uitkomst voor 0.
    PORTC =~ ((((left << 1) >> 5) << 3) | ((right << 1) >> 5));
}

// Regel de D pinnen.
void handleD (int left) {
    // 0b00111111
    // 0b11110000
    // 0b00111100 <- uitkomst voor 0.
    PORTD =~ ((left << 4) >> 2);
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

    // Zet de B pinnen op output.
    DDRB = 0b00001111;

    // Zet de C pinnen op output.
    DDRC = 0b00111111;

    // Zet de D pinnen op output.
    DDRD = 0b00111100;

    while (1)
    {
        int left  = numbers[a / 10];
        int right = numbers[a % 10];

        // Regel de B pinnen.
        handleB(left);

        // Regel de C pinnen.
        handleC(left, right);

        // Regel de D pinnen.
        handleD(right);

        // Wacht 1 seconden.
        _delay_ms(1000);

        // Tel de A op.
        a++;

        // Reset de count.
        if (a > 99) {
            a = 0;
        }
    }

    return 0;
}
