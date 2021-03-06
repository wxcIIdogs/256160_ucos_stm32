#ifndef __UART_H
#define __UART_H

#include "stm32f10x.h"

#define uint16_t u16
#define uint8_t u8
#define uint32_t u32

	#define NULL  0
	#define UART_CR1_REG_INDEX               1    
	#define UART_CR2_REG_INDEX               2    
	#define UART_CR3_REG_INDEX               3 
	#define UART_HandleTypeDef USART_TypeDef
	#define __HAL_UART_GET_FLAG(__HANDLE__, __FLAG__) (((__HANDLE__)->SR & (__FLAG__)) == (__FLAG__))
	#define UART_FLAG_TXE                       ((uint32_t)USART_SR_TXE)
	#define UART_FLAG_CTS                       ((uint32_t)USART_SR_CTS)
	#define UART_FLAG_LBD                       ((uint32_t)USART_SR_LBD)
	#define UART_FLAG_TXE                       ((uint32_t)USART_SR_TXE)
	#define UART_FLAG_TC                        ((uint32_t)USART_SR_TC)
	#define UART_FLAG_RXNE                      ((uint32_t)USART_SR_RXNE)
	#define UART_FLAG_IDLE                      ((uint32_t)USART_SR_IDLE)
	#define UART_FLAG_ORE                       ((uint32_t)USART_SR_ORE)
	#define UART_FLAG_NE                        ((uint32_t)USART_SR_NE)
	#define UART_FLAG_FE                        ((uint32_t)USART_SR_FE)
	#define UART_FLAG_PE                        ((uint32_t)USART_SR_PE)
	#define UART_IT_PE                       ((uint32_t)(UART_CR1_REG_INDEX << 28 | USART_CR1_PEIE))
	#define UART_IT_TXE                      ((uint32_t)(UART_CR1_REG_INDEX << 28 | USART_CR1_TXEIE))
	#define UART_IT_TC                       ((uint32_t)(UART_CR1_REG_INDEX << 28 | USART_CR1_TCIE))
	#define UART_IT_RXNE                     ((uint32_t)(UART_CR1_REG_INDEX << 28 | USART_CR1_RXNEIE))
	#define UART_IT_IDLE                     ((uint32_t)(UART_CR1_REG_INDEX << 28 | USART_CR1_IDLEIE))

	#define UART_IT_LBD                      ((uint32_t)(UART_CR2_REG_INDEX << 28 | USART_CR2_LBDIE))

	#define UART_IT_CTS                      ((uint32_t)(UART_CR3_REG_INDEX << 28 | USART_CR3_CTSIE))
	#define UART_IT_ERR                      ((uint32_t)(UART_CR3_REG_INDEX << 28 | USART_CR3_EIE))	
	
	#define UART_IT_MASK  ((uint32_t) USART_CR1_PEIE | USART_CR1_TXEIE | USART_CR1_TCIE | USART_CR1_RXNEIE | \
                                  USART_CR1_IDLEIE | USART_CR2_LBDIE | USART_CR3_CTSIE | USART_CR3_EIE )
																	
	#define __HAL_UART_ENABLE_IT(__HANDLE__, __INTERRUPT__)   ((((__INTERRUPT__) >> 28) == UART_CR1_REG_INDEX)? ((__HANDLE__)->CR1 |= ((__INTERRUPT__) & UART_IT_MASK)): \
                                                           (((__INTERRUPT__) >> 28) == UART_CR2_REG_INDEX)? ((__HANDLE__)->CR2 |=  ((__INTERRUPT__) & UART_IT_MASK)): \
                                                           ((__HANDLE__)->CR3 |= ((__INTERRUPT__) & UART_IT_MASK)))
	#define __HAL_UART_GET_IT_SOURCE(__HANDLE__, __IT__) (((((__IT__) >> 28) == UART_CR1_REG_INDEX)? (__HANDLE__)->CR1:(((((uint32_t)(__IT__)) >> 28) == UART_CR2_REG_INDEX)? \
																												(__HANDLE__)->CR2 : (__HANDLE__)->CR3)) & (((uint32_t)(__IT__)) & UART_IT_MASK))

	#define __HAL_UART_DISABLE_IT(__HANDLE__, __INTERRUPT__)  ((((__INTERRUPT__) >> 28) == UART_CR1_REG_INDEX)? ((__HANDLE__)->CR1 &= ~((__INTERRUPT__) & UART_IT_MASK)): \
																														(((__INTERRUPT__) >> 28) == UART_CR2_REG_INDEX)? ((__HANDLE__)->CR2 &= ~((__INTERRUPT__) & UART_IT_MASK)): \
																														((__HANDLE__)->CR3 &= ~ ((__INTERRUPT__) & UART_IT_MASK)))
	typedef enum
{
	HAL_OK = 0,
	HAL_ERROR = 1,
}HAL_StatusTypeDef;




