#include "comPro.h"
#include <stdio.h>

/* Usage
 * USB 		-> sudo ./demo 2 /dev/usb/hiddev 115200 5
 * Serail Port	-> sudo ./demo 1 /dev/ttyS 115200
 */
void usage_help(void)
{
	printf("Invalid run parameter, usage help:\n\
		'sudo ./demo PortType Node BaudRate MaxNodeNumber StartNodeNumber' \
		which \n \
		PortType set 1(when serial port), set 2 (when usb) \n \
		Node is a string indicate the path of device node \n \
		BaudRate is baud rate when communication \n \
		MaxNodeNumber is maximum node number been set, optional \n \
		StartNodeNumber is the start number of node, optional \n \
		Example: sudo ./demo 2 /dev/usb/hiddev 115200 5 0\n");
}

int main(int argc,char* argv[])
{
	int icdev,st,number;
	char szVer[128];
	int iNode = 0;
	char szNodeHeader[128];
	char szNode[128];
	int linkMaxNodes = 1;
	unsigned char runMode;
	unsigned char szClient[256];
	int iTermNumber = 0;
	int tryCount = 0;
	int portType = 0;
	int baudRate = 0;

	if(argc >= 3)
	{
		portType = strtol(argv[1], NULL, 10);
		strcpy(szNodeHeader, argv[2]);
		baudRate = strtol(argv[3], NULL, 10);
		
		if(argc > 4)
		{
			linkMaxNodes = strtol(argv[4], NULL, 10);

			if(argc > 5)
				iNode = strtol(argv[5], NULL, 10);
		}
		printf("Max test node number: %d\n", linkMaxNodes);
	}
	else
	{
		usage_help();
		return 0;
	}

	//link port ...
	do
	{
		sprintf(szNode, "%s%d", szNodeHeader,iNode);
		iNode++;
		icdev=lc_init_ex(portType,szNode,baudRate);
		printf("lc_init_ex: %s return  %d\n",szNode, icdev);
		if(icdev == -1)
		{
			if(iNode >= linkMaxNodes)
			{
				printf("lc_init_ex ERR %d\n",icdev);
				return 0;
			}
		}
		else
		{
			st = lc_getver(icdev, szVer);
			if(st ==0)
			{
				printf("version:%s\n",szVer);
				break;
			}
			else
			{ 
				lc_exit(icdev);//Release invalid device
				printf("%s init error\n",szNode);
			}
		}
	}while(1);
	
	

	////serila port ...
	/*
	do
	{
		//sprintf(szNode, "/dev/ttyS%d", iNode);
		sprintf(szNode, "/dev/ttyUSB%d", iNode);
		iNode++;
		if((icdev=lc_init_ex(1,szNode,115200))== -1)
		{
			printf("lc_init_ex ERR %d\n",icdev);
			return 0;
		}
		else
		{
			st = lc_getver(icdev, szVer);
			if(st ==0)
			{
				break;
			}
			else
			{ 
				printf("%s init error\n",szNode);
			}
		}
	}while(icdev != -1);
	*/

	////Net port ...
	/*
	st = lc_net_serverStart(51006);
	if(st != 0)
	{
		printf("server start error\n");
		return 0;
	}
	do
	{
		iTermNumber = lc_net_termList(szClient);
		printf("Listen terminal number: %d, entry:%s \n", iTermNumber, (char*)szClient);
		if(iTermNumber > 0)
		{
			icdev = lc_init_ex(4, szClient, 0);
			if(icdev == -1)
			{
				printf("lc_init_ex error\n");
				return 0;
			}
			printf("Link %s ok\n", (char*)szClient);
			break;
		}
		else
		{
			tryCount++;
			if(tryCount > 5)
			{
				printf("No client linked.\n");
				return 0;
			}
			sleep(1);
		}
		
	}while(iTermNumber == 0);
	*/
	
	
	lc_beep(icdev,10);
	lc_getReaderMode(icdev, &runMode);

	printf("%s init ok, run mode: %s\n",szNode, (runMode==1)?"Read Only":"Read&Write");
        printf("1----Device\n");
        printf("2----MifareOne \n");
	printf("3----Mifare Card Loop Find \n");
	printf("4----Contactless-CPU \n");
	printf("6----Contact-CPU card \n");
	printf("7----MultiANT test \n");
	printf("8----ISO14443B test \n");
	printf("9----SIM test \n");
	printf("10---4428 test \n");
	printf("11---AT24C64 test \n");
	printf("12---4442 test \n");
	printf("15---UHF test \n");
	printf("16---NDEF \n");
	printf("20---FM12xx Initial \n");
	printf("21---FM12xx write data \n");
	printf("22---FM12xx read data \n");
	printf("30---125K ID Card Test \n");
	printf("50---SSC Read\n");
	printf("100--Auto Dectect Cards \n");
	printf("101--Auto Get Data \n");
	printf("0----Quit   \n");

        scanf("%d",&number);

	switch(number)
	{
	case 1:
		st = test_device(icdev);
		break;	
	case 2:
		st = test_m1(icdev);
		break;	
	case 3:
		st = autoTest_m1(icdev);
		break;
	case 4:
		st = contactLess_cpu_test(icdev);
		break;
	case 6:
		st = contact_cpu_test(icdev);
		break;	
	case 7:
		st = test_mutiANT(icdev);
		break;
	case 8:
		st = iso14443TypeB_test(icdev);
		break;
	case 9:
		st = sim_test(icdev);
		break;
	case 10:
		st = contact_4428_test(icdev);
		break;
	case 11:
		st = contact_24c64_test(icdev);
		break;
	case 12:
		st = contact_4442_test(icdev);
		break;
	case 15:
		st = dectectUHF_Tag_Test(icdev);
		break;
	case 16:
		st = test_ndef(icdev);
		break;
	case 20:
		st = fm12xx_initial(icdev);
		break;
	case 21:
		st = fm12xx_writeID(icdev);
		break;
	case 22:
		st = fm12xx_readID(icdev);
		break;
	case 30:
		st = find_125K_ID_card_test(icdev);
		break;
	case 50:
		st = ssc_test(icdev);
		break;
	case 100:
		st = dectectCardsTest(icdev);
		break;
	case 101:
		st = autoGetDataTest(icdev);
		break;
        default:
		break;
	}

       lc_exit(icdev);
       return 0; 
}
