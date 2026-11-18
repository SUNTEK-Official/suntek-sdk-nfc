#include "delay.h"
#include "sys.h"
#include "usart.h" 
#include "functions.h"
#include <string.h>

long gl_icdev = 1;//No use
unsigned char szDevHWVer[64];

//// Test functions 
void TestMFCard(int icdev);//M1/S70
void contactLess_cpu_test(int icdev);
int contact_cpu_test(int icdev, unsigned char slot);
int iso15693_test(int icdev);

int main(void)
{		
	int st;
	
	delay_init();	    	 
	NVIC_Configuration(); 	
	uart_init(115200);
	
	st = lc_getver(gl_icdev, szDevHWVer);
	if(st != 0)
	{
		//printf("Get version failed.\n");
//		while(1);
	}
	//printf("Got version %s\n", (char*)szDevHWVer);
	lc_beep(gl_icdev, 10);
	
	TestMFCard(gl_icdev);
	//contactLess_cpu_test(gl_icdev);
	//contact_cpu_test(gl_icdev, 0);
	//iso15693_test(gl_icdev);
	
	while(1)
	{
		delay_ms(10);
	}	 
}

/////////////////////////////////////////////////////////////////// TEST ///
void TestMFCard(int icdev)
{
	int st;//the state of each operation
	unsigned char snr[17];//card serial number
	unsigned char snrSize;
	unsigned int  tag;
	unsigned char sak;
	unsigned long counter =0;
	unsigned char keybuf[7]={0xff,0xff,0xff,0xff,0xff,0xff};
	unsigned char wdata[17]={0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x10,0xaa,0xbb,0xcc,0xdd,0xee,0xff};//the buffer to write a block
	unsigned char rdata[17];//the buffer read from a block
	unsigned char sec=3;//sector to operation
	unsigned char block=12;//the block to write/read

	while(1)
	{
		counter++;
		//if(counter >1000)break;
		//printf("+++++++++++  Test %d  ++++\n",counter);
		//find card
		st=lc_card(icdev,0,snr, &snrSize, &tag, &sak);
		if(st)
		{
		 //printf("Find Card Error!%d\n",st);
		 continue;
		}
		
		//printf("The Card Serial Number is: ");
		//for(i=0; i< snrSize; i++)
		//{
		//	printf("%02X ", snr[i]);
		//}
		//printf("\n");
		lc_beep(icdev, 5);
		//authenication 
		st= lc_authentication(icdev,0x60,sec,keybuf);
		if(st)
		{
			 //printf("Authenicate Error!%d\n",st);
			 continue;
		}
		//printf("Authenicate ok!\n");

		/// write block
		st=lc_write(icdev,block,wdata);
		if(st)
		{
		 //printf("Write Block Data Error!%d\n",st);
		 continue;
		}
		//printf("Write Data To Block Ok!\n");

		//Read block data
		st=lc_read(icdev,block,rdata);
		if(st)
		{
		 //printf("Read Block Data Error!%d\n",st);
		 continue;
		}
		
		lc_halt(icdev);//Halt this card
		
		lc_beep(icdev, 10);

	}//while(1)
	
}

void contactLess_cpu_test(int icdev)
{
	int st;//the state of each operation
	unsigned char ucTmp;
	unsigned int rlen;
	unsigned char snr[17];//card serial number
	unsigned char snrSize;
	unsigned int  tag;
	unsigned char sak;
	unsigned char rdata[128];//the buffer read from a block
	unsigned char	tt= 7,fg= 56;
	unsigned char buf_cmd_src1[]={0x00,0x84,0x00,0x00,0x08};
	unsigned int cmdLen;

	//device reset
	lc_rfReset(icdev,1);

	//find card
	while(1)
	{
		st=lc_card(icdev,0,snr, &snrSize, &tag, &sak);
		if(st != 0)
		{
			continue;
		}
		
		delay_ms(10);
		
		//card reset
		st = lc_pro_reset(icdev,&ucTmp,rdata);
		if(st)
		{
			//printf("ERROR(%d): Card reset failed.\n",st);
			continue;
		} 
		//printf("Reset info: ");
		//rlen &= 0xff;
		//for(i=0; i<ucTmp; i++) printf("%02X",rdata[i]);
		//printf("\n");

		//command test
		memset(rdata,0,sizeof(rdata));
		cmdLen = sizeof(buf_cmd_src1);
		//printf("sent data: ");
		//for(i=0; i<cmdLen; i++) printf("%02X",buf_cmd_src1[i]);
		//printf("\n");

		st = lc_pro_commandlink(icdev,cmdLen,buf_cmd_src1,&rlen,rdata,tt,fg);
		if(st)
		{
			//printf("ERROR(%d): Command failed.\n",st);
			continue;
		}
	//	printf("Returned Info: ");
	//	for(i=0; i<rlen; i++) printf("%02X",rdata[i]);
	//	printf("\n");
		lc_beep(icdev, 10);
	}

}

int contact_cpu_test(int icdev, unsigned char slot)
{
	int st;//the state of each operation
	unsigned char ucTmp;
	unsigned int rlen;
	unsigned char rdata[128];//the buffer read from a block
	unsigned char buf_cmd_src1[]={0x00,0x84,0x00,0x00,0x08};
	unsigned int cmdLen;
	

	//device reset
	st = lc_iccSelCardType(icdev,slot, 0x0C);
	if(st)
	{
		//printf("ERROR(%d): Select card failed.\n",st);
		return st;
	} 
	
	//card reset
	st = lc_iccGetATR(icdev,slot, rdata, &ucTmp);
	if(st)
	{
		//printf("ERROR(%d): Card reset failed.\n",st);
		return st;
	} 
	//printf("Reset info: ");
	//rlen &= 0xff;
	//for(i=0; i<ucTmp; i++) printf("%02X",rdata[i]);
	//printf("\n");

	//command test
	memset(rdata,0,sizeof(rdata));
	cmdLen = sizeof(buf_cmd_src1);
	//printf("sent data: ");
	//for(i=0; i<cmdLen; i++) printf("%02X",buf_cmd_src1[i]);
	//printf("\n");

	st = lc_icc_APDU(icdev,slot, cmdLen,buf_cmd_src1,&rlen,rdata);
	if(st)
	{
		//printf("ERROR(%d): Command failed.\n",st);
		return st;
	}
//	printf("Returned Info: ");
//	for(i=0; i<rlen; i++) printf("%02X",rdata[i]);
//	printf("\n");
	lc_beep(icdev, 10);

	return 0;
}

int iso15693_test(int icdev)
{
	int st;//the state of each operation
	unsigned char rlen;
	unsigned char rbuffer[17];
	unsigned char szCardSn[9] ={0};
	unsigned char m_StaAddr = 0x04;
	unsigned char m_Blockno = 0x01;
	

	while(1)
	{
		//Find card
		st = lc_find15693(icdev,0x16,szCardSn,&rlen); 
		if(st)
		{
			continue;
		} 
		
		//Read card
		st = lc_15693_readBlock(icdev,szCardSn,m_StaAddr,m_Blockno,&rlen,rbuffer);
		if(st)
		{
			continue;
		} 
		
		lc_beep(icdev, 10);
	}

	return 0;
}



