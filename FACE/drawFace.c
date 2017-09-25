

#include "256160.h"
#include "drawFace.h"
#include "includes.h"
#include "math.h"
#include "calcuFace.h"
#include "flash.h"
#include <math.h>
#include "MeterArea.h"
static double g_arrNum[10] = {0};
static char g_strNum[10][10];

void clean_arrarNum()
{
	memset(g_arrNum,0,sizeof(g_arrNum));
	for(int i= 0 ; i < 10; i ++)
	{
		memset(g_strNum[i],0,sizeof(g_strNum[i]));
	}
}
FACE_ENUM getIDEnum(structFaceInfo *info)
{
	return (FACE_ENUM)info->menu[getLocalId()].id;
}
//主界面
int get_num_len(double num)
{
	char temp[20] = {0};
	sprintf(temp,"%.3lf",num);
	return strlen((char *)temp);
}
int operation_index = 0;

void operation_key_change(int len,FACE_ENUM enterEnum,int event,uchar arrSet[][30])
{
	int listLen = len;
	static double addNum = 1;
	static int enterFlag = 0;
	static int addindex = -1;
	int numLen = get_num_len(g_arrNum[operation_index]);
	int zhNumLen = numLen -4;
	if(event & KEY_CANCEL)
	{		
		if(enterFlag)
		{
			enterFlag = 0;			
			addindex = -1;
			addNum = 1;
		}
		else
		{
			operation_index = 0;			
			stop_parcelSurvey();
			setReturnFACE_ENUM(g_currentFace->list->pro->id);
			return ;			
		}
	}
	if(event & KEY_ENTER)
	{
		if(enterFlag)
		{
			enterFlag = 0;			
			addindex = -1;
			addNum = 1;
			
		}
		else
		{
			operation_index = 0;
			setReturnFACE_ENUM(enterEnum + 1);
			return ;
		}
		
	}
	if(event & KEY_TOP)
	{
		if(enterFlag == 1)
		{
			g_arrNum[operation_index] += addNum;
			if(g_arrNum[operation_index] > 10)
			{
				g_arrNum[operation_index] --;
			}
		}
		else
		{
			operation_index --;
			if(operation_index < 0)
				operation_index = listLen -1;					
		}

	}
	if(event & KEY_BOTTON)
	{
		if(enterFlag == 1)
		{
			g_arrNum[operation_index] -= addNum;
			if(g_arrNum[operation_index] < 0 )
			{
				g_arrNum[operation_index] ++;
			}
		}
		else
		{
			operation_index ++;
			if(operation_index == listLen)
				operation_index = 0;
		}
		
	}
	if(event & KEY_RIGHT)
	{
		if(enterFlag == 0)
		{
			enterFlag = 1;
			addindex = 1;
			addNum =  pow(10,zhNumLen-1);
		}
		else
		{
			if(++addindex == zhNumLen+1)
			{
				addindex++;
			}
			if(addindex >numLen)
			{
				addindex = numLen;
			}
			addNum/=10;
			if(addNum < 0.001)
			{
				addNum = 0.001;
			}
		}
	}
	if(event & KEY_LEFT && enterFlag)
	{
		if(--addindex == zhNumLen+1)
		{
			addindex--;
		}
		if(addindex == 0)
		{
			addindex = 1;
		}
		addNum *=10;
		if(addNum >pow(10,zhNumLen-1))
		{
			addNum = pow(10,zhNumLen-1);
		}
	}
	for(int i = 0 ; i < len ; i ++)
	{
		sprintf(g_strNum[i],"%+.3lf%s",g_arrNum[i]*g_len_unit_num,g_len_unit);		
	}
	draw_show_num_menu(operation_index,g_strNum,addindex,arrSet,len);
}

void main_key(int id,int event)
{
	if(event & KEY_ENTER)
	{
		setReturnFACE_ENUM(getIDEnum(g_currentFace));
		return ;
	}
	draw_menu(g_currentFace);
	if(event == KEY_TOP)
	{
		char buff[100];
		sprintf(buff,"$ICEGPS,CONNECT,1");
		sendIcegpsData(buff);
		sprintf(buff,"$ICEGPS,GETRADIO");
		sendIcegpsData(buff);
	}
}
FACE_ENUM draw_main_face(Inode *node, structFaceInfo *info)
{
	OS_ERR err;
	FACE_ENUM rec = faceNull;	
	register_key_event(info->id , main_key, KEY_ALL & ~(KEY_CANCEL));   //娉ㄥ唽鎸夐敭

	if(info->ishead == 1)
	{
		draw_title();  //鏄剧ず寮�澶?
	}	
	draw_title_data_menu("冰河导航PD110",32,4);
	setLocalId(0);
	draw_menu(info);
	while(1)
	{		
		OSTimeDlyHMSM(0, 0,0,50,OS_OPT_TIME_HMSM_STRICT,&err);
		if((rec = getReturnFACE_ENUM()) < faceNull)
		{
			return rec;
		}
	}	
}




