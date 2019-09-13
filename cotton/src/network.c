

#include <string.h>
#include <stdio.h>
#include <api_os.h>
#include <api_event.h>
#include <api_socket.h>
#include <api_network.h>
#include <api_debug.h>
#include "api_hal_i2c.h"
#include "global.h"
#include "network.h"
#include "api_info.h"
#include "api_sim.h"



#define TEST_TASK_STACK_SIZE    (2048 * 2)
#define TEST_TASK_PRIORITY      1
#define TEST_TASK_NAME          "Socket Test Task"



int socketFd = -1;
uint8_t buffer[RECEIVE_BUFFER_MAX_LENGTH];
HANDLE sem = NULL;
int errorCode = 0;

static TcpSocketInfo_T stTcpSocketInfo;
static NetworkStatus_T stNetworkStatus;

T_U32 GetNetworkStatus(T_VOID)
{
	return stNetworkStatus.u32EventFlag;
}

T_VOID SetNetworkStatus(T_U32 u32Status)
{
	stNetworkStatus.u32EventFlag = u32Status;
}

void ImeiRead(uint8_t *imei)
{    	
	memset(imei,0,sizeof(imei));        
	INFO_GetIMEI(imei);        
	Trace(1,"%s",imei);        
}

void IccidRead(uint8_t *iccid)
{              
	SIM_GetICCID(iccid);        
	Trace(1,"ICCID:%s",iccid);        
	//OS_Sleep(3000);    
}

void EventDispatch(API_Event_t* pEvent)
{
    switch(pEvent->id)
    {
        case API_EVENT_ID_NO_SIMCARD:
            Trace(10,"!!NO SIM CARD%d!!!!",pEvent->param1);
            SetNetworkStatus(EVT_NO_SIM);
            break;

        case API_EVENT_ID_NETWORK_REGISTERED_HOME:
        case API_EVENT_ID_NETWORK_REGISTERED_ROAMING:
            Trace(2,"network register success");
            Network_StartAttach();
            SetNetworkStatus(EVT_REG_OK);
            break;

        case API_EVENT_ID_NETWORK_ATTACHED:
            Trace(2,"network attach success");
            SetNetworkStatus(EVT_ATTACH_OK);
            Network_PDP_Context_t context = {
                .apn        ="cmnet",
                .userName   = ""    ,
                .userPasswd = ""
            };
            Network_StartActive(context);
            break;

        case API_EVENT_ID_NETWORK_ACTIVATED:
            Trace(2,"network activate success");
            SetNetworkStatus(EVT_ACT_OK);
            // if(sem)
            //     OS_ReleaseSemaphore(sem);
           // sem = 1;
            break;

        case API_EVENT_ID_SOCKET_CONNECTED:
         	SetNetworkStatus(EVT_CONNECT_OK);
            Trace(2,"event connect");
            // if(sem)
            //     OS_ReleaseSemaphore(sem);
            //sem = 1;
            break;

        case API_EVENT_ID_SOCKET_SENT:
        	SetNetworkStatus(EVT_SEND_OK);
            // if(sem)
            //     OS_ReleaseSemaphore(sem);
           // sem = 1;
            Trace(2,"event send");
            break;
        case API_EVENT_ID_SOCKET_RECEIVED:
        {
           // int fd = pEvent->param1;
           // int length = pEvent->param2>RECEIVE_BUFFER_MAX_LENGTH?RECEIVE_BUFFER_MAX_LENGTH:pEvent->param2;
            stTcpSocketInfo.s32SocketFd = pEvent->param1;
            stTcpSocketInfo.u16DataLen = pEvent->param2>RECEIVE_BUFFER_MAX_LENGTH?RECEIVE_BUFFER_MAX_LENGTH:pEvent->param2;
            SetNetworkStatus(EVT_RCV_OK);
            //memset(buffer,0,sizeof(buffer));
            stTcpSocketInfo.u16DataLen = Socket_TcpipRead(stTcpSocketInfo.s32SocketFd, stTcpSocketInfo.u8Buf, stTcpSocketInfo.u16DataLen);
            Trace(2,"socket %d received %d bytes",stTcpSocketInfo.s32SocketFd, stTcpSocketInfo.u16DataLen);
            break;
        }
        case API_EVENT_ID_SOCKET_CLOSED:
        {
            int fd = pEvent->param1;
            SetNetworkStatus(EVT_CLOSE);
            Trace(2,"socket %d closed",fd);
            // if(sem)
            //     OS_ReleaseSemaphore(sem);
            sem = 1;
            break;
        }
        case API_EVENT_ID_SOCKET_ERROR:
        {
            int fd = pEvent->param1;
            SetNetworkStatus(EVT_ERR);
            Trace(2,"socket %d error occurred,cause:%d",fd,pEvent->param2);
            stTcpSocketInfo.s32ErrorCode = pEvent->param2;
            // if(sem)
            //     OS_ReleaseSemaphore(sem);
            sem = 1;
            break;
        }

        case API_EVENT_ID_UART_RECEIVED:   
        {
	        Trace(1,"uart received API_EVENT_ID_UART_RECEIVED:%d",pEvent->param1); 
	        if(pEvent->param1 == UART1)         
	        {                
		        uint8_t data[pEvent->param2+1];                
		        data[pEvent->param2] = 0;                
		        memcpy(data,pEvent->pParam1,pEvent->param2);                
		        UART_Write(UART1,data,pEvent->param2);                
		        Trace(1,"uart received data,length:%d,data:%s",pEvent->param2,data);
	        }
			break;   
        }            
        default:
            break;
    }
}

