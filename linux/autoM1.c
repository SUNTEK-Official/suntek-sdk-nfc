#include "comPro.h"
#include <stdio.h>

int autoTest_m1(int icdev)
{
int st;//the state of each operation
unsigned char snr[17];//card serial number
unsigned char snrSize;
unsigned int  tag;
unsigned char sak;
unsigned char cardSt = 1;
unsigned long counter =0;
int i;

while(1)
{
	//find card
	st=lc_card(icdev,1, snr, &snrSize, &tag,&sak);//find card with mode multi card
	if(st ==0)
	{ 
		cardSt = 1;
		printf("Find Card[%d]: %u\n",counter++);
		for(i=0; i< snrSize; i++)
		{
			printf("%02X ", snr[i]);
		}
		printf("\n");
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