//系统设置

void sysSet_key(int id,int event)
{
	if(event & KEY_CANCEL)
	{
		setReturnFACE_ENUM(g_currentFace->list->pro->id);
		return ;		
	}
	if(event & KEY_ENTER)
	{
		setReturnFACE_ENUM(getIDEnum(g_currentFace));	
		return ;		
	}
	draw_menu(g_currentFace);
}

FACE_ENUM draw_sysSet_face(Inode *node, structFaceInfo *info)
{
	OS_ERR err;
	FACE_ENUM rec = faceNull;
	register_key_event(info->id , sysSet_key, KEY_ALL);   //娉ㄥ唽鎸夐敭

	if(info->ishead == 1)
	{
		draw_title();  //鏄剧ず寮�澶?
	}	
	setLocalId(0);	
	draw_title_data_menu("系统设置",60,4);
	draw_menu(info);
	while(1)
	{
		
		OSTimeDlyHMSM(0, 0,1,30,OS_OPT_TIME_HMSM_STRICT,&err);
		if((rec = getReturnFACE_ENUM()) < faceNull)
		{
			return rec;
		}
		
	}		
}


////地块测量
int g_enterCount = 0;
OS_TMR timer;
char arryParcel[][100] = 
{
{"请开到地块边缘，按确定键开始测量"},
{"开始测量，请将铲斗降低到地面然后按确定键继续"},
{"正在计算起点地面高度，请勿调整铲斗"},
{"起点高度计算完毕，请将铲斗升高到最高然后按确认键继续"},
{"正在计算铲斗上升高度，请勿调整铲斗"},
{"铲斗上升高度计算完毕，请开车绕地一周进行测量，按确认键开始"},
{"地块测量中，回到起点之后请按确定键结束"},
{"地块测量完毕"},
};
void parcelSurvey_print(char *data)
{
	disp_clean(1,16,16,4);
	setCurrentIndex(1,16);
	printf("%s",data);
}
void parcelSurvey_key(int id,int event)
{
	if(event & KEY_CANCEL)
	{			
		setReturnFACE_ENUM(g_currentFace->list->pro->id);
		stop_parcelSurvey();
		g_enterCount = 0;
		return ;		
	}
	if(event & KEY_ENTER)
	{

		g_enterCount ++;
		if(g_enterCount == 1)
		{//获取最低高度
			
		}
		else if(g_enterCount == 3)
		{//获取起点高度
		
		}
		else if(g_enterCount == 5)
		{//开始测量
		
		}
		else if(g_enterCount == 6)
		{//结束测量
		
			setReturnFACE_ENUM(g_currentFace->list->pro->id);
			stop_parcelSurvey();		
			return ;
		}
		//save
		
	}
	parcelSurvey_print(arryParcel[g_enterCount]);
}
void timerUpdataInfo(void *p_tmr, void *p_arg)
{
	structFaceInfo *info = (structFaceInfo *)p_arg;
	updata_parcelSurvey(&g_node,info);		
}
FACE_ENUM draw_parcelSurvey_face(Inode *node, structFaceInfo *info)
{
	OS_ERR err;
	FACE_ENUM rec = faceNull;
	register_key_event(info->id , parcelSurvey_key, KEY_CANCEL);   //娉ㄥ唽鎸夐敭

	if(info->ishead == 1)
	{
		draw_title();  //鏄剧ず寮�澶?
	}	
	draw_title_data_menu("地块测量",60,4);
	setLocalId(-1);
	draw_menu(info);
	init_parcelSurvey();
	//创建定时器，定时刷新数据
	OSTmrCreate(&timer,"updata",100,100,OS_OPT_TMR_PERIODIC ,timerUpdataInfo,info,&err); 

	parcelSurvey_key(0,0);
	while(1)
	{
		OSTimeDlyHMSM(0, 0,1,30,OS_OPT_TIME_HMSM_STRICT,&err);
		if((rec = getReturnFACE_ENUM()) < faceNull)
		{
			OSTmrDel(&timer,&err);
			return rec;
		}
	}	
}

//做平面

