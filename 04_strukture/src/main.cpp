/*AVR-LV
dejan.rakijasic@gmail.com

Primjer: Struktura u  C/C++ jeziku
Definiramo strukturu s_zbroj koja sadrži dva podatka (a i b), te funkciju izracun() koja kao argument prima pokazivač na strukturu
s_zbroj, zbroji brojeve a i b, te vraća rezultat.

U glavnom programu definiramo dvije varijable (s1 i s2) tipa s_zbroj, inicijaliziramo ih brojevima koje želimo zbrojiti i pozivamo funkciju izracun() za svaku od njih.
Rezultat ispisujemo preko Serial monitora pomoću Arduino funkcije Serial.print().
*/

#include <Arduino.h>

typedef struct
{
  uint8_t a;
  uint8_t b;
} s_zbroj;

/*Strukture u funkcije prenosimo preko pokazivača da bi vrijednosti strukture postavljene u funkciji bile zapamćene i izvan nje
 "arrow" operator -> služi za pristupanje strukutrama, s tim da možemo pristupiti na drugi način kako je navedno dolje u komentaru
 return (*s).a + (*s).b
*/
int izracun(s_zbroj *s)
{
  return s->a + s->b;
  // return (*s).a + (*s).b;
}

void setup()
{
  Serial.begin(115200);

  s_zbroj s1 = {3, 4};
  s_zbroj s2 = {5, 5};

  Serial.print("Zbroj z1: ");
  Serial.println(izracun(&s1));
  Serial.print("Zbroj z2: ");
  Serial.println(izracun(&s2)); // u funkciju se prenosi adresa strukture
}

void loop() {}
