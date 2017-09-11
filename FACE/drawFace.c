

#include "256160.h"
#include "drawFace.h"
#include "includes.h"
FACE_ENUM getIDEnum(structFaceInfo *info)
{
	return (FACE_ENUM)info->menu[getLocalId()].id;
}
//主界面
FACE_ENUM draw_main_face(Inode *node, structFaceInfo *info)
{
	OS_ERR err;
	register_key_event(info->id , main_menu_keyEvent, KEY_ALL);   //注册按键

	if(info->ishead == 1)
	{
		draw_title();  //显示开头
	}	
	draw_menu(info);
	while(1)
	{
		
		OSTimeDlyHMSM(0, 0,1,30,OS_OPT_TIME_HMSM_STRICT,&err);
		if(getEndflag() & KEY_CANCEL)
		{
			return MAINMENU;
		}
		if(getEndflag() & KEY_ENTER)
		{
			return getIDEnum(info);
		}
	}	
}




//系统设置
FACE_ENUM draw_sysSet_face(Inode *node, structFaceInfo *info)
{
	OS_ERR err;
	register_key_event(info->id , main_menu_keyEvent, KEY_ALL);   //注册按键

	if(info->ishead == 1)
	{
		draw_title();  //显示开头
	}	
	draw_menu(info);
	while(1)
	{
		
		OSTimeDlyHMSM(0, 0,1,30,OS_OPT_TIME_HMSM_STRICT,&err);
		if(getEndflag() & KEY_CANCEL)
		{
			return MAINMENU;
		}
		if(getEndflag() & KEY_ENTER)
		{
			return getIDEnum(info);
		}
	}		
}


////地块测量
FACE_ENUM draw_parcelSurvey_face(Inode *node, structFaceInfo *info)
{
	OS_ERR err;
	register_key_event(info->id , main_menu_keyEvent, KEY_CANCEL);   //注册按键

	if(info->ishead == 1)
	{
		draw_title();  //显示开头
	}	
	setLocalId(-1);
	draw_menu(info);
	while(1)
	{
		
		
		OSTimeDlyHMSM(0, 0,1,30,OS_OPT_TIME_HMSM_STRICT,&err);
		if(getEndflag() & KEY_CANCEL)
		{			
			return (FACE_ENUM)g_currentFace->list->pro->id;
		}
	}	
}
//做平面
FACE_ENUM draw_planeMenu_face(Inode *node, structFaceInfo *info)
{
	OS_ERR err;
	register_key_event(info->id , main_menu_keyEvent, KEY_CANCEL);   //注册按键

	if(info->ishead == 1)
	{
		draw_title();  //显示开头
	}	
	setLocalId(-1);	
	draw_menu(info);
	while(1)
	{
		
		OSTimeDlyHMSM(0, 0,1,30,OS_OPT_TIME_HMSM_STRICT,&err);
		if(getEndflag() & KEY_CANCEL)
		{			
			return (FACE_ENUM)g_currentFace->list->pro->id;
		}
	}	
}
//做斜面
FACE_ENUM draw_xieMenu_face(Inode *node, structFaceInfo *info)
{
	OS_ERR err;
	register_key_event(info->id , main_menu_keyEvent, KEY_CANCEL);   //注册按键

	if(info->ishead == 1)
	{
		draw_title();  //显示开头
	}	
	setLocalId(-1);	
	draw_menu(info);
	while(1)
	{
		
		OSTimeDlyHMSM(0, 0,1,30,OS_OPT_TIME_HMSM_STRICT,&err);
		if(getEndflag() & KEY_CANCEL)
		{			
			return (FACE_ENUM)g_currentFace->list->pro->id;
		}
	}
}
//测量数据
FACE_ENUM draw_meauseData_face(Inode *node, structFaceInfo *info)
{
	OS_ERR err;
	static int index = 0;
	register_key_event(info->id , main_menu_keyEvent, KEY_TOP | KEY_BOTTON | KEY_CANCEL);	 //注册按键

	if(info->ishead == 1)
	{
		draw_title();  //显示开头
	}	
	structCeData * data = (structCeData *)malloc(sizeof(structCeData));
	draw_line_y(3);
	draw_menu_cedata(info, index,data );
	while(1)
	{				
		OSTimeDlyHMSM(0, 0,1,30,OS_OPT_TIME_HMSM_STRICT,&err);
		if(getEndflag() & KEY_CANCEL)
		{			
			return (FACE_ENUM)g_currentFace->list->pro->id;
		}
	}
}
//设置平面高度
uchar array_setPlabHigh[][30] = {{"Meauaverhigh:"},{"currentHigh:"},{"plansethigh:"}};
uchar setPlanHigh_title[50] = "dadsadsadsadsmvsvnsdvnnldfna";
void draw_setPlaneHigh_num_menu(int index)
{
	int x = 14*8;
	int y = 7;
	double num = 0.0;
	for(int i = 0 ;i < 3; i ++)
	{	
		if(index == i)
			draw_set_num_menu(num, 1,x,y);
		else
			draw_set_num_menu(num, 0,x,y);
		y += 2;
	}
}
FACE_ENUM draw_setPlaneHigh_face(Inode *node, structFaceInfo *info)
{
	OS_ERR err;
	int index = 0;
	register_key_event(info->id , main_menu_keyEvent, KEY_ALL);   //注册按键

	if(info->ishead == 1)
	{
		draw_title();  //显示开头
	}	
	draw_set_menu(array_setPlabHigh,3);	
	draw_set_low_title_menu(setPlanHigh_title,1,19);
	while(1)
	{
		draw_setPlaneHigh_num_menu(index);
		OSTimeDlyHMSM(0, 0,1,30,OS_OPT_TIME_HMSM_STRICT,&err);
		if(getEndflag() & KEY_CANCEL)
		{			
			return (FACE_ENUM)g_currentFace->list->pro->id;
		}
		if(getEndflag() & KEY_ENTER)
		{
			return PANELMENU;
		}
		if(getEndflag() & KEY_TOP)
		{
			index --;
			if(index < 0)
				index %= 3;
		}
		if(getEndflag() & KEY_BOTTON)
		{
			index ++;
			if(index > 2)
				index = 0;
		}
		
	}
}



