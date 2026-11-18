#include "comPro.h"
#include <stdio.h>
#include <string.h>

int contact_4428_test(int icdev)
{
int st,i;//the state of each operation
unsigned char rdata[1024];//the buffer received by reader
unsigned char wdata[1024];//Buffer for writting test
unsigned char showData[34]={0};//hex type data
unsigned int rwAddr = 0;
unsigned int rwLen = 100;
unsigned char cardSt = 0;
unsigned char card_slot = 0;//Main Slot
unsigned char password[2]={0xff,0xff};


//Get card state
st = lc_iccGetCardState(icdev, card_slot, &cardSt); //0x00 -> main-slot
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

//Card Select 
st = lc_iccSelCardType(icdev,card_slot,CARD_4428);
if(st)
{
	printf("ERROR(%d): Card select failed.\n",st);
	goto EXIT;
} 
printf("Found card\n");

//Verify 4428 Card's Password
st = lc_icc_VerifyUserPass(icdev, card_slot, 2, password);
if(st)
{
	printf("ERROR(%d): Card'password verify failed.\n",st);
	goto EXIT;
} 
printf("Verify card's password ok\n");

//Write Data 
for(i=0; i<rwLen; i++)wdata[i] = i&0xff;
st = lc_icc_WriteMem(icdev, card_slot, rwAddr, rwLen, wdata);
if(st)
{
	printf("ERROR(%d): Write data failed.\n",st);
	goto EXIT;
} 
printf("Write data ok\n");

//Read data
memset(rdata,0,sizeof(rdata));
st = lc_icc_ReadMem(icdev,card_slot, rwAddr, rwLen, rdata);
if(st)
{
	printf("ERROR(%d): Read data failed.\n",st);
	goto EXIT;
}
printf("Readed data: ");
for(i=0; i<rwLen; i++) printf("%02X ",rdata[i]);
printf("\n");
	

EXIT:

return st;
}
