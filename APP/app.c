/******************** (C) COPYRIGHT 2012 WildFire Team **************************
 * 文件名  ：app.c
 * 描述    ：LED单任务    
 * 实验平台：野火STM32开发板
 * 库版本  ：ST3.5.0
 系   统   ：uCOS-III
 *
 * 作者    ：wildfire team 
 * 论坛    ：www.ourdev.cn/bbs/bbs_list.jsp?bbs_id=1008
 * 淘宝    ：http://firestm32.taobao.com
**********************************************************************************/
#include "includes.h"
#include "commom.h"
extern	OS_TCB	StartUp_TCB;						//任务堆栈

static  OS_TCB	keyScan;		   					//定义任务控制块
static	CPU_STK	Key_Stk[TASK_LED1_STK_SIZE];	   	//定义任务堆栈

static  OS_TCB	show_TCB;		   					//定义任务控制块
static	CPU_STK	show_Stk[TASK_LED2_STK_SIZE];	   	//定义任务堆栈

static  OS_TCB	uart_TCB;		   					//定义任务控制块
static	CPU_STK	uart_Stk[TASK_LED3_STK_SIZE];	   	//定义任务堆栈

static  OS_TCB	face_TCB;		   					//定义任务控制块
static	CPU_STK	face_Stk[TASK_LED3_STK_SIZE];	   	//定义任务堆栈

/* 
 * 函数名：Task_Start
 * 描述  : 	启动任务，
 			优先级为3，
			创建LED1、LED2和LED3的任务
 * 输入  ：无
 * 输出  : 无
 */
void Task_Start(void *p_arg)
{
	OS_ERR err;
    (void)p_arg;                		// 'p_arg' 并没有用到，防止编译器提示警告
	CPU_SR_ALLOC();
	OS_CRITICAL_ENTER(); 
	//创建任务LED1	
	OSTaskCreate((OS_TCB     *)&keyScan,					//任务控制块指针          
                 (CPU_CHAR   *)"keyscan",						//任务名称
                 (OS_TASK_PTR )Task_key,					//任务代码指针
                 (void       *)0,							//传递给任务的参数parg
                 (OS_PRIO     )TASK_LED1_PRIO,				//任务优先级
                 (CPU_STK    *)&Key_Stk[0],				//任务堆栈基地址
                 (CPU_STK_SIZE)TASK_LED1_STK_SIZE/10,		//堆栈剩余警戒线
                 (CPU_STK_SIZE)TASK_LED1_STK_SIZE,			//堆栈大小
                 (OS_MSG_QTY  )0,							//可接收的最大消息队列数
                 (OS_TICK     )0,							//时间片轮转时间
                 (void       *)0,							//任务控制块扩展信息
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),	 //任务选项
                 (OS_ERR     *)&err);						//返回值

	//创建任务LED2	
	OSTaskCreate((OS_TCB     *)&show_TCB,					//任务控制块指针          
                 (CPU_CHAR   *)"showtcb",						//任务名称
                 (OS_TASK_PTR )Task_show,					//任务代码指针
                 (void       *)0,							//传递给任务的参数parg
                 (OS_PRIO     )TASK_LED2_PRIO,				//任务优先级
                 (CPU_STK    *)&show_Stk[0],				//任务堆栈基地址
                 (CPU_STK_SIZE)TASK_LED2_STK_SIZE/10,		//堆栈剩余警戒线
                 (CPU_STK_SIZE)TASK_LED2_STK_SIZE,			//堆栈大小
                 (OS_MSG_QTY  )0,							//可接收的最大消息队列数
                 (OS_TICK     )0,							//时间片轮转时间
                 (void       *)0,							//任务控制块扩展信息
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),	 //任务选项
                 (OS_ERR     *)&err);						//返回值

	//创建任务LED3	
	OSTaskCreate((OS_TCB     *)&uart_TCB,					//任务控制块指针          
                 (CPU_CHAR   *)"uart",						//任务名称
                 (OS_TASK_PTR )Task_uart,					//任务代码指针
                 (void       *)0,							//传递给任务的参数parg
                 (OS_PRIO     )TASK_LED3_PRIO,				//任务优先级
                 (CPU_STK    *)&uart_Stk[0],				//任务堆栈基地址
                 (CPU_STK_SIZE)TASK_LED3_STK_SIZE/10,		//堆栈剩余警戒线
                 (CPU_STK_SIZE)TASK_LED3_STK_SIZE,			//堆栈大小
                 (OS_MSG_QTY  )0,							//可接收的最大消息队列数
                 (OS_TICK     )0,							//时间片轮转时间
                 (void       *)0,							//任务控制块扩展信息
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),	 //任务选项
                 (OS_ERR     *)&err);						//返回值
   //任务4    
	OSTaskCreate((OS_TCB     *)&face_TCB,					//任务控制块指针          
                 (CPU_CHAR   *)"face",						//任务名称
                 (OS_TASK_PTR )Task_face,					//任务代码指针
                 (void       *)0,							//传递给任务的参数parg
                 (OS_PRIO     )TASK_FACE_PRIO,				//任务优先级
                 (CPU_STK    *)&face_Stk[0],				//任务堆栈基地址
                 (CPU_STK_SIZE)TASK_FACE_STK_SIZE/10,		//堆栈剩余警戒线
                 (CPU_STK_SIZE)TASK_FACE_STK_SIZE,			//堆栈大小
                 (OS_MSG_QTY  )0,							//可接收的最大消息队列数
                 (OS_TICK     )0,							//时间片轮转时间
                 (void       *)0,							//任务控制块扩展信息
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),	 //任务选项
                 (OS_ERR     *)&err);						//返回值
		OS_CRITICAL_EXIT();						 
		OSTaskDel(&StartUp_TCB,&err);				//任务删除自己				 
}