void planeMenu_key(int id,int event)
{

	if(event & KEY_CANCEL)
	{			
		setReturnFACE_ENUM(MAINMENU+1);
		return ;		
	}
}
void timerUpdataInfoplane(void *p_tmr, void *p_arg)
{
	structFaceInfo *info = (structFaceInfo *)p_arg;
	updata_planeMenu(&g_node,info);
}

FACE_ENUM draw_planeMenu_face(Inode *node, structFaceInfo *info)
{
	OS_ERR err;
	FACE_ENUM rec = faceNull;
	register_key_event(info->id , planeMenu_key, KEY_CANCEL);   //娉ㄥ唽鎸夐敭
	if(info->ishead == 1)
	{
		draw_title();  //鏄剧ず寮�澶?
	}	
	draw_title_data_menu("做平面",60,4);
	setLocalId(-1);	
	draw_menu(info);
	OSTmrCreate(&timer,"updata",100,100,OS_OPT_TMR_PERIODIC ,timerUpdataInfoplane,info,&err); 
	while(1)
	{		
		
		OSTimeDlyHMSM(0, 0,1,30,OS_OPT_TIME_HMSM_STRICT,&err);		
		if((rec = getReturnFACE_ENUM()) < faceNull)
		{
			OSTmrDel(&timer,&err);
			return rec;
		}
	}	
}
//做斜面

void xieMenu_key(int id,int event)
{
	if(event & KEY_CANCEL)
	{			
		setReturnFACE_ENUM(MAINMENU+1);
		return ;		
	}
}
void timerUpdataInfoxie(void *p_tmr, void *p_arg)
{
	structFaceInfo *info = (structFaceInfo *)p_arg;
	updata_xieMenu(&g_node,info);
}

FACE_ENUM draw_xieMenu_face(Inode *node, structFaceInfo *info)
{
	OS_ERR err;
	FACE_ENUM rec = faceNull;
	register_key_event(info->id , xieMenu_key, KEY_CANCEL);   //娉ㄥ唽鎸夐敭

	if(info->ishead == 1)
	{
		draw_title();  //鏄剧ず寮�澶?
	}	
	setLocalId(-1);	
	draw_title_data_menu("做斜面",60,4);
	draw_menu(info);
	OSTmrCreate(&timer,"updata",100,100,OS_OPT_TMR_PERIODIC ,timerUpdataInfoxie,info,&err); 
	while(1)
	{			
		OSTimeDlyHMSM(0, 0,1,30,OS_OPT_TIME_HMSM_STRICT,&err);
		if((rec = getReturnFACE_ENUM()) < faceNull)
		{
			OSTmrDel(&timer,&err);
			return rec;
		}
	}
}
//测量数据

char ceDataTitleBuff[30] = {0};
int ceDataIndex = 0;
structCeData * ceData;
structFaceInfo *ceInfo;
void meauseData_key(int id,int event)
{
	if(event & KEY_CANCEL)
	{	
		g_ceDataFlash.startAdress = (uint32_t )ceDataStartAdress;
		memset(ceDataTitleBuff,0,30);
		setReturnFACE_ENUM(g_currentFace->list->pro->id);
		free(ceData);
		return ;		
	}
	if(event & KEY_ENTER)
	{			
		g_ceDataFlash.startAdress = ceDataStartAdress;
		g_node.parcelData->area = ceData->area;
		g_node.parcelData->averH = ceData->dhigh;
		g_node.parcelData->EtherDis = ceData->tufl;
		g_node.parcelData->maxH = ceData->high;
		g_node.parcelData->minH = ceData->low;
		g_node.parcelData->PeriMeter = ceData->zhouc;
		g_node.Distance[0] = ceData->dis[0];
		g_node.Distance[1] = ceData->dis[1];				
		setReturnFACE_ENUM(g_currentFace->list->pro->id);
		return ;		
	}
	if(event & KEY_LEFT)
	{			
		ceDataIndex --;
		if(ceDataIndex < 0)
		{
			ceDataIndex = 0;
		}
		g_ceDataFlash.startAdress -= sizeof(structCeData);		
	}
	if(event & KEY_RIGHT)
	{			
		ceDataIndex ++;
		ceDataIndex %= g_ceDataFlash.count;
		g_ceDataFlash.startAdress += sizeof(structCeData);
	}
	sprintf(ceDataTitleBuff,"测量数据(%02d/%02d)",ceDataIndex,g_ceDataFlash.count);
	draw_title_data_menu((u8 *)ceDataTitleBuff,50,1);
	STMFLASH_ReadStruct(g_ceDataFlash.startAdress , ceData, sizeof(structCeData));
	update_cedata(ceInfo,ceData);
	draw_menu_data(ceInfo);
}

