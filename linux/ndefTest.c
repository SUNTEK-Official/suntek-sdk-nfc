#include "comPro.h"
#include "compro_nfch.h"
#include <stdio.h>

int test_ndef(int icdev)
{
int st;//the state of each operation
char pRBuffer[1024]="";//the buffer read from card
unsigned int  counter = 0;
unsigned int  i;
int tagType = 0x0A;//0;//0-M1, card types, defined see compro_nfc.h
int textFormat = 0x03;//0x01-GBK, 0x02-Unicode, 0x03-utf8
int payloadType = 0;
unsigned char cardSt = 1;

while(1)
{

	//counter++;
	//if(counter >1000)break;

	//printf("+++++++++++  Test %d  ++++\n",counter);

	//find card
	st= lc_NFC_ReadTag(icdev,tagType, textFormat, "",  &payloadType, pRBuffer);
	if(st == 0)
	{
		cardSt = 1;
		printf("Read text:%s\n", pRBuffer);
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
	//break;

}//while(1)

return st;
}
