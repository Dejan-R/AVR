/*AVR-LV
dejan.rakijasic@gmail.com

Zadatak:
Timer/Counter1 postavljen je u normalni mod rada (MODE 0) i prekidna rutina,
u kojoj se mijenja stanje na izlazu PB2 (pin10), izvršava se svake sekunde.
*/
#include <Arduino.h>
#define LED 2 // PORTB - PB2 - pin10

void setup()
{
  DDRB |= (1 << LED); // OUTPUT
  // konfiguracija T/C1 - normal mode
  TCCR1A = 0;
  TCCR1B = 0;
  TCCR1B |= (1 << CS12) | (1 << CS10);
  TIMSK1 |= (1 << TOIE1);
  TCNT1 = 49911; // početna vrijednost TCNT1
  sei();
}

ISR(TIMER1_OVF_vect) // prekidna rutina
{
  TCNT1 = 49911;
  PORTB ^= (1 << LED);
}

void loop()
{
  // nop
}