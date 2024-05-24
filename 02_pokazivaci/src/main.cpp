/*AVR-LV
dejan.rakijasic@gmail.com

Zadatak: pokazivači primjer

*/

#include <Arduino.h>

int a = 5;
int *p = &a;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.print("a= ");
  Serial.print(a);
  Serial.println();
  Serial.print("pokazivač *p= ");
  Serial.print(*p);
  Serial.println();

  *p = 10;
  Serial.print("*p=10; - sada je a= ");
  Serial.print(a);
  Serial.println("");

  a = 20;
  Serial.print("a=20; - sada je *p= ");
  Serial.print(*p);
}

void loop()
{
}