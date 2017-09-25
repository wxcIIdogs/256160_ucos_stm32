#include "256160.h"
#include "drawSysSet.h"
#include "includes.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "calcuFace.h"
void draw_return_info(int index)
{	
	int x= 60,y = 8;
	setCurrentIndex(x,y);	
	printf("你确定退出？");
	y +=2;
	setCurrentIndex(x,y);	
	if(index == 1)
	{
		
		printf("【是】  不是");
	}
	else
	{
		printf("是  【不是】");	
	}
	
}

//画 菜单  len是有几个
void draw_sysset_menu(u8 data[][50],int x ,int y,int len)
{
	for(int i = 0;i <len ; i ++)
	{
		setCurrentIndex(x,y);	
		printf("%s",data[i]);
		y+=2;
	}
}
//画一个数据，在指定的下标，根据flag进行高亮处理

void draw_sysSet_data_index_menu(u8 *data,int x, int y ,int index)
{
	setCurrentIndex(x,y);
	for(int i = 0 ;i < strlen((char *)data); i ++)
	{
		if(i == index)
		{
			setBackColor(0);
		}
		printf("%c",data[i]);
		setBackColor(1);
	}
}

//画系统设置的数据，根据下标进行高亮处理
void draw_sysSet_data_menu(u8 *data,int x, int y ,int flag)
{
	disp_clean(x, y,strlen((char *)data),2);
	setCurrentIndex(x,y);	
	setBackColor(1-flag);
	printf("%s",data);
	setBackColor(1);
}
//画一个数字，并且高亮
void draw_sysSet_num_menu(double data,int x,int y ,int flag)
{
	setCurrentIndex(x,y);
	setBackColor(1-flag); //BACK_BLACK 0
	printf("%.2lf",data);
	setBackColor(1);
}
void draw_change_num_menu(int event,int len,char *data,int x,int y,double *reData)
{
	double num = *reData;
	static double addNum = 1;
	static int index = 1;

	if(event & KEY_CANCEL)
	{			
		setReturnFACE_ENUM(g_currentFace->list->pro->id);
		return;
	}
	if(event & KEY_ENTER)
	{
		//save
		*reData = num;
		setReturnFACE_ENUM(g_currentFace->list->pro->id);
		return;		
	}
	if(event & KEY_TOP)
	{
		num += addNum;
		if(num > 10)
		{
			num -=addNum;
		}
	}
	if(event & KEY_BOTTON)
	{
		num -= addNum;
		if(num < 0)
		{
			num +=addNum;
		}
	}
	if(event & KEY_RIGHT)
	{
		
		addNum/=10;
		index ++;
		if(index == 2)
		{
			index ++;
		}
		if(index > 4)
		{
			index = 4;
		}
		if(addNum < 0.01)
		{
			addNum = 0.01;
			
		}
	}
	if(event & KEY_LEFT)
	{
		addNum*=10;
		index --;
		if(index == 2)
		{
			index --;
		}
		if(index == 0 )
		{
			index = 1;
		}
		if(addNum > 1)
		{
			addNum = 1;
		}
	}
	u8 buff[10] = {0};
	num *= g_len_unit_num;
	int temp = (num - (int)num) *100;
	int tempint = num;
	sprintf((char *)buff,data,tempint,temp,g_len_unit);
	draw_sysSet_data_index_menu(buff,x,y,index);	
}


//度量单位
u8 array_unitmeasure[][50] = {{"面积单位:"},{"长度单位:"},{"体积单位:"}};
u8 array_area[][6] = {{"平米"},{"亩"},{"大亩"},{"公顷"}};
u8 array_len[][6] = {{"米"},{"英尺"}};
u8 array_tiji[][20] = {{"方"},{"立方英尺"}};

int g_areaUnit = 0;
int g_lengthUnit = 0;
int g_volumeUnit = 0;

u8 g_area_unit[6];
u8 g_len_unit[6];
u8 g_tiji_unit[6];

double g_area_unit_num = 0;
double g_len_unit_num = 0;
double g_volue_unit_num = 0;


