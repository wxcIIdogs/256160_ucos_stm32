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
	//涓嬫爣浠巟 = 1, y = 8 寮�濮?  鍙宠竟瀵瑰叾x鏄?40
	{3,"地块测量",{0},0,1,7,0},
	{7,"做平面",{0},0,2,9,0},
	{8,"做斜面",{0},0,2,11,0},
	{10,"卫星信号",{0},0,140,7,0},
	{6,"测量数据",{0},0,140,9,0},
	{2,"系统设置",{0},0,140,11,0},
};

structMenu sysSet[] = 
{
	//涓嬫爣浠巟 = 1, y = 8 寮�濮?  鍙宠竟瀵瑰叾x鏄?40
	{11,"度量单位","0",0,2,7,0},
	{12,"电台频道",{0},0,2,9,0},
	{13,"铲斗宽度",{0},0,2,11,0},
	{14,"天线位置",{0},0,2,13,0},
	{15,"升降校准",{0},0,2,15,0},
	{16,"时间设置",{0},0,140,7,0},
	{17,"语言选择",{0},0,140,9,0},
	{18,"清空内存",{0},0,140,11,0},
	{19,"有关本机",{0},0,140,13,0},
};
//地块测量
structMenu parcelSurvey[] = 
{
	{1,"面积:",{0},1,2,7,0},
	{2,"最高:",{0},0,2,9,0},
	{3,"平均:",{0},0,2,11,0},
	{4,"当前:",{0},0,2,13,0},
	{5,"周长:",{0},0,140,7,0},
	{6,"最低:",{0},0,140,9,0},
	{7,"土方:",{0},2,140,11,0},
	{8,"距离:",{0},0,140,13,0},
};
//做平面
structMenu planeMenu[] = 
{
	{1,"标高:",{0},0,60,7,0},
	{2,"当前:",{0},0,60,9,0},
	{3,"高差:",{0},0,60,11,0},
	{4,"动作:", {0},0,60,13,0},
	{5,"距离起点:",{0},0,60,15,0},
	{6,"前进方向:",{0},0,60,17,0},
	{7,"行驶速度:",{0},0,60,19,0},
};
//做斜面
structMenu xieMenu[] = 
{
	{1,"标高:",{0},0,60,7,0},
	{2,"当前:",{0},0,60,9,0},
	{3,"高差:",{0},0,60,11,0},
	{4,"动作:",{0},0,60,13,0},
	{5,"距离起点:",{0},0,60,15,0},
	{6,"前进方向: ",{0},0,60,17,0},
	{7,"行驶速度:",{0},0,60,19,0},
};
//测量数据
structMenu meauseData[] = 
{
	{1,"编号:",{0},0,2,4,0},
	{2,"时间:",{0},0,2,6,0},//%d-%02d-%02d %02d:%02d
	{3,"面积:",{0},0,2,8,0},
	{4,"周长:",{0},0,2,10,0},
	{5,"平均高度:",{0},0,2,12,0},
	{6,"土方计算:",{0},0,2,14,0},	
	{7,"最高点:",{0},0,2,16,0},//%.2lf/%.2lf"
	{8,"最低点:",{0},0,2,18,0},//%.2lf/%.2lf"
};

struct list_pro list[22] = {0};
structFaceInfo g_arrayface[] = 
{
	//id   ishead   title  list     func   facemenu          void *data
	
	{1 , 1 , "冰河导航平地机" ,  &list[1]  ,  draw_main_face ,  mainMenu  ,6 ,  NULL} ,   //1
	{2 , 1 , "系统设置" ,       &list[2]  ,  draw_sysSet_face  ,  sysSet  , 9 , NULL} , //2
	{3 , 1 , "地块测量" ,       &list[3]  ,  draw_parcelSurvey_face  ,  parcelSurvey  ,8 , NULL} , //3
	{4 , 1 , "做平面" ,         &list[4] , draw_planeMenu_face , planeMenu ,  7, NULL} , //4
	{5 , 1 , "做斜面" ,         &list[5] , draw_xieMenu_face , xieMenu , 7,NULL} , //5
	{6 , 0 , "测量数据" ,       &list[6] , draw_meauseData_face , meauseData , 8 , NULL} , //6
	{7 , 1 , "设置平面高度" ,   &list[7] , draw_setPlaneHigh_face , NULL ,0 ,  NULL} , //7
	{8 , 1 , "设置斜面起点" ,   &list[8] , draw_setXieHigh_face , NULL ,0 , NULL} , //8
	{9 , 1 , "设置斜面终点" ,   &list[9] , draw_setEndXieHigh_face , NULL , 0 ,NULL} , //9
	{10 , 1 , "卫星信号" ,      &list[10] , draw_setStat_face , NULL , 0 ,NULL} , //10
	{11 , 1 , "度量单位" ,      &list[11] , draw_unitmeasure_face , NULL ,0 , NULL} , //11
	{12 , 1 , "电台频道" ,      &list[12] , draw_boardchannel_face , NULL ,0 , NULL} , //12
	{13 , 1 , "铲斗宽度" ,      &list[13] , draw_bucketwidght_face , NULL ,0 , NULL} , //13
	{14 , 1 , "天线位置" ,      &list[14] , draw_antlocal_face , NULL ,0 , NULL} , //14
	{15 , 1 , "升降校准" ,      &list[15] , draw_roisedownadj_face , NULL ,0 , NULL} , //15
	{16 , 1 , "时间设置" ,      &list[16] , draw_timeset_face , NULL ,0 , NULL} , //16
	{17 , 1 , "语言选择" ,      &list[17] , draw_langselect_face , NULL ,0 , NULL} , //17
	{18 , 1 , "清空内存" ,      &list[18] , draw_cleanmem_face , NULL ,0 , NULL} , //18
	{19 , 1 , "有关本机" ,      &list[19] , draw_about_face , NULL ,0 , NULL} , //19
};




