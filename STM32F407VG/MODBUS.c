#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "periphinit.h"


uint16_t TIMEOUT_ENABLE  = 0 ; 
uint16_t TIMEOUT_COUNTER = 0 ; 
uint16_t MODBUS_COUNTER  = 0 ; 

uint8_t TX_INDEX                 = 0x00; 
uint8_t RX_INDEX                 = 0x00; 
uint8_t MODBUS_STATE             = 0x00;

uint8_t TX_ID                    = 0x32;
uint8_t SLAVE_ID                 = 0x00;
uint8_t FUNCTION                 = 0x00;
uint8_t DATA                     = 0x00;
uint8_t EOC                      = 0xAA;
uint8_t MODBUS_TRANSMIT_ENABLE   = 0x00;

uint8_t MODBUS_TX_BUFFER[MODBUS_BUFFER_SIZE]  ; 
uint8_t MODBUS_RX_BUFFER[MODBUS_BUFFER_SIZE];

void MODBUS_TRANSMIT(uint8_t SLAVE_ID, uint8_t FUNCTION, uint8_t DATA)
{  
  if(MODBUS_TRANSMIT_ENABLE)
  {
    MODBUS_TX_BUFFER[0] = TX_ID ; 
    MODBUS_TX_BUFFER[1] = SLAVE_ID  ; 
    MODBUS_TX_BUFFER[2] = FUNCTION ; 
    MODBUS_TX_BUFFER[3] = DATA ; 
    MODBUS_TX_BUFFER[4] = EOC ; 
    
    
    
    switch(MODBUS_STATE)
    {
      case(MODBUS_WAIT):
        {
          MODBUS_STATE=MODBUS_WORK; 
          break;
        }
      case(MODBUS_WORK):
        {                 
          if(TX_INDEX < MODBUS_BUFFER_SIZE)
          {
            UART4->DR = *(MODBUS_TX_BUFFER+TX_INDEX) ; 
            TX_INDEX ++ ;
          }
          else
          {
            MODBUS_TRANSMIT_ENABLE = 0 ; 
            TX_INDEX     = 0 ;                        
          }      
          
          MODBUS_STATE = MODBUS_WAIT ; 
          break;
        }
    }
  }
  
  
  else
  {
    __ASM("NOP");    
  }
  
}

void MODBUS_TIMEOUT_COUNTROLLER(void)
{
  if(TIMEOUT_ENABLE)
  {
    if(TIMEOUT_COUNTER < 10)
    {
      TIMEOUT_COUNTER ++ ;
    }
    else
    {
      if(RX_INDEX != 0x05)
      {
        TIMEOUT_COUNTER= 0 ; 
        TIMEOUT_ENABLE = 0 ; 
        RX_INDEX = 0 ;
        MODBUS_RX_BUFFER[0]= 0x00;
        MODBUS_RX_BUFFER[1]= 0x00;
        MODBUS_RX_BUFFER[2]= 0x00;
        MODBUS_RX_BUFFER[3]= 0x00;
        MODBUS_RX_BUFFER[4]= 0x00;
        
      }
      else
      {
          __ASM("NOP");
      }
    }
  }
}