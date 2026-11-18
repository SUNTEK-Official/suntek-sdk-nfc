#include "comPro.h"
#include <stdio.h>
#include <string.h>

int contactLess_cpu_test(int icdev)
{
int st,i;//the state of each operation
unsigned long sn;
unsigned int rlen;
unsigned char snr[17];//card serial number
unsigned char snrSize;
unsigned int  tag;
unsigned char sak;
unsigned char cmd_1[17]={0x00,0x84,0x00,0x00,0x08};//the buffer to write a block
unsigned char rdata[1024];//the buffer read from a block
unsigned char showData[34]={0};//hex type data
unsigned char	tt= 7,fg= 255;//56;
unsigned char buf_cmd_src1[]={0x00,0x84,0x00,0x00,0x08};
unsigned int cmdLen;




//device reset
st = lc_rfReset(icdev,10);
if(st)
{
	printf("ERROR(%d): Device reset failed.\n",st);
	goto EXIT;
}
printf("Device reset OK.\n");

//find card
st = lc_card(icdev,1,snr, &snrSize,&tag,&sak);
if(st )
{
	printf("ERROR(%d):Find No card.\n",st);
	goto EXIT;
}

//card reset
st = lc_pro_reset(icdev,(unsigned char*)&rlen,rdata);
if(st)
{
	printf("ERROR(%d): Card reset failed.\n",st);
	goto EXIT;
} 
printf("Reset info: ");
rlen &= 0xff;
for(i=0; i<rlen; i++) printf("%02X",rdata[i]);
printf("\n");

//command test
memset(rdata,0,sizeof(rdata));
cmdLen = sizeof(buf_cmd_src1);
printf("sent data: ");
for(i=0; i<cmdLen; i++) printf("%02X",buf_cmd_src1[i]);
printf("\n");

st = lc_pro_commandlink(icdev,cmdLen,buf_cmd_src1,&rlen,rdata,tt,fg);
if(st)
{
	printf("ERROR(%d): Command failed.\n",st);
	goto EXIT;
}
printf("Returned Info: ");
for(i=0; i<rlen; i++) printf("%02X",rdata[i]);
printf("\n");
			

EXIT:

return st;
}
