#include "comPro.h"
#include <stdio.h>

int test_m1(int icdev)
{
int st;//the state of each operation
unsigned char snr[17];//card serial number
unsigned char snrSize;
unsigned int  tag;
unsigned char sak;
unsigned long value;
unsigned char keybuf[7]={0xff,0xff,0xff,0xff,0xff,0xff};
unsigned char wdata[17]={0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x10,0xaa,0xbb,0xcc,0xdd,0xee,0xff};//the buffer to write a block
unsigned char rdata[17];//the buffer read from a block
unsigned char showData[34]={0};//hex type data
unsigned char sec=3;//sector to operation
unsigned char block=12;//the block to write/read
unsigned int  counter = 0;
unsigned int  i;


while(1)
{

counter++;
if(counter >1000)break;

printf("+++++++++++  Test %d  ++++\n",counter);

st = lc_rfReset(icdev, 10);
if(st)
{
 printf("lc_rfReset error!%d\n", st);
 continue;
}

//find card
st=lc_card(icdev,1,snr, &snrSize, &tag, &sak);//find card with mode multi card
if(st)
{
 printf("Find Card Error!%d\n",st);
 continue;
}
printf("Hava Card!\n");
printf("The Card Serial Number is: ");
for(i=0; i< snrSize; i++)
{
	printf("%02X ", snr[i]);
}
printf("\n");


//authenication 
st=lc_authentication(icdev,0x60,sec,keybuf);
if(st)
{
 printf("Authenicate Error!%d\n",st);
 continue;
}
printf("Authenicate ok!\n");

/// write block
/*
st=lc_write(icdev,block,wdata);
if(st)
{
 printf("Write Block Data Error!%d\n",st);
 goto EXIT;
}
printf("Write Data To Block Ok!\n");
*/

//Read block data
st=lc_read(icdev,block,rdata);
if(st)
{
 printf("Read Block Data Error!%d\n",st);
 continue;
}
//hex_a(showData,rdata,32);
hex_asc(rdata, showData, 16);
printf("Read Block %d Ok!The Data Is:%s\n",block,showData);

}//while(1)

return st;
}
