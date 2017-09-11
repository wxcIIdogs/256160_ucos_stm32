#include "256160.h"
#include "drawSysSet.h"
#include "includes.h"

int draw_return_cancel_ok()
{
	
}

void draw_sysset_menu(u8 data[][50],int x ,int y,int len)
{
	for(int i = 0;i <len ; i ++)
	{
		setCurrentIndex(x,y);	
		printf("%s:",data[i]);
		y+=2;
	}
}
void draw_sysSet_data_menu(u8 data[6],int x, int y ,int flag)
{
	setCurrentIndex(x,y);
	setBackColor(1-flag);
	printf("%s",data);
}
void draw_sysSet_num_menu(double data,int x,int y ,int flag)
{
	setCurrentIndex(x,y);
	setBackColor(1-flag);
	printf("%.2lf",data);
	setBackColor(1);
}


//度量单位
u8 array_unitmeasure[][50] = {{"areaunit"},{"lengthuint"},{"tijiuunit"}};
u8 array_area[][6] = {{"ping"},{"mu"},{"damu"},{"gong"}};
u8 array_len[][6] = {{"mi"},{"ying"}};
u8 array_tiji[][6] = {{"fang"}};


FACE_ENUM draw_unitmeasure_face(Inode *node, structFaceInfo *info)
{
	OS_ERR err;
	register_key_event(info->id , main_menu_keyEvent, KEY_ALL);   //注册按键

	draw_line_y(3);	
	draw_sysset_menu(array_unitmeasure,1,4,3);
	draw_sysSet_data_menu(array_area[0],75,4,0);
	draw_sysSet_data_menu(array_len[0],75,6,0);
	draw_sysSet_data_menu(array_tiji[0],75,8,0);	
	while(1)
	{		
		OSTimeDlyHMSM(0, 0,1,30,OS_OPT_TIME_HMSM_STRICT,&err);
		if(getEndflag() & KEY_CANCEL)
		{			
			return (FACE_ENUM)g_currentFace->list->pro->id;;
		}
		if(getEndflag() & KEY_ENTER)
		{
			
		}
	}	
}
//电台频道
u8 array_board[][50] = {{"channel"}};
FACE_ENUM draw_boardchannel_face(Inode *node, structFaceInfo *info)
{
	OS_ERR err;
	register_key_event(info->id , main_menu_keyEvent, KEY_ALL);   //注册按键

	draw_line_y(3);	
	draw_sysset_menu(array_board,60,8,1);
	
	draw_sysSet_num_menu(8.0,150,8,0);
	while(1)
	{		
		OSTimeDlyHMSM(0, 0,1,30,OS_OPT_TIME_HMSM_STRICT,&err);
		if(getEndflag() & KEY_CANCEL)
		{			
			return (FACE_ENUM)g_currentFace->list->pro->id;;
		}
		if(getEndflag() & KEY_ENTER)
		{
			
		}
	}	
}


//铲斗宽度
u8 array_bucketwidght[][50] = {{"bucketwi    M"}};

FACE_ENUM draw_bucketwidght_face(Inode *node, structFaceInfo *info)
{
	OS_ERR err;
	register_key_event(info->id , main_menu_keyEvent, KEY_ALL);   //注册按键

	draw_line_y(3);	
	draw_sysset_menu(array_bucketwidght,60,8,1);
	draw_sysSet_num_menu(3.50,120,8,0);
	while(1)
	{		
		OSTimeDlyHMSM(0, 0,1,30,OS_OPT_TIME_HMSM_STRICT,&err);
		if(getEndflag() & KEY_CANCEL)
		{			
			return (FACE_ENUM)g_currentFace->list->pro->id;;
		}
		if(getEndflag() & KEY_ENTER)
		{
			
		}
	}	
}


//天线位置

u8 array_antlocal[][50] = {{"stat recvive nat in "},{"pianliweizhi"},{"dingyizhengfu:fafadsadasds"}};


FACE_ENUM draw_antlocal_face(Inode *node, structFaceInfo *info)
{
	OS_ERR err;
	register_key_event(info->id , main_menu_keyEvent, KEY_ALL);   //注册按键

	draw_line_y(3);	
	draw_sysset_menu(array_antlocal,1,4,2);
	draw_sysSet_num_menu(3.50,60,8,1);
	draw_sysset_menu(array_antlocal+2,1,10,1);
	while(1)
	{		
		OSTimeDlyHMSM(0, 0,1,30,OS_OPT_TIME_HMSM_STRICT,&err);
		if(getEndflag() & KEY_CANCEL)
		{			
			return (FACE_ENUM)g_currentFace->list->pro->id;;
		}
		if(getEndflag() & KEY_ENTER)
		{
			
		}
	}	
}