void CreateSem(HANDLE* sem_)
{
    *sem_ = 0;
    // *sem = OS_CreateSemaphore(0);
}

void WaitSem(HANDLE* sem_)
{
    // OS_WaitForSemaphore(*sem,OS_WAIT_FOREVER);
    // OS_DeleteSemaphore(*sem);
    // *sem = NULL;
    while(*sem_ == 0)
        OS_Sleep(1);
    *sem_ = 0;
}

bool Close(int socketfd)
{    
	//CreateSem(&sem);    
	Socket_TcpipClose(socketfd);    
	//WaitSem(&sem);    
	return true;
}

bool Connect(T_S32 *ps32SocketFds)
{
	char ipInfo[32] = {0};
	//int socketFds = 0;
	int DelayConut = 200;
	int ret=-1;
   // memset(buffer,0,sizeof(buffer));
    while(1)
    {
    	Trace(2, "DNS start get hostname %s\n", DNS_DOMAIN);
	    if(DNS_GetHostByName2(DNS_DOMAIN, ipInfo) != 0)
	    {
	    	Trace(3,"DNS_GetHostByName2 is failed\n");
	    	OS_SleepUs(DelayConut);
	    	if(DelayConut < 3000)
	    	{
	    		DelayConut += 200;
	    	}
	    	
	        continue;
	    }
	    
	    Trace(2,"DNS,domain:%s,ip:%s:%d,strlen(ip)",DNS_DOMAIN, ipInfo, strlen(ipInfo));
	    //CreateSem(&sem);
	    *ps32SocketFds = Socket_TcpipConnect(TCP, ipInfo, SERVER_PORT);
	    Trace(2,"connect tcp server,socketFd:%d", *ps32SocketFds);
	   // WaitSem(&sem);
	    DelayConut = 100;
	    while(1)
	    {
			//if(GetNetworkStatus() != EVT_CONNECT_OK )
		   	//{   	
				OS_SleepUs(1000);
		   	//}

		   	if(GetNetworkStatus() == EVT_CONNECT_OK )
		   	{
		   		Trace(2,"connect successful \n");
		   		ret = RET_SUCCESS;
				break;
		   	}

			if(GetNetworkStatus() == EVT_ERR)
			{
				Trace(2,"connect error %d \n", stTcpSocketInfo.s32ErrorCode);
				ret = RET_FAILED;
				Close(*ps32SocketFds);
				break;
			}

	    }

	   if(ret == RET_FAILED)
	   {
			continue;
	   }else if(ret == RET_SUCCESS)
	   {
			break;
	   }
	   
    }
    
    return true;
}

