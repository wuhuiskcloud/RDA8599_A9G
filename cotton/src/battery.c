#include "stdbool.h"
#include "stdint.h"
#include "stdio.h"
#include "string.h"

#include "api_os.h"
#include "api_debug.h"
#include "api_event.h"
#include "api_hal_adc.h"


void InitBattery(void)
{
	uint16_t value = 0, mV = 0;    
	ADC_Config_t config = 
	{        
		.channel = ADC_CHANNEL_0,        
		.samplePeriod = ADC_SAMPLE_PERIOD_100MS    
	};   

	ADC_Init(config);
}

int ReadBettery(void)
{
	uint16_t value = 0, mV = 0;
	
	if(ADC_Read(ADC_CHANNEL_0, &value, &mV))  //读到的ADC值和毫伏电压(0-1.8v)
	{
		Trace(1,"ADC value:%d, %dmV",value,mV); 
		return mV;
	}   
	
	OS_Sleep(3000);
	return 0;
}


