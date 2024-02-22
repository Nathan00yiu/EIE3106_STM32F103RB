// Pin Usage
// Function ** Pin Name ** Board Pin Out

#include "stm32f10x.h" // Device header

// TIM2 CH1 IC2 ** PB3 ** D10
#define TIM2_CH2_IT1_RCC_GPIO RCC_APB2Periph_GPIOB
#define TIM2_CH2_IT1_GPIO GPIOB
#define TIM2_CH2_IT1_PIN GPIO_Pin_3

// TIM2 CH3 PWM ** PB10 ** D12 //leftwheel
#define TIM2_CH3_PWM_RCC_GPIO RCC_APB2Periph_GPIOB
#define TIM2_CH3_PWM_GPIO GPIOB
#define TIM2_CH3_PWM_PIN GPIO_Pin_10

// TIM3 CH1 PWM ** PB4 ** D12 //rightwheel
#define TIM3_CH1_PWM_RCC_GPIO RCC_APB2Periph_GPIOB
#define TIM3_CH1_PWM_GPIO GPIOB
#define TIM3_CH1_PWM_PIN GPIO_Pin_4

// TIM3 CH2 PWM ** PA7 ** D12
#define TIM3_CH2_PWM_RCC_GPIO RCC_APB2Periph_GPIOA
#define TIM3_CH2_PWM_GPIO GPIOA
#define TIM3_CH2_PWM_PIN GPIO_Pin_7

// TIM4 CH1 IC1 ** PB6 ** D10
#define TIM4_CH1_IT1_RCC_GPIO RCC_APB2Periph_GPIOB
#define TIM4_CH1_IT1_GPIO GPIOB
#define TIM4_CH1_IT1_PIN GPIO_Pin_6

//Function prototypes
void TIM4_CH1_IC1_init(void);	//left wheel counter
void TIM2_CH2_IC2_init(void);	//right wheel counter
//void TIM2_CH3_PWM_init(void);	//left wheel speed control
//void TIM3_CH1_PWM_init(void);	//right wheel speed control
void TIM3_CH2_PWM_init(void);	//ultrasonic sensor
void USART3_init(void);
unsigned char USART3Read(void);
void USART3Send(unsigned char character);
void speedchangeright(int speed);
void speedchangeleft(int speed);


//GPIO init
void PA8_init(void);	//left wheel forward, backward
void PB5_init(void);	//right wheel forward, backward
void PB0_init(void);
void PA4_init(void);
void PA5_init(void);
void PA6_init(void);
void PA7_init(void);

