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

// USART wordt gebruikt voor het debuggen van de sensor data.
#include <USART.h>

// De pin waar de DHT11 data over verstuurd wordt.
#define DHT11_PIN PD6

// De bank waar de DHT11 data over verstuurd wordt.
#define DHT11_BANK DDRD

// De port waar de DHT11 data over verstuurd wordt.
#define DHT11_PORT PORTD

// Variabele om tijdelijk de data (enkele bit) van de sensor op te slaan.
uint8_t c = 0;

// Variabele om de integraal van de luchtvochtigheid op te slaan.
uint8_t integral_humidity;

// Variabele om de decimaal van de luchtvochtigheid op te slaan.
uint8_t decimal_humidity;

// Variabele om de integraal van de temperatuur (in celcius) op te slaan.
uint8_t integral_temperature;

// Variabele om de decimaal van de temperatuur (in celcius) op te slaan.
uint8_t decimal_temperature;

// Variabele om de checkcum over de 4 eerder genoemde data op te slaan.
uint8_t checksum;

// Initialiseer de DHT11 sensor.
void init_DHT11()
{
    // In de datasheet is er uitgelegd dat de DHT11 sensor 1 seconde nodig 
    // heeft met opstarten. Daarom even een delay van 1 seconde.
    _delay_ms(1000);
}

// Delay in miliseconden hoe lang de DHT11 sensor wacht voor het meten van
// nieuwe data. Deze tijd komt uit de datasheet.
void DHT11_measure_time()
{
    // Wacht 2 seconden.
    _delay_ms(2000);
}

// Wacht net zolang dat de DHT11 pin clear is.
void loop_until_dht_is_clear()
{
    // Wacht net zolang dat de DHT11 pin clear is.
    loop_until_bit_is_clear(PIND, DHT11_PIN);
}

// Wacht net zolang dat de DHT11 pin geset is.
void loop_until_dht_is_set()
{
    // Wacht net zolang dat de DHT11 pin geset is.
    loop_until_bit_is_set(PIND, DHT11_PIN);
}

// Functie om de request uit te voeren richting de DHT11 sensor.
void request()
{
    // Geef aan dat de DHT11 pin op de D bank gebruikt gaat worden.
    DHT11_BANK |= (1 << DHT11_PIN);

    // Zet de DHT11 pin op 0. Dit heb ik in mijn vorige verslag beschreven als
    // een "pull-down".
    DHT11_PORT &= ~(1 << DHT11_PIN);

    // De Pull Down moet minimaal 18 miliseconden plaats vinden.
    _delay_ms(18);

    // Zet de DHT11 pin op 1. Dit heb ik in mijn vorige verslag beschreven als
    // een "pull-up".
    DHT11_PORT |= (1 << DHT11_PIN);

    // De Pull Up moet exact 40 microseconden plaats vinden.
    _delay_us(40);
}

// Functie die de (automatische) response van de DHT11 sensor afhandelt.
void response()
{
    // Zet de DHT11 pin op 0. Nu kan de DHT11 sensor zijn response geven.
    DHT11_BANK &= ~(1 << DHT11_PIN);

    // Loop net zolang dat de DHT11 pin clear is.
    loop_until_dht_is_clear();

    // Loop net zolang dat de DHT11 pin geset is.
    // Dit is de 54 microseconden die ik in de uitleg aangeef.
    loop_until_bit_is_set(PIND, DHT11_PIN);

    // Loop net zolang dat de DHT11 pin clear is.
    // Dit is de 80 microseconden die ik in de uitleg aangeef.
    loop_until_dht_is_clear();
}

// Verkrijg de 8-bit data van de sensor.
uint8_t receive_data()
{
    // Elk stuk data bestaat uit 8-bit. Daarom wordt er 8x een bit uitgelezen.
    for (int q = 0; q < 8; q++)
    {
        // Loop net zolang dat de DHT11 pin clear is.
        // Dit is de 54 microseconden de ik in de uitleg aangeef.
        loop_until_dht_is_clear();

        // Loop net zolang dat de DHT11 pin geset is.
        loop_until_bit_is_set(PIND, DHT11_PIN);

        // Als de bit 0 moet zijn wordt er voor 24 microseconden gewacht.
        // Als de bit 1 moet zijn wordt er voor 70 microseconden gewacht.
        // Ik wil precies op de helft van de tijd tussen low en high wachten.
        // Op dat moment kan je uitlezen of de pin high of low staat.
        _delay_us((24 + 70) / 2);

        // Kijk of de DHT11 pin op high staat wordt er een 1 bedoelt als bit.
        if (PIND & (1 << DHT11_PIN))
        {
            // Schuif de vorige waarde 1 plek naar links en sla een nieuwe 1 op
            // in het binaire getal.
            c = (c << 1) | (0x01);
        }

        // Als de pin op low staat wordt er een 0 bedoelt als bit.
        else
        {
            // Schuif de vorige waarde 1 plek naar links. Automatisch wordt er 
            // aan de rechter kant een nul toegevoegd.
            c = (c << 1);
        }
        
        // Loop net zolang dat de DHT11 op hoog staat.
        // Dit is de 54 microseconden de ik in de uitleg aangeef.
        loop_until_dht_is_clear();
    }

    // Geef het binaire getal terug.
    return c;
}

// Sla alle data uit de sensor uit.
void save_data()
{
    // Sla de integraal van de luchtvochtigheid op.
    integral_humidity = receive_data();

    // Sla de decimaal van de luchtvochtigheid op.
    decimal_humidity = receive_data();
    
    // Sla de integraal van de temperatuur op.
    integral_temperature = receive_data();
    
    // Sla de decimaal van de temperatuur op.
    decimal_temperature = receive_data();

    // Sla de checksum op.
    checksum = receive_data();
}

// Valideer de sensor data door middel van de checksum.
uint8_t validate_sensor_data()
{
    // Tel de luchtvochtigheid en de temeratuur bij elkaar op.
    uint8_t combined = integral_humidity + decimal_humidity + integral_temperature + decimal_temperature;

    // Geef terug dat de data klopt.
    return combined == checksum;
}

// De main functie.
int main(void)
{
    // placeholder voor de data voor het printen.
    char data[5];

    // Initialiseer de seriele verbinding voor het schrijven.
    initUSART();

    // Initialiseer de DHT11 sensor.
    init_DHT11();

    // Loop voor altijd.
    while (1)
    {
        // Geef aan de DHT11 sensor door dat je een request wilt gaan doen.
        request();

        // Handel de (automatische) response van de DHT11 sensor af.
        response();

        // Sla de data van de sensor op in variabelen.
        save_data();

        // Controleer of de DHT sensor data valide is.
        if (validate_sensor_data())
        {
            itoa(integral_humidity, data, 10);
            printString(data);
            printString(".");

            itoa(decimal_humidity, data, 10);
            printString(data);
            printString("%");

            printString(" ");

            itoa(integral_temperature, data, 10);
            printString(data);
            printString(".");

            itoa(decimal_temperature, data, 10);
            printString(data);
            printString("°");
            printString("C");

            printString("\n");
        }

        // Als de checksum niet correct is. Bij het versturen van foutieve gegevens.
        else { }

        // Wacht net zolang totdat de DHT11 weer nieuwe data gaat meten.
        DHT11_measure_time();
    }
}
