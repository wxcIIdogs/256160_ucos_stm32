#include "led.h"
#include "256160.h"
#include "string.h"


int time = 0;
int setTime = 0;
void timeSet()
{
	time++;
	if(time == setTime)
	{
		time = 0;
		setTime = 0;
	}
	time %= 65535;
}


/*??:1???i?*/
void Delay_us(int s)
{
	setTime = s;
	time = 0;
	while(setTime != 0);
}

void delay(int i)               
{
	Delay_us(100*i);
}

//=============transfer command to LCM===============
void transfer_command_lcd(int data1)     
{
	cs1(0);
	rs(0);
	rd(0);
	Delay_us(1);
	wr(0);
	P1(data1);
	rd(1);
	Delay_us(1);
	cs1(1);
	rd(0);
}

//-----------transfer data to LCM---------------
void transfer_data_lcd(int data1)
{
	cs1(0);
	rs(1);
	rd(0);
	Delay_us(1);
	wr(0);
	P1(data1);
	rd(1);
	Delay_us(1);
	cs1(1);
	rd(0);
}


void initial_lcd()
{   	
	lcd_reset(0);
	delay(10);
	lcd_reset(1);
	delay(10);


  transfer_command_lcd(0x30);   //EXT=0
	transfer_command_lcd(0x08); 
	transfer_command_lcd(0x94);   //Sleep out
	transfer_command_lcd(0x31);   //EXT=1
	transfer_command_lcd(0xD7);   //Autoread disable
	transfer_data_lcd(0X9F);      // 
	transfer_command_lcd(0xAA);  
	transfer_data_lcd(0x01); 
	transfer_command_lcd(0x32);   //Analog SET
	transfer_data_lcd(0x00);  		//OSC Frequency adjustment
	transfer_data_lcd(0x01);  		//Frequency on booster capacitors->6KHz
	transfer_data_lcd(0x03);  		//Bias=1/11

	transfer_command_lcd(0x20);   // Gray Level
	transfer_data_lcd(0x01); 
	transfer_data_lcd(0x03);
	transfer_data_lcd(0x05);
	transfer_data_lcd(0x07); 
	transfer_data_lcd(0x09);
	transfer_data_lcd(0x0b);
	transfer_data_lcd(0x0d);
	transfer_data_lcd(0x10);
	transfer_data_lcd(0x11);
	transfer_data_lcd(0x13);
	transfer_data_lcd(0x15);
	transfer_data_lcd(0x17);
	transfer_data_lcd(0x19);
	transfer_data_lcd(0x1b);
	transfer_data_lcd(0x1d);
	transfer_data_lcd(0x1f);

	transfer_command_lcd(0x30);   //EXT=0
	transfer_command_lcd(0xA6);
	transfer_command_lcd(0x75);   //Page Address setting	
	transfer_data_lcd(0X00);      // XS=0
	transfer_data_lcd(0X28);      // XE=159 0x28
	transfer_command_lcd(0x15);   //Clumn Address setting
	transfer_data_lcd(0X00);      // XS=0
	transfer_data_lcd(0Xff);      // XE=256

	transfer_command_lcd(0xBC);    //Data scan direction
	//transfer_data_lcd(0x00);  		 //MX.MY=Normal
	transfer_data_lcd(0x00);  		 //MX.MY=Normal

	transfer_command_lcd(0xCA);    //Display Control
	transfer_data_lcd(0X00);  		 // 
	transfer_data_lcd(0X9F);  		 //Duty=160
	transfer_data_lcd(0X20);  		 //Nline=off

	transfer_command_lcd(0xF0);    //Display Mode 
	transfer_data_lcd(0X10);  		 //10=Monochrome Mode,11=4Gray

	transfer_command_lcd(0x81);    //EV control
	transfer_data_lcd(0x38);   		 //VPR[5-0]
	transfer_data_lcd(0x04);  		 //VPR[8-6]
		
	transfer_command_lcd(0x20);    //Power control
	transfer_data_lcd(0x0B);   		 //D0=regulator ; D1=follower ; D3=booste,  on:1 off:0
	Delay_us(100);           
	transfer_command_lcd(0xAF);    //Display on
}
extern const unsigned char font16_16[][32];
extern const unsigned char font16_16_index[];
void draw_all(const unsigned char dp[][32])
{
	int x=1,y =1;
	int j;
	for(int i = 0; i < 160 ; i++)
	{
		lcd_address(x,y,16,2);
		for(j=0;j<32;j++)
		{
			transfer_data_lcd(~dp[i][j]);
		}
		x+=16;
		if(x> 256)
		{
			x = 1;
			y+=2;
			if(y> 21)
			{
				y = 1;
				clear_screen();
			}
		}
	}
}

void draw_all_zh()
{
	for(int i = 0 ;i < 50 ;i ++)
	{
		draw_all(&font16_16[i*160]);
		delay(100);
	}

}
//-----------------------------
void Drow_lcd()
{									
	
	initial_lcd(); 									
	clear_screen();
	draw_all_zh();
}




