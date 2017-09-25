#ifndef __CALCUFACE__
#define __CALCUFACE__
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "commom.h"
#include "common.h"


extern void init_parcelSurvey(void);


extern void updata_parcelSurvey(Inode *node,structFaceInfo *info);


extern void stop_parcelSurvey(void);


extern void updata_planeMenu(Inode *node,structFaceInfo *info);

extern void updata_xieMenu(Inode *node,structFaceInfo *info);


extern void update_cedata(structFaceInfo *info,structCeData *data);
extern void set_xieMenu_data(Inode *node);


extern void setxieEndData(Inode *node);



extern void sendIcegpsData(char data[]);








#endif
