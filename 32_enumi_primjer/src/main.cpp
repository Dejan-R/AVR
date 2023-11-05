/*AVR-LV
dejan.rakijasic@gmail.com

Zadatak: enumi - primjer
Treba napraviti izbornik - 1 tipka i 3 LED - svaki pritisak tipke svijetli sljedeća LED (kružno). */

#include <Arduino.h>

volatile uint8_t brojac = 1;
#define led1 1  // PORTB - PB1 (pin9)
#define led2 2  // PORTB - PB2 (pin10)
#define led3 3  // PORTB - PB3 (pin11)
#define tipka 2 // PORTD - PD2 (pin2)

// enumi - vrsta vrijable koju definira sam korisnik radi bolje preglednosti koda
enum STANJA
{
  LED1, // svijetli LED1
  LED2, // svijetli LED2
  LED3  // svijetli LED3
};
STANJA stanje; // zadržava trenutno stanje sustava

void setup()
{
  DDRB |= (1 << led1) | (1 << led2) | (1 << led3);
  DDRD &= ~(1 << tipka);
  PORTD |= (1 << tipka);
  stanje = LED1; // početno stanje

  EICRA = 0;
  EIMSK = 0;
  EIMSK |= (1 << INT0);
  EICRA |= (1 << ISC01) | (1 << ISC00);
  sei();
}
ISR(INT0_vect)
{
  if (brojac < 3)
  {
    brojac++;
  }
  else
  {
    brojac = 1;
  }
}

void provjera_ulaza()
{
  switch (stanje)
  {
  case LED1:
    if (brojac == 2)
    {
      stanje = LED2;
    }
    break;
  case LED2:
    if (brojac == 3)
    {
      stanje = LED3;
    }
    break;
  case LED3:
    if (brojac == 1)
    {

      stanje = LED1;
    }
    break;
  }
}

void izvrsavanje_stanja()
{
  switch (stanje)
  {
  case LED1:
    PORTB |= (1 << led1);
    PORTB &= ~(1 << led2);
    PORTB &= ~(1 << led3);
    break;

  case LED2:
    PORTB &= ~(1 << led1);
    PORTB |= (1 << led2);
    PORTB &= ~(1 << led3);
    break;

  case LED3:
    PORTB &= ~(1 << led1);
    PORTB &= ~(1 << led2);
    PORTB |= (1 << led3);
    break;
  }
}

void loop()
{
  izvrsavanje_stanja(); // funkcija koja izvršava određeno stanje sustava
  provjera_ulaza();
}
