#ifndef	_APP_H_
#define	_APP_H_


/*******************设置任务优先级*******************/
#define STARTUP_TASK_PRIO       3
#define	TASK_LED1_PRIO			6	   
#define	TASK_LED2_PRIO			5
#define	TASK_LED3_PRIO			4 
#define	TASK_FACE_PRIO			3 

/************设置栈大小（单位为 OS_STK ）************/
#define STARTUP_TASK_STK_SIZE   1024 
#define	TASK_LED1_STK_SIZE		1024  
#define	TASK_LED2_STK_SIZE		1024
#define	TASK_LED3_STK_SIZE		1024
#define	TASK_FACE_STK_SIZE		1024


/**************** 用户任务声明 *******************/

void Task_Start(void *p_arg);
void Task_key(void *p_arg);
void Task_uart(void *p_arg);
void Task_show(void *p_arg);
void Task_face(void *p_arg);



extern void callback_rev_data(unsigned char ch);

extern int updateInfoData(void );
#endif	//_APP_H_
