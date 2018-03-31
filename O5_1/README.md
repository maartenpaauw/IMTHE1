# Opdracht 5.1

> ET Phone Home

Deze opdracht bestaat uit twee kleinere opdrachten:

1. **Elke IMTHE-Box bevat unieke componenten. Zoek naar de datasheets van deze componenten en maak een kort verslag per component over de protocollen die gebruikt worden en hoe je dit moet gebruiken vanuit de AVR code.**
2. Zoek naar een library op internet om het HD44780 display te kunnen besturen en maak een programma dat jouw naam en studentnummer op het display laat zien.

## De unieke componenten

In de IMTHE-Box zitten 2 unieke componenten. Één uniek input component en één uniek output component. De componenten die in mijn IMTHE-Box zitten zijn één **DHT11**, dit is een temperatuur en luchtvochtigheid sensor, en twee **LED 8×8 Matrix**.

### DHT11

De DHT11 is een temperatuur en luchtvochtigheid sensor. De DHT11 meet de  temperatuur en luchtvochtigheid van de nabijne lucht en vertaald het naar een digitaal signaal. De sensor is nauwkeurig gekalibreerd in een labratorium en deze kalibratie wordt opgeslagen op het component zelf. Er zijn geen analoge pinnen nodig om het signaal uit te lezen. Alle data van de sensor wordt verzonden over één digitale pin. Het beste is om de bedrading tussen de DHT11 en de AVR korter te houden dan 20 meter. Ook wordt er aangeraden om de DHT11 op 5 volt aan te sluiten.

Het enigste nadeel van de DHT11 is dat de sensor maar 1 keer per 2 seconden de omliggende lucht meet.

#### Protocol (Single-Wire Two-Way)

De protocol waarvan gebruik wordt gemaakt is interessant. Alle sensor data wordt verstuurd over 1 digitale pin. Om data te kunnen versturen (vanaf de sensor) moet er worden aangegeven om welke data het gaat zodat de ontvanger en de verzender weten waar er over gecommuniceerd wordt. Dit wordt gedaan door een zogenaamde *pull-up*. Als de data pin verbonden is met de *VCC* pin (door middel van een resistor) wordt er geen data verstuurd (uitgelezen).

*Bij het programmeren van de Arduino moet er rekening gehouden worden dat er eerst 1 seconden gewacht moet worden voordat er contact gemaakt kan worden met de DHT11. De DHT11 heeft 1 seconden nodig voor het opstarten.*

Er zijn 3 stappen die gemaakt moeten worden om de data uit te lezen van de DHT11. De stappen zijn hieronder opgenomen.

##### Request

Om er voor te zorgen dat de DHT11 data gaat versturen moet er eerst een ***request*** gemaakt worden. Dit wordt gedaan door eerst een ***pull-down***, langer dan 1**8 milliseconden**, te versturen en daarna een ***pull-up*** van **40 microseconden** te versturen. Vervolgens wordt er een response verstuurd.

##### Response

De DHT11 stuurt een ***response*** terug nadat er een ***request*** gemaakt is. De ***reponse*** bestaat uit een ***low pin*** van **54 microseconden** en een ***high pin*** van **80 microseconden**.

##### Data Reading

Nadat er een ***response*** is gegeven volgt direct de data. De data wordt verstuurd in **5 pakketen**. Ieder van **8-bit**. In totaal zijn die **40-bits**. Hieronder is per **8-bit** uitgelegd wat de data betekent:

- Integraal van de luchtvochtigheid.
- Decimaal van de luchtvochtigheid .
- Integraal van de temperatuur (in celsius).
- Decimaal van de temperatuur (in celsius) .
- Checksum over de 4 vorige waardes.

Elke bit wordt via de volgende manier gecommuniceerd; eerst wordt de **pin** op **low** gezet voor **54 microseconden**. Vervolgens wordt de **pin** op high **gezet** voor **24 microseconden** als het **0** is en **70 microseconden** als het **1** is. Aan het einde van 8 bit wordt er vervolgens de **pin** op **low** gezet voor **54 microseconden**.

*Alle informatie heb ik gewonnen uit de datasheet van het component:*

*[https://akizukidenshi.com/download/ds/aosong/DHT11.pdf][1]*

### 8×8 Matrix

De 8×8 Matrix is een component waar 64 leds in zitten. Deze 64 leds zijn gerankschikt in 8 rijen van 8. Dit vormt samen een vierkant. Alle pinnen van de leds zijn verbonden met 8 rij pinnen en 8 kolom pinnen. Een combinatie van één rij en één kolom pin zorgt voor het aan gaan van één led. Over de 8×8 matrix valt minder te vertellen vergeleken met de DHT11 component met betrekking tot het programmeren. De volgorde van de pinnen kan alleen een beetje verwarrend zijn. De pinnen lopen in de vorm van de letter U 90 graden gedraaid tegen de klok in. De pin linksonder is pin 1 en de pin linksboven is pin 16. De pinnen zelf staan niet op vorgorde van de rijen en kolommen. Welke pin voor welke rij of kolom is kan terug gevonden worden in de afbeelding van de pinout.

*Bij het aansluiten moet er wel rekening gehouden worden dat er bij elke pin van de rijen of bij elke pin van de kolommen er een resistor aangesloten moet worden. Het component zelf heeft deze niet ingebouwd.*

*Alle informatie heb ik gewonnen uit de datasheet van het component:*

*[https://cdn-shop.adafruit.com/datasheets/BL-M12A881.PDF][2]*

### Hardware

De compontenten die ik heb zijn hieronder opgenomen in de tabel.

| Onderdelen               |
| ------------------------ |
| DHT11(input) - 1×        |
| 8×8 Matrix (output) - 2× |

## Datasheets

### DHT11

![DHT11 Pinout](https://raw.githubusercontent.com/maartenpaauw/IMTHE1/master/O5_1/assets/data_sheets/dht11.png)

De [DHT11 Pinout](https://raw.githubusercontent.com/maartenpaauw/IMTHE1/master/O5_1/assets/data_sheets/dht11.png) is te vinden in de datasheet. Deze datasheet heb ik via Google gevonden en is terug te vinden via de volgende link:

[https://akizukidenshi.com/download/ds/aosong/DHT11.pdf][1]

### 8×8 Matrix

![8×8 Matrix Pinout](https://raw.githubusercontent.com/maartenpaauw/IMTHE1/master/O5_1/assets/data_sheets/8x8_matrix.png)

De [8×8 Matrix Pinout](https://raw.githubusercontent.com/maartenpaauw/IMTHE1/master/O5_1/assets/data_sheets/8x8_matrix.png) heb ik uit de datasheet van de 8×8 Matrix. De datasheet is terug te vinden via de volgende link:

[https://cdn-shop.adafruit.com/datasheets/BL-M07C881.PDF][2]

## Bronvermelding

* [https://akizukidenshi.com/download/ds/aosong/DHT11.pdf][1] (DHT11 Datasheet)
* [https://cdn-shop.adafruit.com/datasheets/BL-M07C881.PDF][2] (8×8 Matrix Datasheet)

[1]: https://akizukidenshi.com/download/ds/aosong/DHT11.pdf "DHT11 Datasheet"
[2]: https://cdn-shop.adafruit.com/datasheets/BL-M07C881.PDF "8×8 Matrix Datasheet"