void setUnit()
{
	g_areaUnit = (int)g_initFlashStruct.areaunit;
	g_lengthUnit = (int)g_initFlashStruct.lengthunit;
	g_volumeUnit = (int)g_initFlashStruct.volumeunit;
	
	memcpy(g_area_unit,array_area[g_areaUnit],sizeof(array_area[g_areaUnit]));
	memcpy(g_len_unit,array_len[g_lengthUnit],sizeof(array_len[g_lengthUnit]));
	memcpy(g_tiji_unit,array_tiji[g_volumeUnit],sizeof(array_tiji[g_volumeUnit]));

	switch(g_areaUnit)
	{
		case 0:
			g_area_unit_num = 1;
			break;
		case 1:
			g_area_unit_num = 3.0/2000;
			break;		
		case 2:
			g_area_unit_num = 0.01;
			break;
		case 3:
			g_area_unit_num = 0.0001;
			break;		
	}
	if(g_lengthUnit == 0)
	{
		g_len_unit_num = 1;
	}
	else
	{
		g_len_unit_num = 3.2808;
	}
	if(g_volumeUnit == 0)
	{
		g_volumeUnit = 1;
	}
	else
	{
		g_volumeUnit = 35.3147;
	}
}

//void setEndXieHigh_key(int id,int event)
void unitmeasure_key(int id,int event)
{
	static int arrLen = 3;
	static int select = 0;	
	int localnum[3] = {g_initFlashStruct.areaunit , g_initFlashStruct.lengthunit , g_initFlashStruct.volumeunit};
	if(g_initFlashStruct.areaunit != g_node.flashData->areaunit)
	{
		localnum[0] = g_node.flashData->areaunit;
	}
	if(g_initFlashStruct.lengthunit != g_node.flashData->lengthunit)
	{
		localnum[1] = g_node.flashData->lengthunit;
	}
	if(g_initFlashStruct.volumeunit != g_node.flashData->volumeunit)
	{
		localnum[2] = g_node.flashData->volumeunit;
	}
	
	draw_clean_show(4);
	if(event & KEY_CANCEL)
	{			
		g_node.flashData->areaunit = g_initFlashStruct.areaunit;
		g_node.flashData->lengthunit = g_initFlashStruct.lengthunit;
		g_node.flashData->volumeunit = g_initFlashStruct.volumeunit;
		setReturnFACE_ENUM(g_currentFace->list->pro->id);
		return ;		
	}
	if(event & KEY_ENTER)
	{
		//save
		g_initFlashStruct.areaunit = g_node.flashData->areaunit;
		g_initFlashStruct.lengthunit = g_node.flashData->lengthunit;
		g_initFlashStruct.volumeunit = g_node.flashData->volumeunit;
		writeFlashStruct();
		setUnit();
		setReturnFACE_ENUM(g_currentFace->list->pro->id);
		return ;		
	}
	if(event & KEY_TOP)
	{
		select --;
		if(select < 0)
		{
			select = 0;
		}
	}
	if(event & KEY_BOTTON)
	{
		select ++;
		select %= arrLen;
	}
	if(event & KEY_LEFT)
	{		
		localnum[select]--;
		localnum[select] = localnum[select]<0?0:localnum[select];
		
	}
	if(event & KEY_RIGHT)
	{
		localnum[select]++;
		switch (select)
			{
			case 0:
				localnum[select] %= 4;
				break;
			case 1:
				localnum[select] %= 2;			
				break;
			case 2:
				localnum[select] %= 1;			
				break;			
			}
	}	
	int y = 4;
	for(int i = 0 ; i < arrLen ; i++)
	{
		if(i == select)
		{
			draw_sysSet_data_menu(array_unitmeasure[i] , 1 , y , 1);		
		}
		else
		{
			draw_sysSet_data_menu(array_unitmeasure[i] , 1 , y , 0);		
		}
		y +=2;
	}
	draw_sysSet_data_index_menu(array_area[localnum[0]], 80 , 4 , -1 );
	draw_sysSet_data_index_menu(array_len[localnum[1]], 80 , 6 , -1 );
	draw_sysSet_data_index_menu(array_tiji[localnum[2]], 80 , 8 , -1 );
	
	if(localnum[0] != g_node.flashData->areaunit)
	{
		g_node.flashData->areaunit = localnum[0];
	}
	if(localnum[1] != g_node.flashData->lengthunit)
	{
		g_node.flashData->lengthunit= localnum[1];
	}
	if(localnum[2] != g_node.flashData->volumeunit)
	{
		g_node.flashData->volumeunit = localnum[2] ;
	}
	
}
FACE_ENUM draw_unitmeasure_face(Inode *node, structFaceInfo *info)
{
	OS_ERR err;
	FACE_ENUM rec = faceNull;
	register_key_event(info->id , unitmeasure_key, KEY_ALL);   //注册按键
	draw_title_data_menu("度量单位",1,1);
	draw_line_y(3);	
	draw_sysset_menu(array_unitmeasure,1,4,3);
	draw_sysSet_data_menu(array_area[0],75,4,0);
	draw_sysSet_data_menu(array_len[0],75,6,0);
	draw_sysSet_data_menu(array_tiji[0],75,8,0);	
	while(1)
	{		
		OSTimeDlyHMSM(0, 0,1,30,OS_OPT_TIME_HMSM_STRICT,&err);
		if((rec = getReturnFACE_ENUM()) < faceNull)
		{
			return rec;
		}
	}	
}
//电台频道
u8 array_board[][50] = {{"频道:"}};

