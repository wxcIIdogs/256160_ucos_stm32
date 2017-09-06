/******************** (C) COPYRIGHT 2012 WildFire Team **************************
 * �ļ���  ��bsp.c
 * ����    ���弶��ʼ��    
 * ʵ��ƽ̨��Ұ��STM32������
 * ��汾  ��ST3.5.0
 	ϵ   ͳ��uCOS-III
 *
 * ����    ��wildfire team 
 * ��̳    ��www.ourdev.cn/bbs/bbs_list.jsp?bbs_id=1008
 * �Ա�    ��http://firestm32.taobao.com
**********************************************************************************/

#include "includes.h"
#include "os_cfg_app.h"

OS_SEM uartSemEvent;

u8 pxbuff[SIZE_SERIAL] = {0};
u8 prbuff[SIZE_SERIAL] = {0};

UART_FIFO_Typedef_t uart_t;

/*
 * ��������BSP_Init
 * ����  ��ʱ�ӳ�ʼ����Ӳ����ʼ��
 * ����  ����
 * ���  ����
 */

void BSP_Init(void)
{
	OS_ERR err;


 	SysTick_init();
    LED_GPIO_Config();  /* LED �˿ڳ�ʼ�� */
    USART2_Config();
    FIFO_UartVarInit(&uart_t,USART2,pxbuff,prbuff,SIZE_SERIAL,SIZE_SERIAL,NULL,NULL,callback_rev_data);
	Drow_lcd();

//信号量初始化
	OSSemCreate(&uartSemEvent,"uartSem",1,&err);

    
}

/*
 * ��������SysTick_init
 * ����  ������SysTick��ʱ��
 * ����  ����
 * ���  ����
 */
void SysTick_init(void)
{
    SysTick_Config(SystemCoreClock/OS_CFG_TICK_RATE_HZ);//��ʼ����ʹ��SysTick��ʱ��
	if (SysTick_Config(SystemCoreClock/OS_CFG_TICK_RATE_HZ))	// ST3.5.0��汾
	{ 
		/* Capture error */ 
		while (1);
	}
}


/***********ʱ�����غ���***************/
//void CPU_TS_TmrInit(void)
//{
//}
//
//uint32_t CPU_TS_TmrRd(void)
//{
//	uint32_t i;
//	return i;
//}

