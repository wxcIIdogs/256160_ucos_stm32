/******************** (C) COPYRIGHT 2012 WildFire Team **************************
 * �ļ���  ��main.c
 * ����    ��uCOS-III������LED��ˮ�ơ�         
 * ʵ��ƽ̨��Ұ��STM32������
 * ��汾  ��ST3.5.0
 * ϵ   ͳ ��uCOS-III
 * ����    ��wildfire team 
 * ��̳    ��www.ourdev.cn/bbs/bbs_list.jsp?bbs_id=1008
 * �Ա�    ��http://firestm32.taobao.com
**********************************************************************************/
#include "includes.h"



OS_TCB	StartUp_TCB;		   					//����������ƿ�
CPU_STK	StartUp_Stk[STARTUP_TASK_STK_SIZE];		//���������ջ

/* 
 * ��������main
 * ����  : ������
 * ����  ����
 * ���  : ��
 */
int main(void)
{			
		
	OS_ERR err;		
	BSP_Init();			//�弶��ʼ��
	OSInit(&err);		//ϵͳ��ʼ��
	/*��������*/
	OSTaskCreate((OS_TCB     *)&StartUp_TCB,				//������ƿ�ָ��          
                 (CPU_CHAR   *)"StartUp",						//��������
                 (OS_TASK_PTR )Task_Start,					//�������ָ��
                 (void       *)0,							//���ݸ�����Ĳ���parg
                 (OS_PRIO     )STARTUP_TASK_PRIO,			//�������ȼ�
                 (CPU_STK    *)&StartUp_Stk[0],				//�����ջ����ַ
                 (CPU_STK_SIZE)STARTUP_TASK_STK_SIZE/10,	//��ջʣ�ྯ����
                 (CPU_STK_SIZE)STARTUP_TASK_STK_SIZE,		//��ջ��С
                 (OS_MSG_QTY  )0,							//�ɽ��յ������Ϣ������
                 (OS_TICK     )0,							//ʱ��Ƭ��תʱ��
                 (void       *)0,							//������ƿ���չ��Ϣ
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),	 //����ѡ��
                 (OS_ERR     *)&err);						//����ֵ
	
    OSStart(&err);  
  

}
/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/