void boardchannel_key(int id,int event)
{
	int chennelData = g_initFlashStruct.channel;
	if(g_initFlashStruct.channel != g_node.flashData->channel)
	{
		chennelData = g_node.flashData->channel;
	}
	if(event & KEY_CANCEL)
	{			
		g_node.flashData->channel = g_initFlashStruct.channel;
		setReturnFACE_ENUM(g_currentFace->list->pro->id);
		return ;		
	}
	if(event& KEY_ENTER)
	{
		//save
		g_initFlashStruct.channel = g_node.flashData->channel;
		writeFlashStruct();
		setReturnFACE_ENUM(g_currentFace->list->pro->id);
		char buff[100];
		sprintf(buff,"$ICEGPS,SETRADIO,%d",chennelData);
		sendIcegpsData(buff);
		return ;
	}
	if(event & KEY_TOP)
	{
		chennelData ++;
		chennelData %= (int)g_node.flashData->MaxChannel;
	
	}
	if(event & KEY_BOTTON)
	{
		chennelData --;
		chennelData = chennelData < g_node.flashData->MinChannel?g_node.flashData->MaxChannel:chennelData;	
	}
	u8 buff[6] = {0};
	sprintf((char *)buff,"%d",chennelData);
	draw_sysSet_data_menu(buff,100,8,0);
	if(g_node.flashData->channel != chennelData)
	{
		g_node.flashData->channel = chennelData;		
	}
}
FACE_ENUM draw_boardchannel_face(Inode *node, structFaceInfo *info)
{
	OS_ERR err;
	FACE_ENUM rec = faceNull;

	register_key_event(info->id , boardchannel_key, KEY_ALL);   //注册按键
	draw_title_data_menu("电台频道",100,1);

	draw_line_y(3);	
	draw_sysset_menu(array_board,60,8,1);

	boardchannel_key(0,0);
	while(1)
	{		
		OSTimeDlyHMSM(0, 0,1,30,OS_OPT_TIME_HMSM_STRICT,&err);
		if((rec = getReturnFACE_ENUM()) < faceNull)
		{
			return rec;
		}		

	}	
}


//铲斗宽度
u8 array_bucketwidght[][50] = {{"铲斗宽度:"},};

