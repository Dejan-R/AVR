/*AVR-LV
dejan.rakijasic@gmail.com

Zadatak:
Mikroupravljač svake sekunde šalje UART sučeljem podatak 'D'. Mikropravljač Potrebno je namjestiti baud rate na 9600 bps!*/

#include <Arduino.h>
void setup()
{
  UCSR0A = 0;
  UCSR0B = 0;
  UCSR0C = 0;
  /*UART(Asynchornous), Parity disabled, 1 STOP bit, 8-bit/char*/
  UCSR0B |= (1 << UDRIE0) | (1 << TXEN0);
  UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
  UBRR0L = 103; // Baud rate 9600
  sei();        // global interrupt enables
}
// ISR - UDRE flag
ISR(USART_UDRE_vect)
{
}
void loop()
{
  UDR0 = 'D';
  delay(1000);
}