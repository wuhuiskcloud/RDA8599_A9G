/*********************************************
* @�ļ�: network.h
* @����: wuhuiskt
* @�汾: v1.0.1
* @ʱ��: 2019-9-2
* @��Ҫ: ʵ�ְ�����ɾ�Ĳ���߼�
*********************************************/
#ifndef NETWORK_H
#define NETWORK_H
	
#ifdef __cplusplus
	extern "C" {
#endif//end __cplusplus

#include "baseType.h"

/*******************************************************************/
/////////////////////////socket configuration////////////////////////

//#define DNS_DOMAIN  "47.97.154.253"
//#define SERVER_PORT 4430

//122.114.122.174 
#define DNS_DOMAIN  "122.114.122.174 "
#define SERVER_PORT 33397
/*******************************************************************/

#define MAIN_TASK_STACK_SIZE    (2048 * 2)
#define MAIN_TASK_PRIORITY      0
#define MAIN_TASK_NAME          "Socket Test Main Task"
#define RECEIVE_BUFFER_MAX_LENGTH 200

typedef enum tagNetworkStatus{
	EVT_NONE=0x00,
	EVT_NO_SIM=0x01,
	EVT_REG_OK,   //ע��ɹ�
	EVT_ATTACH_OK,  //�����ɹ�
	EVT_ACT_OK,      //����ɹ�
	EVT_CONNECT_OK, //��������
	EVT_SEND_OK,    //���Է�������
	EVT_RCV_OK,     //��������
	EVT_CLOSE,
	EVT_ERR,
}NetworkStatus_E;

typedef struct tagNetwork{
	T_U32 u32EventFlag; //�����¼���ʶ
}NetworkStatus_T;

typedef struct tagTcpSocketInfo{
	T_U8 u8Buf[RECEIVE_BUFFER_MAX_LENGTH];
	T_S32 s32SocketFd;
	T_U16 u16DataLen;
	T_S32 s32ErrorCode;
}TcpSocketInfo_T;

typedef int (*NetworkFunc)(NetworkStatus_E evt, T_VOID *pvData);

void MainTask(void *pData);

#ifdef __cplusplus
}
#endif //end __cplusplus

#endif //NETWORK_H


