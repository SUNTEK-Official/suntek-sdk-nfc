#include "comPro.h"
#include <stdio.h>
#include <sys/time.h>

int test_mutiANT(int icdev)
{
int st = 0;//the state of each operation
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
unsigned int  antNum = 22;
unsigned int  j;
static unsigned int stc_record_find_suc_cnt[22]={0};
struct timeval t1, t2;
double timeCost;


while(1)
{

counter++;
if(counter >1000)break;

printf("+++++++++++  Test %d  ++++\n",counter);

//st = lc_rfReset(icdev, 10);
//if(st)
//{
// printf("lc_rfReset error!%d\n", st);
// continue;
//}

gettimeofday(&t1,NULL);//Record Start time

//--------------------------------- ANT Loop  Begin -----
for(j = 0; j< antNum; j++)
{

printf(" ANT %d testing................................\n", j+1);

lc_selectANT(icdev, j+1);

//find card
st=lc_card(icdev,1,snr, &snrSize, &tag, &sak);//find card with mode multi card
if(st)
{
 //printf("Find Card Error!%d\n",st);
 continue;
}

stc_record_find_suc_cnt[j]++;

//lc_beep(icdev, 5);
printf("ANT %d found Card! Count: %d\n", j+1, stc_record_find_suc_cnt[j]);
//printf("The Card Serial Number is: ");
//for(i=0; i< snrSize; i++)
//{
//	printf("%02X ", snr[i]);
//}
//printf("\n");


//authenication 
st=lc_authentication(icdev,0x60,sec,keybuf);
if(st)
{
 //printf("Authenicate Error!%d\n",st);
 continue;
}
//printf("Authenicate ok!\n");

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
 //printf("Read Block Data Error!%d\n",st);
 continue;
}
//hex_a(showData,rdata,32);
//hex_asc(rdata, showData, 16);
//printf("Read Block %d Ok!The Data Is:%s\n",block,showData);

}//for(j = 0; j< antNum; j++)
//--------------------------------- ANT Loop  End -----

gettimeofday(&t2, NULL);//Get test end time
timeCost = (t2.tv_sec - t1.tv_sec) + (double)(t2.tv_usec - t1.tv_usec) / 1000000.0;

printf("Time cost: %f \n", timeCost);

}//while(1)

return st;
}