//升降速度校准

u8 array_roisedownadj[][50] = {{"shangsheng:      m/s "},{"xiajiang     m/s"}};


FACE_ENUM draw_roisedownadj_face(Inode *node, structFaceInfo *info)
{
	OS_ERR err;
	register_key_event(info->id , main_menu_keyEvent, KEY_ALL);   //注册按键

	draw_line_y(3);	
	draw_sysset_menu(array_roisedownadj,1,4,1);	draw_sysset_menu(array_roisedownadj+1,120,4,1);
	draw_sysset_menu(array_roisedownadj,1,6,1);	draw_sysset_menu(array_roisedownadj+1,120,6,1);
	draw_sysset_menu(array_roisedownadj,1,8,1);	draw_sysset_menu(array_roisedownadj+1,120,8,1);
	draw_sysset_menu(array_roisedownadj,1,10,1);  draw_sysset_menu(array_roisedownadj+1,120,10,1);


	while(1)
	{		
		OSTimeDlyHMSM(0, 0,1,30,OS_OPT_TIME_HMSM_STRICT,&err);
		if(getEndflag() & KEY_CANCEL)
		{			
			return (FACE_ENUM)g_currentFace->list->pro->id;;
		}
		if(getEndflag() & KEY_ENTER)
		{
			
		}
	}	
}


//时间设置
u8 array_timeset[][50] = {{"shiqu:"},{"xialingshi:"}};
u8 array_timeslect[][50] = {{"+8 beijin/xiangg/taibei/xinjiapo"}};



FACE_ENUM draw_timeset_face(Inode *node, structFaceInfo *info)
{
	OS_ERR err;
	register_key_event(info->id , main_menu_keyEvent, KEY_ALL);   //注册按键

	draw_line_y(3);	
	draw_sysset_menu(array_roisedownadj,1,4,2);
	draw_sysset_menu(array_timeslect,80,4,1);
	draw_sysSet_data_menu("[shi]",60,6,0);
	while(1)
	{		
		OSTimeDlyHMSM(0, 0,1,30,OS_OPT_TIME_HMSM_STRICT,&err);
		if(getEndflag() & KEY_CANCEL)
		{			
			return (FACE_ENUM)g_currentFace->list->pro->id;;
		}
		if(getEndflag() & KEY_ENTER)
		{
			
		}
	}	
}


//语言选择
u8 array_langselect[][50] = {{"hanyu"},{"english"}};



FACE_ENUM draw_langselect_face(Inode *node, structFaceInfo *info)
{
	OS_ERR err;
	register_key_event(info->id , main_menu_keyEvent, KEY_ALL);   //注册按键

	draw_line_y(3);	
	draw_sysset_menu(array_langselect,32,4,2);
	while(1)
	{		
		OSTimeDlyHMSM(0, 0,1,30,OS_OPT_TIME_HMSM_STRICT,&err);
		if(getEndflag() & KEY_CANCEL)
		{			
			return (FACE_ENUM)g_currentFace->list->pro->id;;
		}
		if(getEndflag() & KEY_ENTER)
		{
			
		}
	}	
}








//清空内存

FACE_ENUM draw_cleanmem_face(Inode *node, structFaceInfo *info)
{
	OS_ERR err;
	register_key_event(info->id , main_menu_keyEvent, KEY_ALL);   //注册按键

	draw_line_y(3);	
	draw_sysSet_data_menu("shi",60,8,0);
	draw_sysSet_data_menu("[fou]",80,8,0);

	while(1)
	{		
		OSTimeDlyHMSM(0, 0,1,30,OS_OPT_TIME_HMSM_STRICT,&err);
		if(getEndflag() & KEY_CANCEL)
		{			
			return (FACE_ENUM)g_currentFace->list->pro->id;;
		}
		if(getEndflag() & KEY_ENTER)
		{
			
		}
	}	
}


//有关本机

u8 array_about[][50] = {{"icegpsdadsada"},{"xinhao"},{"chuankou"}};
FACE_ENUM draw_about_face(Inode *node, structFaceInfo *info)
{
	OS_ERR err;
	register_key_event(info->id , main_menu_keyEvent, KEY_ALL);   //注册按键

	draw_line_y(3);	

	draw_sysset_menu(array_about,1,4,3);

	while(1)
	{		
		OSTimeDlyHMSM(0, 0,1,30,OS_OPT_TIME_HMSM_STRICT,&err);
		if(getEndflag() & KEY_CANCEL)
		{			
			return (FACE_ENUM)g_currentFace->list->pro->id;;
		}
		if(getEndflag() & KEY_ENTER)
		{
			
		}
	}	
}








