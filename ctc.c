#define F_CPU 16000000UL
#include <avr/io.h>

void delay_1ms_ctc(); 

int main(void)
{
	DDRB |= (1 << DDB5);

	while(1){
		PORTB |= (1 << PORTB5);
		delay_1ms_ctc();
		PORTB &= ~(1 << PORTB5);
		delay_1ms_ctc();		
	}
}

void delay_1ms_ctc(){
	unsigned char temp = 0;
	TCNT0 = temp;
	temp = 249;
	OCR0A = temp;
	
	temp = 0x02;
	TCCR0A = temp;
	temp = 0x03;
	TCCR0B = temp;
	
	do{
		temp = TIFR0;
	}
	while(!(temp & (1<<OCF0A)));
	
	temp = 0;
	TCCR0A = temp;
	TCCR0B = temp;

	temp = (1 << OCF0A);
	TIFR0 = temp;
	
	return;
}

