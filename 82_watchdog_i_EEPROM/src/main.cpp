

/*AVR-LV
dejan.rakijasic@gmail.com

Zadatak:
Watchdog timer treba konfigurirati tako da pokrene WDT prekidnu rutinu i resetira sustav nakon 2 sekunde ako mikroupravljač ne resetira WDT.
U glavnoj petlji napisana je 'for' petlja kroz koju prolazi svaki put sve duže kako se povećava varijabla petlja_brojac.
Kada vrijeme prolaska kroz 'for' petlju bude duže od 2 sekunde, mikroupravljač neće moći resetirati WDT te će WDT resetirati mikroupravljač.
Mikroupravljač posprema podatak (varijablu 'WDT_podaci') u EEPROM prije resetiranja, a nakon ponovnog pokretanja istu čita iz EEPROM-a.
*/

#include <Arduino.h>
#include <avr/wdt.h>    //makronaredbe za watchdog timer - by ATMEL
#include <avr/eeprom.h> // funkcije za pristup EEPROM-u - by ATMEL
int petlja_brojac = 0;
uint8_t WDT_podaci; // podaci koje treba pohraniti u EEPROM

#define LED 3 // PORTB - PB1 (pin 9)

void watchdog_init(void)
{
  cli(); // disable interrupts
  /*resetiranje WDT-a i brisanje svih postavki*/
  wdt_reset();
  MCUSR &= ~(1 << WDRF); // brisanje  WDRF bita u MCUSR registru
  WDTCSR |= (1 << WDCE) | (1 << WDE);
  WDTCSR = 0x00;

  /*
  WDTCSR konfiguracija:
  WDIE = 1 - Interrupt Enable
  WDE = 1 - Reset Enable
  Da bi postavili preliv za 2000ms moramo postaviti sljedeće bitove:
  WDP3 = 0
  WDP2 = 1
  WDP1 = 1
  WDP0 = 1
*/
  // ULAZ u postavke watchdog timera:
  WDTCSR |= (1 << WDCE) | (1 << WDE);
  // Postavke WDT za WDT interrupt i resetiranje sustava
  WDTCSR = (1 << WDE) | (1 << WDIE) | (1 << WDP2) | (1 << WDP1) | (1 << WDP0);
  sei(); // globalno omogućavanje prekida
}
void setup()
{
  wdt_disable(); // moramo onemogućiti WDT (problem sa nekim Arduino bootloaderima)
  Serial.begin(115200);
  Serial.println("Pokretanje...");
  DDRB |= (1 << LED);
  PORTB |= (1 << LED); // PB1 - HIGH
  delay(500);
  watchdog_init();
  Serial.print("Čitam WDT_podaci iz EEPROM-a:");
  WDT_podaci = eeprom_read_byte((uint8_t *)0); // čitamo iz EEPROM-a
  Serial.println(WDT_podaci);
}

void loop()
{
  // LED svijetli kako brojač broji
  for (int i = 0; i <= petlja_brojac; i++)
  {
    PORTB |= (1 << LED);
    delay(100);
    PORTB &= ~(1 << LED);
    delay(100);
  }
  petlja_brojac++;
  wdt_reset(); // naredba kojom resetiramo WDT - to se mora dogoditi ispod 2 sekunde, tj. prije preliva WDT-a
  Serial.print(petlja_brojac);
  Serial.print(". brojac priblizno ");
  Serial.print(petlja_brojac * 200);
  Serial.println(" millisekundi.");
}
ISR(WDT_vect) // Watchdog timer interrupt.
{
  // Ovdje možemo uključiti kod (npr. spremiti određene postavke prije reseta i sl.)
  // Ali treba biti oprezan te ne koristiti funkcije koje mogu spriječiti resetiranje.
  Serial.println("Pospremam podatke prije resetiranja...");
  Serial.print("WDT_podaci = ");
  Serial.println(WDT_podaci++);
  eeprom_write_byte((uint8_t *)0, WDT_podaci); // upisujemo u EEPROM
}