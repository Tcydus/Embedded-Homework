.nolist
#include<m328pdef.inc> 
.list

.org 0x0000
	rjmp main

main:	
	sbi ddrb,5
loop: 
	sbi portb,5
	rcall delay_ctc
	cbi portb,5
	rcall delay_ctc
	rjmp loop

delay_ctc:
	ldi r20,0
	out tcnt0,r20
	ldi r20,249
	out ocr0a,r20

	ldi r20,0x20
	out tccr0a,r20
	ldi r20,0x05
	out tccr0b,r20

again: 
	in r20,tifr0
	sbrs r20,ocf0a
	rjmp again

	ldi r20,0x00
	out tccr0a,r20
	out tccr0b,r20

	ldi r20,(1<<ocf0a)
	out tifr0,r20
	
	ret


