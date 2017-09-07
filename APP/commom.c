#include "commom.h"

static struct list_pro list = {0};

structFaceInfo g_headFace = {
	0,
	.list = &list,
	0,
};
structFaceInfo *g_currentFace = &g_headFace;
FlashInfo g_initFlashStruct = {0};
Inode g_node = {0};

