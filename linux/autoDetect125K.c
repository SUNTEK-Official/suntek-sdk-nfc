#include "comPro.h"
#include <stdio.h>

#define CARD_TYPE_MF1K		0x01
#define CARD_TYPE_MF4K		0x02
#define CARD_TYPE_NTAG		0x03
#define CARD_TYPE_S20		0x04
#define CARD_TYPE_MINI		0x05
#define CARD_TYPE_MF_PLUS	0x06
#define CARD_TYPE_DESFIRE	0x07
#define CARD_TYPE_14443A_4	0x10
#define CARD_TYPE_UNDEFINED	0xff


int find_125K_ID_card_test(int icdev)
{
int st;//the state of each operation
unsigned char snr[17];//card serial number
unsigned char snrSize;
unsigned int  tag;
unsigned char sak;
unsigned char contaclessCardSt = 0;
unsigned char contactCardSt = 0;
unsigned char fContactlessPresent = 0;
unsigned char fContactlessRemove = 0;
unsigned char fContactPresent = 0;
unsigned char fContactRemove = 0;
int i;
char szCardType[128]={0};
unsigned char iCardType = 0;
unsigned char atrLen;
unsigned char atr[128];

printf("Auto dectect 125K card running...\n");

while(1)
{
	//Dectect contactless slot...
	lc_rfReset(icdev, 10);
	st=lc_find_125K_ID_Card(icdev, snr, &snrSize);
	if(st ==0)
	{ 
		fContactlessRemove = 0;
		if(0 == fContactlessPresent)
		{
			printf("Find Card, uid size: %d, UID:\n", snrSize);
			for(i=0; i< snrSize; i++)
			{
				printf("%02X ", snr[i]);
			}
			printf("\n");
			lc_beep(icdev, 10);
			fContactlessPresent = 1;
		}//if(0 == fContactlessPresent)
	}
	else
	{
		fContactlessPresent = 0;
		if(0 == fContactlessRemove)
		{
			printf("Contactless card removed\n");
			fContactlessRemove = 1;
		}//if(0 == fContactlessRemove)
	}

}

return st;
}


