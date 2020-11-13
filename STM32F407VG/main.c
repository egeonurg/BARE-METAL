#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "periphinit.h"
#include "MODBUS.h"

#define SPI_STEP1 1
#define SPI_STEP2 2
#define SPI_STEP3 3
#define SPI_STEP4 4

uint8_t SPI_STEP = 1 ; 
uint8_t SPI_TX_BUFFER[10] = "EGEONURGUL" ;
uint8_t SPI_INDEX = 0 ;

void main()
{  
  CLOCK_INIT();
  GPIO_INIT();   
  SPI_INIT();
  UART_INIT(); 
  TIMER_SCHEDULER_1m();
  TIMER_SCHEDULER_100u();
  
  while(1) 
  {
    
    
  }
  
}

void IRQ_100u (void) // 1 ms Handler
{
  CLEAR_100u_IRQ_FLAG() ;
  RED_LED_TOGGLE()  ;  
  
  switch(SPI_STEP)
  {      
    case(SPI_STEP1):
      {
        
        if(SPI_INDEX < 9)
        {
          SPI_INDEX ++ ; 
        }
        else
        {
          SPI_INDEX = 0 ;             
        }          
        
        SPI1->DR  = *(SPI_TX_BUFFER + SPI_INDEX) ;
        SPI1->CR1 |= (1<<7) ; 
        SPI_STEP = SPI_STEP2 ;
        
      }
      
    case(SPI_STEP2):
      {   
        ORANGE_LED_OFF();
        SPI_STEP = SPI_STEP1;          
      }                        
  }
  
}


void IRQ_1m(void) // 100 us Handler 
{  
  
  if(MODBUS_COUNTER > 99)
  {
    MODBUS_TRANSMIT_ENABLE = 1 ; 
    
    MODBUS_COUNTER = 0 ; 
  }
  else
  {
    MODBUS_COUNTER ++ ; 
  }
  
  
  MODBUS_TRANSMIT(0x12,0x21,0x22);
  MODBUS_TIMEOUT_COUNTROLLER();
  CLEAR_1m_IRQ_FLAG();    
  BLUE_LED_TOGGLE();    
  
}


void UART4_IRQHandler(void)
{
  TIMEOUT_ENABLE = 1 ; 
  
  if(RX_INDEX < MODBUS_BUFFER_SIZE)
  {
    MODBUS_RX_BUFFER[RX_INDEX] = UART4->DR ; 
    RX_INDEX ++ ; 
  }
  else
  {
    RX_INDEX = 0 ;
    TIMEOUT_ENABLE = 0 ; 
    TIMEOUT_COUNTER= 0 ; 
    
  }
  
}