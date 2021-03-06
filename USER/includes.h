#ifndef  __INCLUDES_H__
#define  __INCLUDES_H__

#include "stm32f10x.h"
#include "stm32f10x_rcc.h"

#include "os.h"  		//uC/OS-II系统函数头文件
#include "os_type.h"  		//uC/OS-II系统函数头文件
#include "BSP.h"			//与开发板相关的函数
#include "app.h"			//用户任务函数
#include "led.h"			//LED驱动函数
#include "keyevent.h"
#include "uart.h"
#include "usrtConfig.h"
#include "256160.h"








extern OS_SEM uartSemEvent;
extern UART_FIFO_Typedef_t uart_t;


#endif //__INCLUDES_H__
