/*AVR-LV
dejan.rakijasic@gmail.com

Zadatak:
Timer/Counter1 konfiguriran je za brojanje vanjskih impulse dovedene na ulaz T1 - PD5 (pin 5).
Na svaki padajući brid signala na ulazu T1, povećava se sadržaj TCNT1 registra za jedan.  */

#include <Arduino.h>
#define ulaz_brojaca 5 // PORTD - T1 PD5 (pin5)
uint16_t a;
void setup()
{
  Serial.begin(115200);
  DDRD &= ~(1 << ulaz_brojaca); // ULAZ
  PORTD |= (1 << ulaz_brojaca); // Pull-up aktiviran
  /*Timer1 – COUNTER – broji vanjske impulse dovedene
   * na ulaz T1 (PD5), takt na padajući brid (FALLING EDGE)*/
  TCCR1A = 0;
  TCCR1B = 0;
  TCCR1B |= (1 << CS12) | (1 << CS11);
  TCNT1 = 0; // postavlja TCNT1 registar u 0
  Serial.print("Sadrzaj TCNT1 registra: ");
  Serial.println();
}
void loop()
{
  if (a != TCNT1)
  {
    Serial.println(TCNT1);
    a = TCNT1;
  }
}