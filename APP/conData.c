#include "commom.h"
#include "drawFace.h"
#include "drawSysSet.h"
#include "minmea.h"
#include "common.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"


void updateInfoData()
{
        
	g_node.speed = gps_data.speed;
	memcpy(&g_node.time,&gps_data.time,sizeof(g_node.time));
	memcpy(&g_node.date,&gps_data.date,sizeof(g_node.date));

	g_node.fixMode = gps_data.fixMode;
	g_node.lat = gps_data.lat;
	g_node.lot = gps_data.lot;
	g_node.nowH = gps_data.nowH;
	g_node.delayTime = gps_data.delay;
	g_node.stat = gps_data.sate;

	g_node.PlaneData->direc = gps_data.direc;

	g_node.action = gps_data.rev_data.buckStat;
	g_node.xieData->direc = gps_data.direc;
	g_node.aimH = gps_data.rev_data.aimH;

	g_node.workMode = gps_data.rev_data.wordMode;
	g_node.autoMode = gps_data.rev_data.autoMode;
	g_node.dataType = gps_data.rev_data.dataype;
	g_node.Channel = gps_data.rev_data.NowChannel;

	g_node.diffH = gps_data.rev_data.nowdiffH;
	g_node.flashData->MaxChannel = gps_data.rev_data.MaxChannel;
	g_node.flashData->MinChannel = gps_data.rev_data.MinChannel;
	g_node.isConnect = gps_data.rev_data.isConnect;
}
structMenu mainMenu[] = 
{
	//下标从x = 1, y = 8 开�?  右边对其x�?40
	{3,"�ؿ����",{0},0,1,7,0},
	{7,"��ƽ��",{0},0,2,9,0},
	{8,"��б��",{0},0,2,11,0},
	{10,"�����ź�",{0},0,140,7,0},
	{6,"��������",{0},0,140,9,0},
	{2,"ϵͳ����",{0},0,140,11,0},
};

structMenu sysSet[] = 
{
	//下标从x = 1, y = 8 开�?  右边对其x�?40
	{11,"������λ","0",0,2,7,0},
	{12,"��̨Ƶ��",{0},0,2,9,0},
	{13,"�������",{0},0,2,11,0},
	{14,"����λ��",{0},0,2,13,0},
	{15,"����У׼",{0},0,2,15,0},
	{16,"ʱ������",{0},0,140,7,0},
	{17,"����ѡ��",{0},0,140,9,0},
	{18,"����ڴ�",{0},0,140,11,0},
	{19,"�йر���",{0},0,140,13,0},
};
//�ؿ����
structMenu parcelSurvey[] = 
{
	{1,"���:",{0},1,2,7,0},
	{2,"���:",{0},0,2,9,0},
	{3,"ƽ��:",{0},0,2,11,0},
	{4,"��ǰ:",{0},0,2,13,0},
	{5,"�ܳ�:",{0},0,140,7,0},
	{6,"���:",{0},0,140,9,0},
	{7,"����:",{0},2,140,11,0},
	{8,"����:",{0},0,140,13,0},
};
//��ƽ��
structMenu planeMenu[] = 
{
	{1,"���:",{0},0,60,7,0},
	{2,"��ǰ:",{0},0,60,9,0},
	{3,"�߲�:",{0},0,60,11,0},
	{4,"����:", {0},0,60,13,0},
	{5,"�������:",{0},0,60,15,0},
	{6,"ǰ������:",{0},0,60,17,0},
	{7,"��ʻ�ٶ�:",{0},0,60,19,0},
};
//��б��
structMenu xieMenu[] = 
{
	{1,"���:",{0},0,60,7,0},
	{2,"��ǰ:",{0},0,60,9,0},
	{3,"�߲�:",{0},0,60,11,0},
	{4,"����:",{0},0,60,13,0},
	{5,"�������:",{0},0,60,15,0},
	{6,"ǰ������: ",{0},0,60,17,0},
	{7,"��ʻ�ٶ�:",{0},0,60,19,0},
};
//��������
structMenu meauseData[] = 
{
	{1,"���:",{0},0,2,4,0},
	{2,"ʱ��:",{0},0,2,6,0},//%d-%02d-%02d %02d:%02d
	{3,"���:",{0},0,2,8,0},
	{4,"�ܳ�:",{0},0,2,10,0},
	{5,"ƽ���߶�:",{0},0,2,12,0},
	{6,"��������:",{0},0,2,14,0},	
	{7,"��ߵ�:",{0},0,2,16,0},//%.2lf/%.2lf"
	{8,"��͵�:",{0},0,2,18,0},//%.2lf/%.2lf"
};

struct list_pro list[22] = {0};
structFaceInfo g_arrayface[] = 
{
	//id   ishead   title  list     func   facemenu          void *data
	
	{1 , 1 , "���ӵ���ƽ�ػ�" ,  &list[1]  ,  draw_main_face ,  mainMenu  ,6 ,  NULL} ,   //1
	{2 , 1 , "ϵͳ����" ,       &list[2]  ,  draw_sysSet_face  ,  sysSet  , 9 , NULL} , //2
	{3 , 1 , "�ؿ����" ,       &list[3]  ,  draw_parcelSurvey_face  ,  parcelSurvey  ,8 , NULL} , //3
	{4 , 1 , "��ƽ��" ,         &list[4] , draw_planeMenu_face , planeMenu ,  7, NULL} , //4
	{5 , 1 , "��б��" ,         &list[5] , draw_xieMenu_face , xieMenu , 7,NULL} , //5
	{6 , 0 , "��������" ,       &list[6] , draw_meauseData_face , meauseData , 8 , NULL} , //6
	{7 , 1 , "����ƽ��߶�" ,   &list[7] , draw_setPlaneHigh_face , NULL ,0 ,  NULL} , //7
	{8 , 1 , "����б�����" ,   &list[8] , draw_setXieHigh_face , NULL ,0 , NULL} , //8
	{9 , 1 , "����б���յ�" ,   &list[9] , draw_setEndXieHigh_face , NULL , 0 ,NULL} , //9
	{10 , 1 , "�����ź�" ,      &list[10] , draw_setStat_face , NULL , 0 ,NULL} , //10
	{11 , 1 , "������λ" ,      &list[11] , draw_unitmeasure_face , NULL ,0 , NULL} , //11
	{12 , 1 , "��̨Ƶ��" ,      &list[12] , draw_boardchannel_face , NULL ,0 , NULL} , //12
	{13 , 1 , "�������" ,      &list[13] , draw_bucketwidght_face , NULL ,0 , NULL} , //13
	{14 , 1 , "����λ��" ,      &list[14] , draw_antlocal_face , NULL ,0 , NULL} , //14
	{15 , 1 , "����У׼" ,      &list[15] , draw_roisedownadj_face , NULL ,0 , NULL} , //15
	{16 , 1 , "ʱ������" ,      &list[16] , draw_timeset_face , NULL ,0 , NULL} , //16
	{17 , 1 , "����ѡ��" ,      &list[17] , draw_langselect_face , NULL ,0 , NULL} , //17
	{18 , 1 , "����ڴ�" ,      &list[18] , draw_cleanmem_face , NULL ,0 , NULL} , //18
	{19 , 1 , "�йر���" ,      &list[19] , draw_about_face , NULL ,0 , NULL} , //19
};




