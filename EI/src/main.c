/*
 * Eindopdracht - Show Your Moves
 * 
 * Eigenaar:
 * Maarten Paauw <s1094220@student.hsleiden.nl>
 * s1094220
 * INF3C
 * 
 * Versie: 1
 * Aangemaakt: 22 maart 2018
 * Gewijzigd: 29 maart 2018
 */

#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>
#include <util/delay.h>

#include <USART.h>

// De pin waar de DHT11 data over verstuurd wordt.
#define DHT11_PIN PD6
#define DHT11_BANK DDRD

uint8_t c = 0, I_RH, D_RH, I_Temp, D_Temp, CheckSum;

void Request()
{
    DHT11_BANK |= (1 << DHT11_PIN);
    PORTD &= ~(1 << DHT11_PIN);
    _delay_ms(20);
    PORTD |= (1 << DHT11_PIN);
}

void Response()
{
    DDRD &= ~(1 << DHT11_PIN);
    while (PIND & (1 << DHT11_PIN));
    while ((PIND & (1 << DHT11_PIN)) == 0);
    while (PIND & (1 << DHT11_PIN));
}

uint8_t Receive_data()
{
    for (int q = 0; q < 8; q++)
    {
        while ((PIND & (1 << DHT11_PIN)) == 0);
        
        _delay_us(30);
        
        if (PIND & (1 << DHT11_PIN))
        {
            c = (c << 1) | (0x01);
        }
        
        else
        {
            c = (c << 1);
        }
        
        while (PIND & (1 << DHT11_PIN));
    }
    return c;
}

int main(void)
{
    char data[5];

    initUSART();

    _delay_ms(100);

    while (1)
    {
        Request();
        Response();
        I_RH = Receive_data();
        D_RH = Receive_data();
        I_Temp = Receive_data();
        D_Temp = Receive_data();
        CheckSum = Receive_data();

        if ((I_RH + D_RH + I_Temp + D_Temp) != CheckSum)
        {
            printString("Error");
        }

        else
        {
            itoa(I_RH, data, 10);
            printString(data);
            printString(".");

            itoa(D_RH, data, 10);
            printString(data);
            printString("%");

            itoa(I_Temp, data, 10);
            printString(data);
            printString(".");

            itoa(D_Temp, data, 10);
            printString(data);
            printString("°");
            printString("C ");

            itoa(CheckSum, data, 10);
            printString(data);
            printString(" ");

            printString("\n");
        }

        _delay_ms(500);
    }
}