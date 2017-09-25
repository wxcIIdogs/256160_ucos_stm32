#include "commom.h"
#include "common.h"
#include "uart.h"
#include "includes.h"
#include "minmea.h"
#include <stdio.h>
#include <string.h>
extern OS_SEM uartSemEvent;






GPS_DATA gps_data = {0};
void input_ublox(char * ch)
{
	OS_ERR err;
	char *line = ch;
	switch (minmea_sentence_id(line, false)) {
		case MINMEA_SENTENCE_RMC: {
				struct minmea_sentence_rmc g_rmcframe;
				if (minmea_parse_rmc(&g_rmcframe, line)) {
				
					/*printf(INDENT_SPACES "$xxRMC floating point degree coordinates and speed: (%f,%f) %f\n",
										minmea_tocoord(&g_rmcframe.latitude),
										minmea_tocoord(&g_rmcframe.longitude),
										minmea_tofloat(&g_rmcframe.speed));
                               */
                     gps_data.speed = minmea_tofloat(&g_rmcframe.speed);
                     memcpy(&gps_data.time,&g_rmcframe.time,sizeof(g_rmcframe.time));
                     memcpy(&gps_data.date,&g_rmcframe.date,sizeof(g_rmcframe.date));                     					                                   
										 gps_data.direc = minmea_tofloat(&g_rmcframe.course);
				}
				else {
						//printf(INDENT_SPACES "$xxRMC sentence is not parsed\n");
				}
		} break;

		case MINMEA_SENTENCE_GGA: {
				struct minmea_sentence_gga g_ggaframe;
				if (minmea_parse_gga(&g_ggaframe, line)) {
						//printf(INDENT_SPACES "$xxGGA: fix quality: %d\n", g_ggaframe.fix_quality);
						gps_data.fixMode = g_ggaframe.fix_quality;
						gps_data.lat = minmea_tofloat(&g_ggaframe.latitude);
						gps_data.lot = minmea_tofloat(&g_ggaframe.longitude);
						gps_data.nowH = minmea_tofloat(&g_ggaframe.altitude) + minmea_tofloat(&g_ggaframe.height);					
						gps_data.delay = g_ggaframe.dgps_age;
						gps_data.sate = g_ggaframe.satellites_tracked;
						
				}
				else {
						//printf(INDENT_SPACES "$xxGGA sentence is not parsed\n");
				}
		} break;
		case MINMEA_SENTENCE_GSA: {
				struct minmea_sentence_gsa g_gsaframe;
				if (minmea_parse_gsa(&g_gsaframe, line)) {
						//printf(INDENT_SPACES "$xxGGA: fix quality: %d\n", g_gsaframe.fix_quality);
						memcpy(gps_data.statStren,g_gsaframe.sats,sizeof(int)*12);
				}
				else {
						//printf(INDENT_SPACES "$xxGSA sentence is not parsed\n");
				}
		} break;

		case MINMEA_SENTENCE_GSV: {
				struct minmea_sentence_gsv g_gsvframe;
				if (minmea_parse_gsv(&g_gsvframe, line)) {
				
						/*
						printf(INDENT_SPACES "$xxGSV: message %d of %d\n", g_gsvframe.msg_nr, g_gsvframe.total_msgs);
						printf(INDENT_SPACES "$xxGSV: sattelites in view: %d\n", g_gsvframe.total_sats);
						for (int i = 0; i < 4; i++)
								printf(INDENT_SPACES "$xxGSV: sat nr %d, elevation: %d, azimuth: %d, snr: %d dbm\n",
										g_gsvframe.sats[i].nr,
										g_gsvframe.sats[i].elevation,
										g_gsvframe.sats[i].azimuth,
										g_gsvframe.sats[i].snr);
                                       */										
				}
				else {
						//printf(INDENT_SPACES "$xxGSV sentence is not parsed\n");
				}
		} break;
		case MINMEA_SENTENCE_ICEGPS: {
			ICEPGS_Data g_IcegpsData = gps_data.rev_data;
			char *p = ",*";
			char *temp;
			if(minmea_parse_icegps(&g_IcegpsData,line))
			{
				switch(g_IcegpsData.dataype)
				{
					case VERSION:
						
						temp = strtok(line,p);//icegps
						temp = strtok(NULL,p);//type
						temp = strtok(NULL,p);//机器型号						
						memcpy(g_IcegpsData.machModol,temp,strlen(temp));
						temp = strtok(NULL,p);//设备序列						
						memcpy(g_IcegpsData.machSN,temp,strlen(temp));
						temp = strtok(NULL,p);//软件版本						
						memcpy(g_IcegpsData.machVersion,temp,strlen(temp));
						temp = strtok(NULL,p);//板卡型号						
						memcpy(g_IcegpsData.machBoard,temp,strlen(temp));
						temp = strtok(NULL,p);//数传型号						
						memcpy(g_IcegpsData.machTran,temp,strlen(temp));
						temp = strtok(NULL,p);//当前频道
						g_IcegpsData.NowChannel = temp[0]-'0';
						incodeing_return_ok();
					break;
					case RADIO:						
						temp = strtok(line,p);//icegps
						temp = strtok(NULL,p);//type
						temp = strtok(NULL,p);//数传型号
						temp = strtok(NULL,p);//最大频道
						g_IcegpsData.MaxChannel = temp[0] -'0';
						temp = strtok(NULL,p);//最小频道
						g_IcegpsData.MinChannel = temp[0]-'0';						
						temp = strtok(NULL,p);//当前频道
						g_IcegpsData.NowChannel = temp[0]-'0';						
						incodeing_return_ok();						
					break;
					case CONTROL:
						temp = strtok(line,p);//icegps
						temp = strtok(NULL,p);//type
						temp = strtok(NULL,p);//铲斗状态
						g_IcegpsData.buckStat = temp[0]-'0';
						incodeing_return_ok();						
					break;
					case MOED:
						temp = strtok(line,p);//icegps
						temp = strtok(NULL,p);//type
						temp = strtok(NULL,p);//工作模式
						g_IcegpsData.autoMode = temp[0] - '0';
						incodeing_return_ok();						
					break;
					case STATUS:
						temp = strtok(line,p);//icegps
						temp = strtok(NULL,p);//type
						temp = strtok(NULL,p);//工作状态
						g_IcegpsData.wordMode = temp[0] - '0';
						temp = strtok(NULL,p);//铲斗状态
						g_IcegpsData.buckStat = temp[0] - '0';
						temp = strtok(NULL,p);//工作模式
						g_IcegpsData.autoMode = temp[0] - '0';	
						incodeing_return_ok();												
					break;
					case GRADER:
						temp = strtok(line,p);//icegps
						temp = strtok(NULL,p);//type
						temp = strtok(NULL,p);//工作状态
						g_IcegpsData.wordMode = temp[0] - '0';
						if(g_IcegpsData.wordMode !=2)
							break;
						temp = strtok(NULL,p);//目标高度
						g_IcegpsData.aimH = atof(temp);
						temp = strtok(NULL,p);//实时高差
						g_IcegpsData.nowdiffH = atof(temp);
						temp = strtok(NULL,p);//铲斗状态
						g_IcegpsData.buckStat = temp[0] - '0';
						temp = strtok(NULL,p);//工作模式
						g_IcegpsData.autoMode = temp[0] - '0';
						incodeing_return_ok();						
					break;
					case MACH_OK:	
					//修改
					g_IcegpsData.isConnect = 1;
					break;
					case MACH_ERROR:
					
					break;
					case MACH_UNLINK:
					g_IcegpsData.isConnect = 0;					
					break;
					default:break;
				}
				memcpy(&gps_data.rev_data,&g_IcegpsData,sizeof(g_IcegpsData));
			}
		} break;

		default: {
				//printf(INDENT_SPACES "$xxxxx sentence is not parsed\n");
		} break;
	}
	OSSemPost(&uartSemEvent,OS_OPT_POST_1,&err);
}
int checkout(u8 ch)
{
	if(ch == '$')
	{
		return 1;
	}
	if(ch == 0x0A)
	{
		return 0;
	}
	return 1;
}
char g_arrGetData[MINMEA_MAX_LENGTH] = {0};
void callback_rev_data(u8 ch)
{
	static int flag = 1;
	static int index = 0;
	if(checkout(ch))
	{
		flag = 1;		
	}
	else
	{
		flag = 0;
		g_arrGetData[index++] = ch;
		input_ublox(g_arrGetData);
		index = 0;
		memset(g_arrGetData,0,MINMEA_MAX_LENGTH);
	}
	if(flag)
	{
		g_arrGetData[index++] = ch;
	}
	
}

