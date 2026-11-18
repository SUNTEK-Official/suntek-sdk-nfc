#include "comPro.h"
#include <stdio.h>

void ParsePackage(char* pszContext, char idItem, char* szItemStr)
{
	int txtPointer = 0;
	int contextLen = strlen(pszContext);
	char* pSplitFlag;
	int itemStrLen = 0;

	szItemStr[0 ] = 0;

	while(txtPointer < contextLen)
	{
		if(pszContext[txtPointer] == idItem)
		{
			pSplitFlag = strstr(&pszContext[txtPointer], "\r\n");
			if(pSplitFlag != 0)
			{
				itemStrLen =  pSplitFlag - &pszContext[txtPointer];
				itemStrLen--;
			}
			else
			{
				itemStrLen = strlen(&pszContext[txtPointer]) - 1;
			}
			memcpy(szItemStr, &pszContext[txtPointer+1], itemStrLen );
			szItemStr[itemStrLen] = 0;
			break;
		}
		else
		{
			pSplitFlag = strstr(&pszContext[txtPointer], "\r\n");
			if(pSplitFlag != 0)
			{
				itemStrLen = pSplitFlag - &pszContext[txtPointer];
				txtPointer += itemStrLen;
				txtPointer += 2;
			}
			else
			{
				break;
			}
		}
	}

}

int sim_test(int icdev)
{
	int st;//the state of each operation
	unsigned char card_slot = 0; //0-Contact Master Card Slot, 1-SAM1, ...
	char szResult[1024];
	char szItemStr[128];
	char szMsgForShow[1024]= "";

	//read card
	st= lc_readSIM(icdev, card_slot, szResult);
	if(st)
	{
		printf("Read SIM Error!%d\n",st);
	}
	else
	{ //Show data
		printf("Read SIM ok\n");
		ParsePackage(szResult, '1', szItemStr);
		if(strlen(szItemStr) != 0)
		{
			strcat(szMsgForShow, "IMSI:	");
			strcat(szMsgForShow, szItemStr);
			strcat(szMsgForShow, "\r\n");
		}
		
		ParsePackage(szResult, '2', szItemStr);
		if(strlen(szItemStr) != 0)
		{
			strcat(szMsgForShow, "ICCID:	");
			strcat(szMsgForShow, szItemStr);
			strcat(szMsgForShow, "\r\n");
		}
		printf("Content: \n%s\n", szMsgForShow);
	}


	return st;
}
