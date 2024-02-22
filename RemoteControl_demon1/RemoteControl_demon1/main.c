/*
 * RemoteControl_demon1.c
 *
 * Created: 7/2/2024 3:33:50 pm
 * Author : 21093734d
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char Send_data = 'n';
int state = 0;
int adc0_1 = 0;
int adc_low;
int adc_high;
int cal, sum = 0;


void ADC0_init()
{
	ADMUX = (1 << REFS0) | (0 << MUX0); //ADC0 //AVCC
}

void ADC1_init()
{
	ADMUX = (1 << REFS0) | (1 << MUX0); //ADC1 //AVCC
}

void state1()
{
	if(adc0_1 == 0)
	{
		ADC0_init();
		ADCSRA |= (1 << ADSC); //start conversion
		
		sum = adc_low;
		adc0_1 = 1;
	}
	else if (adc0_1 == 1)
	{
		ADC1_init();
		ADCSRA |= (1 << ADSC); //start conversion
		
		sum = sum + adc_low;
		if(sum >= 253 && sum <= 257) //up
		{
			USART_Transmit(intToAscii(1));
		}
		else if(sum >= 77 && sum <= 81) //left
		{
			USART_Transmit(intToAscii(2));
		}
		else if(sum >= 239 && sum <= 243) //right
		{
			USART_Transmit(intToAscii(3));
		}
		else if(sum >= 91 && sum <= 95) //back
		{
			USART_Transmit(intToAscii(4));
		}
		else if(sum >= 169 && sum <= 174)//stop
		{
			USART_Transmit(intToAscii(0));
		}
		
// 		USART_Transmit(' ');
// 		cal = sum/100;
// 		USART_Transmit(intToAscii(cal));
// 		cal = (sum % 100)/10;
// 		USART_Transmit(intToAscii(cal));
// 		cal = sum % 10;
// 		USART_Transmit(intToAscii(cal));
// 		USART_Transmit(' ');
		
		adc0_1 = 0;
	}
}

void USART_Init(void)
{
	/*Set baud rate */
	UBRR0H = 0x00; //set baud rate
	UBRR0L = 0x08; //set baud rate = 115200 set UBRR value = 7.68
	/*Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0); //receive enable, transmit enable
	/* Set frame format: 8data, 1stop bit */
	UCSR0C = (0<<USBS0)|(3<<UCSZ00); //1 stop bits, character size
}

void USART_Transmit( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)))  //if UDRE0 is 1, buffer is empty, means ready to be written
	;
	/* Put data into buffer, sends the data */
	UDR0 = data;
}
unsigned char USART_Receive( void )
{
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) ) //if the receive buffer is disable, RXC0 = 0
	;
	/* Get and return received data from buffer */
	return UDR0;
}

int checkState()
{
	if (PINB & (1 << 0))	//Check PB0
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

ISR (ADC_vect)
{
	adc_low = ADCL;
	adc_high = ADCH;
	ADCSRA |= (1 << ADSC);
}

int intToAscii(int number) 
{
	return '0' + number;
}

void ctcdelay()
{
	for(int j = 0; j < 160; j++) //10ms delay
	{
		OCR0A = 100; //set OCR0A to 100
		TCCR0A = 0x02; //set timer0 to CTC mode
		TCCR0B = 0x01; //set no per-scaler
		while((TIFR0&(1<<OCF0A))==0); // when OCF0A = 0 (not overflow), wait
		TCCR0B = 0; //reset timer
		TIFR0 = 0x02;
	}
}

int main(void)
{
	DDRB = 0x00;		//PB0 = input
	USART_Init();
	sei();
	ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	
    while (1) 
    {
		if(!state)
		{
			for (int i = 0; i < 10; i++) //delay 1s
			{
				ctcdelay();
			}
			state = checkState();
		}
		else if(state)
		{
			state1();
			for (int i = 0; i < 10; i++) //delay 1s
			{
				ctcdelay();
			}
			ctcdelay();
		}
    }
}
