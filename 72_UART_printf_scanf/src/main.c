/*dejan.rakijasic@gmail.com

Primje: UART - printf() i scanf()
Primjer upotrebe (printf() i scanf()) za serijsku komunikaciju preko UART-a.

printf_P() - (makronaredba PSTR iz pgmspace.h) - sprema u FLASH umjesto u SRAM.
*/
#define F_CPU 16000000L
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
//#include <avr/pgmspace.h>

// Funkcija za slanje jednog znaka UART-om (stdio.h)
int uart_char_slanje(char c, FILE *stream) {
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = c;
    return 0;
}
// Funkcija za primanje jednog znaka UART-om (stdio.h)
int uart_char_primanje(FILE *stream) {
    loop_until_bit_is_set(UCSR0A, RXC0);
    return UDR0;
}

//makronaredba FDEV_SETUP_STREAM konfigurira FILE strukture ('uart_output' i 'uart_input') za usmjeravanje standardnog izlaza i ulaza na UART.
FILE uart_output = FDEV_SETUP_STREAM(uart_char_slanje, NULL, _FDEV_SETUP_WRITE);
FILE uart_input = FDEV_SETUP_STREAM(NULL, uart_char_primanje, _FDEV_SETUP_READ);

int main(void)
{
//USART konfiguracija
  UCSR0A = 0;
  UCSR0B = 0;
  UCSR0C = 0;
  /*  Rx i Tx omogućeno UART(Asynchornous) asinkrono,
  paritet onemogućen, 1 STOP bit, 8-bitoova poznaku*/
  UCSR0B = (1<<RXEN0) | (1<<TXEN0);
  UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
  UBRR0L = 103; // Baud rate 9600

stdout = &uart_output; //pokazivač na FILE objekt
stdin = &uart_input; //pokazivač na FILE objekt

    printf("Upišite svoje ime: \n");  //printf_P(PSTR("Upišite svoje ime: \n"));
    char ime[20];
    scanf("%s", ime);
    printf("Pozdrav, %s!\n", ime);   //printf_P(PSTR("Pozdrav, %s!\n"), ime);
    while (1) {
        //
    }
}
