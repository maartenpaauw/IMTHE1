/*
 * Opdracht Opdracht 5.2 - ET Phone Home
 * 
 * Maarten Paauw <s1094220@student.hsleiden.nl>
 * s1094220
 * INF3C
 */
#include "hd44780.h"

// Mijn naam.
#define NAAM "Maarten Paauw"

// Mijn studentnummer.
#define STUDENTNUMMER "s1094220"

// De main functie.
int main(void)
{
    // Initialiseer het LCD display.
    lcd_init();

    // Maak het LCD display leeg.
    lcd_clrscr();
    
    // Schrijf mijn naam op de eerste regel.
    lcd_puts(NAAM);

    // Ga naar de tweede regel.
    lcd_goto(0x40);

    // Schrijf mijn studentnummer op de tweede regel.
    lcd_puts(STUDENTNUMMER);

    // Loop voor altijd.
    while (1) { }

    // Geef 0 terug.
    return 0;
}
