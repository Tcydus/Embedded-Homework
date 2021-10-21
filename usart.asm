.nolist
#include<m328pdef.inc> 
.list 

	.equ	F_CPU = 16000000
	.equ	baud = 9600			
	.equ	bps	= (F_CPU/16/baud) - 1

.org 0x0000
	jmp main

main:
	rcall initUART			
	ldi	r16,'a'				
	rcall putc

loop:
	rjmp loop


initUART:
	ldi	r16,LOW(bps)			
	ldi	r17,HIGH(bps)

	sts	UBRR0L,r16			
	sts	UBRR0H,r17				

	ldi	r16,(1<<RXEN0)|(1<<TXEN0)	
	sts	UCSR0B,r16			

	ret

putc:	
	lds	r17,UCSR0A		
	sbrs r17,UDRE0			
	rjmp putc				

	sts	UDR0,r16	
		
	ret	
				