#include "stdbool.h"
#include "stdint.h"
#include "stdio.h"
#include "string.h"

#include "api_os.h"
#include "api_debug.h"
#include "global.h"

T_S32 ALL_Init(T_VOID **ppvAllHandle)
{
	AllHandle *pstAllHandle = T_NULL;
	ASSERT_EQUAL_RETVAL(ppvAllHandle, T_NULL, RET_FAILED);
    //I2C Çý¶¯³õÊ¼»¯
	pstAllHandle = (AllHandle *)malloc(sizeof(AllHandle));

	
    pstAllHandle->socketTaskHandle = OS_CreateTask(socket_MainTask,
        NULL, NULL, MAIN_TASK_STACK_SIZE, MAIN_TASK_PRIORITY, 0, 0, MAIN_TASK_NAME);
    OS_SetUserMainHandle(& pstAllHandle->socketTaskHandle);
	return RET_SUCCESS£»
}