//设置斜面高度
uchar array_setXieHigh[][30] = {{"Meauaverhigh:"},{"currentHigh:"}};
uchar setXieHigh_title[50] = "dadsadsadsadsmvsvnsdvnnldfna";
void draw_setXieHigh_num_menu(int index)
{
	int x = 14*8;
	int y = 7;
	double num = 0.0;
	for(int i = 0 ;i < 2; i ++)
	{	
		if(index == i)
			draw_set_num_menu(num, 1,x,y);
		else
			draw_set_num_menu(num, 0,x,y);
		y += 2;
	}
}
FACE_ENUM draw_setXieHigh_face(Inode *node, structFaceInfo *info)
{
	OS_ERR err;
	int index = 0;
	register_key_event(info->id , main_menu_keyEvent, KEY_ALL);   //注册按键

	if(info->ishead == 1)
	{
		draw_title();  //显示开头
	}	
	draw_set_menu(array_setXieHigh,2);	
	draw_set_low_title_menu(setXieHigh_title,1,19);
	while(1)
	{
		draw_setXieHigh_num_menu(index);
		OSTimeDlyHMSM(0, 0,1,30,OS_OPT_TIME_HMSM_STRICT,&err);
		if(getEndflag() & KEY_CANCEL)
		{			
			return (FACE_ENUM)g_currentFace->list->pro->id;
		}
		if(getEndflag() & KEY_ENTER)
		{
			return SETXIEENDHIGH;
		}
		if(getEndflag() & KEY_TOP)
		{
			index --;
			if(index < 0)
				index %= 2;
		}
		if(getEndflag() & KEY_BOTTON)
		{
			index ++;
			if(index > 1)
				index = 0;
		}
		
	}
}
//设置斜面终点 
uchar array_setXieEndHigh[][30] = {{"Meauaverhigh:"},{"currentHigh:"},{"Meauaverhigh:"},{"Meauaverhigh:"},{"Meauaverhigh:"},{"Meauaverhigh:"},};
uchar setXieEndHigh_title[50] = "dadsadsadsadsmvsvnsdvnnldfna";
void draw_setXieEndHigh_num_menu(int index)
{
	int x = 14*8;
	int y = 7;
	double num = 0.0;
	for(int i = 0 ;i < 6; i ++)
	{	
		if(index == i)
			draw_set_num_menu(num, 1,x,y);
		else
			draw_set_num_menu(num, 0,x,y);
		y += 2;
	}
}
FACE_ENUM draw_setEndXieHigh_face(Inode *node, structFaceInfo *info)
{
	OS_ERR err;
	int index = 0;
	register_key_event(info->id , main_menu_keyEvent, KEY_ALL);   //注册按键

	if(info->ishead == 1)
	{
		draw_title();  //显示开头
	}	
	draw_set_menu(array_setXieEndHigh,6);	
	draw_set_low_title_menu(setXieEndHigh_title,1,19);
	while(1)
	{
		draw_setXieEndHigh_num_menu(index);
		OSTimeDlyHMSM(0, 0,1,30,OS_OPT_TIME_HMSM_STRICT,&err);
		if(getEndflag() & KEY_CANCEL)
		{			
			return (FACE_ENUM)g_currentFace->list->pro->id;
		}
		if(getEndflag() & KEY_ENTER)
		{
			return XIEMENU;
		}
		if(getEndflag() & KEY_TOP)
		{
			index --;
			if(index < 0)
				index %= 6;
		}
		if(getEndflag() & KEY_BOTTON)
		{
			index ++;
			if(index > 5)
				index = 0;
		}
		
	}
}



//卫星信号

void draw_setStat_num_menu(int *statSingArray)
{
	int x = 1;
	int y = 4;
	for(int i = 0 ; i < 12 ; i++)
	{
//		void draw_stat_stren_num_menu(int index,int len,int x,int y);
		draw_stat_stren_num_menu(i+1,statSingArray[i],x,y);
		draw_stat_stren_num_menu(i+1,statSingArray[i+12],x+60,y);
		draw_stat_stren_num_menu(i+1,statSingArray[i+12*2],x+120,y);
		y += 2;
	}
}
FACE_ENUM draw_setStat_face(Inode *node, structFaceInfo *info)
{
	OS_ERR err;
	int index;
	int statSingArray[12*3+1] = {5};
	register_key_event(info->id , main_menu_keyEvent, KEY_CANCEL);   //注册按键
	
	draw_StatTitle_menu(12,12,12);
	draw_line_y(3);
	while(1)
	{
		draw_setStat_num_menu(statSingArray);
		OSTimeDlyHMSM(0, 0,1,30,OS_OPT_TIME_HMSM_STRICT,&err);
		if(getEndflag() & KEY_CANCEL)
		{			
			return (FACE_ENUM)g_currentFace->list->pro->id;
		}		
	}

}






