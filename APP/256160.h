#ifndef __19264__
#define __19264__

#include "stm32f10x.h"
#include "string.h"

#include "stdlib.h"
#include "stdio.h"

//#include "measure.h"
//#include "MeterArea.h"

#define X_HRAD  (256-15)
#define X_TILE  (-16)
#define COUNT32 4
#define COUNT16 2
#define COUNT8 1
#define COUNT_TYPE   16 
#define CHINA_COUNT  16
#define CHAR_COUNT   8
#define uchar unsigned char 
#define uint unsigned int
	

#define ARRAY(__X__)    (sizeof(__X__)/sizeof(__X__[0]))



extern void transfer_command_lcd(int data1);
extern void transfer_data_lcd(int data1);
extern void delay(int i);

extern void lcd_address(int x,int y,int x_total,int y_total);
extern void disp_16x16_num(int x,int y , uchar dp[][16],int len,int flag);
extern void disp_8x16_num(int x, int y, uchar *dp,int flag);


extern void clear_screen(void);

extern void Drow_lcd(void );

extern void setCurrentIndex(int x,int y);
extern void setBackColor(int index);

extern void draw_line_stat_sign(int stren);

#endif

