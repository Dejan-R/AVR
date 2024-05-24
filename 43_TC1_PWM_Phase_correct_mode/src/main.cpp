/*AVR-LV
dejan.rakijasic@gmail.com

Zadatak:
Timer/Counter1 postavljen je u fazno korektivni (Phase correct) PWM mod rada (MODE 10). Izlaz OC1A(PB1,  pin  9) u neinvertirajućem,
a izlaz OC1B(PB2, pin 10) u invertirajućem modu generira  pravokutni signal frekvencije 250 Hz s promjenom
faktora ispune (duty cycle) od 0 do 100%. Radni takt mikroupravljača je 16MHz. */

#include <Arduino.h>
#define LED1 1 // LED na PB1 (pin 9) OC1A
#define LED2 2 // LED na PB2 (pin 10) OC1B
void setup()
{
  DDRB |= (1 << LED1); // PB1(pin 9) – OUTPUT
  DDRB |= (1 << LED2); // PB2(pin 10) – OUTPUT
  // T/C1 inicijalizacija – PHASE CORRECT PWM (MODE10)

  // f = 16000000MHz/(8*2*4000) = 250Hz
  TCCR1A = 0;
  TCCR1B = 0;
  TCCR1A |= (1 << COM1A1) | (1 << COM1B1) | (1 << COM1B0) | (1 << WGM11);
  TCCR1B |= (1 << WGM13) | (1 << CS11);
  ICR1 = 4000; // TOP vrijenost
}
void loop()
{
  for (int i = 0; i <= 4000; i++)
  {
    OCR1A = i;
    OCR1B = i;
    _delay_us(400);
  }
  for (int i = 4000; i >= 0; i--)
  {
    OCR1A = i;
    OCR1B = i;
    _delay_us(400);
  }
}