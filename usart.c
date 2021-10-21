#define F_CPU 16000000UL

#include <avr/io.h>

#define buad 9600
#define bps (F_CPU/16/buad) - 1

unsigned char r16,r17;

void initUART();
void putC();

int main(void)
{
	initUART();
	r16 = 'a';
	putC();
	while(1);
}

void initUART(){
	r16 = bps;
	r17 = (bps >> 8);
		
	UBRR0L = r16;
	UBRR0H = r17;
		
	r16 = (1<<RXEN0)|(1<<TXEN0);
	UCSR0B = r16;
	
	return;
}

void putC(){
	putc_label:
		r17 = UCSR0A;
		if(!(r17 & (1<<UDRE0))){
			goto putc_label;
		}
	UDR0 = r16;
	
	return;
}

