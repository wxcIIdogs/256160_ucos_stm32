#ifndef  __INCLUDES_H__
#define  __INCLUDES_H__

#include "stm32f10x.h"
#include "stm32f10x_rcc.h"

#include "os.h"  		//uC/OS-IIϵͳ����ͷ�ļ�
#include "os_type.h"  		//uC/OS-IIϵͳ����ͷ�ļ�
#include "BSP.h"			//�뿪������صĺ���
#include "app.h"			//�û�������
#include "led.h"			//LED��������
#include "keyevent.h"
#include "uart.h"
#include "usrtConfig.h"
#include "256160.h"








extern OS_SEM uartSemEvent;
extern UART_FIFO_Typedef_t uart_t;


#endif //__INCLUDES_H__
