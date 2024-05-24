/*AVR-LV
dejan.rakijasic@gmail.com

Zadatak:
Timer/Counter0 - MODE 5 – generira fazno korektivni PWM signal na izlazu OCR0B -
PD5 (pin5)
Timer/Counter1 - ICP – mjeri frekvenciju i duty cycle signala na ulazu PB0 (pin8).
PB0 (pin8) i PD5 (pin5) moraju biti povezani!
*/

#include <Arduino.h>
volatile unsigned int edge1, edge2, edge3, high, period;
volatile int edge = 1;
volatile long frequency, f;
volatile float duty_cycle, dc;
void setup()
{
  Serial.begin(115200);
  DDRB &= ~(1 << PB0); // PB0/pin 8 - ICP pin - ULAZ
  PORTB |= (1 << PB0); // Pull-up aktiviran na PB0/pin8 - ICP
  DDRD |= (1 << PD5);  // PD5(pin5) - OC0B (PWM) - IZLAZ

  // Timer/Counter0 – MODE 5 – Phase Correct PWM
  // f=16MHz/(2*8*TOP(250)) = 4000 Hz
  TCCR0A = 0;
  TCCR0B = 0; // Prescaler(djelitelj frekvencije) 8
  TCCR0A |= (1 << COM0B1) | (1 << WGM00);
  TCCR0B |= (1 << CS01) | (1 << WGM02);
  OCR0A = 250; // TOP vrijednost
  OCR0B = 125; // Duty cycle-50%

  // Timer1 Input Capture Unit aktivirana
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  TCCR1B |= (1 << ICES1) | (1 << CS10); // rastući brid (RISING EDGE) - početno, (PRESCALER = 1)
  TIMSK1 |= (1 << ICIE1);
  sei();
}
ISR(TIMER1_CAPT_vect)
{
  switch (edge)
  {
  case 1:
    edge1 = ICR1;       // 1. RISING EDGE detektiran
    TCCR1B = B00000001; // padajući brid (FALLING EDGE), (PRESCALER = 1)
    edge = 2;
    break;
  case 2:
    edge2 = ICR1;       // 2. FALLING EDGE detektiran
    TCCR1B = B01000001; // rastući brid (RISING EDGE), (PRESCALER = 1)
    edge = 3;
    break;
  case 3:
    edge3 = ICR1;                       // 3. RISING EDGE detektiran
    TCCR1B = 0;                         // STOP TIMER/COUNTER1 – zaustavljamo brojač
    if (edge1 < edge2 && edge2 < edge3) // provjeravamo vrijednosti zbog preliva (overflow)
    {
      high = edge2 - edge1;
      period = edge3 - edge1;
      // frkvencija
      frequency = F_CPU / period;
      // duty cycle
      duty_cycle = ((float)high / (float)period) * 100;
    }
    // START TIMER/COUNTER1 – pokrećemo brojač ponovno
    TCCR1A = 0;
    TCNT1 = 0;
    TCCR1B = B01000001; // rastući brid (RISING EDGE), (PRESCALER = 1)
    TIMSK1 |= (1 << ICIE1);
    edge = 1;
    break;
  }
}
void loop()
{

  if ((f != frequency) || (dc != duty_cycle))
  {
    // ispisujemo frekvenciju i faktor ispune (duty cycle)
    Serial.print("Frekvencija: ");
    Serial.print(frequency);
    Serial.println(" Hz");
    Serial.println(" ");
    Serial.print("Duty cycle: ");
    Serial.print(duty_cycle);
    Serial.println(" %");
    f = frequency;
    dc = duty_cycle;
  }
}
