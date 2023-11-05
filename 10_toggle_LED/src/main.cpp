/*AVR-LV
dejan.rakijasic@gmail.com

Zadatak: toogle primjer
Promjena stanja LED na PB3 svake sekunde
*/
#include <Arduino.h>
#define LED 3
void setup()
{
  DDRB |= (1 << LED);
}

void loop()
{
  // PORTB ^= (1 << LED);
  PINB |= (1 << LED);
  delay(1000);
}