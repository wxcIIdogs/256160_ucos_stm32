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

extern	OS_TCB	StartUp_TCB;						//�����ջ

static  OS_TCB	keyScan;		   					//����������ƿ�
static	CPU_STK	Key_Stk[TASK_LED1_STK_SIZE];	   	//���������ջ

static  OS_TCB	show_TCB;		   					//����������ƿ�
static	CPU_STK	show_Stk[TASK_LED2_STK_SIZE];	   	//���������ջ

static  OS_TCB	uart_TCB;		   					//����������ƿ�
static	CPU_STK	uart_Stk[TASK_LED3_STK_SIZE];	   	//���������ջ

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
								 
		OSTaskDel(&StartUp_TCB,&err);				//����ɾ���Լ�				 
}


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
        OSTimeDlyHMSM(0, 0,0,200,OS_OPT_TIME_HMSM_STRICT,&err);
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
	
    while (1)
    {
	    OSSemPend(&uartSemEvent,0,OS_OPT_PEND_BLOCKING,0,&err);
	    updateInfoData();
		OSTimeDlyHMSM(0, 0,0,300,OS_OPT_TIME_HMSM_STRICT,&err);
    }
}
/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/

