/*
 * Opdracht 4.3 - Led There Be Light
 * 
 * Maarten Paauw <s1094220@student.hsleiden.nl>
 * s1094220
 * INF3C
 */

// Baud rate.
#define BAUD 9600

#include <avr/io.h>
#include <util/setbaud.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// Uit het bestand USART.
void initUSART(void)
{
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;
    #if USE_2X
        UCSR0A |= (1 << U2X0);
    #else
        UCSR0A &= ~(1 << U2X0);
    #endif
        UCSR0B = (1 << TXEN0) | (1 << RXEN0);
        UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

// Uit het bestand USART.
uint8_t receiveByte(void)
{
    loop_until_bit_is_set(UCSR0A, RXC0);
    return UDR0;
}

// Uit het bestand USART.
void transmitByte(uint8_t data)
{
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = data;
}

// Uit het bestand USART.
void printString(const char myString[])
{
    uint8_t i = 0;
    while (myString[i])
    {
        transmitByte(myString[i]);
        i++;
    }
}

void initTimerOverflow()
{
    // Timer mask.
    TIMSK0 |= (1 << TOIE0);

    // Timer instellingen.
    TCCR0B |= (1 << CS02) | (1 << CS00);
    sei();
}

void intPWMTimerLED()
{
    // Timer 1 (Voor rood en groen).
    TCCR1A |= (1 << WGM10) | (1 << WGM12); // Fast PWM.
    TCCR1B |= (1 << CS11);                 // PWM freq.

    // Timer 2 (Voor blauw).
    TCCR2A |= (1 << WGM20) | (1 << WGM21); // Fast PWM.
    TCCR2B |= (1 << CS21);                 // PWM freq.

    // Rode en groene led.
    TCCR1A |= (1 << COM1A1) | (1 << COM1B1);

    // Blauwe led.
    TCCR2A |= (1 << COM2A1);
}

// LED pinnen.
#define LED_RED PB1
#define LED_GREEN PB2
#define LED_BLUE PB3

// Count.
int count = 0;

// Valiabele voor de kleur code.
char color;

// Als er geschreven wordt naar de seriele verbinding.
ISR (USART_RX_vect)
{
    // Verkrijg de kleur vanuit de serial.
    color = UDR0;

    // Kijk welke kleur het is.
    switch (color)
    {
    // Als het rood is.
    case 'r':
        printString("De kleur wordt rood.\n");
        break;
    
    // Als het groen is.
    case 'g':
        printString("De kleur wordt groen.\n");
        break;

    // Als het blauw is.
    case 'b':
        printString("De kleur wordt blauw.\n");
        break;

    // De standaard switch case.
    default:
        printString("Toets R, G of B in.\n");
        break;
    }
}

// Main methode.
int main(void)
{
    // Initialiseer de RGB LED pinnen.
    DDRB = (1 << LED_RED) | (1 << LED_GREEN) | (1 << LED_BLUE);

    // Initialiseer de USART.
    initUSART();

    // Initialiseer de overflow timer.
    initTimerOverflow();

    // Initialiseer de led timer.
    intPWMTimerLED();

    // Loop voor altijd.
    while (1)
    {
    }

    // Geef niets terug.
    return 0;
}
