#include "sys.h"
#include "usart.h"	  
////////////////////////////////////////////////////////////////////////////////// 	 
//ʹucos,ͷļ.
#if SYSTEM_SUPPORT_UCOS
#include "includes.h"					//ucos ʹ	  
#endif
 	  
//////////////////////////////////////////////////////////////////
//´,֧printf,Ҫѡuse MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//׼Ҫֺ֧                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//_sys_exit()Աʹðģʽ    
_sys_exit(int x) 
{ 
	x = x; 
} 
//ضfputc 
int fputc(int ch, FILE *f)
{      
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET); 
    USART_SendData(USART1,(uint8_t)ch);   
	return ch;
}
#endif 

 
#if EN_USART1_RX   //ʹ˽
//1жϷ
//ע,ȡUSARTx->SRܱĪĴ   	
u8 USART_RX_BUF[USART_REC_LEN];     //ջ,USART_REC_LENֽ.
u16 UART_RX_CNT = 0;       //ռ

//ʼIO 1 
//bound:
void uart_init(u32 bound)
{
	//GPIO˿
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//ʹUSART1GPIOAʱ
	USART_DeInit(USART1);  //λ1
	//USART1_TX   PA.9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//
	GPIO_Init(GPIOA, &GPIO_InitStructure); //ʼPA9

	//USART1_RX	  PA.10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//
	GPIO_Init(GPIOA, &GPIO_InitStructure);  //ʼPA10


	//USART ʼ

	USART_InitStructure.USART_BaudRate = bound;//һΪ9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//ֳΪ8λݸʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//żУλ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//Ӳ
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//շģʽ

	USART_Init(USART1, &USART_InitStructure); //ʼ
	#if EN_USART1_RX		  //ʹ˽  
	//Usart1 NVIC 
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//ռȼ3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//ȼ3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨʹ
	NVIC_Init(&NVIC_InitStructure);	//ָĲʼVICĴ

	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//ж
	#endif
	USART_Cmd(USART1, ENABLE);                    //ʹܴ 

}

void USART1_IRQHandler(void)                	//1жϷ
{
	u8 Res;

	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  
	{
		Res =USART_ReceiveData(USART1);	//ȡյ
		
		if(UART_RX_CNT < USART_REC_LEN)
		{
			USART_RX_BUF[UART_RX_CNT] = Res;	//¼յֵ
			UART_RX_CNT++;	//ݼ1 
			
			if(UART_RX_CNT == USART_REC_LEN)
			{
				UART_RX_CNT = 0;
			}
		} 		 
	} 
} 

void UART1_Send_Data(const u8 *buf,u16 len)
{
	u16 t;

	for(t=0;t<len;t++)		//ѭ
	{		   
		while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
		USART_SendData(USART1,buf[t]);
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
	}	 
	
}

#endif	
