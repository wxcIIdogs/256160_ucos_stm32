/******************** (C) COPYRIGHT 2012 WildFire Team **************************
 * �ļ���  ��app.c
 * ����    ��LED������    
 * ʵ��ƽ̨��Ұ��STM32������
 * ��汾  ��ST3.5.0
 ϵ   ͳ   ��uCOS-III
 *
 * ����    ��wildfire team 
 * ��̳    ��www.ourdev.cn/bbs/bbs_list.jsp?bbs_id=1008
 * �Ա�    ��http://firestm32.taobao.com
**********************************************************************************/
#include "includes.h"
#include "commom.h"
extern	OS_TCB	StartUp_TCB;						//�����ջ

static  OS_TCB	keyScan;		   					//����������ƿ�
static	CPU_STK	Key_Stk[TASK_LED1_STK_SIZE];	   	//���������ջ

static  OS_TCB	show_TCB;		   					//����������ƿ�
static	CPU_STK	show_Stk[TASK_LED2_STK_SIZE];	   	//���������ջ

static  OS_TCB	uart_TCB;		   					//����������ƿ�
static	CPU_STK	uart_Stk[TASK_LED3_STK_SIZE];	   	//���������ջ

static  OS_TCB	face_TCB;		   					//����������ƿ�
static	CPU_STK	face_Stk[TASK_LED3_STK_SIZE];	   	//���������ջ

/* 
 * ��������Task_Start
 * ����  : 	��������
 			���ȼ�Ϊ3��
			����LED1��LED2��LED3������
 * ����  ����
 * ���  : ��
 */
void Task_Start(void *p_arg)
{
	OS_ERR err;
    (void)p_arg;                		// 'p_arg' ��û���õ�����ֹ��������ʾ����
	CPU_SR_ALLOC();
	OS_CRITICAL_ENTER(); 
	//��������LED1	
	OSTaskCreate((OS_TCB     *)&keyScan,					//������ƿ�ָ��          
                 (CPU_CHAR   *)"keyscan",						//��������
                 (OS_TASK_PTR )Task_key,					//�������ָ��
                 (void       *)0,							//���ݸ�����Ĳ���parg
                 (OS_PRIO     )TASK_LED1_PRIO,				//�������ȼ�
                 (CPU_STK    *)&Key_Stk[0],				//�����ջ����ַ
                 (CPU_STK_SIZE)TASK_LED1_STK_SIZE/10,		//��ջʣ�ྯ����
                 (CPU_STK_SIZE)TASK_LED1_STK_SIZE,			//��ջ��С
                 (OS_MSG_QTY  )0,							//�ɽ��յ������Ϣ������
                 (OS_TICK     )0,							//ʱ��Ƭ��תʱ��
                 (void       *)0,							//������ƿ���չ��Ϣ
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),	 //����ѡ��
                 (OS_ERR     *)&err);						//����ֵ

	//��������LED2	
	OSTaskCreate((OS_TCB     *)&show_TCB,					//������ƿ�ָ��          
                 (CPU_CHAR   *)"showtcb",						//��������
                 (OS_TASK_PTR )Task_show,					//�������ָ��
                 (void       *)0,							//���ݸ�����Ĳ���parg
                 (OS_PRIO     )TASK_LED2_PRIO,				//�������ȼ�
                 (CPU_STK    *)&show_Stk[0],				//�����ջ����ַ
                 (CPU_STK_SIZE)TASK_LED2_STK_SIZE/10,		//��ջʣ�ྯ����
                 (CPU_STK_SIZE)TASK_LED2_STK_SIZE,			//��ջ��С
                 (OS_MSG_QTY  )0,							//�ɽ��յ������Ϣ������
                 (OS_TICK     )0,							//ʱ��Ƭ��תʱ��
                 (void       *)0,							//������ƿ���չ��Ϣ
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),	 //����ѡ��
                 (OS_ERR     *)&err);						//����ֵ

	//��������LED3	
	OSTaskCreate((OS_TCB     *)&uart_TCB,					//������ƿ�ָ��          
                 (CPU_CHAR   *)"uart",						//��������
                 (OS_TASK_PTR )Task_uart,					//�������ָ��
                 (void       *)0,							//���ݸ�����Ĳ���parg
                 (OS_PRIO     )TASK_LED3_PRIO,				//�������ȼ�
                 (CPU_STK    *)&uart_Stk[0],				//�����ջ����ַ
                 (CPU_STK_SIZE)TASK_LED3_STK_SIZE/10,		//��ջʣ�ྯ����
                 (CPU_STK_SIZE)TASK_LED3_STK_SIZE,			//��ջ��С
                 (OS_MSG_QTY  )0,							//�ɽ��յ������Ϣ������
                 (OS_TICK     )0,							//ʱ��Ƭ��תʱ��
                 (void       *)0,							//������ƿ���չ��Ϣ
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),	 //����ѡ��
                 (OS_ERR     *)&err);						//����ֵ
   //����4    
	OSTaskCreate((OS_TCB     *)&face_TCB,					//������ƿ�ָ��          
                 (CPU_CHAR   *)"face",						//��������
                 (OS_TASK_PTR )Task_face,					//�������ָ��
                 (void       *)0,							//���ݸ�����Ĳ���parg
                 (OS_PRIO     )TASK_FACE_PRIO,				//�������ȼ�
                 (CPU_STK    *)&face_Stk[0],				//�����ջ����ַ
                 (CPU_STK_SIZE)TASK_FACE_STK_SIZE/10,		//��ջʣ�ྯ����
                 (CPU_STK_SIZE)TASK_FACE_STK_SIZE,			//��ջ��С
                 (OS_MSG_QTY  )0,							//�ɽ��յ������Ϣ������
                 (OS_TICK     )0,							//ʱ��Ƭ��תʱ��
                 (void       *)0,							//������ƿ���չ��Ϣ
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),	 //����ѡ��
                 (OS_ERR     *)&err);						//����ֵ
		OS_CRITICAL_EXIT();						 
		OSTaskDel(&StartUp_TCB,&err);				//����ɾ���Լ�				 
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
	   	{ //没有等到数据
	   		
	   	}
	    updateInfoData();
      OSTimeDlyHMSM(0, 0,0,60,OS_OPT_TIME_HMSM_STRICT,&err);
    }
}

/* 
 * ��������Task_LED3
 * ����  : 	LED����3��
 			���ȼ�Ϊ6��
			��300ms�ļ���������ر�LED3
 * ����  ����
 * ���  : ��
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

