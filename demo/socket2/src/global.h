/*********************************************
* @�ļ�: global.h
* @����: wuhuiskt
* @�汾: v1.0.1
* @ʱ��: 2019-6-1
* @��Ҫ: ʵ�ְ�����ɾ�Ĳ���߼�
*********************************************/
#ifndef GLOBAL_H
#define GLOBAL_H
	
#ifdef __cplusplus
	extern "C" {
#endif//end __cplusplus

#include "baseType.h"


#define VER		" " //�汾��Ϣ
#define WD_EN	0	//���Ź�ʹ�� �������

#include <string.h>
#include <stdio.h>
#include <api_os.h>
#include <api_event.h>
#include <api_socket.h>
#include "baseType.h"
#include "assert.h"


typedef struct tagAllHandle{
	 HANDLE socketTaskHandle;
	 int a;
	 int b;
}AllHandle;


#ifdef __cplusplus
}
#endif //end __cplusplus

#endif //GLOBAL_H
