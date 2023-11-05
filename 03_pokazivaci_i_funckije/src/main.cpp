/*AVR-LV
dejan.rakijasic@gmail.com

Zadatak: pokazivači primjer

prijenos varijable u funkciju preko pokazivača
-korisiti se radi uštede memorije jer na taj način se ne kopira vrijednost u nove varijable,
nego samo pokazuje na vrijednost.
- također, pass-by-pointer omogućava da se varijabla unutar funkcije promijeni i da se ta promijenjena
vrijednost zadrži i izvan funkcije
*/
#include <Arduino.h>
int a = 3;
int b = 5;

int *a_pok = &a;
int *b_pok = &b;

int zbroj(int *a_pok, int *b_pok)
{
  return *a_pok + *b_pok;
}

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  Serial.print("rezultat = ");
  int rezultat = zbroj(a_pok, b_pok);
  Serial.println(rezultat);
  delay(1000);
}