bool Write(T_S32 s32SocketFd, uint8_t* data, uint16_t len)
{
    Trace(2,"Write");
    //CreateSem(&sem);
    
    int ret = Socket_TcpipWrite(s32SocketFd, data, len);
    if(ret <= 0)
    {
        Trace(2,"socket write fail:%d",ret);
        return false;
    }    
    Trace(2,"### socket %d send %d bytes data to server:%s,ret:%d",s32SocketFd, len, data,ret);
    //WaitSem(&sem);
    //Trace(2,"### write end");
    /*if(errorCode != 0)
    {
        errorCode = 0;
        Trace(2,"error ocurred");
        return false;
    }*/
    
    if(stTcpSocketInfo.s32ErrorCode !=0)
    {
        Trace(2,"error ocurred %d\n", stTcpSocketInfo.s32ErrorCode);
        stTcpSocketInfo.s32ErrorCode = 0;
        Close(s32SocketFd);
        return false;
    }
    
    return true;
}

uint16_t Read(uint8_t* data, uint16_t len)
{
	T_U16 u16DataLen = 0;
	
	ASSERT_EQUAL_RETVAL(data, T_NULL, 0);
	ASSERT_EQUAL_RETVAL(len, 0, 0);
	
	if(GetNetworkStatus() == EVT_RCV_OK)
	{
		if(stTcpSocketInfo.u16DataLen > len)
		{
			memcpy(data, stTcpSocketInfo.u8Buf, len);
			u16DataLen = len;
		}else{
			memcpy(data, stTcpSocketInfo.u8Buf, stTcpSocketInfo.u16DataLen);
			u16DataLen = stTcpSocketInfo.u16DataLen;
		}
	}

	memset(stTcpSocketInfo.u8Buf, 0, sizeof(stTcpSocketInfo.u8Buf));
	stTcpSocketInfo.u16DataLen = 0;
	
	return u16DataLen;
}

void NetworkTask(void* param)
{
    int failCount = 0;
    int count = 0;
    T_S32 s32ScokectFd = -1;
	AllHandle *pstAllHandle = (AllHandle *)param;
    //WaitSem(&sem);
    //Trace(2,"sem:%d,%p",(int)sem,(void*)sem);
    //Trace(1,"start connect now");
    
    while(GetNetworkStatus() != EVT_ACT_OK)
    {
    	OS_Sleep(1);
    }
    
    ImeiRead(pstAllHandle->imei);  
    IccidRead(pstAllHandle->iccid);
    
    Trace(1,"start connect now");
   
    Connect(&s32ScokectFd);
    
    while(1)
    {
        if(failCount == 5)
        {
            Close(s32ScokectFd);
        }
        if(failCount >= 5)
        {
            if(Connect(&s32ScokectFd))
                failCount = 0;
            else
                ++failCount;
        }
        else
        {
            if(!Write(s32ScokectFd, "test string test string \r\n",strlen("test string test string \r\n")))
            {
                ++failCount;
                Trace(2,"write fail");
            }
        }
        Trace(2,"count:%d",count++);
        OS_Sleep(5000);
    }
}


void MainTask(void *pData)
{
    API_Event_t* event=NULL;
	AllHandle *pstAllHandle = (AllHandle *)pData;
	
    CreateSem(&sem);
    OS_CreateTask(NetworkTask,
        pData, NULL, TEST_TASK_STACK_SIZE, TEST_TASK_PRIORITY, 0, 0, TEST_TASK_NAME);
    while(1)
    {
        if(OS_WaitEvent(pstAllHandle->MainTaskHandle, (void**)&event, OS_TIME_OUT_WAIT_FOREVER))
        {
            EventDispatch(event);
            OS_Free(event->pParam1);
            OS_Free(event->pParam2);
            OS_Free(event);
        }
    }
}

