#include "comPro.h"
#include <stdio.h>


int dectectUHF_Tag_Test(int icdev)
{
int st;//the state of each operation
unsigned char fContactlessPresent = 0;
unsigned char fContactlessRemove = 0;
int i;
unsigned char utf_tag_data[256];
unsigned char utf_tag_size;

printf("Auto dectect UHF tag running...\n");

while(1)
{
	st=lc_uhf_inventory(icdev, 300, utf_tag_data, &utf_tag_size);
	if(st ==0)
	{ 
		fContactlessRemove = 0;
		if(0 == fContactlessPresent)
		{
			printf("Found UHF tag, UID:\n");
			for(i=0; i< utf_tag_size; i++)
			{
				printf("%02X ", utf_tag_data[i]);
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
			printf("utf tag removed\n");
			fContactlessRemove = 1;
		}//if(0 == fContactlessRemove)
	}

	usleep(100);

}

return st;
}



