/*AVR-LV
dejan.rakijasic@gmail.com

 Mjerenje udaljenosti pomoću HC-SR04 - ultrazvučnnog senzora
 trigger - PD5 - Arduino pin5
 cho - PB0 - Arduino pin8

 */
#include <Arduino.h>
volatile unsigned int a, b, high;
volatile int brid = 1;
void setup()
{
  Serial.begin(115200);
  DDRB &= ~(1 << PB0); // PB0/pin 8 - ICP pin - ULAZ - ECHO
  PORTB |= (1 << PB0); // aktiviran pull-up na PB0/pin8 - ICP pin - HC04 ECHO
  DDRD |= (1 << PD5);  // PD5(pin5) - IZLAZ - HC04 TRIGGER

  // definiramo Timer1 za hvatanje signala (Input Capture) na ICP pinu
  // ali i za komparacijski mod (CTC MOD4) zbog slanja impulsa senzoru svakih 70ms
  TCCR1A = 0;
  TCNT1 = 0;
  TCCR1B = B01001100; // RASTUĆI(rising) brid, (PRESCALER = 256)
  TIMSK1 = B00100010;
  OCR1A = 892; // TOP vrijednost za CTC mod4
  sei();
}

// svakih približno 70ms šaljemo trigger pin senzoru (impuls trajanja 10us)
ISR(TIMER1_COMPA_vect)
{
  digitalWrite(5, HIGH);
  delayMicroseconds(10);
  digitalWrite(5, LOW);
}

ISR(TIMER1_CAPT_vect)
{
  switch (brid)
  {
  case 1:                    // rastući brid
    a = ICR1;                // 1. spremamo vrijednost za RASTUĆI brid
    TIFR1 = (1 << ICF1);     // brisanje ICP bita (Input Capture flag)
    TCCR1B &= ~(1 << ICES1); // postavljamo sljedeći padajući brid
    brid = 2;
    break;
  case 2:                   // padajući brid
    b = ICR1;               // 2. spremamo vrijednost za PADAJUĆI brid
    TIFR1 = (1 << ICF1);    // brisanje ICP bita (Input Capture flag)
    TCCR1B |= (1 << ICES1); // postavljamo sljedeći rastući brid

    if ((a < b)) // provjeravamo očitane vrijednosti da bi izbjegli preliv (overflow)
    {
      high = b - a;
      // 16 ide zbog djelitelja (prescaler(256) = 62500, pa je onda 16*62500Hz = 1 MHz)
      // brzina zvuka 343 m/s
      // dobijemo udaljenost u MILIMETRIMA
      //  :2 jer se zvučni val prijeđe dupli put - do prepreke i nazad
      long d = (16 * high * (0.343) / 2) / 10;

      // ispis vrijednosti
      Serial.print("d: ");
      Serial.print(d);
      Serial.println(" cm");
    }
    else
    {
      Serial.println("Izvan opsega!!");
    }
    brid = 1;
    break;
  }
}

void loop()
{
}