typedef void (*FuncPtr_t)(void);
typedef void (*FuncPtrU8_t)(uint8_t);

#define DISABLE_INT()                                { __set_PRIMASK(1); }	/* å³ä¸­æ?*/
#define ENABLE_INT()                                 { __set_PRIMASK(0); }	/* å¼ä¸­æ­ */

/* ä¸²å£è®¾å¤ç»æä½?*/
typedef struct
{
    UART_HandleTypeDef *huart; /* ä¸²å£è®¾å¤æé */
    uint8_t *pTxBuf;           /* åéç¼å²åº */
    uint8_t *pRxBuf;           /* æ¥æ¶ç¼å²å?*/
    uint16_t usTxBufSize;      /* åéç¼å²åºå¤§å° */
    uint16_t usRxBufSize;      /* æ¥æ¶ç¼å²åºå¤§å°?*/
    __IO uint16_t usTxWrite;   /* åéç¼å²åºåæé?*/
    __IO uint16_t usTxRead;    /* åéç¼å²åºè¯»æé?*/
    __IO uint16_t usTxCount;   /* ç­å¾åéçæ°æ®ä¸ªæ° */
    __IO uint16_t usRxWrite;   /* æ¥æ¶ç¼å²åºåæé */
    __IO uint16_t usRxRead;    /* æ¥æ¶ç¼å²åºè¯»æé */
    __IO uint16_t usRxCount;   /* è¿æªè¯»åçæ°æ°æ®ä¸ªæ° */
    FuncPtr_t SendBeforFunc;   /* å¼å§åéä¹åçåè°å½æ°æéï¼ä¸»è¦ç¨äºRS485åæ¢å°åéæ¨¡å¼ï¼ */
    FuncPtr_t SendOverFunc;    /* åéå®æ¯çåè°å½æ°æéï¼ä¸»è¦ç¨äºRS485å°åéæ¨¡å¼åæ¢ä¸ºæ¥æ¶æ¨¡å¼ï¼?*/
    FuncPtrU8_t ReciveNewFunc; /* ä¸²å£æ¶å°æ°æ®çåè°å½æ°æé?*/
    uint8_t initDoneFlag;      /* åå§åå®ææ å¿?*/
} UART_FIFO_Typedef_t;

extern HAL_StatusTypeDef UartSendByte(UART_HandleTypeDef *huart, uint8_t ucByte);
extern void UartSendBuffer(UART_HandleTypeDef *huart, uint8_t *ucBuffer, uint16_t usLength);
extern HAL_StatusTypeDef UartReadByte(UART_HandleTypeDef *huart, uint8_t *ucByte);
extern HAL_StatusTypeDef UartSetBaudRate(UART_HandleTypeDef *huart, uint32_t baudRate);

extern void FIFO_UartVarInit(UART_FIFO_Typedef_t *pFIFO_Uart,
                             UART_HandleTypeDef *huart,
                             uint8_t *pTxBuf,
                             uint8_t *pRxBuf,
                             uint16_t usTxBufSize,
                             uint16_t usRxBufSize,
                             FuncPtr_t SendBeforFunc,
                             FuncPtr_t SendOverFunc,
                             FuncPtrU8_t ReciveNewFunc);
extern void FIFO_UartSetSendBeforFunc(UART_FIFO_Typedef_t *pFIFO_Uart, FuncPtr_t SendBeforFunc);
extern void FIFO_UartSetSendOverFunc(UART_FIFO_Typedef_t *pFIFO_Uart, FuncPtr_t SendOverFunc);
extern void FIFO_UartSetReciveNewFunc(UART_FIFO_Typedef_t *pFIFO_Uart, FuncPtrU8_t ReciveNewFunc);
extern HAL_StatusTypeDef FIFO_UartSetBaudRate(UART_FIFO_Typedef_t *pFIFO_Uart, uint32_t baudRate);
extern HAL_StatusTypeDef FIFO_UartReadByte(UART_FIFO_Typedef_t *pFIFO_Uart, uint8_t *ucByte);
extern uint16_t FIFO_UartReadBuffer(UART_FIFO_Typedef_t *pFIFO_Uart, uint8_t *ucBuffer, uint16_t usLen);
extern void FIFO_UartSendBuffer(UART_FIFO_Typedef_t *pFIFO_Uart, uint8_t *ucBuffer, uint16_t usLen);
extern void FIFO_UartSendByte(UART_FIFO_Typedef_t *pFIFO_Uart, uint8_t ucByte);
extern void FIFO_UartIRQ(UART_FIFO_Typedef_t *pFIFO_Uart);



#endif /* __UART_H */
