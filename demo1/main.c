#include "stm32f10x.h" // Device header
#include "PinMap.h"

unsigned char input1[3];
uint8_t input;
int inputint;

int main(void) {
	
	USART3_init();	
	//TIM4_CH1_IC1_init();	//left wheel counter
	//TIM2_CH2_IC2_init();	//right wheel counter
	TIM2_CH3_PWM_init();	//left wheel speed control
	TIM3_CH1_PWM_init();	//right wheel speed control
	
	
	while(1)
	{
		GPIO_WriteBit(GPIOA, GPIO_Pin_8, Bit_RESET);
		GPIO_WriteBit(GPIOB, GPIO_Pin_5, Bit_SET);
		input = USART3Read();
		if(input == ' ')
		{
			for(int i = 0; i < 3; i++)
			{
				input1[i] = USART3Read();
			}
		}
		inputint = (input1[0] - '0')*100;
		inputint = input + (input1[1] - '0')*10;
		inputint = input + (input1[2] - '0');
		
		if(inputint == 248) //UP
		{
			
		}		
		else if (inputint == 76)
		{
		}
		else if(inputint == 233)
		{
		}
		else if(inputint == 91)
		{
		}
	}
}
