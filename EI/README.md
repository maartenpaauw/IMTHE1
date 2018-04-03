# Eindopdracht

> Show Your Moves

In opdracht 5 heb je jouw unieke IMTHE-Box componenten uitgezocht. Het doel van de eindopdracht is dat je iets unieks gaat maken met die componenten. Wat je gaat maken is aan jou, zolang het maar voldoet aan de volgende eisen:

* Je maakt correct gebruik van minimaal 1 uniek input en 1 uniek output component. Het staat je vrij om daarnaast elk ander onderdeel uit je IMTHE-Box te gebruiken in je oplossing.
* De afhandeling van je in- en output gebeurt asynchroon door bijvoorbeeld ISR toe te passen.
* Je maakt gebruik van de nauwkeurigheid van de gegeven componenten. Je probeert dus zoveel mogelijk uit je component te halen.

De eindopdracht wordt ook in het verslag opgenomen met alle eisen eraan die al genoemd zijn. Daarnaast geef je ook een beschrijving van het concept inclusief waar het toegepast zou kunnen worden en film je je uitwerking uitgebreid, waarin duidelijk wordt dat je de uitwerking getest hebt in verschillende situaties.

## Aanpak & Uitvoering

In opdracht [5.1](https://github.com/maartenpaauw/IMTHE1/blob/master/O5_1/README.md) heb ik al eerder beschreven hoe de 8×8 Matrix werkt en in opdracht [3.1](https://github.com/maartenpaauw/IMTHE1/blob/master/O3_1/README.md) heb ik de 8×8 Matrix al eerder toegepast. Ook heb ik al eerder in opdracht [5.1](https://github.com/maartenpaauw/IMTHE1/blob/master/O5_1/README.md) beschreven hoe de DHT11 sensor werkt. Het aansluiten en programmeren van de DHT11 sensor ligt na het uitzoeken en uitleggen voor de hand. Dit ga ik niet behandelen in dit hoofdstuk. Dit kan in de hoofdstukken teruggevonden worden van de eerder genoemde opdrachten.

### Extra Hardware

Om er voor te zorgen dat de 8×8 Matrix aangestuurd kan worden met zo min mogelijk pinnen van de Arduino zelf heb ik gebruik gemaakt van 2 shift registers. De eerste shift register regelt de rij pinnen van de 8×8 Matrix en de tweede shift register regels de kolommen van de 8×8 Matrix. Beide shift registers zitten aan elkaar gekoppelt. Zo zijn er maar 3 data kabels nodig om de shift registers te bedienen. Hoe de shift register werkt is vrij gemakkelijk. Door te timen met klokken en de data verstuur pin laag en hoog te zetten kunnen er bits in de shift register gestopt worden. Omdat ik er twee achter elkaar heb kunnen ze bij elkaar 16 bits onthouden en dus 16 pinnen hoog of laag zetten. Dit is precies genoeg voor de 8×8 Matrix. Hoe de shift registers aangesloten moeten worden is terug te vinden in het hoofdstuk **datasheets**.

### Het Concept

Het concept zelf is niet origineel maar wel effectief. Met mijn concept wordt er door de DHT11 sensor de temperatuur en de luchtvochtigheid in een ruimte / kamer gemeten. Deze waarde gaat door een formule heen. Deze formule kijkt of de luchtvochtigheid tussen de 40 en 60 procent is en de temperatuur tussen de 18 en de 22 graden is. Deze luchtvochtigheid en temperatuur zorgt voor een aangenaamde omgeving. Dit is vooral belangrijk als je, net zoals ik, astma hebt. Als deze omstandigheden goed zijn wordt er een blij gezichtje op de 8×8 Matrix getoond. Zo niet wordt er een verdrietig gezichtje op de 8×8 Matrix getoond. Als dit concept in een handzaam model in massa productie gebracht kan worden, het product ook draadloos wordt en het tegen een acceptabele prijs voor concumenten op de markt gebracht zou kunnen worden, is het in potentie een goed product. Mensen kunnen het dan in huis nemen en doorlopend de temperatuur en luchtvochtigheid meten. Bij een te hoge of een te lage waarde kunnen zij hun maatregelen nemen.

## Afbeelding

![Eindopdracht - Show Your Moves - Afbeelding](https://raw.githubusercontent.com/maartenpaauw/IMTHE1/master/EI/assets/setup.jpg)

De afbeelding van de setup kan ook gedownload worden via de volgende link:

[https://raw.githubusercontent.com/maartenpaauw/IMTHE1/master/EI/assets/setup.jpg](https://raw.githubusercontent.com/maartenpaauw/IMTHE1/master/EI/assets/setup.jpg)

## Video

[![Eindopdracht - Show Your Moves - Video](https://img.youtube.com/vi/Fws1fKBU__s/maxresdefault.jpg)](https://www.youtube.com/watch?v=Fws1fKBU__s)

Deze video is te vinden op **YouTube**:

[https://www.youtube.com/watch?v=Fws1fKBU__s](https://www.youtube.com/watch?v=Fws1fKBU__s)

De video kan ook gedownload worden via de volgende **Google Drive** link:

[https://drive.google.com/file/d/1I-y5v60qYhmbd6CQqKD0_loOBw4m0HeY/view?usp=sharing](https://drive.google.com/file/d/1I-y5v60qYhmbd6CQqKD0_loOBw4m0HeY/view?usp=sharing)

## Breadboard Schema

[![Eindopdracht - Show Your Moves - Schema](https://raw.githubusercontent.com/maartenpaauw/IMTHE1/master/EI/assets/fritzing/schema.png)](https://raw.githubusercontent.com/maartenpaauw/IMTHE1/master/EI/assets/fritzing/schema.png)

***LET OP:*** *Het programma **Fritzing** had geen DHT11 component. Daarom heb ik een component gepak dat het meest in de buurt komt. Op het component, dat in mijn IMTHE-Box zit, is een resistor van de data pin naar de 5v5 pin gesoldeerd. Deze resistor heb ik weggelaten in mijn Fritzing schema. Net als bij opdracht [3.1](https://github.com/maartenpaauw/IMTHE1/blob/master/O3_1/README.md) is er in het programma **Fritzing** geen kleine 8×8 Matrix te vinden. Ik heb daarom een grote gepakt en deze aangesloten op een appart breadboard zodat de pinnen van het component te verbinden zijn met de shift registers.*

Het **Fritzing** schema kan ook gedownload worden via de volgende link:

[https://github.com/maartenpaauw/IMTHE1/raw/master/EI/assets/fritzing/schema.fzz](https://github.com/maartenpaauw/IMTHE1/raw/master/EI/assets/fritzing/schema.fzz)

### Hardware

| Onderdelen               |
| ------------------------ |
| Arduino Nano (v3.0) - 1× |
| DHT11 - 1×               |
| SN74HC595 - 2×           |
| 220Ω Resistor - 8×       |
| 8×8 Matrix - 1×          |
| Dupont Kabel - 45×       |

## Code

```c
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
 * Gewijzigd: 31 maart 2018
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

// Count variabele
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

// De DHT11 sensor moet 1 seconden wachten voor het meten van
// nieuwe data. Deze tijd komt uit de datasheet.
int DHT11_measure_time()
{
    // (1000 / (16000000 / 1024)) * 1000 = 64;
    return 64;
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
        _delay_us(24 + (70 / 2));

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

    // Trek 1 van de rij af.
    int real_row = row - 1;

    // Trek 1 van de kolom af.
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

// Overflow timer.
void init_timer_overflow()
{
    // Timer mask 0.
    TIMSK0 |= (1 << TOIE0);

    // Timer mask 1.
    TIMSK1 |= (1 << TOIE1);

    // Timer 0 instellingen.
    TCCR0B |= (1 << CS00) | (1 << CS02);

    // Timer 1 instellingen.
    TCCR1B |= (1 << CS10);

    // Zet de interrupts aan.
    sei();
}

// Functie voor het controleren of er tussen 2 waardes in zit.
uint8_t between(int value, int min, int max)
{
    // Kijk of het tussen 2 waardes in ligt.
    return (value <= max && value >= min);
}

// Functie om te controleren of de temeratuur en de luchtvochtigheid perfect zijn.
uint8_t right_conditions ()
{
    // Geef het terug.
    return (between(integral_temperature, 18, 22) && between(integral_humidity, 40, 60));
}

// Timer overflow interrupt.
ISR (TIMER0_OVF_vect)
{
    // Willen maar 1 keer meten per 10 seconden.
    int count_check = DHT11_measure_time() * 10;

    // Is het tijd voor een nieuwe meting?
    if (count > count_check)
    {
        // Zet de count terug op 0.
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
    }

    // Zo niet;
    else
    {
        // Tel de count 1 op.
        count++;
    }
}

// Functie on de matrix te bedienen.
ISR (TIMER1_OVF_vect)
{
    // Bereken de temperatuur.
    if (right_conditions())
    {
        // Blije smiley.
        matrix_smiley_happy();
    }

    // Niet de juiste omstandigheden.
    else
    {
        // Verdrietige smiley.
        matrix_smiley_sad();
    }
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
```

De code kan ook gevonden worden in mijn **GitHub** *repository* via de volgende link:

[https://github.com/maartenpaauw/IMTHE1/blob/master/EI/src/main.c](https://github.com/maartenpaauw/IMTHE1/blob/master/EI/src/main.c)

## Datasheets

### Arduino Nano

![Arduino Nano Pinout](https://raw.githubusercontent.com/maartenpaauw/IMTHE1/master/EI/assets/data_sheets/nano.png)

De [Arduino Nano Pinout][1] is uitgedeeld tijdens de eerste les en terug te vinden via het volgende forum post:

[https://forum.arduino.cc/index.php?topic=147582.0][1]

### SN74HC595

![SN74HC595 Pinout](https://raw.githubusercontent.com/maartenpaauw/IMTHE1/master/EI/assets/data_sheets/sn74hc595.png)

De [SN74HC595 Pinout](https://raw.githubusercontent.com/maartenpaauw/IMTHE1/master/EI/assets/data_sheets/sn74hc595.png) heb ik uit de datasheet van de SN74HC595. De datasheet is terug te vinden via de volgende link:

[http://www.ti.com/lit/ds/symlink/sn74hc595.pdf][4]

### DHT11

![DHT11 Pinout](https://raw.githubusercontent.com/maartenpaauw/IMTHE1/master/EI/assets/data_sheets/dht11.png)

De [DHT11 Pinout](https://raw.githubusercontent.com/maartenpaauw/IMTHE1/master/EI/assets/data_sheets/dht11.png) is te vinden in de datasheet. Deze datasheet heb ik via Google gevonden en is terug te vinden via de volgende link:

[http://robocraft.ru/files/datasheet/DHT11.pdf][5]

### 8×8 Matrix

![8×8 Matrix Pinout](https://raw.githubusercontent.com/maartenpaauw/IMTHE1/master/EI/assets/data_sheets/8x8_matrix.png)

De [8×8 Matrix Pinout](https://raw.githubusercontent.com/maartenpaauw/IMTHE1/master/EI/assets/data_sheets/8x8_matrix.png) heb ik uit de datasheet van de 8×8 Matrix. De datasheet is terug te vinden via de volgende link:

[https://cdn-shop.adafruit.com/datasheets/BL-M07C881.PDF][6]

## Bronvermelding

* [https://forum.arduino.cc/index.php?topic=147582.0][1] (Arduino Nano Pinout)
* [https://protostack.com.au/2010/05/introduction-to-74hc595-shift-register-controlling-16-leds/][2] (Shift Register Controlling 16 Leds)
* [http://www.electronicwings.com/avr-atmega/dht11-sensor-interfacing-with-atmega16-32][3] (DHT11 Sensor Interfacing with AVR ATmega16/ATmega32)
* [http://www.ti.com/lit/ds/symlink/sn74hc595.pdf][4] (SN74HC595 Datasheet)
* [http://robocraft.ru/files/datasheet/DHT11.pdf][5] (DHT11 Datasheet)
* [https://cdn-shop.adafruit.com/datasheets/BL-M07C881.PDF][6] (8×8 Matrix Datasheet)

[1]: https://forum.arduino.cc/index.php?topic=147582.0 "Arduino Nano Pinout"
[2]: https://protostack.com.au/2010/05/introduction-to-74hc595-shift-register-controlling-16-leds/ "Shift Register Controlling 16 Leds"
[3]: http://www.electronicwings.com/avr-atmega/dht11-sensor-interfacing-with-atmega16-32 "DHT11 Sensor Interfacing with AVR ATmega16/ATmega32"
[4]: http://www.ti.com/lit/ds/symlink/sn74hc595.pdf "SN74HC595"
[5]: http://robocraft.ru/files/datasheet/DHT11.pdf "DHT11 Datasheet"
[6]: https://cdn-shop.adafruit.com/datasheets/BL-M07C881.PDF "8×8 Matrix Datasheet"
