#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "periphinit.h"

#define  MODBUS_WAIT 0
#define  MODBUS_WORK 1
#define  MODBUS_BUFFER_SIZE 5 


extern uint8_t TX_ID    ;
extern uint8_t RX_ID    ;
extern uint8_t FUNCTION ;
extern uint8_t DATA     ;
extern uint8_t EOC      ;
extern uint8_t TX_INDEX  ; 
extern uint8_t RX_INDEX  ; 
extern uint8_t MODBUS_STATE   ;
extern uint16_t MODBUS_COUNTER;
extern uint8_t MODBUS_TRANSMIT_ENABLE  ;
extern uint8_t MODBUS_TX_BUFFER[MODBUS_BUFFER_SIZE];
extern uint8_t MODBUS_RX_BUFFER[MODBUS_BUFFER_SIZE];
extern uint16_t TIMEOUT_ENABLE ;
extern uint16_t TIMEOUT_COUNTER ;
void MODBUS_TRANSMIT(uint8_t SLAVE_ID, uint8_t FUNCTION, uint8_t DATA) ;
void MODBUS_TIMEOUT_COUNTROLLER(void);