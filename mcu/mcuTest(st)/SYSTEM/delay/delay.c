#include "delay.h"
#include "sys.h"
////////////////////////////////////////////////////////////////////////////////// 	 
//ʹucos,ͷļ.
#if SYSTEM_SUPPORT_UCOS
#include "includes.h"					//ucos ʹ	  
#endif
////////////////////////////////////////////////////////////////////////////////// 	 
static u8  fac_us=0;//usʱ
static u16 fac_ms=0;//msʱ
#ifdef OS_CRITICAL_METHOD 	//OS_CRITICAL_METHOD,˵ʹucosII.
//systickжϷ,ʹucosʱõ
void SysTick_Handler(void)
{				   
	OSIntEnter();		//ж
	OSTimeTick();       //ucosʱӷ               
	OSIntExit();        //лж
}
#endif

//ʼӳٺ
//ʹucosʱ,˺ʼucosʱӽ
//SYSTICKʱӹ̶ΪHCLKʱӵ1/8
//SYSCLK:ϵͳʱ
void delay_init()	 
{

#ifdef OS_CRITICAL_METHOD 	//OS_CRITICAL_METHOD,˵ʹucosII.
	u32 reload;
#endif
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//ѡⲿʱ  HCLK/8
	fac_us=SystemCoreClock/8000000;	//Ϊϵͳʱӵ1/8  
	 
#ifdef OS_CRITICAL_METHOD 	//OS_CRITICAL_METHOD,˵ʹucosII.
	reload=SystemCoreClock/8000000;		//ÿӵļ λΪK	   
	reload*=1000000/OS_TICKS_PER_SEC; // OS_TICKS_PER_SEC ʱ
							//reloadΪ24λĴ,ֵ:16777216,72M,Լ1.86s	
	fac_ms=1000/OS_TICKS_PER_SEC;//ucosʱٵλ	   
	SysTick->CTRL|=SysTick_CTRL_TICKINT_Msk;   	//SYSTICKж
	SysTick->LOAD=reload; 	//ÿ1/OS_TICKS_PER_SECжһ	
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;   	//SYSTICK    
#else
	fac_ms=(u16)fac_us*1000;//ucos,ÿmsҪsystickʱ   
#endif
}								    

#ifdef OS_CRITICAL_METHOD	//ʹucos
//ʱnus
//nusΪҪʱus.		    								   
void delay_us(u32 nus)
{		
	u32 ticks;
	u32 told,tnow,tcnt=0;
	u32 reload=SysTick->LOAD;	//LOADֵ	    	 
	ticks=nus*fac_us; 			//ҪĽ	  		 
	tcnt=0;
	told=SysTick->VAL;        	//սʱļֵ
	while(1)
	{
		tnow=SysTick->VAL;	
		if(tnow!=told)
		{	    
			if(tnow<told)tcnt+=told-tnow;//עһSYSTICKһݼļͿ.
			else tcnt+=reload-tnow+told;	    
			told=tnow;
			if(tcnt>=ticks)break;//ʱ䳬/Ҫӳٵʱ,˳.
		}  
	}; 									    
}
//ʱnms
//nms:Ҫʱms
void delay_ms(u16 nms)
{	
	if(OSRunning==TRUE)//osѾ	    
	{		  
		if(nms>=fac_ms)//ʱʱucosʱ 
		{
   			OSTimeDly(nms/fac_ms);//ucosʱ
		}
		nms%=fac_ms;				//ucosѾ޷ṩôСʱ,ͨʽʱ    
	}
	delay_us((u32)(nms*1000));	//ͨʽʱ,ʱucos޷.
}
#else//ucosʱ
//ʱnus
//nusΪҪʱus.		    								   
void delay_us(u32 nus)
{		
	u32 temp;	    	 
	SysTick->LOAD=nus*fac_us; //ʱ	  		 
	SysTick->VAL=0x00;        //ռ
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;          //ʼ	 
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//ȴʱ䵽   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;       //رռ
	SysTick->VAL =0X00;       //ռ	 
}
//ʱnms
//עnmsķΧ
//SysTick->LOADΪ24λĴ,,ʱΪ:
//nms<=0xffffff*8*1000/SYSCLK
//SYSCLKλΪHz,nmsλΪms
//72M,nms<=1864 
void delay_ms(u16 nms)
{	 		  	  
	u32 temp;		   
	SysTick->LOAD=(u32)nms*fac_ms;//ʱ(SysTick->LOADΪ24bit)
	SysTick->VAL =0x00;           //ռ
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;          //ʼ  
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//ȴʱ䵽   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;       //رռ
	SysTick->VAL =0X00;       //ռ	  	    
} 
#endif































