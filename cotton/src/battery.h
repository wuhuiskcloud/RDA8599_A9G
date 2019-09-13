/*********************************************
* @文件: battery.h
* @作者: wuhuiskt
* @版本: v1.0.1
* @时间: 2019-09-7
* @概要: 定义进本数据类型
*********************************************/
#ifndef _BATTERY_H
#define _BATTERY_H

#ifdef __cplusplus
extern "C" {
#endif//end __cplusplus

void InitBattery(void);
int ReadBettery(void);

#ifdef __cplusplus
}
#endif//end __cplusplus

#endif //end _BATTERY_H