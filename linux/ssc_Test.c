#include "comPro.h"
#include <stdio.h>

extern void ParsePackage(char* pszContext, char idItem, char* szItemStr);
#if 0
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
#endif //if 0

int ssc_test(int icdev)
{
	int st;//the state of each operation
	unsigned char card_slot = 100; //0-Contact Master Card Slot, 100-RF Slot
	char szResult[1024];
	char szItemStr[128];
	char szMsgForShow[1024]= "";

	//read card
	st= lc_readSSC(icdev, card_slot, szResult);
	if(st)
	{
		printf("Read SSC Error!%d\n",st);
	}
	else
	{ //Show data
		printf("Read SSC ok\n");
		ParsePackage(szResult, '1', szItemStr);
		if(strlen(szItemStr) != 0)
		{
			strcat(szMsgForShow, "Version:	");
			strcat(szMsgForShow, szItemStr);
			strcat(szMsgForShow, "\r\n");
		}
		
		ParsePackage(szResult, '2', szItemStr);
		if(strlen(szItemStr) != 0)
		{
			strcat(szMsgForShow, "ID:	");
			strcat(szMsgForShow, szItemStr);
			strcat(szMsgForShow, "\r\n");
		}
		printf("Content: \n%s\n", szMsgForShow);
	}


	return st;
}
