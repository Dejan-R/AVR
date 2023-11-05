/*AVR-LV
dejan.rakijasic@gmail.com

Zadatak:
Potenciometar je spojen na analogni ulaz PC0 (pin A0) mikroupravljača. Za referentni napon odabran je AVCC,
a djelitelj  frekvencije je 128. Omogućen je prekidni vektor za  ADC. Omogućeno je automatsko
pokretanje AD pretvornika - Auto Trigger (ADATE bit). */

#include <Arduino.h>
#define analogni_ulaz 0 // PORTC - PC0(pin A0)
void setup()
{
  Serial.begin(115200);
  // definiramo ULAZ za ADC
  DDRC &= ~(1 << analogni_ulaz); // PC0 (pin A0)
  // ADC automatski izvršava AD pretvorbu
  ADCSRA = B11101111; // ADCEN=1, ADSC=1, ADATE=1, ADIE=1, ck/128
  ADCSRB = B00000000; // free running mode – AD pretvornik stalno uzima uzorke i ažurira
  // ADC registar
  ADMUX = B01000000; // AVcc - ref, C0 - ULAZ
  sei();             // global interrupt enables
}
ISR(ADC_vect) // Interrupt Service Routine za ADC
{
  Serial.println(ADC); // ispis rezultata AD pretvorbe (ADC registar)
}
void loop()
{
}