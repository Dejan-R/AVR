/*AVR-LV
dejan.rakijasic@gmail.com

Zadatak: debounce primjer
debounce - problem istitravanja. Da bi eliminirali taj problem, koristimo minimalno kašnjenje (npr. 50ms) kada se mijenja stanje priključka (HIGH u LOW i obrnuto).
*/
#include <Arduino.h>
#define LED 5
#define tipka 2
int a = 0;
void setup()
{
  DDRB |= (1 << LED);
  DDRD &= ~(1 << tipka);
  PORTD |= (1 << tipka);
}
void loop()
{
  if (((PIND & (1 << tipka)) == 0) && a == 0) // ako je tipkalo pritisnuto
  {
    delay(50); // čekanje 50ms
    a = 1;
  }
  // provjera je li tipkalo još uvijek pritisnuto (nakon 50ms)
  else if (((PIND & (1 << tipka)) == 0) && a == 1)
  {
    PORTB |= (1 << LED); // ako je, uključi LED
    a = 0;
  }
  else
  {
    PORTB &= ~(1 << LED); // isključi LED
  }
}