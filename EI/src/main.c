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
 * Gewijzigd: 30 maart 2018
 */

#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// USART wordt gebruikt voor het debuggen van de sensor data.
#include <USART.h>

// De pin waar de DHT11 data over verstuurd wordt.
#define DHT11_PIN PD6

// De bank waar de DHT11 data over verstuurd wordt.
#define DHT11_BANK DDRD

// De port waar de DHT11 data over verstuurd wordt.
#define DHT11_PORT PORTD

// De bank waar de 8x8 matrix pinnen op aangesloten zitten.
#define MATRIX_BANK DDRC

// De port waar de 8x8 matrix pinnen op aangesloten zitten.
#define MATRIX_PORT PORTC

// De port en pin voor de SER pin op de shift register.
#define SER_PIN PC0

// De port en pin voor de RCLK pin op de shift register.
#define RCLK_PIN PC1

// De port en pin voor de SRCLK pin op de shift register.
#define SRCLK_PIN PC2

int count = 0;

// Variabele om tijdelijk de data (enkele bit) van de sensor op te slaan.
uint8_t temporarily = 0;

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
    // Wacht 1 seconden.
    _delay_ms(1000);
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
    // een "pull down".
    DHT11_PORT &= ~(1 << DHT11_PIN);

    // De "pull down" moet minimaal 18 miliseconden plaats vinden.
    // Ik hou het bij de minimale "pull down" tijd.
    _delay_ms(18);

    // Zet de DHT11 pin op 1. Dit heb ik in mijn vorige verslag beschreven als
    // een "pull up".
    DHT11_PORT |= (1 << DHT11_PIN);

    // De "pull up" moet exact 40 microseconden plaats vinden.
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
            temporarily = (temporarily << 1) | (0x01);
        }

        // Als de pin op low staat wordt er een 0 bedoelt als bit.
        else
        {
            // Schuif de vorige waarde 1 plek naar links. Automatisch wordt er
            // aan de rechter kant een nul toegevoegd.
            temporarily = (temporarily << 1);
        }

        // Loop net zolang dat de DHT11 op hoog staat.
        // Dit is de 54 microseconden de ik in de uitleg aangeef.
        loop_until_dht_is_clear();
    }

    // Geef het binaire getal terug.
    return temporarily;
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
    uint8_t combined = integral_humidity +
                       decimal_humidity +
                       integral_temperature +
                       decimal_temperature;

    // Geef terug dat de data klopt.
    return combined == checksum;
}

// Print de sensor data uit.
void debug(int sensor_data, char extra_string[])
{
    // placeholder voor de data voor het printen.
    char data[5];

    // Formateer de integer naar een string.
    itoa(sensor_data, data, 10);

    // Toon de sensor data.
    printString(data);

    // Voeg de extra string toe.
    printString(extra_string);
}

// Initialiseer de 8x8 matrix.
void init_8x8_matrix()
{
    // Defineer de pinnen die nodig zijn.
    MATRIX_BANK = (1 << SER_PIN) | (1 << RCLK_PIN) | (1 << SRCLK_PIN);

    // Zet alle C pinnen op low.
    MATRIX_PORT = 0b00000000;
}

// Zet te serial pin laag.
void ser_pin_low()
{
    // Zet te serial pin laag.
    MATRIX_PORT &= ~(1 << SER_PIN);
}

// Zet te serial pin hoog.
void ser_pin_high()
{
    // Zet te serial pin hoog.
    MATRIX_PORT |= (1 << SER_PIN);
}

// Zet te rclk pin laag.
void rclk_pin_low()
{
    // Zet te rclk pin laag.
    MATRIX_PORT &= ~(1 << RCLK_PIN);
}

// Zet te rclk pin hoog.
void rclk_pin_high()
{
    // Zet te rclk pin hoog.
    MATRIX_PORT |= (1 << RCLK_PIN);
}

// Zet te srclk pin laag.
void srclk_pin_low()
{
    // Zet te srclk pin laag.
    MATRIX_PORT &= ~(1 << SRCLK_PIN);
}

// Zet te srclk pin hoog.
void srclk_pin_high()
{
    // Zet te srclk pin hoog.
    MATRIX_PORT |= (1 << SRCLK_PIN);
}

// Zet iets op het display.
void turn_on_dot (int row, int column)
{
    // Zet de srclk pin op laag.
    srclk_pin_low();

    // Zet de rclk pin op laag.
    rclk_pin_low();

    int real_row = row - 1;
    int real_column = column - 1;

    // Loop door 8 bits heen
    for (int i = 0; i < 8; i++) 
    {
        // Controleer of de bit hoog moet zijn
        if (i == real_row)
        {
            // Zet de SER pin op hoog.
            ser_pin_high();
        }

        // Zo niet;
        else
        {
            // Zet de SER pin op laag.
            ser_pin_low();
        }

        // Zet de RCLK pin op hoog.
        srclk_pin_high();

        // Zet de RCLK pin op laag.
        srclk_pin_low();
    }

    // Loop door 8 bits heen
    for (int i = 0; i < 8; i++) 
    {
        // Controleer of de bit hoog moet zijn
        if (i == real_column)
        {
            // Zet de SER pin op hoog.
            ser_pin_low();
        }

        // Zo niet;
        else
        {
            // Zet de SER pin op laag.
            ser_pin_high();
        }

        // Zet de RCLK pin op hoog.
        srclk_pin_high();

        // Zet de RCLK pin op laag.
        srclk_pin_low();
    }

    // Zet de srclk pin op hoog.
    rclk_pin_high();
}

