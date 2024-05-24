
/*AVR-LV
dejan.rakijasic@gmail.com

Primjer: Struktura C/C++ jezika - .cpp i .h datoteke

*/
#include <Arduino.h>
#include "izracun.h"
void setup()
{
  Serial.begin(115200);
}

void loop()
{
  Serial.print("Hello world!");
  int rezultat = zbroj(3, 5);
  Serial.println(rezultat);
  delay(1000);
}
