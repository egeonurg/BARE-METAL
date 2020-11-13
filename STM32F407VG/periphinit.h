#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#define BUTTON_STATUS          (GPIOA->IDR & (1<<0))
#define GREEN_LED_ON()         (GPIOD->ODR |= (1<<12))      
#define GREEN_LED_OFF()        (GPIOD->ODR &=~ (1<<12))
#define ORANGE_LED_ON()        (GPIOD->ODR |= (1<<13))
#define ORANGE_LED_OFF()       (GPIOD->ODR &=~ (1<<13))
#define RED_LED_ON()           (GPIOD->ODR |= (1<<14))
#define RED_LED_OFF()          (GPIOD->ODR &=~ (1<<14))
#define BLUE_LED_ON()          (GPIOD->ODR |= (1<<15))
#define BLUE_LED_OFF()         (GPIOD->ODR &=~ (1<<15))
#define GREEN_LED_TOGGLE()     (GPIOD->ODR ^= (1<<12))      
#define ORANGE_LED_TOGGLE()    (GPIOD->ODR ^=(1<<13))
#define RED_LED_TOGGLE()       (GPIOD->ODR ^= (1<<14))
#define BLUE_LED_TOGGLE()      (GPIOD->ODR ^= (1<<15))

#define DEBUG_TOGGLE()      (GPIOC->ODR ^= (1<<11))
#define CLEAR_100u_IRQ_FLAG()    (TIM1->SR &=~ (1<<0)) 
#define CLEAR_1m_IRQ_FLAG()      (TIM2->SR &=~ (1<<0)) 

#define  MODBUS_WAIT 0
#define  MODBUS_WORK 1
#define  MODBUS_BUFFER_SIZE 5 

void UART_INIT(void);
void CLOCK_INIT(void);
void GPIO_INIT(void); 
void TIMER_SCHEDULER_100u(void); 
void TIMER_SCHEDULER_1m(void); 
void SPI_INIT(void);