// Show sad smiley.
void matrix_smiley_sad()
{
    // Rijen en kolommen die aan moeten voor het tonen van een zielig gezicht.
    uint8_t dots [30][2] = {
        {1, 2},
        {1, 3},
        {1, 4},
        {1, 5},
        {1, 6},
        {1, 7},
        {2, 1},
        {2, 8},
        {3, 1},
        {3, 3},
        {3, 6},
        {3, 8},
        {4, 1},
        {4, 8},
        {5, 1},
        {5, 4},
        {5, 5},
        {5, 8},
        {6, 1},
        {6, 3},
        {6, 6},
        {6, 8},
        {7, 1},
        {7, 8},
        {8, 2},
        {8, 3},
        {8, 4},
        {8, 5},
        {8, 6},
        {8, 7},
    };

    // Loop 30 keer (zoveel leds zijn er nodig).
    for (int i = 0; i < 30; i++)
    {
        // Zet de specifieke led aan.
        turn_on_dot(dots[i][0], dots[i][1]);

        // Laat de led heel even aan staan.
        _delay_us(100);
    }
}

// Show happy smiley.
void matrix_smiley_happy()
{
    // Rijen en kolommen die aan moeten voor het tonen van een blij gezicht.
    uint8_t dots [30][2] = {
        {1, 2},
        {1, 3},
        {1, 4},
        {1, 5},
        {1, 6},
        {1, 7},
        {2, 1},
        {2, 8},
        {3, 1},
        {3, 3},
        {3, 6},
        {3, 8},
        {4, 1},
        {4, 8},
        {5, 1},
        {5, 3},
        {5, 6},
        {5, 8},
        {6, 1},
        {6, 4},
        {6, 5},
        {6, 8},
        {7, 1},
        {7, 8},
        {8, 2},
        {8, 3},
        {8, 4},
        {8, 5},
        {8, 6},
        {8, 7},
    };

    // Loop 30 keer (zoveel leds zijn er nodig).
    for (int i = 0; i < 30; i++)
    {
        // Zet de specifieke led aan.
        turn_on_dot(dots[i][0], dots[i][1]);

        // Laat de led heel even aan staan.
        _delay_us(100);
    }
}

// Timer overflow interrupt.
ISR (TIMER0_OVF_vect)
{
    if (count > 65)
    {
        count = 0;

        // Geef aan de DHT11 sensor door dat je een request wilt gaan doen.
        request();

        // Handel de (automatische) response van de DHT11 sensor af.
        response();

        // Sla de data van de sensor op in variabelen.
        save_data();

        // Controleer of de DHT sensor data valide is.
        if (validate_sensor_data())
        {
            // Print een titel.
            printString("Luchtvochtigheid: ");

            // Print de luchtvochtigheid.
            debug(integral_humidity, ".");
            debug(decimal_humidity, "%");

            // Print een enter.
            printString("\n");

            // Print een titel.
            printString("Temperatuur: ");

            // Print de temperatuur.
            debug(integral_temperature, ".");
            debug(decimal_temperature, "°C");

            // Print twee enters.
            printString("\n\n");
        }

        // Wacht net zolang totdat de DHT11 weer nieuwe data gaat meten.
        // DHT11_measure_time();
    }

    else
    {
        count++;
    }
}

// Functie on de matrix te bedienen.
ISR (TIMER1_OVF_vect)
{
    // Bereken de temperatuur.
    if (integral_temperature > 21)
    {
        // Blije smiley.
        matrix_smiley_happy();
    }

    else
    {
        // Verdrietige smiley.
        matrix_smiley_sad();
    }
}

// Overflow timer.
void init_timer_overflow()
{
    // Timer mask.
    TIMSK0 |= (1 << TOIE0);
    TIMSK1 |= (1 << TOIE1);

    // Timer 0 instellingen.
    TCCR0B |= (1 << CS00) | (1 << CS02);

    // Timer 1 instellingen.
    TCCR1B |= (1 << CS10);

    // Zet de interrupts aan.
    sei();
}

// De main functie.
int main(void)
{
    // Initialiseer de seriele verbinding voor het schrijven.
    initUSART();

    // Initialiseer de DHT11 sensor.
    init_DHT11();

    // Initialiseer de 8x8 matrix.
    init_8x8_matrix();

    // Initialiseer de overflow timer.
    init_timer_overflow();

    // Loop voor altijd.
    while (1) { }
}
