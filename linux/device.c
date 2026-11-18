#include "comPro.h"
#include <stdio.h>

int test_device(int icdev)
{
	int st;//the state of each operation
	unsigned char rdata[1024];
	unsigned char wdata[1024];
	int rwlen = 1;//200;
	int i;

/*
	st = lc_rfReset(icdev, 5);
	if(st)
	{
		printf("lc_rfReset error:0x%x\n",st);
		goto DO_EXIT;
	}
*/
	st = lc_beep(icdev, 10);
	if(st)
	{
		printf("lc_beep error:0x%x\n",st);
		goto DO_EXIT;
	}


	for(i=0; i< rwlen; i++) wdata[i] = 1+i;

	
	st = lc_swr_flash(icdev, 0, rwlen, wdata);
	if(st)
	{
		printf("lc_swr_flash error:0x%x\n", st);
		goto DO_EXIT;
	}

	st =lc_srd_flash(icdev, 0, rwlen, rdata);
	if(st)
	{
		printf("lc_srd_flash error:0x%x\n",st);
		goto DO_EXIT;
	}
	printf("lc_srd_flash ok\n");

	for(i=0; i<rwlen; i++)
		printf("%02X ", rdata[i]);
	printf("\n");


DO_EXIT:
	return st;
}
