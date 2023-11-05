/*AVR-LV
dejan.rakijasic@gmail.com

Zadatak: enkoder primjer sa pin change interrupt
 */

#include <Arduino.h>

#define clk 4 // Arduino UNO (nano) pin 2
#define dt 2  // Arduino UNO (nano) pin 4
volatile byte A = 0;
volatile byte B = 0;
volatile byte encoder = 0;
volatile byte encoder_old = 0;
volatile byte encoder_read = 0;

volatile uint8_t PORTD_default = 0xFF;

void setup()
{
  Serial.begin(115200);
  DDRD &= ~(1 << clk);
  DDRD &= ~(1 << dt);
  PORTD |= (1 << clk);
  PORTD |= (1 << dt);

  // postavke za PCINT
  PCICR |= (1 << PCIE2);
  PCMSK2 |= (1 << PCINT18) | (1 << PCINT20);
  sei();
}

void loop()
{
  if (encoder_old != encoder)
  {
    Serial.println(encoder);
    encoder_old = encoder;
  }
}

ISR(PCINT2_vect)
{
  uint8_t PORTD_change;
  PORTD_change = PIND ^ PORTD_default;
  PORTD_default = PIND;

  if (PORTD_change & (1 << PIND2)) // PCINT na CLK pin
  {
    encoder_read = PIND & 0x14;
    if (encoder_read == B00010100 && A)
    {            // na prvi rastući brid
      encoder--; // dekrementiramo varijablu encoder
      B = 0;
      A = 0;
    }
    else if (encoder_read == B00000100)
      B = 1;
  }

  if (PORTD_change & (1 << PIND4)) // PCINT na DT pin
  {
    encoder_read = PIND & 0x14;
    if (encoder_read == B00010100 && B)
    {            // na prvi rastući brid
      encoder++; // inkrementiramo varijablu encoder
      B = 0;
      A = 0;
    }
    else if (encoder_read == B00010000)
      A = 1;
  }
}