void bucketwidght_key(int id,int event)
{
    double data = g_initFlashStruct.bucketwidgth;
    if(g_node.flashData->bucketwidgth != g_initFlashStruct.bucketwidgth)
    {
    	data = g_node.flashData->bucketwidgth;
    }
	draw_change_num_menu(event,1,"%+d.%02d%s",130,8,&data);
	
	if(data != g_node.flashData->bucketwidgth)
	{
		g_node.flashData->bucketwidgth = data;
	}
	
	if(event == KEY_ENTER)
	{
		g_initFlashStruct.bucketwidgth = data;
		writeFlashStruct();
	}
}

FACE_ENUM draw_bucketwidght_face(Inode *node, structFaceInfo *info)
{
	OS_ERR err;
	FACE_ENUM rec = faceNull;


	register_key_event(info->id , bucketwidght_key, KEY_ALL);   //注册按键
	draw_title_data_menu("铲斗宽度",90,1);
	draw_line_y(3);
	draw_sysset_menu(array_bucketwidght,60,8,1);
	bucketwidght_key(0,0);
	while(1)
	{		
		OSTimeDlyHMSM(0, 0,1,30,OS_OPT_TIME_HMSM_STRICT,&err);
		if((rec = getReturnFACE_ENUM()) < faceNull)
		{
			if(rec == KEY_ENTER)
			{
				writeFlashStruct();
			}
			return rec;
		}

	}	
}


//天线位置

u8 array_antlocal[][50] = {{"卫星接收天线在平地机上的位置"},{"偏离中线距离:"},{"正负定义:偏左为负，偏右为正"}};

void antlocal_key(int id,int event)
{
	double antlocal = g_initFlashStruct.antlocal;
	if(g_initFlashStruct.antlocal != g_node.flashData->antlocal)
	{
		antlocal = g_node.flashData->antlocal;
	}
	draw_change_num_menu(event,1,"%+d.%02d米",120,8,&antlocal);
	if(g_node.flashData->antlocal != antlocal)
	{
		g_node.flashData->antlocal = antlocal;
	}
	if(event == KEY_ENTER)
	{
		g_initFlashStruct.antlocal = antlocal;
		writeFlashStruct();
	}
}
FACE_ENUM draw_antlocal_face(Inode *node, structFaceInfo *info)
{
	OS_ERR err;
	FACE_ENUM rec = faceNull;
	

	register_key_event(info->id , antlocal_key, KEY_ALL);   //注册按键
	draw_title_data_menu("天线位置",80,1);

	draw_line_y(3);	
	draw_sysset_menu(array_antlocal,1,4,2);
	
	draw_sysset_menu(array_antlocal+2,1,10,1);
	antlocal_key(0,0);
	while(1)
	{		
		OSTimeDlyHMSM(0, 0,1,30,OS_OPT_TIME_HMSM_STRICT,&err);
		if((rec = getReturnFACE_ENUM()) < faceNull)
		{
			return rec;
		}

	}	
}

//升降速度校准

u8 array_roisedownadj[][50] = {{"上升:"},{"下降:"}};
u8 roisedownadj_char[10] = {"m/s"};

void roisedownadj_key(int id,int event)
{
	if(getEndflag() & KEY_CANCEL)
	{			
		setReturnFACE_ENUM(g_currentFace->list->pro->id);
		return ;		
	}
	if(getEndflag() & KEY_ENTER)
	{
		//save		
		setReturnFACE_ENUM(g_currentFace->list->pro->id);
		return ;		
	}	
}
FACE_ENUM draw_roisedownadj_face(Inode *node, structFaceInfo *info)
{
	OS_ERR err;
	FACE_ENUM rec = faceNull;	
	register_key_event(info->id , NULL, KEY_ALL);   //注册按键
	draw_title_data_menu("升降校准",1,1);	
	draw_line_y(3);	
	
	setCurrentIndex(20,8);	
	printf("请确认铲斗升降安全，按确认键开始");
	while(!(getEndflag() & KEY_ENTER))
	{
		OSTimeDlyHMSM(0, 0,0,30,OS_OPT_TIME_HMSM_STRICT,&err);
	}
	
	register_key_event(info->id , roisedownadj_key, KEY_ALL);   //注册按键	
	draw_sysset_menu(array_roisedownadj,1,4,1);	draw_sysset_menu(array_roisedownadj+1,120,4,1);
	draw_sysset_menu(array_roisedownadj,1,6,1);	draw_sysset_menu(array_roisedownadj+1,120,6,1);
	draw_sysset_menu(array_roisedownadj,1,8,1);	draw_sysset_menu(array_roisedownadj+1,120,8,1);
	draw_sysset_menu(array_roisedownadj,1,10,1);  draw_sysset_menu(array_roisedownadj+1,120,10,1);
	while(1)
	{		
		OSTimeDlyHMSM(0, 0,1,30,OS_OPT_TIME_HMSM_STRICT,&err);
		if((rec = getReturnFACE_ENUM()) < faceNull)
		{
			return rec;
		}				
	}	
}


