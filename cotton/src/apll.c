#include "stdbool.h"
#include "stdint.h"
#include "stdio.h"
#include "string.h"

#include "api_os.h"
#include "api_debug.h"
#include "global.h"
#include "network.h"
#include "accelerator.h"
#include "battery.h"


T_S32 ALL_Init(T_VOID **ppvAllHandle)
{
	AllHandle *pstAllHandle = T_NULL;
	ASSERT_EQUAL_RETVAL(ppvAllHandle, T_NULL, RET_FAILED);
    //��ؼ���ʼ��
    InitBattery();
     //I2C �����������ʼ��
    Init_Altr();
    
	pstAllHandle = (AllHandle *)malloc(sizeof(AllHandle));
    pstAllHandle->MainTaskHandle = OS_CreateTask(MainTask, pstAllHandle, NULL, MAIN_TASK_STACK_SIZE, MAIN_TASK_PRIORITY, 0, 0, MAIN_TASK_NAME);
    OS_SetUserMainHandle(&pstAllHandle->MainTaskHandle);
    
	return RET_SUCCESS;
}





