/*AVR-LV
dejan.rakijasic@gmail.com

Zadatak: digitalni ulazi
LED spojena na PB2 svijetli ako je pritisnuta tipka spojena na PD2.
*/

#include <Arduino.h>
#define LED 2   // PORTB -PB2 pin 10
#define tipka 2 // PORTD - PD2 pin 2

void setup()
{
  DDRB |= (1 << LED);    // OUTPUT
  DDRD &= ~(1 << tipka); // INPUT
  PORTD |= (1 << tipka); // PULL-UP
}

void loop()
{
  if ((PIND & (1 << tipka)) == 0) // ako je PD4 == 0
  {
    PORTB |= (1 << LED); // LED ON
  }
  else
  {
    PORTB &= ~(1 << LED); // LED OFF
  }
}