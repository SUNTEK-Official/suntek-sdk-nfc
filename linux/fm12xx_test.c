#include "comPro.h"
#include "_fm1208.h"
#include <stdio.h>
#include <string.h>

/* Public Parameter */
unsigned char g_pInitExKey[]={0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};//
unsigned char g_pExKey []={0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
unsigned char g_pFileProKey[]={0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
unsigned short g_fileID = 0x0003;
unsigned short g_fileSize = 100;
const int g_lenToRW = 10;

int fm12xx_initial(int icdev)
{
	int status,i;//the state of each operation
	unsigned long sn;
	unsigned char rlen;
	unsigned char rdata[256];//the buffer read from a block
	unsigned char showData[34]={0};//hex type data
	unsigned char	tt= 7,fg= 56;
        char pRBuffer[256];
        char pShowBuf[256];
	unsigned short tag;
	unsigned char sak;
	unsigned char bufCard[12];
	unsigned char cardSize;

_FIND_CARD:
	while(1)
	{
		//device reset
		status = lc_rfReset(icdev,10);
		if(status)
		{
			//printf("ERROR(%d): Device reset failed.\n",status);
			//goto EXIT;
			continue;
		}
		//printf("Device reset OK.\n");


		//find card
		status = lc_card(icdev,1,bufCard, &cardSize,&tag,&sak);
		if(status )
		{
			continue;
		}

		//card reset
		status = lc_pro_reset(icdev,(unsigned char*)&rlen,rdata);
		if(status)
		{
			//printf("ERROR(%d): Card reset failed.\n",status);
			continue;
		} 
		//rlen &= 0xff;
		//printf("Reset info: ");
		//for(i=0; i<rlen; i++) printf("%02X",rdata[i]);
		//printf("\n");
		printf("Found card\n");
		break;
	}//while(1)

			//Select main app
            status = FWCosSelecteApp(icdev);
            if (status != 0) {
                printf("FWCosSelecteApp error!\n");
                goto INIT_FM1208_EXIT;
            } else {
                printf("FWCosSelecteApp ok!\n");
            }


            //Authenticate with initial key
            status = FWCosVerifyKey(icdev, 
            	g_pInitExKey,
            	8,
            	FW_KEYTYPE_EXVERIFY);
            if (status != 0) {

		//Authenticate with user's key
		status = FWCosVerifyKey(icdev,
			g_pExKey,
			16,
			FW_KEYTYPE_EXVERIFY);
		
		if(status != 0)
		{
                	printf("FWCosVerifyKey error, invalid card?\n");
                	printf("0x%0x\n",status);
		}

            } else {
                printf("FWCosVerifyKey ok!\n");
            }

	//Delete Current file system  and create key
        status = FWCosDeleteFileSys(icdev);
	if(0 == status)
	{
	   printf("FWCosDeleteFileSys ok!\n");

			//Select main app
            status = FWCosSelecteApp(icdev);
            if (status != 0) {
                printf("FWCosSelecteApp error!\n");
                goto INIT_FM1208_EXIT;
            } else {
                printf("FWCosSelecteApp ok!\n");
            }

		//Create key file
		status = FWCosCreateKeyFile(icdev,
			0x0000,
			0x0001,
			64,
			0);
		if (status != 0) {
        		printf("FWCosCreateKeyFile error!\n");
        		printf("0x%0x\n",status);
        		goto INIT_FM1208_EXIT;
		} else {
        		printf("FWCosCreateKeyFile ok!\n");
    		}
		//Create keys
		status = FWCosAddKey(icdev,
			FW_KEYTYPE_EXVERIFY,
			g_pExKey,
			16);
		if (status != 0) {
        		printf("FWCosAddKey external key error!\n");
        		printf("0x%0x\n",status);
        		goto INIT_FM1208_EXIT;
		} else {
        		printf("FWCosAddKey external key ok!\n");
    		}

		status = FWCosAddKey(icdev,
			FW_KEYTYPE_FILEPROTECT,
			g_pFileProKey,
			16);
		if (status != 0) {
        		printf("FWCosAddKey file protect key error!\n");
        		printf("0x%0x\n",status);
        		goto INIT_FM1208_EXIT;
		} else {
        		printf("FWCosAddKey file protect key ok!\n");
    		}
	}
	else
	{
		printf("FWCosDeleteFileSys error!\n");
		printf("0x%0x\n",status);
		goto INIT_FM1208_EXIT;
	}

	//Create file 
	status = FWCosCreateBinaryFile(icdev,
		(short)0x000,//Directory id, 0x0000 means current directory
		(short)g_fileID,//file id
		g_fileSize, //file size
		(char)0,
		FWCOS_SEC_SO,
		FWCOS_SEC_SO,
		FWCOS_SEC_SO
		);
	if (status != 0) {
        	printf("FWCosCreateBinaryFile error!\n");
        	printf("%X\n",status);
        	goto INIT_FM1208_EXIT;
	} else {
        	printf("FWCosCreateBinaryFile ok!\n");
    	}

  
	lc_beep(icdev, 10);
	

INIT_FM1208_EXIT:

return status;
}

int fm12xx_writeID(int icdev)
{
	int status,i;//the state of each operation
	unsigned long sn;
	unsigned char rlen;
	unsigned char rdata[256];//the buffer read from a block
	unsigned char showData[34]={0};//hex type data
	unsigned char	tt= 7,fg= 56;
        char pRBuffer[256];
      	char pWriteBuffer[256]={0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff};
        char pShowBuf[256];
	unsigned short tag;
	unsigned char sak;
	unsigned char bufCard[12];
	unsigned char cardSize;

_FIND_CARD:
	while(1)
	{
		//device reset
		status = lc_rfReset(icdev,10);
		if(status)
		{
			//printf("ERROR(%d): Device reset failed.\n",status);
			//goto EXIT;
			continue;
		}
		//printf("Device reset OK.\n");


		//find card
		status = lc_card(icdev,1,bufCard, &cardSize,&tag,&sak);
		if(status )
		{
			continue;
		}

		//card reset
		status = lc_pro_reset(icdev,(unsigned char*)&rlen,rdata);
		if(status)
		{
			//printf("ERROR(%d): Card reset failed.\n",status);
			continue;
		} 
		//rlen &= 0xff;
		//printf("Reset info: ");
		//for(i=0; i<rlen; i++) printf("%02X",rdata[i]);
		//printf("\n");
		printf("Found card\n");
		break;
	}//while(1)

			//Select main app
            status = FWCosSelecteApp(icdev);
            if (status != 0) {
                printf("FWCosSelecteApp error!\n");
                goto WRITE_FM1208_EXIT;
            } else {
                printf("FWCosSelecteApp ok!\n");
            }


            //Authenticate key
            status = FWCosVerifyKey(icdev, 
            	g_pInitExKey,
            	8,
            	FW_KEYTYPE_EXVERIFY);
            if (status != 0) {

		//Authenticate with user's key
		status = FWCosVerifyKey(icdev,
			g_pExKey,
			16,
			FW_KEYTYPE_EXVERIFY);
		
		if(status != 0)
		{
                	printf("FWCosVerifyKey error, invalid card!\n");
                	printf("0x%0x\n",status);
			goto WRITE_FM1208_EXIT;
		}

            } else {
                printf("FWCosVerifyKey ok!\n");
            }

	status = FWCosSelectFile(icdev, g_fileID);
	if(status != 0)
	{//No file
		printf("FWCosSelectFile error, invalid card!\n");
        	printf("0x%0x\n",status);
		goto WRITE_FM1208_EXIT;
	}
	else
	{
		printf("FWCosSelectFile ok!\n");
	}
           	//Write binary file
	srand(time(0));
	for(i=0; i< g_lenToRW; i++)pWriteBuffer[i] = rand() % 0xff;
	
            status = FWCosUpdateBinaryFile(icdev, 
            	(short)g_fileID,
            	(short)0x0000,
		pWriteBuffer,
            	g_lenToRW,
            	0, // 0- ,1- +MAC , 2- +MAC
            	g_pFileProKey,
            	16);
            if (status != 0) {
                printf("FWCosUpdateBinaryFile error!\n");
                printf("%X\n",status);
                goto WRITE_FM1208_EXIT;

            } else {
                printf("FWCosUpdateBinaryFile ok!\n");
                
               // printf("%s\n",pRBuffer);
		for(i=0; i<g_lenToRW; i++) printf("%02X ",pWriteBuffer[i] & 0xff);
		printf("\n");
            }
		
	lc_beep(icdev, 10);
	

WRITE_FM1208_EXIT:

return status;
}
int fm12xx_readID(int icdev)
{
	int status,i;//the state of each operation
	unsigned long sn;
	unsigned char rlen;
	unsigned char rdata[256];//the buffer read from a block
	unsigned char showData[34]={0};//hex type data
	unsigned char	tt= 7,fg= 56;
        char pRBuffer[256];
      	char pWriteBuffer[256]={0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff};
        char pShowBuf[256];
	unsigned short tag;
	unsigned char sak;
	unsigned char bufCard[12];
	unsigned char cardSize;

_FIND_CARD:
	while(1)
	{
		//device reset
		status = lc_rfReset(icdev,10);
		if(status)
		{
			//printf("ERROR(%d): Device reset failed.\n",status);
			//goto EXIT;
			continue;
		}
		//printf("Device reset OK.\n");


		//find card
		status = lc_card(icdev,1,bufCard, &cardSize,&tag,&sak);
		if(status )
		{
			continue;
		}

		//card reset
		status = lc_pro_reset(icdev,(unsigned char*)&rlen,rdata);
		if(status)
		{
			//printf("ERROR(%d): Card reset failed.\n",status);
			continue;
		} 
		//rlen &= 0xff;
		//printf("Reset info: ");
		//for(i=0; i<rlen; i++) printf("%02X",rdata[i]);
		//printf("\n");
		printf("Found card\n");
		break;
	}//while(1)

			//Select main app
            status = FWCosSelecteApp(icdev);
            if (status != 0) {
                printf("FWCosSelecteApp error!\n");
                goto READ_FM1208_EXIT;
            } else {
                printf("FWCosSelecteApp ok!\n");
            }


            //Authenticate key
            status = FWCosVerifyKey(icdev, 
            	g_pInitExKey,
            	8,
            	FW_KEYTYPE_EXVERIFY);
            if (status != 0) {

		//Authenticate with user's key
		status = FWCosVerifyKey(icdev,
			g_pExKey,
			16,
			FW_KEYTYPE_EXVERIFY);
		
		if(status != 0)
		{
                	printf("FWCosVerifyKey error, invalid card!\n");
                	printf("0x%0x\n",status);
			goto READ_FM1208_EXIT;
		}

            } else {
                printf("FWCosVerifyKey ok!\n");
            }

	status = FWCosSelectFile(icdev, g_fileID);
	if(status != 0)
	{//No file
		printf("FWCosSelectFile error, invalid card!\n");
        	printf("0x%0x\n",status);
		goto READ_FM1208_EXIT;
	}
	else
	{
		printf("FWCosSelectFile ok!\n");
	}


           	//read binary
            status = FWCosReadBinaryFile(icdev, 
            	(short)g_fileID,
            	pRBuffer,
            	(short)0x00,
            	g_lenToRW,
            	(unsigned char)0x00,
            	g_pFileProKey,
            	16);
            if (status != 0) {
                printf("FWCosReadBinaryFile error!\n");
                printf("%X\n",status);
                goto READ_FM1208_EXIT;

            } else {
                printf("FWCosReadBinaryFile ok!\n");
                
               // printf("%s\n",pRBuffer);
		for(i=0; i<g_lenToRW; i++) printf("%02X ",pRBuffer[i] & 0xff);
		printf("\n");
            }
		lc_beep(icdev, 10);
	

READ_FM1208_EXIT:

return status;
}



