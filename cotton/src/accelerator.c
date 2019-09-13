#include "stdbool.h"
#include "stdint.h"
#include "stdio.h"
#include "string.h"

#include "api_os.h"
#include "api_debug.h"
#include "api_event.h"
#include "api_hal_i2c.h"
#include "global.h"

#define I2C_ACC I2C2

void Init_Altr(void)
{
	
    I2C_Config_t config;

    config.freq = I2C_FREQ_100K;
    I2C_Init(I2C_ACC, config);
}

T_S32 Read_Altr(void)
{
	uint8_t accId;
	//read accelerator chip ID: 0x33
	I2C_ReadMem(I2C_ACC, 0x19, 0x0F, 1, &accId, 1, I2C_DEFAULT_TIME_OUT);
	Trace(1,"accelerator id shold be 0x33, read:0X%02x",accId);
	OS_Sleep(3000);
}