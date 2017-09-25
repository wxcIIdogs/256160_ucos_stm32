/******************** (C) COPYRIGHT 2012 WildFire Team **************************
 * 文件名  ：bsp.c
 * 描述    ：板级初始化    
 * 实验平台：野火STM32开发板
 * 库版本  ：ST3.5.0
 	系   统：uCOS-III
 *
 * 作者    ：wildfire team 
 * 论坛    ：www.ourdev.cn/bbs/bbs_list.jsp?bbs_id=1008
 * 淘宝    ：http://firestm32.taobao.com
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
//读取设置信息
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
//设置单位	
	setUnit();
//读取测量数据信息	
	STMFLASH_ReadStruct(ceDataStartAdressInfo,&g_ceDataFlash, sizeof(g_ceDataFlash));
	if(g_ceDataFlash.count == 0)
	{
		g_ceDataFlash.startAdress = ceDataStartAdress;
	}

	
}

/*
 * 函数名：BSP_Init
 * 描述  ：时钟初始化、硬件初始化
 * 输入  ：无 
 * 输出  ：无
 */

void BSP_Init(void)
{
  OS_ERR err;
  initData();
  LED_GPIO_Config();  /* LED 端口初始化 */
  USART2_Config();    /* LED 串口初始化 */
  FIFO_UartVarInit(&uart_t,USART2,pxbuff,prbuff,SIZE_SERIAL,SIZE_SERIAL,NULL,NULL,NULL);   /* 串口FIFO初始化 */
  Drow_lcd();     /* 画图，初始化显示屏 */
  SysTick_init();
//淇″彿閲忓垵濮嬪寲
  OSSemCreate(&uartSemEvent,"uartSem",1,&err);

    
}

/*
 * 函数名：SysTick_init
 * 描述  ：配置SysTick定时器
 * 输入  ：无
 * 输出  ：无
 */
void SysTick_init(void)
{
  SysTick_Config(SystemCoreClock/OS_CFG_TICK_RATE_HZ);//初始化并使能SysTick定时器
	if (SysTick_Config(SystemCoreClock/OS_CFG_TICK_RATE_HZ))	// ST3.5.0库版本
	{ 
		/* Capture error */ 
		while (1);
	}
}


/***********时间戳相关函数***************/
//void CPU_TS_TmrInit(void)
//{
//}
//
//uint32_t CPU_TS_TmrRd(void)
//{
//	uint32_t i;
//	return i;
//}

