/******************** (C) COPYRIGHT 2012 WildFire Team **************************
 * 文件名  ：main.c
 * 描述    ：uCOS-III多任务LED流水灯。         
 * 实验平台：野火STM32开发板
 * 库版本  ：ST3.5.0
 * 系   统 ：uCOS-III
 * 作者    ：wildfire team 
 * 论坛    ：www.ourdev.cn/bbs/bbs_list.jsp?bbs_id=1008
 * 淘宝    ：http://firestm32.taobao.com
**********************************************************************************/
#include "includes.h"



OS_TCB	StartUp_TCB;		   					//定义任务控制块
CPU_STK	StartUp_Stk[STARTUP_TASK_STK_SIZE];		//定义任务堆栈

/* 
 * 函数名：main
 * 描述  : 主函数
 * 输入  ：无
 * 输出  : 无
 */
int main(void)
{			
		
	OS_ERR err;		
	BSP_Init();			//板级初始化
	OSInit(&err);		//系统初始化
	/*创建任务*/
	OSTaskCreate((OS_TCB     *)&StartUp_TCB,				//任务控制块指针          
                 (CPU_CHAR   *)"StartUp",						//任务名称
                 (OS_TASK_PTR )Task_Start,					//任务代码指针
                 (void       *)0,							//传递给任务的参数parg
                 (OS_PRIO     )STARTUP_TASK_PRIO,			//任务优先级
                 (CPU_STK    *)&StartUp_Stk[0],				//任务堆栈基地址
                 (CPU_STK_SIZE)STARTUP_TASK_STK_SIZE/10,	//堆栈剩余警戒线
                 (CPU_STK_SIZE)STARTUP_TASK_STK_SIZE,		//堆栈大小
                 (OS_MSG_QTY  )0,							//可接收的最大消息队列数
                 (OS_TICK     )0,							//时间片轮转时间
                 (void       *)0,							//任务控制块扩展信息
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),	 //任务选项
                 (OS_ERR     *)&err);						//返回值
	
    OSStart(&err);  
  

}
/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/
