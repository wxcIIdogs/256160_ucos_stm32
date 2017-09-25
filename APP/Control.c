#include "256160.h"
#include "chinese_code.h"
#include "commom.h"
#include "string.h"


static int currentX = 1;
static int currentY = 1;
static int blackColor = BACK_WHITE;
static int size_count = 16;

void lcd_address(int x,int y,int x_total,int y_total)
{
	x=x-1;
	y=y-1;
	
	transfer_command_lcd(0x15);	//Set Column Address
	transfer_data_lcd(x);		
	transfer_data_lcd(x+x_total-1);		

	transfer_command_lcd(0x75);	//Set Page Address	
	transfer_data_lcd(y);		
	transfer_data_lcd(y+y_total-1);	
	transfer_command_lcd(0x30);	
	transfer_command_lcd(0x5c);
}


void clear_screen()
{
	int i,j;	
	lcd_address(1,1,256,21);
	for(i=0;i<21;i++)
	{
		for(j=0;j<256;j++)
		{
			transfer_data_lcd(0x00);
		}
	}
}



void disp_clean(int x,int y,int len,int count)
{
	int j;	
	lcd_address(x,y,size_count*len,count);
	for(int i = 0 ; i < len ; i++)
	{		
		for(int k = 0; k < count ; k ++)
		{
			for(j=0;j<size_count;j++)
			{
				transfer_data_lcd(0x00);
			}
		}
	}
}



void setXLen_8_char()
{
	size_count = 8;
}
void setXLen_16_ZH()
{
	size_count = 16;
}
void disp_8x16_num(int x, int y, uchar *dp,int flag)
{
	setXLen_8_char();	  //设置成字符模�?
	disp_clean(x,y,1,2);  //清除一个空格空�?
	setXLen_16_ZH();	  //还原

	lcd_address(x,y,CHAR_COUNT,2);
	for(int i = 0; i < 16 ; i ++)
	{
		if(flag == 1)
		{
			transfer_data_lcd(dp[i]);
		}
		else
		{
			transfer_data_lcd(~dp[i]);
		}
	}
}
void disp_16x16_zh(int x,int y, uchar dp[][32],int len,int flag)
{
	disp_clean(x,y,len,2);

	for(int j = 0; j < len ; j++)
	{
		lcd_address(x,y,CHINA_COUNT,2);
		for(int i = 0; i < 32 ; i ++)
		{
			if(flag == 1)
			{
				transfer_data_lcd(dp[j][i]);
			}
			else
			{
				transfer_data_lcd(~dp[j][i]);
			}
			
		}
	}

}

void setIndex()
{
	if(currentX > 256)
	{
		currentX = 1;
		if((currentY+=2) > 21)
		{
			currentY = 1;
		}
	}
}

int getZhIndex(unsigned char *data,int flag)
{
	if(flag == 1)
	{//再字库里面查�?
		return (94*(data[0] - 0xa1) +(data[1]-0xa1));
	}
	if(flag == 0)
	{//再字模里面查�?
		
	}
	return 1;
}
extern const unsigned char font16_16[][32];
int getZHdisDp(unsigned char *data,uchar dp[][32])
{
	int index = 0;
	int i = 0;
	for( i = 0 ; i < strlen((char *)data);i+=2)
	{
		index = getZhIndex(&(data[i]),1);
		memcpy(dp[i/2],font16_16[index],32);
	}
	return i/2;
}
void disp_hz(uchar *data)
{
	uchar dp[20][32];
	int len = getZHdisDp(data,dp);
	disp_16x16_zh(currentX,currentY,dp,len,blackColor);
}
void setCurrentIndex(int x,int y)
{
 	currentX = x;
 	currentY = y;
}

void setBackColor(int index)
{
	blackColor = index;
}

int fputc(int ch, FILE *f)
{
	/* 将Printf内容发往串口*/
	//USART_SendData(USART2, (unsigned char) ch);
	//while (!(USART2->SR & USART_FLAG_TXE));
	static char prochar = 0;
	if(ch >= 0x20 && ch <= 0x7E)
	{
		uchar dp[16];
		memcpy(dp,CHAR_4x16[ch-0x20],16);
		disp_8x16_num(currentX,currentY,dp,blackColor);
		currentX += CHAR_COUNT;
	}
	if(prochar != 0)
	{
		uchar data[3] = {prochar,(char )ch,'\0'};		
		disp_hz(data);
		currentX += CHINA_COUNT;
		prochar = 0;
	}
	else
	{
		if(prochar == 0 && (ch < 0x20 || ch > 0x7E))
		{
			prochar = ch;
		}
	}
	setIndex();

	return (ch);
}


