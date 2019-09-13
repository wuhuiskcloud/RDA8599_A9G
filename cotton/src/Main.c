
#include "apll.h"

void cotton_Main(void)
{

	T_VOID *pvAllHandle = T_NULL;
	
	if(RET_SUCCESS != ALL_Init(&pvAllHandle))
	{	
		return -1;
	}
	
	//ALL_Run(pvAllHandle);

}

	