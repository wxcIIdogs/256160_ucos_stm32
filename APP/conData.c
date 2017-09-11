#include "commom.h"
#include "drawFace.h"
#include "drawSysSet.h"


void updateInfoData()
{
	
}






structMenu mainMenu[] = 
{
	//下标从x = 1, y = 8 开始   右边对其x是140
	{3,"1.�ؿ����",0,0,1,7,0},
	{4,"2.��ƽ��",0,0,2,9,0},
	{5,"3.��б��",0,0,2,11,0},
	{10,"4.�����ź�",0,0,140,7,0},
	{6,"5.��������",0,0,140,9,0},
	{2,"6.ϵͳ����",0,0,140,11,0},
};

structMenu sysSet[] = 
{
	//下标从x = 1, y = 8 开始   右边对其x是140
	{11,"1.������λ",0,0,2,7,0},
	{12,"2.��̨Ƶ��",0,0,2,9,0},
	{13,"3.�������",0,0,2,11,0},
	{14,"4.����λ��",0,0,2,13,0},
	{15,"5.����У׼",0,0,2,15,0},
	{16,"6.ʱ������",0,0,140,7,0},
	{17,"7.����ѡ��",0,0,140,9,0},
	{18,"8.����ڴ�",0,0,140,11,0},
	{19,"9.�йر���",0,0,140,13,0},
};
//�ؿ����
structMenu parcelSurvey[] = 
{
	{1,"���:%c%.3lfĶ",0,0,2,7,0},
	{2,"���:%c%.3lf��",0,0,2,9,0},
	{3,"ƽ��:%c%.3lf��",0,0,2,11,0},
	{4,"��ǰ:%c%.3lf��",0,0,2,13,0},
	{5,"�ܳ�:%c%.3lf��",0,0,140,7,0},
	{6,"���:%c%.3lf��",0,0,140,9,0},
	{7,"����:%c%.3lf��",0,0,140,11,0},
	{8,"����:%c%.3lf��",0,0,140,13,0},
};
//��ƽ��
structMenu planeMenu[] = 
{
	{1,"���:%c%.3lf��",0,0,60,7,0},
	{2,"��ǰ:%c%.3lf��",0,0,60,9,0},
	{3,"�߲�:%c%.3lf��",0,0,60,11,0},
	{4,"����:��",       0,0,60,13,0},
	{5,"�������:%.3lf��",0,0,60,15,0},
	{6,"ǰ������:%d ����",0,0,60,17,0},
	{7,"��ʻ�ٶ�:%0lffKm/h",0,0,60,19,0},
};
//��б��
structMenu xieMenu[] = 
{
	{1,"���:%c%.3lf��",0,0,60,7,0},
	{2,"��ǰ:%c%.3lf��",0,0,60,9,0},
	{3,"�߲�:%c%.3lf��",0,0,60,11,0},
	{4,"����:��",       0,0,60,13,0},
	{5,"�������:%.3lf��",0,0,60,15,0},
	{6,"ǰ������:%d ����",0,0,60,17,0},
	{7,"��ʻ�ٶ�:%01ffKm/h",0,0,60,19,0},
};
//��������
structMenu meauseData[] = 
{
	{1,"���:%03d",0,0,2,4,0},
	{2,"���:%dĶ",0,0,2,6,0},
	{3,"�ܳ�:%dĶ",0,0,2,8,0},
	{4,"����:%.2dĶ",0,0,2,10,0},
	{5,"ʱ��:",0,0,90,4,0},//%d-%02d-%02d %02d:%02d
	{6,"��������:%.0lf��",0,0,106,6,0},
	{7,"������:%.0lf��",0,0,106,8,0},	
	{8,"��/��:",0,0,106,10,0},//%.2lf/%.2lf"
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




