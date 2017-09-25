#ifndef __FLASH_H_
#define __FLASH_H_
#include "stm32f10x.h"


/* ���Ͷ��� ------------------------------------------------------------------*/
/* �궨�� --------------------------------------------------------------------*/
/************************** STM32 �ڲ� FLASH ���� *****************************/
#define STM32_FLASH_SIZE        512  // ��ѡSTM32��FLASH������С(��λΪK)
#define STM32_FLASH_WREN        1    // stm32оƬ����FLASH д��ʹ��(0������;1��ʹ��)

/* ��չ���� ------------------------------------------------------------------*/
/* �������� ------------------------------------------------------------------*/
uint16_t STMFLASH_ReadHalfWord(uint32_t faddr);		  //��������

void STMFLASH_WriteLenByte(uint32_t WriteAddr, uint32_t DataToWrite, uint16_t Len );	      //ָ����ַ��ʼд��ָ�����ȵ�����
uint32_t STMFLASH_ReadLenByte(uint32_t ReadAddr, uint16_t Len );					                    	//ָ����ַ��ʼ��ȡָ����������
void STMFLASH_Write( uint32_t WriteAddr, uint16_t * pBuffer, uint16_t NumToWrite );		//��ָ����ַ��ʼд��ָ�����ȵ�����
void STMFLASH_Read( uint32_t ReadAddr, uint16_t * pBuffer, uint16_t NumToRead );   	//��ָ����ַ��ʼ����ָ�����ȵ�����
void STMFLASH_WriteStruct(uint32_t WriteAddr, void * pBuffer, uint16_t NumToWrite);
void STMFLASH_ReadStruct(uint32_t WriteAddr, void * pBuffer, uint16_t NumToWrite);

#endif

