/*AVR-LV
dejan.rakijasic@gmail.com

Zadatak:
Na PB2 (pin10) spojena je LED. Kada dođe podatak na UART, izvodi se prekidna rutina ISR(USART_RX_vect) u kojoj se
primljeni podatak sprema u varijablu 'podatak’, te se uključuje LED ako je primljeni podatak 'D', odnosno isključuje LED
ako je primljeni podatak 'n'. Potrebno je namjestiti baud rate na 9600 bps!*/

#include <Arduino.h>

#define LED 2
volatile int podatak;
void setup()
{
  DDRB |= (1 << LED);
  UCSR0A = 0;
  UCSR0B = 0;
  UCSR0C = 0;
  /* RXCIE0, Rx omogućeno UART(Asynchornous) asinkrono,
  paritet onemogućen, 1 STOP bit, 8-bitoova poznaku*/
  UCSR0B |= (1 << RXCIE0) | (1 << RXEN0);
  UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
  UBRR0L = 103; // Baud rate 9600
  sei();        // omogućeni globalni prekidi
}
// ISR – prekidna rutina–RxC statusni bit
ISR(USART_RX_vect)
{
  podatak = UDR0;
}
void loop()
{
  if (podatak == 'D')
  {
    PORTB |= (1 << LED);
  }
  if (podatak == 'n')
  {
    PORTB &= ~(1 << LED);
  }
}