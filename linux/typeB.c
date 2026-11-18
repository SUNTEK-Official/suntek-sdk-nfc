#include "comPro.h"
#include <stdio.h>
#include <string.h>

int iso14443TypeB_test(int icdev)
{
int st,i;//the state of each operation
unsigned long sn;
unsigned int rlen;
unsigned char snr[65];//card serial number
unsigned char snrSize;
unsigned char buf_cmd_src1[]={0x00,0x36,0x00,0x00,0x08};//The apdu command to send
unsigned char rdata[1024];
unsigned char showData[34]={0};//hex type data
unsigned int cmdLen;
unsigned char cardSt = 1;

while(1)
{
	//find typeb card
	st = lc_findTypeB(icdev,1,snr, &snrSize);
	if(st == 0)
	{
		cardSt = 1;
		printf("Found typeB card: ");
		for(i=0; i<snrSize; i++) printf("%02X",snr[i]);
		printf("\n");

		//command test
		memset(rdata,0,sizeof(rdata));
		cmdLen = sizeof(buf_cmd_src1);

		st = lc_typeB_command(icdev,cmdLen,buf_cmd_src1,&rlen,rdata);
		if(st == 0)
		{
			printf("sent command: ");
			for(i=0; i<cmdLen; i++) printf("%02X",buf_cmd_src1[i]);
			printf("\n");

			printf("Command Returned Info: ");
			for(i=0; i<rlen; i++) printf("%02X",rdata[i]);
			printf("\n");
		}
		else
		{
			//printf("ERROR(%d): Command failed.\n",st);
		}

		lc_beep(icdev, 10);
	}
	else
	{
		if(cardSt == 1)
		{
			cardSt = 0;
			printf("NO card, put card on the reader...\n");
		}
	}

}

return st;
}
