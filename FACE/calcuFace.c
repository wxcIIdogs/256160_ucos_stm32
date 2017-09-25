#include "calcuFace.h"
#include "commom.h"
#include "common.h"
#include "MeterArea.h"
#include "usrtConfig.h"
#include "string.h"
void init_parcelSurvey()
{
	initMeter();
}
static int sum = 0;
static int numCount = 0;
void calcAverH(double nowH , double *averH)
{
	sum += nowH;
	numCount ++;	
	*averH = sum/numCount;	
}
void cleanCalc()
{
	sum = 0;
	numCount = 0;
}
void setData2node(Inode *node)
{
	node->parcelData->area = GPS_MeteringData.Area;
	node->parcelData->EtherDis = GPS_MeteringData.EtherDis;
	node->parcelData->PeriMeter = GPS_MeteringData.PeriMeter;
}

void updata_parcelSurvey(Inode *node,structFaceInfo *info)
{
	insertDataToMeter(node->lat , node->lot , node->speed , node->fixMode);
	calcAverH(node->nowH ,&node->parcelData->averH);	
	GetEtherDistance(node->nowH , node->parcelData->averH ,node->speed , node->flashData->bucketwidgth);
	
	setData2node(node);
	if(node->parcelData->maxH < node->nowH)
	{
		node->parcelData->maxH = node->nowH;
	}
	if(node->parcelData->minH > node->nowH)
	{
		node->parcelData->minH = node->nowH;
	}
	
	info->menu[0].num = node->parcelData->area;
	sprintf(info->menu[0].data,"%.3lf%s",info->menu[0].num*g_area_unit_num,g_area_unit);
	info->menu[1].num = node->parcelData->maxH;
	sprintf(info->menu[1].data,"%+.3lf%s",info->menu[1].num*g_len_unit_num,g_len_unit);
	info->menu[2].num = node->parcelData->averH;
	sprintf(info->menu[2].data,"%+.3lf%s",info->menu[2].num*g_len_unit_num,g_len_unit);	
	info->menu[3].num = node->nowH;
	sprintf(info->menu[3].data,"%+.3lf%s",info->menu[3].num*g_len_unit_num,g_len_unit);		
	info->menu[4].num = node->parcelData->PeriMeter;
	sprintf(info->menu[4].data,"%.3lf%s",info->menu[4].num*g_len_unit_num,g_len_unit);		
	info->menu[5].num = node->parcelData->minH;
	sprintf(info->menu[5].data,"%+.3lf%s",info->menu[5].num*g_len_unit_num,g_len_unit);			
	info->menu[6].num = node->parcelData->EtherDis;//    GPS_MeteringData.EtherDis;
	sprintf(info->menu[6].data,"%.3lf%s",info->menu[6].num*g_volue_unit_num,g_tiji_unit);				
	info->menu[7].num = GetDistance(node->Distance[0],node->Distance[1],node->lat, node->lot );     //  GPS_MeteringData.Distance;	
	sprintf(info->menu[7].data,"%.3lf%s",info->menu[7].num*g_len_unit_num,g_len_unit);					
	
	draw_menu_data(info);
}

void stop_parcelSurvey()
{
	GPS_StopMetering();
	cleanCalc();
}


void updata_planeMenu(Inode *node,structFaceInfo *info)
{
	setData2node(node);
	
	info->menu[0].num = node->aimH;
	sprintf(info->menu[0].data,"%+.3lf%s",info->menu[0].num*g_len_unit_num,g_len_unit);
	info->menu[1].num = node->nowH;
	sprintf(info->menu[1].data,"%+.3lf%s",info->menu[1].num*g_len_unit_num,g_len_unit);	
	info->menu[2].num = node->nowH - node->aimH;
	sprintf(info->menu[2].data,"%+.3lf%s",info->menu[2].num*g_len_unit_num,g_len_unit);	
	info->menu[3].num = node->action;
//wa
	if(info->menu[3].num == 1)
	{
		sprintf(info->menu[3].data,"挖");		
	}
	else if(info->menu[3].num == 2) 
	{
		sprintf(info->menu[3].data,"填");
	}
	else
	{	
		sprintf(info->menu[3].data,"平");		
	}
	info->menu[4].num = GetDistance(node->Distance[0],node->Distance[1],node->lat, node->lot ); 
	sprintf(info->menu[4].data,"%.3lf%s",info->menu[4].num*g_len_unit_num,g_len_unit);	
	info->menu[5].num = node->PlaneData->direc;
	if(info->menu[5].num > 0 && info->menu[5].num < 90)
	{
		sprintf(info->menu[5].data,"%+.0lf 东北",info->menu[5].num);		
	}
	if(info->menu[5].num > 90 && info->menu[5].num < 180)
	{
		sprintf(info->menu[5].data,"%+.0lf 东南",info->menu[5].num);		
	}
	if(info->menu[5].num > 180 && info->menu[5].num < 270)
	{
		sprintf(info->menu[5].data,"%+.0lf 西南",info->menu[5].num);		
	}
	if(info->menu[5].num > 0 && info->menu[5].num < 90)
	{
		sprintf(info->menu[5].data,"%+.0lf 西北",info->menu[5].num);		
	}
	
	info->menu[6].num = node->speed;
	sprintf(info->menu[6].data,"%+.1lfkm/h",info->menu[6].num);	
	
	draw_menu_data(info);
}

