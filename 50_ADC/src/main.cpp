/*AVR-LV
dejan.rakijasic@gmail.com

Zadatak:
Potenciometar je spojen na analogni ulaz PC0 (pin A0) mikroupravljača. Za referentni napon odabran je AVCC,
a djelitelj  frekvencije je 128.*/

#include <Arduino.h>
#define analogni_ulaz 0 // PORTC - PC0(pin A0)
void setup()
{
  Serial.begin(115200);
  // definiramo ULAZ za ADC
  DDRC &= ~(1 << analogni_ulaz); // PC0 (pin A0)
  ADCSRA = B10000111;            // ADCEN=1, prescaler-ck/128
  ADMUX = B01000000;             // AVcc - ref, C0 je ulaz
}
void loop()
{
  ADCSRA |= (1 << ADSC); // ADC enable
  while (!(ADCSRA & (1 << ADIF)))
    ;                    // čekamo dok ADC pretvorba ne završi
  ADCSRA |= (1 << ADIF); // brisanje zastavice upisivanjem '1'
  Serial.println(ADC);
}