//Task_face

void Task_key(void *p_arg)
{
	OS_ERR err;
    (void)p_arg;                	
	
     while (1)
    {
		scanKeyEvent();
        OSTimeDlyHMSM(0, 0,0,50,OS_OPT_TIME_HMSM_STRICT,&err); 
				      
    }
}

void Task_show(void *p_arg)
{
	OS_ERR err;
    (void)p_arg;                	
	
    while (1)
    {  
	    OSSemPend(&uartSemEvent,100,OS_OPT_PEND_BLOCKING,0,&err);//wait 100ms
	   	if(err == OS_ERR_TIMEOUT)
	   	{ //娌℃湁绛夊埌鏁版嵁
	   		
	   	}
	    updateInfoData();
      OSTimeDlyHMSM(0, 0,0,60,OS_OPT_TIME_HMSM_STRICT,&err);
    }
}

/* 
 * 函数名：Task_LED3
 * 描述  : 	LED任务3，
 			优先级为6，
			以300ms的间隔点亮、关闭LED3
 * 输入  ：无
 * 输出  : 无
 */
void Task_uart(void *p_arg)
{
	OS_ERR err;
 (void)p_arg;      
	u8 ch = 0;
    while (1)
    {	 	    
	    while(FIFO_UartReadByte(&uart_t,&ch) == HAL_OK)
			{
				callback_rev_data(ch);
				OSTimeDlyHMSM(0, 0,0,1,OS_OPT_TIME_HMSM_STRICT,&err);
			}
			OSTimeDlyHMSM(0, 0,0,10,OS_OPT_TIME_HMSM_STRICT,&err);
    }
}


void Task_face(void *p_arg)
{
	OS_ERR err;
 	(void)p_arg;      
	FACE_ENUM index;
	index = Draw_face(MAINMENU);
	while (1)
	{	 	        	    
		index = Draw_face(index);    	
		OSTimeDlyHMSM(0, 0,0,30,OS_OPT_TIME_HMSM_STRICT,&err);
	}
}

/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/