void set_xieMenu_data(Inode *node)
{
	insertDataToMeter(node->lat , node->lot , node->speed , node->fixMode);
	setData2node(node);
}

void updata_xieMenu(Inode *node,structFaceInfo *info)
{	
	set_xieMenu_data(node);

	info->menu[0].num = node->aimH;
	sprintf(info->menu[0].data,"%+.3lf%s",info->menu[0].num*g_len_unit_num,g_len_unit);
	info->menu[1].num = node->nowH;
	sprintf(info->menu[1].data,"%+.3lf%s",info->menu[1].num*g_len_unit_num,g_len_unit);	
	info->menu[2].num = node->nowH - node->aimH;
	sprintf(info->menu[2].data,"%+.3lf%s",info->menu[2].num*g_len_unit_num,g_len_unit);	
	info->menu[3].num = node->action;
//wa
	if(info->menu[3].num == 1)
	{
		sprintf(info->menu[3].data,"挖");		
	}
	else if(info->menu[3].num == 2) 
	{
		sprintf(info->menu[3].data,"填");
	}
	else
	{	
		sprintf(info->menu[3].data,"平");		
	}
	info->menu[4].num = GetDistance(node->Distance[0],node->Distance[1],node->lat, node->lot ); 
	sprintf(info->menu[4].data,"%.3lf%s",info->menu[4].num*g_len_unit_num,g_len_unit);
	
	info->menu[5].num = node->PlaneData->direc;
	if(info->menu[5].num > 0 && info->menu[5].num < 90)
	{
		sprintf(info->menu[5].data,"%+.0lf 东北",info->menu[5].num);		
	}
	if(info->menu[5].num > 90 && info->menu[5].num < 180)
	{
		sprintf(info->menu[5].data,"%+.0lf 东南",info->menu[5].num);		
	}
	if(info->menu[5].num > 180 && info->menu[5].num < 270)
	{
		sprintf(info->menu[5].data,"%+.0lf 西南",info->menu[5].num);		
	}
	if(info->menu[5].num > 0 && info->menu[5].num < 90)
	{
		sprintf(info->menu[5].data,"%+.0lf 西北",info->menu[5].num);		
	}
	
	info->menu[6].num = node->speed;
	sprintf(info->menu[6].data,"%+.1lfkm/h",info->menu[6].num);	
	
	draw_menu_data(info);
}


void update_cedata(structFaceInfo *info,structCeData *data)
{
	info->menu[0].num = data->id;
	sprintf(info->menu[0].data,"%03d",(int)info->menu[0].num);
	
	sprintf(info->menu[1].data,"%04d-%02d-%02d %02d:%02d",data->year,data->mon,data->day,data->hour,data->min );

	info->menu[1].num = data->area;
	sprintf(info->menu[2].data,"%.3lf%s",info->menu[1].num*g_area_unit_num,g_area_unit);
	info->menu[2].num = data->zhouc;
	sprintf(info->menu[3].data,"%.3lf%s",info->menu[2].num*g_len_unit_num,g_len_unit);
	info->menu[3].num = data->dhigh;
	sprintf(info->menu[4].data,"%.3lf%s",info->menu[3].num*g_len_unit_num,g_len_unit);


	info->menu[5].num = data->tufl;
	sprintf(info->menu[5].data,"%.3lf%s",info->menu[5].num*g_volue_unit_num,g_tiji_unit);
	info->menu[6].num = data->high;
	sprintf(info->menu[6].data,"%.3lf%s",data->high*g_len_unit_num,g_len_unit);
	info->menu[7].num = data->low;	
	sprintf(info->menu[7].data,"%.3lf%s",data->low*g_len_unit_num,g_len_unit);
}


static void AddChecksum(char *p)
{
    char *q = NULL;
    unsigned char sum = 0;
    for (q = p + 1, sum = 0; *q; q++)
        sum ^= *q; /* check-sum */
    sprintf(p + strlen(p), "*%02X\r\n", sum);
}
void sendIcegpsData(char data[])
{
	AddChecksum((char *)data);
	sendUsartDate((char *)data,strlen((char *)data));
}


