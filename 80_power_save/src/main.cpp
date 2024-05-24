
/*AVR-LV
dejan.rakijasic@gmail.com

Zadatak:
ATmega8 se postavlja u štedljivi način rada, 'POWER DOWN MODE' nakon što deset puta toggla LED na PB0 (pin8).
Pritiskom na tipku PD2 (interrupt INT0) LOW signalom budimo mikroupravljač. LED2 (PD7) nam signalizira interrupt. Potrošnja energije mikroupravljača u spavanju, značajno
je manja!
*/

#include <Arduino.h>
#include <avr/sleep.h> //makronaredbe za sleep mode rada - by ATMEL
#include <avr/power.h> //makronaredbe za sleep mode rada - by ATMEL

#define pin_za_budjenje 2    // PORTD - PD2 (pin2) INT0 (interrupt)- buđenje
#define LED1 0                // PORTB - PB0  
#define LED2 7               // PORTD - PD7 
volatile uint8_t brojac = 0; // brojac

ISR(INT0_vect) // prekidna rutina nakon buđenja
{
    // ovdje ide kod nakon buđenja (a prije povratka u loop funkciju)
   PORTD ^= (1 << LED2);
}

void setup()
{
  /* Postoji 6 modova:
   *     SLEEP_MODE_IDLE         -najmanja ušteda enerrgije
   *     SLEEP_MODE_ADC
   *     SLEEP_MODE_PWR_SAVE
   *     SLEEP_MODE_EXT_STANDBY
   *     SLEEP_MODE_STANDBY
   *     SLEEP_MODE_PWR_DOWN     -najveća ušteda

   * Interrupt se MORA generirati na LOW signal za sve modove rada (osim IDLE)
   * Da bi mikroupravljač probudili iz stanja spavanja, treba nam korištenje prekida,
   * jer osim prekida probuditi ga može samo resetiranje (Reset).
   * Izuzetak je mod spavanje IDLE iz koje se mikroupravljač budi signalom na pinu za serijsku komunikaciju (UART).
   */

  set_sleep_mode(SLEEP_MODE_PWR_DOWN); // postavljamo sleep mode

  DDRD &= ~(1 << pin_za_budjenje); // INPUT
  PORTD |= (1 << pin_za_budjenje); // PULLUP
  DDRB |= (1 << LED1);
  DDRD |= (1 << LED2);
  // konfiguracija vanjskog prekida - INT0 na vanjski signal (PD2)
  EICRA = 0;
  EIMSK = 0;
  EICRA &= ~((1 << ISC01) | (1 << ISC00)); //interrupt INT0 (LOW)

}



void loop()
{
    brojac = 0;
      EIMSK |= (1 << INT0); //omgućujemo INT0
      set_sleep_mode(SLEEP_MODE_PWR_DOWN); //postavljamo SLEEP MODE

      // stavljamo mikroupravljač na spavanje (postavke u SMCR registru)
      sleep_enable();
      sei(); //omogućujemo globalne prekide
      sleep_cpu();
      sleep_disable();
      EIMSK &= ~(1 << INT0); //onemogućujemo INT0
      cli(); //onemogućujemo globalne prekide
}
