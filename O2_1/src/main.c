/*
 * Opdracht 2.1 - Count Me In
 * 
 * Eigenaar:
 * Maarten Paauw <s1094220@student.hsleiden.nl>
 * s1094220
 * INF3C
 * 
 * Versie: 1
 * Aangemaakt: 15 februari 2018
 * Gewijzigd: 27 maart 2018
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

// Regel de C pinnen.
void handleC(int number)
{
    // 0b00111111
    // 0b01111110
    // 0b00000011 <- uitkomst voor 0.
    PORTC = ~((number << 1) >> 5);
}

// Regel de D pinnen.
void handleD(int number)
{
    // 0b00111111
    // 0b11110000
    // 0b00111100 <- uitkomst voor 0.
    PORTD = ~((number << 4) >> 2);
}

// De main functie.
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

    // Zet de C pinnen op output.
    DDRC = 0b00111111;

    // Zet de D pinnen op output.
    DDRD = 0b00111100;

    // Loop voor altijd.
    while (1)
    {
        // Rechter digit.
        int right = numbers[a % 10];

        // Regel de C pinnen.
        handleC(right);

        // Regel de D pinnen.
        handleD(right);

        // Wacht 1 seconden.
        _delay_ms(1000);

        // Tel de A op.
        a++;

        // Als het getal groter is dan 9.
        if (a > 9)
        {
            // Reset de count.
            a = 0;
        }
    }

    // Geef 0 terug.
    return 0;
}
