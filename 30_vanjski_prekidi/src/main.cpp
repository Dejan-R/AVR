/*AVR-LV
dejan.rakijasic@gmail.com

Zadatak: primjer korištenja vanjskih prekida

LED je spojena na PB2 i mijenja stanje na svaki rastući brid signala dovedenog na PD2, koji generira prekid INT0.
*/

#include <Arduino.h>
#define LED 2     // PORTB
#define int_pin 2 // PORTD
void setup()
{
  DDRB |= (1 << LED);
  // PD2 (INT0 pin) - INPUT
  DDRD &= ~(1 << int_pin);
  // Pull-up na PD2
  PORTD |= (1 << int_pin);
  // EICRA – generiranje prekida na rastući brid
  EICRA |= (1 << ISC01) | (1 << ISC00);
  EIMSK |= (1 << INT0); // enable INT0
  sei();                // globalno omogućavanje prekida
}

// Interrupt Service Routine
ISR(INT0_vect)
{
  PORTB ^= (1 << LED);
}

void loop()
{
  // nop
}