FACE_ENUM draw_meauseData_face(Inode *node, structFaceInfo *info)
{
	OS_ERR err;
	FACE_ENUM rec = faceNull;
	register_key_event(info->id , meauseData_key, KEY_TOP | KEY_BOTTON | KEY_CANCEL);	 //娉ㄥ唽鎸夐敭

	if(info->ishead == 1)
	{
		draw_title(); 
	}	
		
	draw_line_y(3);
	draw_menu(info);
	
	ceData = (structCeData *)malloc(sizeof(structCeData));
	ceInfo = info;

	while(1)
	{				
		OSTimeDlyHMSM(0, 0,1,30,OS_OPT_TIME_HMSM_STRICT,&err);
		if((rec = getReturnFACE_ENUM()) < faceNull)
		{
				return rec;
		}

	}
}
//设置平面高度
uchar array_setPlabHigh[][30] = {{"测量平均高度:"},{"当前铲斗高度:"},{"平面设置高度:"}};
uchar setPlanHigh_title[50] = "请修改平面设置高度，然后按确认键";

void initPlaneHighData(Inode *node)
{
	node->aimH = node->nowH;
}

void setPlaneHigh_key(int id,int event)
{
	operation_key_change(3,PANELMENU,event,array_setPlabHigh);
}
FACE_ENUM draw_setPlaneHigh_face(Inode *node, structFaceInfo *info)
{
	OS_ERR err;
	FACE_ENUM rec = faceNull;
	register_key_event(info->id , setPlaneHigh_key, KEY_ALL);   //娉ㄥ唽鎸夐敭

	if(info->ishead == 1)
	{
		draw_title();  //鏄剧ず寮�澶?
	}	
	initPlaneHighData(node);
	draw_title_data_menu("设置平面高度",60,4);
	draw_set_menu(array_setPlabHigh,3);	
	draw_set_low_title_menu(setPlanHigh_title,1,19);
	clean_arrarNum();//清空全局数组
	operation_index = 2;
	setPlaneHigh_key(0,0);
	g_arrNum[0] = node->parcelData->averH;
	g_arrNum[1] = node->nowH;
	g_arrNum[2] = node->aimH;
	g_node.Distance[0] = node->lat;
	g_node.Distance[1] = node->lot;
	while(1)
	{		
		OSTimeDlyHMSM(0, 0,1,30,OS_OPT_TIME_HMSM_STRICT,&err);
		if((rec = getReturnFACE_ENUM()) < faceNull)
		{		
			node->parcelData->averH = g_arrNum[0];
		 	node->aimH = g_arrNum[2];	
			return rec;
		}		
	}
}



//设置斜面起点高度
uchar array_setXieHigh[][30] = {{"铲斗现在高度:"},{"斜面起点高度:"}};
uchar setXieHigh_title[50] = "请修改斜面起点高度，然后按确认键";
void initXieStartData(Inode *node)
{
	node->xieData->startH = node->nowH;
}
void setXieStartData(Inode *node)
{
	node->xieData->startH = node->nowH;
}
void setXieHigh_key(int id,int event)
{
	operation_key_change(2,SETXIEENDHIGH,event,array_setXieHigh);
}
FACE_ENUM draw_setXieHigh_face(Inode *node, structFaceInfo *info)
{
	OS_ERR err;
	FACE_ENUM rec = faceNull;
	register_key_event(info->id , setXieHigh_key, KEY_ALL);   //娉ㄥ唽鎸夐敭

	if(info->ishead == 1)
	{
		draw_title();  //鏄剧ず寮�澶?
	}	 	
	draw_title_data_menu("设置斜面高度",60,4);	
	draw_set_menu(array_setXieHigh,2);	
	draw_set_low_title_menu(setXieHigh_title,1,19);
	operation_index = 1;
	clean_arrarNum();	
	setXieHigh_key(0,0);
	g_arrNum[0] = node->nowH;
	g_arrNum[1] = node->xieData->startH;
	init_parcelSurvey();
	g_node.Distance[0] = node->lat;
	g_node.Distance[1] = node->lot;
	while(1)
	{		
		OSTimeDlyHMSM(0, 0,1,30,OS_OPT_TIME_HMSM_STRICT,&err);
		if((rec = getReturnFACE_ENUM()) < faceNull)
		{
			node->xieData->startH = g_arrNum[1];
			return rec;
		}		
	}
}
//设置斜面终点高度
uchar array_setXieEndHigh[][30] = {{"斜面起点高度:"},{"斜面终点高度:"},{"起点到终点高差:"},{"起点到终点距离:"},{"起点到终点坡度:"},{"起点到终点度数:"}};
uchar setXieEndHigh_title[50] = "请修改斜面终点高度，然后按确认键";
void setEndXieHigh_key(int id,int event)
{
	operation_key_change(4, XIEMENU, event,array_setXieEndHigh);
}

