#include "comPro.h"
#include <stdio.h>
#include <string.h>

int contact_cpu_test(int icdev)
{
int st,i;//the state of each operation
unsigned char ucRLen;
unsigned char cmd_1[]={0x00,0x84,0x00,0x00,0x08};//the buffer send to reader
unsigned char rdata[1024];//the buffer received by reader
unsigned char showData[34]={0};//hex type data
unsigned int cmdLen;
unsigned int rlen;
unsigned char cardSt = 0;


//Get card state
st = lc_iccGetCardState(icdev, 0x00, &cardSt); //0x00 -> main-slot
if(st != 0)
{
	printf("ERROR(%02x): get card state failed.\n", st);
	goto EXIT;
}
else
{
	if(0 == cardSt)
	{
		printf("No card.\n");
		goto EXIT;
	}
}

//card reset
st = lc_iccGetATR(icdev,0,rdata,&ucRLen);
if(st)
{
	printf("ERROR(%d): Card reset failed.\n",st);
	goto EXIT;
} 
printf("Reset info: ");
for(i=0; i<ucRLen; i++) printf("%02X ",rdata[i]);
printf("\n");

//command test
memset(rdata,0,sizeof(rdata));
cmdLen = sizeof(cmd_1);
printf("sent data: ");
for(i=0; i<cmdLen; i++) printf("%02X ",cmd_1[i]);
printf("\n");

st = lc_icc_APDU(icdev,0,cmdLen,cmd_1,&rlen,rdata);
if(st)
{
	printf("ERROR(%d): Command failed.\n",st);
	goto EXIT;
}
printf("Returned Info: ");
for(i=0; i<rlen; i++) printf("%02X ",rdata[i]);
printf("\n");
	

EXIT:

return st;
}