//menu == 0
//
//
//
//
FACE_ENUM Draw_face(int index)
{
	FACE_ENUM menu = faceNull;	
	if(g_arrayface == &g_headFace)
	{
		index = MAINMENU;
	}
	if(index == faceNull)
	{//后退到上�?
		clear_screen();
		menu = g_currentFace->func(&g_node,g_currentFace);		
		g_currentFace->data = NULL;
		g_currentFace->list->next = NULL;
		g_currentFace = g_currentFace->list->pro;	
	}
	else
	{//进入某个界面
		g_currentFace->list->next = &g_arrayface[index];
		if(g_currentFace->id != g_arrayface[index].id )
		{
			g_arrayface[index].list->pro = g_currentFace;
		}
		g_currentFace = &g_arrayface[index];
 		clear_screen();
		menu = g_currentFace->func(&g_node,g_currentFace);
		if(menu == g_currentFace->list->pro->id -1)
		{
			g_currentFace->data = NULL;
			g_currentFace->list->next = NULL;
			g_currentFace = g_currentFace->list->pro;
		}			
	}
	
	return menu;
}

const uchar lintArray[] = {0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08};

void draw_line_y(int y)
{
	for(int j = 1; j < 256 ; j+=8)
	{
		lcd_address(j,y,CHAR_COUNT,1);
		for(int i = 0; i < 8 ; i ++)
		{
			transfer_data_lcd(lintArray[i]);			
		}
	}
}

void draw_line_stat_sign(int stren)
{
	lcd_address(currentX,currentY,stren,2);
	for(int j = 0; j < stren ; j++)
	{		
		for(int i = 0; i < 16 ; i ++)
		{
			transfer_data_lcd(0xff);			
		}
	}
}
volatile FLASH_Status wxcFLASHStatus = FLASH_COMPLETE;

void Readflash(uint32_t Address ,double *getdata)
{	
	memcpy(getdata,(uint32_t *)Address,8);
}

void Writeflash(uint32_t Address,  double *data)
{

	uint32_t ddd[3] = {0};
	memcpy(ddd,data,8);
	if(wxcFLASHStatus == FLASH_COMPLETE)
	{
		wxcFLASHStatus = FLASH_ProgramWord(Address, ddd[0]);
		wxcFLASHStatus = FLASH_ProgramWord(Address+4, ddd[1]);
		
	}
}


void writeFlashStruct()
{
	FLASH_Unlock();
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR); 
	wxcFLASHStatus = FLASH_ErasePage(StartAdress);
	int i =0;
	i+=8;
	Writeflash(StartAdress+i, &g_initFlashStruct.antlocal);
	i+=8;
	Writeflash(StartAdress+i, &g_initFlashStruct.areaunit);
	i+=8;	
	Writeflash(StartAdress+i, &g_initFlashStruct.bucketwidgth);
	i+=8;
	Writeflash(StartAdress+i, &g_initFlashStruct.channel);
	i+=8;	
	Writeflash(StartAdress+i, &g_initFlashStruct.dataAdress);
	i+=8;	
	Writeflash(StartAdress+i, &g_initFlashStruct.dataCount);
	i+=8;
	Writeflash(StartAdress+i, &g_initFlashStruct.langselect);
	i+=8;	
	Writeflash(StartAdress+i, &g_initFlashStruct.lengthunit);
	i+=8;	
	Writeflash(StartAdress+i, &g_initFlashStruct.timesetlocal);
	i+=8;	
	Writeflash(StartAdress+i, &g_initFlashStruct.timesetXia);	
	i+=8;	
	Writeflash(StartAdress+i, &g_initFlashStruct.volumeunit);

	FLASH_Lock();	
}
void readFlashStruct()
{

	int i = 0;
	Readflash(StartAdress+i, &g_initFlashStruct.antlocal);
	i+=8;
	Readflash(StartAdress+i, &g_initFlashStruct.areaunit);
	i+=8;	
	Readflash(StartAdress+i, &g_initFlashStruct.bucketwidgth);
	i+=8;
	Readflash(StartAdress+i, &g_initFlashStruct.channel);
	i+=8;	
	Readflash(StartAdress+i, &g_initFlashStruct.dataAdress);
	i+=8;	
	Readflash(StartAdress+i, &g_initFlashStruct.dataCount);
	i+=8;	
	Readflash(StartAdress+i, &g_initFlashStruct.langselect);
	i+=8;	
	Readflash(StartAdress+i, &g_initFlashStruct.lengthunit);
	i+=8;	
	Readflash(StartAdress+i, &g_initFlashStruct.timesetlocal);
	i+=8;	
	Readflash(StartAdress+i, &g_initFlashStruct.timesetXia);	
	i+=8;	
	Readflash(StartAdress+i, &g_initFlashStruct.volumeunit);	
	i+=8;		

}



