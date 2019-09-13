/*********************************************
* @文件: apll.h
* @作者: wuhuiskt
* @版本: v1.0.1
* @时间: 2017-12-4
* @概要: 实现应用逻辑层的业务功
                   能，组织个每一个状态逻
                   辑。
*********************************************/
#ifndef APLL_H
#define APLL_H
	
#ifdef __cplusplus
	extern "C" {
#endif//end __cplusplus

#include "baseType.h"


/********************************************
 *功能：上层应用逻辑层初始化接口
 *输入：应用逻辑层handle
 *输出：无
 *条件：无
 *返回：无
 注意:无
********************************************/
T_S32 ALL_Init(T_VOID **ppvAllHandle);



#ifdef __cplusplus
}
#endif //end __cplusplus

#endif //APLL_H
