/*dejan.rakijasic@gmail.com
ATmega328P - Assembler primjer - digital I/O
    - ako je pritisnuta tipka na PD2, uključi LED na PB1
*/

#ifndef __SFR_OFFSET
/* Define as 0 before including this file for compatibility with old asm
   sources that don't subtract __SFR_OFFSET from symbolic I/O addresses.  */
#define __SFR_OFFSET 0x00
#endif
#include "avr/io.h"
.global main
main:

LDI R16, 0x04
OUT DDRD,R16 //PD2 - INPUT
OUT PORTD, R16 //PD2 - aktiviran PULL-UP

LDI R17, 0x02
OUT DDRB,R17 //PB1 - OUTPUT

ponovi:
    SBIS PIND, 2 ;preskoči sljedeću instrukciju (izvršava LED_ON:) ako je postavljen PD2 (tipka pritisnuta)
    RJMP LED_ON   
    CBI PORTB, 1 ;postavlja PB1 - LOW (LED OFF) 
    RJMP ponovi       

LED_ON:
    SBI PORTB, 1  ;postavlja PB1 - HIGH (LED ON)    
    RJMP ponovi         
   