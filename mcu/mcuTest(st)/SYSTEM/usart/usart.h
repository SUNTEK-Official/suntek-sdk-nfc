#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 
	
#define USART_REC_LEN  			200  	//ֽ 200
#define EN_USART1_RX 				1		//ʹܣ1/ֹ01
	  	
extern u8  USART_RX_BUF[USART_REC_LEN]; //ջ,USART_REC_LENֽ.ĩֽΪз 
extern u16 UART_RX_CNT;         		//״̬	
void uart_init(u32 bound);
void UART1_Send_Data(const u8 *buf,u16 len);

#endif //__USART_H

