/*AVR-LV
dejan.rakijasic@gmail.com

Zadatak:
Timer/Counter1 postavljen je u CTC mod rada (MODE 4) i prekidna rutina,
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
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS12) | (1 << CS10);
  TIMSK1 |= (1 << OCIE1A);
  OCR1A = 15624; // komparacijski registar
  sei();
}

ISR(TIMER1_COMPA_vect) // prekidna rutina TCNT1 = OCR1A
{
  PORTB ^= (1 << LED);
}

void loop()
{
  // nop
}