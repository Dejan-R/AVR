/*AVR-LV
dejan.rakijasic@gmail.com

Zadatak:
Timer/Counter1 postavljen je u brzi (Fast) PWM mod rada (MODE 14). Izlaz OC1A(PB1,  pin  9) u neinvertirajućem,
a izlaz OC1B(PB2, pin 10) u invertirajućem modu generira  pravokutni signal frekvencije 250 Hz s promjenom
faktora ispune (duty cycle) od 0 do 100%. Radni takt mikroupravljača je 16MHz. */

#include <Arduino.h>
#define LED1 1 // LED na PB1 (pin 9) OC1A
#define LED2 2 // LED na PB2 (pin 10) OC1B
void setup()
{
  DDRB |= (1 << LED1); // PB1(pin 9) – OUTPUT
  DDRB |= (1 << LED2); // PB2(pin 10) – OUTPUT
  // T/C1 inicijalizacija – FAST PWM (MODE14)

  // f=16000000MHz/(8*(1+7999)) = 250Hz (4ms)*/
  TCCR1A = 0;
  TCCR1B = 0;
  TCCR1A |= (1 << COM1A1) | (1 << COM1B1) | (1 << COM1B0) | (1 << WGM11);
  TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << CS11);
  ICR1 = 7999; // TOP (vršna) vrijednost
}
void loop()
{
  for (int i = 0; i < 8000; i++)
  {
    OCR1A = i;
    OCR1B = i;
    _delay_us(200);
  }
  for (int i = 7999; i >= 0; i--)
  {
    OCR1A = i;
    OCR1B = i;
    _delay_us(200);
  }
}
