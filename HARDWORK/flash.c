#include "flash.h"
#include "string.h"
/* ˽�����Ͷ��� --------------------------------------------------------------*/
/* ˽�к궨�� ----------------------------------------------------------------*/
#if STM32_FLASH_SIZE < 256
  #define STM_SECTOR_SIZE  1024 //�ֽ�
#else 
  #define STM_SECTOR_SIZE	 2048
#endif


/* ˽�б��� ------------------------------------------------------------------*/
#if STM32_FLASH_WREN	//���ʹ����д 
static uint16_t STMFLASH_BUF [ STM_SECTOR_SIZE / 2 ];//�����2K�ֽ�
#endif

/* ��չ���� ------------------------------------------------------------------*/
/* ˽�к���ԭ�� --------------------------------------------------------------*/
/* ������ --------------------------------------------------------------------*/

/**
  * ��������: ��ȡָ����ַ�İ���(16λ����)
  * �������: faddr:����ַ(�˵�ַ����Ϊ2�ı���!!)
  * �� �� ֵ: ����ֵ:��Ӧ����.
  * ˵    ������
  */
void STMFLASH_WriteStruct(uint32_t WriteAddr, void * pBuffer, uint16_t NumToWrite)
{
	uint16_t numData = 0;
	uint16_t Buffer[STM_SECTOR_SIZE/2];
	int i = 0;
	uint16_t *ppp;
	ppp = (uint16_t *)pBuffer;
	//void STMFLASH_Write ( uint32_t WriteAddr, uint16_t * pBuffer, uint16_t NumToWrite )	
	for(i = 0; i < NumToWrite/2 ;i ++)
	{
		Buffer[i] = *ppp;
		ppp ++;
		numData ++;
	}
	STMFLASH_Write(WriteAddr,Buffer,numData);
	
}	
void STMFLASH_ReadStruct(uint32_t ReadAddr, void * pBuffer, uint16_t NumToRead)
{
	uint16_t Buffer[STM_SECTOR_SIZE/2] = {0};
	STMFLASH_Read(ReadAddr,Buffer,NumToRead/2); //һ�������ֽ�
	memcpy(pBuffer,Buffer,NumToRead);
}	


/**
  * ��������: ��ȡָ����ַ�İ���(16λ����)
  * �������: faddr:����ַ(�˵�ַ����Ϊ2�ı���!!)
  * �� �� ֵ: ����ֵ:��Ӧ����.
  * ˵    ������
  */
uint16_t STMFLASH_ReadHalfWord ( uint32_t faddr )
{
	return *(__IO uint16_t*)faddr; 
}

#if STM32_FLASH_WREN	//���ʹ����д   
/**
  * ��������: ������д��
  * �������: WriteAddr:��ʼ��ַ
  *           pBuffer:����ָ��
  *           NumToWrite:����(16λ)��
  * �� �� ֵ: ��
  * ˵    ������
  */
void STMFLASH_Write_NoCheck ( uint32_t WriteAddr, uint16_t * pBuffer, uint16_t NumToWrite )   
{ 			 		 
	uint16_t i;	
	
	for(i=0;i<NumToWrite;i++)
	{
		FLASH_ProgramHalfWord(WriteAddr,pBuffer[i]);
		WriteAddr+=2;                                    //��ַ����2.
	}  
} 

/**
  * ��������: ��ָ����ַ��ʼд��ָ�����ȵ�����
  * �������: WriteAddr:��ʼ��ַ(�˵�ַ����Ϊ2�ı���!!)
  *           pBuffer:����ָ��
  *           NumToWrite:����(16λ)��(����Ҫд���16λ���ݵĸ���.)
  * �� �� ֵ: ��
  * ˵    ������
  */
void STMFLASH_Write ( uint32_t WriteAddr, uint16_t * pBuffer, uint16_t NumToWrite )	
{
//	uint32_t SECTORError = 0;
	uint16_t secoff;	   //������ƫ�Ƶ�ַ(16λ�ּ���)
	uint16_t secremain; //������ʣ���ַ(16λ�ּ���)	   
	uint16_t i;    
	uint32_t secpos;	   //������ַ
	uint32_t offaddr;   //ȥ��0X08000000��ĵ�ַ
	
	if(WriteAddr<FLASH_BASE||(WriteAddr>=(FLASH_BASE+1024*STM32_FLASH_SIZE)))
		return;//�Ƿ���ַ
	
	FLASH_Unlock();						//����
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR); 
	offaddr=WriteAddr-FLASH_BASE;		//ʵ��ƫ�Ƶ�ַ.
	secpos=offaddr/STM_SECTOR_SIZE;			//������ַ  0~127 for STM32F103RBT6
	secoff=(offaddr%STM_SECTOR_SIZE)/2;		//�������ڵ�ƫ��(2���ֽ�Ϊ������λ.)
	secremain=STM_SECTOR_SIZE/2-secoff;		//����ʣ��ռ��С   
	if(NumToWrite<=secremain)
		secremain=NumToWrite;//�����ڸ�������Χ	
	while(1) 
	{	
		STMFLASH_Read(secpos*STM_SECTOR_SIZE+FLASH_BASE,STMFLASH_BUF,STM_SECTOR_SIZE/2);//������������������
		for(i=0;i<secremain;i++)//У������
		{
			if(STMFLASH_BUF[secoff+i]!=0XFFFF)
				break;//��Ҫ����  	  
		}
		if(i<secremain)//��Ҫ����
		{
			//�����������
			/* Fill EraseInit structure*/
			uint32_t Sector   = secpos*STM_SECTOR_SIZE+FLASH_BASE;
			FLASH_ErasePage(Sector);

			for(i=0;i<secremain;i++)//����
			{
				STMFLASH_BUF[i+secoff]=pBuffer[i];	  
			}
			STMFLASH_Write_NoCheck(secpos*STM_SECTOR_SIZE+FLASH_BASE,STMFLASH_BUF,STM_SECTOR_SIZE/2);//д����������  
		}
		else
		{
			STMFLASH_Write_NoCheck(WriteAddr,pBuffer,secremain);//д�Ѿ������˵�,ֱ��д������ʣ������. 				   
		}
		if(NumToWrite==secremain)
			break;//д�������
		else//д��δ����
		{
			secpos++;				//������ַ��1
			secoff=0;				//ƫ��λ��Ϊ0 	 
			pBuffer+=secremain;  	//ָ��ƫ��
			WriteAddr+=secremain;	//д��ַƫ��	   
			NumToWrite-=secremain;	//�ֽ�(16λ)���ݼ�
			if(NumToWrite>(STM_SECTOR_SIZE/2))
				secremain=STM_SECTOR_SIZE/2;//��һ����������д����
			else 
				secremain=NumToWrite;//��һ����������д����
		}	 
	};	
	FLASH_Lock();//����
}
#endif

/**
  * ��������: ��ָ����ַ��ʼ����ָ�����ȵ�����
  * �������: ReadAddr:��ʼ��ַ
  *           pBuffer:����ָ��
  *           NumToRead:����(16λ)��
  * �� �� ֵ: ��
  * ˵    ������
  */
void STMFLASH_Read ( uint32_t ReadAddr, uint16_t *pBuffer, uint16_t NumToRead )   	
{
	uint16_t i;
	
	for(i=0;i<NumToRead;i++)
	{
		pBuffer[i]=STMFLASH_ReadHalfWord(ReadAddr);//��ȡ2���ֽ�.
		ReadAddr+=2;//ƫ��2���ֽ�.	
	}
}

/******************* (C) COPYRIGHT 2015-2020 ӲʯǶ��ʽ�����Ŷ� *****END OF FILE****/
