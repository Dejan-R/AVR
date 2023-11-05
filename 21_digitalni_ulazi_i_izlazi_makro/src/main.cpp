/*AVR-LV
dejan.rakijasic@gmail.com

Zadatak: makornaredbe primjer
Potrebno je definirati i postaviti ulazno/izlazne priključke pomoću makronaredbi.
makonaredba (preporcesorska naradba) - zamjena teksta iza ključne riječi #define
*/

#include <Arduino.h>

#define pin_OUTPUT(DDR, pin) DDR |= (1 << pin)
#define pin_INPUT(DDR, pin) DDR &= ~(1 << pin)
#define pin_set(PORT, pin) PORT |= (1 << pin)
#define pin_clear(PORT, pin) PORT &= ~(1 << pin)
#define pin_toggle(PORT, pin) PORT ^= (1 << pin)

void setup()
{
  pin_OUTPUT(DDRB, 3);
}

void loop()
{
  pin_set(PORTB, 3);
  delay(1000);
  pin_clear(PORTB, 3);
  delay(1000);
}