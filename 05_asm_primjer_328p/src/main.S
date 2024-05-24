/*AVR-LV
dejan.rakijasic@gmail.com*/

#ifndef __SFR_OFFSET
/* Define as 0 before including this file for compatibility with old asm
   sources that don't subtract __SFR_OFFSET from symbolic I/O addresses.  */
    #define __SFR_OFFSET 0x00
#endif

#include "avr/io.h"
.global main

main:
ldi r16, 0b00000100
out DDRB,r16 ;PORTB definiramo kao izlaz
petlja:
ldi r17, 0b00000100
OUT PORTB,R17
RJMP petlja