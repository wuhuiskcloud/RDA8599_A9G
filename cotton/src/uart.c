#include <api_os.h>
#include <api_hal_uart.h>
#include <api_debug.h>
#include <string.h>
#include <stdio.h>
#define USE_EVENT 1

#if USE_EVENT
#include "api_os.h"
#include "api_event.h"
#endif

static void OnUart1ReceivedData(UART_Callback_Param_t param)
{    
	UART_Write(UART1,param.buf,param.length);    
	Trace(1,"uart1 interrupt received data,length:%d,read:,data:%s",param.length,param.buf);
}


UART_Config_t config = {        
	.baudRate = UART_BAUD_RATE_115200,        
	.dataBits = UART_DATA_BITS_8,        
	.stopBits = UART_STOP_BITS_1,        
	.parity   = UART_PARITY_NONE,        
	.rxCallback = OnUart1ReceivedData,        
	.useEvent = false,    
};    

uint32_t times = 0;

#if USE_EVENT    
API_Event_t* event=NULL;    
config.useEvent = true;    
config.rxCallback = NULL;
#endif    

UART_Init(UART1,config);    
config.rxCallback = NULL;    
UART_Init(UART2,config);


  