/*
 * @File  api_mqtt.h
 * @Brief 
 * 
 * @Author: Neucrack 
 * @Date: 2017-12-13 16:19:13 
 * @Last Modified by: Neucrack
 * @Last Modified time: 2017-12-13 16:20:12
 */


#ifndef __API_MQTT_H
#define __API_MQTT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "sdk_init.h"


#define MQTT_ClientNew        CSDK_FUNC(MQTT_ClientNew)
#define MQTT_ClientDestroy    CSDK_FUNC(MQTT_ClientDestroy)
#define MQTT_Connect          CSDK_FUNC(MQTT_Connect)
#define MQTT_Disconnect       CSDK_FUNC(MQTT_Disconnect)
#define MQTT_SetInPubCallback CSDK_FUNC(MQTT_SetInPubCallback)
#define MQTT_Subscribe        CSDK_FUNC(MQTT_Subscribe)
#define MQTT_Unsubscribe      CSDK_FUNC(MQTT_Unsubscribe)
#define MQTT_Publish          CSDK_FUNC(MQTT_Publish)
#define MQTT_IsConnected      CSDK_FUNC(MQTT_IsConnected)

#ifdef __cplusplus
}
#endif

#endif