//时间设置
u8 array_timeset[][50] = {{"时区:"},{"夏令时:"},};
u8 array_timeslect[][50] = {{"+8 北京/香港/台北"},{"+11 湖北/台北"},{"+15 拉萨/香港/台北"}};

int xiatime = 0;
int timeindex = 0 ;

void timeset_key(int id,int event)
{
	static int arrLen = 3;
	static int select = 1;
	draw_clean_show(4);
	if(event & KEY_CANCEL)
	{			
		setReturnFACE_ENUM(g_currentFace->list->pro->id);
		return ;		
	}
	if(event & KEY_ENTER)
	{
		//save
		g_initFlashStruct.timesetlocal = timeindex;
		g_initFlashStruct.timesetXia = xiatime;
		writeFlashStruct();
		setReturnFACE_ENUM(g_currentFace->list->pro->id);
		return ;		
	}
	if(event & KEY_TOP)
	{
		select = 1;
	}
	if(event & KEY_BOTTON)
	{
		select = 0;
	}
	if(event & KEY_LEFT)
	{
		if(select == 1)
		{
			timeindex -- ;
			if(timeindex < 0)
				timeindex = 0;
		}
		else		
		{
			xiatime = 0;
		}
	}
	if(event & KEY_RIGHT)
	{
		if(select == 1)
		{
			timeindex ++;
			timeindex %= arrLen;			
		}
		else
		{
			xiatime = 1;
		}
	}		

	draw_sysset_menu(&array_timeslect[timeindex], 80 , 4 , 1 );
	if(xiatime == 0)
	{
		draw_sysSet_data_menu("【是】   否", 120 , 6 , 0 );
	}
	else				
	{
    	draw_sysSet_data_menu("是    【否】", 120 , 6 , 0);	
	}	
	draw_sysSet_data_menu(array_timeset[0] , 1 , 4 , select );
	draw_sysSet_data_menu(array_timeset[1] , 1 , 6 , 1 - select);	
}
FACE_ENUM draw_timeset_face(Inode *node, structFaceInfo *info)
{
	OS_ERR err;
	FACE_ENUM rec = faceNull;
	register_key_event(info->id , timeset_key, KEY_ALL);   //注册按键


	draw_title_data_menu("时间设置",80,1);
	draw_line_y(3);		
	
	timeindex = g_initFlashStruct.timesetlocal ;
	xiatime = g_initFlashStruct.timesetXia;
	
	timeset_key(0,0);
	while(1)
	{		
		OSTimeDlyHMSM(0, 0,1,30,OS_OPT_TIME_HMSM_STRICT,&err);
		if((rec = getReturnFACE_ENUM()) < faceNull)
		{
			return rec;
		}		
	}	
}


//语言选择
u8 array_langselect[][50] = {{"汉语"},{"english"}};

int lanselect = 0;

