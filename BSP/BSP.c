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
#include "commom.h"
#include "flash.h"
OS_SEM uartSemEvent;

u8 pxbuff[SIZE_SERIAL] = {0};
u8 prbuff[SIZE_SERIAL] = {0};

UART_FIFO_Typedef_t uart_t;

void initData()
{
//��ȡ������Ϣ
	readFlashStruct();
	FlashInfo *temp = (FlashInfo *)malloc(sizeof(FlashInfo));
	g_node.flashData = temp;
	memcpy(g_node.flashData,&g_initFlashStruct,sizeof(g_initFlashStruct));
	structPlane *plane = (structPlane *)malloc(sizeof(structPlane));
	g_node.PlaneData = plane;
	PareclSurvey *parecl = (PareclSurvey *)malloc(sizeof(PareclSurvey));
	g_node.parcelData = parecl;
	xiePlan *xietemp = (xiePlan *)malloc(sizeof(xiePlan));
	g_node.xieData = xietemp;
//���õ�λ	
	setUnit();
//��ȡ����������Ϣ	
	STMFLASH_ReadStruct(ceDataStartAdressInfo,&g_ceDataFlash, sizeof(g_ceDataFlash));
	if(g_ceDataFlash.count == 0)
	{
		g_ceDataFlash.startAdress = ceDataStartAdress;
	}

	
}

/*
 * ��������BSP_Init
 * ����  ��ʱ�ӳ�ʼ����Ӳ����ʼ��
 * ����  ���� 
 * ���  ����
 */

void BSP_Init(void)
{
  OS_ERR err;
  initData();
  LED_GPIO_Config();  /* LED �˿ڳ�ʼ�� */
  USART2_Config();    /* LED ���ڳ�ʼ�� */
  FIFO_UartVarInit(&uart_t,USART2,pxbuff,prbuff,SIZE_SERIAL,SIZE_SERIAL,NULL,NULL,NULL);   /* ����FIFO��ʼ�� */
  Drow_lcd();     /* ��ͼ����ʼ����ʾ�� */
  SysTick_init();
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

