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

unsigned char identiyCard(unsigned int tag, unsigned char sak, char* szOutType);

int dectectCardsTest(int icdev)
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

printf("Auto dectect running...\n");

while(1)
{
	//Dectect contactless slot...
	lc_rfReset(icdev, 10);
	st=lc_card(icdev,0, snr, &snrSize, &tag,&sak);//find card with mode multi card
	if(st ==0)
	{ 
		fContactlessRemove = 0;
		if(0 == fContactlessPresent)
		{
			iCardType = identiyCard(tag,sak, szCardType);
			printf("Find Contactless Card, Type: %s, UID:\n", szCardType);
			for(i=0; i< snrSize; i++)
			{
				printf("%02X ", snr[i]);
			}
			printf("\n");
			if(iCardType == CARD_TYPE_14443A_4)
			{
				st = lc_pro_reset(icdev, &atrLen, atr);
				if(0 == st)
				{
					printf("ATR:\n");
					for(i=0; i< atrLen; i++)
					{
						printf("%02X ", atr[i]);
					}
					printf("\n");
				}
				else
				{
					printf("Get ATR failed\n");
				}
			}
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
	//Dectect contact slot...
	st = lc_iccGetCardState(icdev, 0, &contactCardSt);
	if( (st == 0) && (1 == contactCardSt))
	{
		fContactRemove = 0;
		if(0 == fContactPresent)
		{
			printf("Contact card inserted.\n");
			st = lc_iccGetATR(icdev,0, atr, &atrLen);
			if(0 == st)
			{
				printf("ATR:\n");
				for(i=0; i< atrLen; i++)
				{
					printf("%02X ", atr[i]);
				}
				printf("\n");
			}
			else
			{
				printf("Get ATR failed\n");
			}
			fContactPresent = 1;
		}//if(0 == fContactPresent)
	}
	else 
	{
		fContactPresent = 0;
		if(0 == fContactRemove)
		{
			printf("Contact card removed\n");
			fContactRemove = 1;
		}
	}


}

return st;
}

///////////////////////// 
unsigned char identiyCard(unsigned int tag, unsigned char sak, char* szOutType)
{
	unsigned char _ret = CARD_TYPE_UNDEFINED;

	sprintf(szOutType,"");
	switch(sak)
	{
		case 0x00:
		_ret = CARD_TYPE_NTAG;
		sprintf(szOutType, "NTAG");
		break;
		case 0x04:
		_ret = CARD_TYPE_MF1K;
		sprintf(szOutType, "MF1K (7B-UID)");
		break;
		case 0x08:
		_ret = CARD_TYPE_MF1K;
		sprintf(szOutType, "MF1K(S50)");
		break;
		case 0x09:
		if(tag == 0x04)
		{
			_ret = CARD_TYPE_S20;
			sprintf(szOutType, "S20");
		}
		else
		{
			_ret = CARD_TYPE_MINI;
			sprintf(szOutType, "MF-MINI");
		}
		break;
		case 0x10:
		_ret = CARD_TYPE_MF_PLUS;
		sprintf(szOutType, "MF-Plus");
		break;
		case 0x11:
		_ret = CARD_TYPE_MF_PLUS;
		sprintf(szOutType, "MF-Plus");
		break;
		case 0x18:
		_ret = CARD_TYPE_MF4K;
		sprintf(szOutType, "MF4K(S70)");
		break;
		case 0x20:
		if(tag == 0x0344)
		{
			_ret = CARD_TYPE_DESFIRE;
			sprintf(szOutType, "Desfire");
		}
		else if(tag == 0x0042)
		{
			_ret = CARD_TYPE_MF4K;
			sprintf(szOutType, "MF-Plus");
		}
		else
		{
			_ret = CARD_TYPE_14443A_4;
			sprintf(szOutType, "14443A-4(CPU) Card");
		}
		break;
		case 0x24:
		_ret = CARD_TYPE_DESFIRE;
		sprintf(szOutType, "Desfire");
		break;
		case 0x28:
		_ret = CARD_TYPE_14443A_4;
		sprintf(szOutType, "M1 + 14443A-4(CPU) Card");
		break;
	}
	return _ret;
}

