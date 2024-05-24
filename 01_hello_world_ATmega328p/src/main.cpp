/*AVR-LV
dejan.rakijasic@gmail.com

Primjer: Struktura C/C++ jezika - .c(cpp) i .h datoteke

Ako uključimo (platforimo.ini)) i koristimo Arduino.h .HEX file je mnogo veći

*/
#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include "izracun.h"
// #include <Arduino.h>
int rezultat;

int main(void)
{
  DDRB |= (1 << PB3);
  //  Serial.begin(115200);
  while (1)
  {
    PINB |= (1 << PB3);
    _delay_ms(1000);
    rezultat = zbroj(5, 5);
    // Serial.println(rezultat);
  }
}