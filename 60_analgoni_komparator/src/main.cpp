/*AVR-LV
dejan.rakijasic@gmail.com

Zadatak:
Negativni ulaz (AIN1) ulaz operacijskog pojačala je promijenjen na PC0 (pin A0) i na njega je spojen potenciometar (0-5V).
Na pozitivni ulaz AIN0 (PD6, pin6) spojen izvor 3.3V sa Arduino pločice. LED (spojena na PB2, pin 10) svijetli ako je
AIN0> AIN1 (prekidna rutina). */
#include <Arduino.h>
#define LED 2

void setup()
{
  DDRB |= (1 << LED); // PD3 IZLAZ (LED)
  // Konfiguracija analognog komparatora
  ACSR = 0;
  ACSR |= (1 << ACIE);
  // ADC - OFF
  ADCSRA &= ~(1 << ADEN);
  // odabir priključka na
  // negativni(invertirajući) ulaz
  ADCSRB |= (1 << ACME);
  // negative input is PC0(pin A0)
  ADMUX = 0;
  sei(); // globalno omogućavanje prekida
}
// Prekidna rutina za analogni komparator
ISR(ANALOG_COMP_vect)
{
  // LED svijetli ako je AIN0>AIN1
  // postavljen je ACO
  if (ACSR & (1 << ACO))
    PORTB |= (1 << LED);
  else
    PORTB &= ~(1 << LED);
}
void loop() {}
