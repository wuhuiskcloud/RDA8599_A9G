/*********************************************
* @文件: global.h
* @作者: wuhuiskt
* @版本: v1.0.1
* @时间: 2019-6-1
* @概要: 实现按键增删改查的逻辑
*********************************************/
#ifndef GLOBAL_H
#define GLOBAL_H
	
#ifdef __cplusplus
	extern "C" {
#endif//end __cplusplus

#include "baseType.h"


#define VER		" " //版本信息
#define WD_EN	0	//看门狗使能 方便调试

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