void langselect_key(int id,int event)
{
	draw_clean_show(4);
	if(event & KEY_CANCEL)
	{			
		setReturnFACE_ENUM(g_currentFace->list->pro->id);
		return ;		
	}
	if(event & KEY_ENTER)
	{
		//save
		g_initFlashStruct.langselect = lanselect;
		writeFlashStruct();
		setReturnFACE_ENUM(g_currentFace->list->pro->id);			
		return ;		
	}
	if(event & KEY_TOP)
	{
		lanselect = 0;
	}
	if(event & KEY_BOTTON)
	{
		lanselect = 1;
	}
	if(lanselect == 0)
	{		
		draw_sysSet_data_menu("V",16,4,0);				
	}
	if(lanselect == 1)
	{
		draw_sysSet_data_menu("V",16,6,0);
	}
	draw_sysset_menu(array_langselect,32,4,2);				

}

FACE_ENUM draw_langselect_face(Inode *node, structFaceInfo *info)
{
	OS_ERR err;
	FACE_ENUM rec = faceNull;	
	register_key_event(info->id , langselect_key, KEY_ALL);   //注册按键


	draw_title_data_menu("语言选择",1,1);	
	draw_line_y(3);	
	draw_sysset_menu(array_langselect,32,4,2);

	lanselect = g_initFlashStruct.langselect;
	langselect_key(0,0);
	while(1)
	{		
		OSTimeDlyHMSM(0, 0,1,30,OS_OPT_TIME_HMSM_STRICT,&err);
		if((rec = getReturnFACE_ENUM()) < faceNull)
		{
			return rec;
		}		
	}	
}


//清空内存
void cleanmem_key(int id,int event)
{
	static int cleanmem = 0;

	if(event & KEY_CANCEL)
	{			
		setReturnFACE_ENUM(g_currentFace->list->pro->id);
		return ;		
	}
	if(event & KEY_ENTER)
	{
		//zhixing
		setReturnFACE_ENUM(g_currentFace->list->pro->id);
		return ;
	}
	if(event & KEY_LEFT)
	{
		cleanmem = 0;
	}
	if(event & KEY_RIGHT)
	{
		cleanmem = 1;
	}

	if(cleanmem == 0)
	{
		draw_sysSet_data_menu("[是]",60,8,0);
		draw_sysSet_data_menu("否",100,8,0);		
	}
	else
	{
		draw_sysSet_data_menu("是",60,8,0);
		draw_sysSet_data_menu("[否]",100,8,0);		
	}
}
FACE_ENUM draw_cleanmem_face(Inode *node, structFaceInfo *info)
{
	OS_ERR err;
	FACE_ENUM rec = faceNull;	
	register_key_event(info->id , cleanmem_key, KEY_ALL);   //注册按键

	draw_title_data_menu("清空内存",1,1);
	draw_line_y(3);	
	draw_sysSet_data_menu("是",60,8,0);
	draw_sysSet_data_menu("[否]",80,8,0);

	while(1)
	{		
		OSTimeDlyHMSM(0, 0,1,30,OS_OPT_TIME_HMSM_STRICT,&err);
		if((rec = getReturnFACE_ENUM()) < faceNull)
		{
			return rec;
		}		

	}	
}


//有关本机

u8 array_about[][50] = {{"冰河导航卫星平地机"},{"型号:PD110"},{"串号:124657876121"},{"软件版本:1.1-201708311730"}};
void about_key(int id,int event)
{
	if(event & KEY_CANCEL)
	{			
		setReturnFACE_ENUM(g_currentFace->list->pro->id);
		return;
	}
	if(event & KEY_ENTER)
	{
		setReturnFACE_ENUM(g_currentFace->list->pro->id);
		return;
	}	
}
FACE_ENUM draw_about_face(Inode *node, structFaceInfo *info)
{
	OS_ERR err;
	FACE_ENUM rec = faceNull;	
	register_key_event(info->id , about_key, KEY_ALL);   //注册按键
	draw_title_data_menu("关于本机",1,1);

	draw_line_y(3);	

	draw_sysset_menu(array_about,1,4,3);

	while(1)
	{		
		OSTimeDlyHMSM(0, 0,0,30,OS_OPT_TIME_HMSM_STRICT,&err);
		if((rec = getReturnFACE_ENUM()) < faceNull)
		{
			return rec;
		}	
	}	
}








