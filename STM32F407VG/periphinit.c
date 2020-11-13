#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

#define SYSTEMCORECLOCK 168000000
#define BAUDRATE        9600
#define APB1_PRESCALER  4

void CLOCK_INIT(void)
{
  /* GPIO CLOCK ENABLE*/ 
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN | RCC_AHB1ENR_GPIODEN  | RCC_AHB1ENR_GPIOEEN  ; 
  /*TIM1 CLOCK ENABLE*/
  RCC->APB2ENR |= RCC_APB2ENR_TIM1EN ; // TIM CLOCK ACTIVATE
  RCC->APB1ENR |= RCC_APB1ENR_TIM2EN ; // TIM CLOCK ACTIVATE
  RCC->APB1ENR |= RCC_APB1ENR_UART4EN; // UART4 CLOCK ENABLE 
  RCC->APB2ENR |= RCC_APB2ENR_SPI1EN ; // SPI1 CLOCK ENABLE
}

void GPIO_INIT(void)
{  
  /*LED'S ENABLE*/ 
  GPIOC->MODER |=   (1<<22)  ; 
  GPIOC->PUPDR |=   (1<<23)  ; 
  GPIOD->MODER |=   (1<<24)| (1<<26) | (1<<28)| (1<<30)  ; 
  GPIOD->PUPDR |=   (1<<25)| (1<<27) | (1<<29)| (1<<31)  ;   
  GPIOD->OSPEEDR|= 0xFFFFFFFF ; 
  /*BUTTON ENABLE*/ 
  GPIOA->MODER  &=~(1<<0); 
  GPIOA->OTYPER &=~(1<<0); 
  GPIOA->PUPDR  |= (1<<1); 
  
}

void TIMER_SCHEDULER_100u(void)  // TIM1 INIT 
{   
  TIM1->EGR |= 0x01 ; 
  TIM1->RCR &=~0xFF ;  
  TIM1->CR1 &=~ (1<<6) |(1<<5) | (1<<9)|(1<<8) |(1<<4) ; 
  TIM1->CR1 |=  (1<<0); // START TIMER 
  TIM1->DIER|=  (1<<0);  // CC IRQ ENABLE 
  TIM1->CR1 &=~ (1<<2);  // ENABLE TIM IRQ ON OVERFLOW 
  TIM1->ARR =  0x15D2 ; // 48EF FOR 1 SEC  
  TIM1->PSC |=  2 ;
  TIM1->CR1 |=  (1<<0); // START TIMER 
  TIM1->SR &=~ (1<<0);  
  NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn );     
  NVIC_SetPriority(TIM1_UP_TIM10_IRQn, 0);   
}

void TIMER_SCHEDULER_1m(void)    // TIM2 INIT
{
  TIM2->EGR |= 0x01 ; 
  TIM2->RCR &=~0xFF ;  
  TIM2->CR1 &=~ (1<<6) |(1<<5) | (1<<9)|(1<<8) |(1<<4) ; 
  TIM2->DIER|=  (1<<0);  // CC IRQ ENABLE 
  TIM2->CR1 &=~ (1<<2);  // ENABLE TIM IRQ ON OVERFLOW 
  TIM2->ARR =  0x6D5E ; // 48EF FOR 1 SEC  
  TIM2->PSC |=  2 ;
  TIM2->CR1 |=  (1<<0); // START TIMER 
  TIM2->SR &=~ (1<<0);   
  NVIC_EnableIRQ(TIM2_IRQn);     
  NVIC_SetPriority(TIM2_IRQn , 0); 
}

void UART_INIT(void)             // UART4 INIT
{
  // PA0 UART4 TX AF8
  // PA1 UART4 RX AF8
  GPIOA->MODER |= (1<<1) | (1<<3) ; 
  GPIOA->OTYPER&=~(1<<0) | (1<<1) ; 
  GPIOA->OSPEEDR|=(1<<0) | (1<<1) |(1<<2) | (1<<3) ; 
  GPIOA->PUPDR |= (1<<1) | (1<<3) ; 
  GPIOA->AFR[0]|= (1<<3) | (1<<7) ; 
  
  //UART4 INITIALIZATION
  
  UART4->CR1 |= (1<<2) | (1<<3)  ; // RXEN TXEN
  UART4->BRR |= ((SYSTEMCORECLOCK/APB1_PRESCALER)/BAUDRATE) ;
  UART4->CR1 &=~(1<<12) ; 
  UART4->CR1 |= (1<<5)  ; // RX IRQ EN    
  UART4->CR1 |= (1<<13)  ; //UART EN 
  NVIC_EnableIRQ(UART4_IRQn);     
  NVIC_SetPriority(UART4_IRQn , 2);
  
  
  
}

void SPI_INIT(void)              // SPI1 INIT

{
GPIOA->AFR[0] |= (5<<16) ;  //ENABLE NSS  PA4
GPIOA->AFR[0] |= (5<<20) ;  //ENABLE CLK  PA5
GPIOA->AFR[0] |= (5<<24) ;  //ENABLE MISO PA6
GPIOA->AFR[0] |= (5<<28) ;  //ENABLE MOSI PA7
GPIOE->MODER  |=  (1<<6) ; 
GPIOA->MODER  |=  (2<<14)|(2<<10)|(2<<12); 

SPI1->CR1     |=  (1<<8)|(1<<9);                          
SPI1->CR1     |=  (7<<0) ; //CPOL=1, CPHA=1, MSTR=1
SPI1->CR1     |=  (7<<3) ; //BAUD MAX  
SPI1->CR1     |=  (1<<2) ; //MASTER MODE
SPI1->CR1     |=  (1<<6) ; //SPI ENABLE

}