void setxieEndData(Inode *node)
{	
	char buff[100] = {0};
	set_xieMenu_data(node);
	//斜面起点高度
	g_arrNum[0] = node->xieData->startH;	
	//斜面终点高度	
	g_arrNum[1] = node->nowH;
	//起点到终点高差
	g_arrNum[2] = node->xieData->endH - node->xieData->startH;
	//起点到终点距离
	g_arrNum[3] = GetDistance(node->Distance[0],node->Distance[1],node->lat, node->lot ); 
	//坡度
	g_arrNum[4] = atan2(g_arrNum[2],g_arrNum[3])*180/3.14159;	
	//百分比
	g_arrNum[5] = g_arrNum[2]/g_arrNum[3];	

	sprintf(buff,"%.1lf度",g_arrNum[4]);
	draw_title_data_menu((u8 *)buff,g_currentFace->menu[4].x+5,g_currentFace->menu[4].y);	
	memset(buff,0,sizeof(buff));
	sprintf(buff,"%.1lf%",g_arrNum[5]);
	draw_title_data_menu((u8 *)buff,g_currentFace->menu[5].x+5,g_currentFace->menu[5].y);
	
	setEndXieHigh_key(0,0);
}
double arrNowH[11] = {0};
int arrNowHindex = 0;
double getAverNowH(double *data,int len)
{
	double sum = 0;
	for(int i = 0 ;i < len ; i++)
	{
		sum += data[i];
	}
	sum /= len;
	return sum;
}

void timerUpdataInfosetEndXie(void *p_tmr, void *p_arg)
{
	if(g_node.speed < 0.1)
	{
		memset(arrNowH,0,11*8);
		arrNowHindex = 0;
	}
	else
	{
		arrNowH[arrNowHindex++] = g_node.nowH;
		if(arrNowHindex == 10)
		{
			g_node.nowH = getAverNowH(arrNowH,arrNowHindex);
			setxieEndData(&g_node);		

		}
	}

}

FACE_ENUM draw_setEndXieHigh_face(Inode *node, structFaceInfo *info)
{
	OS_ERR err;
	FACE_ENUM rec = faceNull;
	register_key_event(info->id , setEndXieHigh_key, KEY_ALL);   //娉ㄥ唽鎸夐敭

	if(info->ishead == 1)
	{
		draw_title(); 
	}		
	
	draw_title_data_menu("设置斜面终点",60,4);
	
	draw_set_menu(array_setXieEndHigh,6);	
	
	draw_set_low_title_menu(setXieEndHigh_title,1,19);	

	clean_arrarNum();
	operation_index = 2;

	setEndXieHigh_key(0,0);	

	OSTmrCreate(&timer,"updata",100,100,OS_OPT_TMR_PERIODIC ,timerUpdataInfosetEndXie,info,&err); 
	while(1)
	{
				
		OSTimeDlyHMSM(0, 0, 1,30,OS_OPT_TIME_HMSM_STRICT,&err);
		if((rec = getReturnFACE_ENUM()) < faceNull)
		{
			node->xieData->endH = g_arrNum[1];
			
			OSTmrDel(&timer,&err);
			return rec;
		}
	}
}



//卫星数据

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

void setStat_key(int id,int evnet)
{
	if(evnet & KEY_CANCEL)
	{			
		setReturnFACE_ENUM(g_currentFace->list->pro->id);	
	}
}
FACE_ENUM draw_setStat_face(Inode *node, structFaceInfo *info)
{
	OS_ERR err;
	FACE_ENUM rec = faceNull;	
	int statSingArray[12*3+1] = {5};
	register_key_event(info->id , setStat_key, KEY_CANCEL);   //娉ㄥ唽鎸夐敭

	draw_StatTitle_menu(12,12,12);
	draw_line_y(3);
	draw_setStat_num_menu(statSingArray);
	while(1)
	{		
		OSTimeDlyHMSM(0, 0,0,30,OS_OPT_TIME_HMSM_STRICT,&err);
		if((rec = getReturnFACE_ENUM()) < faceNull)
		{
				return rec;
		}
	}

}






