#include "usart.h"
#include "protocol.h"
#include "ErrCode.h"
#include "delay.h"

unsigned short gl_curUartBufferPointer = 0;
unsigned char	gl_packageIndex = 0;

void  ULToMultiByte(unsigned long val, unsigned char* pArr, int lenArr, int bInv)
{
	int i;

	for(i=0; i<lenArr; i++)
	{
		if(0  == bInv)
			pArr[i] = (unsigned char)( (val >> 8*i) & 0xff);
		else
			pArr[i] = (unsigned char)((val >> 8*(lenArr-1-i)) & 0xff);
	}
}
int _multiByteToUL(unsigned char* pByte, int lenBytes, int iType, unsigned int* pVal)
{
	unsigned int relVal =0;
	int flag = 0;
	int i = 0;

	if(lenBytes >4 || lenBytes <1)
	{
		flag = ERR_PARA;
		goto _exit;
	}

	for(i=0; i< lenBytes; i++)
	{
		if(0 == iType)
			relVal += pByte[i] << 8*i;
		else if(1 == iType)
			relVal += pByte[i] << 8*(lenBytes -1 -i);
		else
		{
			flag = ERR_PARA;
			goto _exit;
		}
	}
	*pVal = relVal;
_exit:
	return flag;
}
unsigned int genXor (unsigned char* buf, unsigned int len)
{
	unsigned int i;
	unsigned int xor = 0;

	for(i=0;i<len;i++)
		xor ^= *(buf++);

	return xor;
}

unsigned char _uart_send(long icdev, unsigned char* pDataForSend, unsigned char sLen)
{
	unsigned char status = 0;
	
	UART1_Send_Data(pDataForSend, sLen);
	
	return status;
}

unsigned char _uart_receive(long icdev, unsigned char* pDataIn,unsigned char dataLenToRev, int* pReceivedLen)
{
	unsigned char status = 0;
	unsigned int waitCounter = 0;
	unsigned char lenDataGot =0;
	

	//-- Wait data coming...
	while(gl_curUartBufferPointer == UART_RX_CNT)
	{
		//Wait a moment
		delay_ms(1);
		waitCounter++;
		if(waitCounter > 500)
		{
			if(lenDataGot == 0)
				status = ERR_TIMEOUT;
			goto _UART_REV_EXIT;
		}
	}
	
	//-- Filling data...
	while(gl_curUartBufferPointer != UART_RX_CNT)
	{
		pDataIn[lenDataGot++] = USART_RX_BUF[gl_curUartBufferPointer ];
		
		gl_curUartBufferPointer++;
		if(gl_curUartBufferPointer >= USART_REC_LEN)
		{
			gl_curUartBufferPointer  = 0;
		}
		
		if(lenDataGot >= dataLenToRev)
		{
			status = ERR_OK;
			break;
		}
	}
	
	_UART_REV_EXIT:
	*pReceivedLen = lenDataGot ;
	return status;
}

//***********************************************************************/
//	Fill serial output buffer																						*/
/*  Data -> Reader 																											*/
/*  Format  																														*/
/*																																			*/
/*  STX + INX + LEN + DEV + CMD  + DATA + CHK														*/
/*  Note: CHK = INX ^ LEN ^ DEV ^ CMD ^Data[0] ^ Data[1] ^  ^ Data[n]	*/
/*  Param exLen: 																												*/
/************************************************************************/

void mf30w_capOutputBuf_serial(void* _pProData,unsigned char* oBuf,int* allLen)
{	
	unsigned int chk;
	PROTOCOL_CMM* pProData = (PROTOCOL_CMM*)_pProData;
	int i;
	
	ULToMultiByte(UART_TX_VAL_STX,&oBuf[UART_TX_ADR_STX],UART_TX_STXLEN,1);

	ULToMultiByte(gl_packageIndex,&oBuf[UART_TX_ADR_INX],UART_TX_INXLEN,1);

	ULToMultiByte(pProData->DATALEN+UART_TX_CMDLEN+UART_TX_DEVLEN,&oBuf[UART_TX_ADR_LEN],UART_TX_LENLEN,1);

	ULToMultiByte(UART_TX_VAL_DEV,&oBuf[UART_TX_ADR_DEV],UART_TX_DEVLEN,1);

	ULToMultiByte(pProData->CMD,&oBuf[UART_TX_ADR_CMD],UART_TX_CMDLEN,1);

	for(i=0; i< pProData->DATALEN; i++)
	{
		oBuf[UART_TX_ADR_DATA + i] = pProData->pData[i];
	}
	
	chk = genXor(&oBuf[UART_TX_ADR_INX], UART_TX_INXLEN + UART_TX_LENLEN + UART_TX_DEVLEN+UART_TX_CMDLEN+pProData->DATALEN );

	ULToMultiByte(chk,&oBuf[UART_TX_ADR_DATA + pProData->DATALEN ],UART_TX_CHKLEN,1);

	*allLen = UART_TX_STXLEN+ UART_TX_INXLEN + UART_TX_DEVLEN + UART_TX_CMDLEN + UART_TX_LENLEN + pProData->DATALEN  + UART_TX_CHKLEN ;
	
}

//********************************************/
//* commond communication with COM func
//* called by other funcs 
//* 
//*return: unzero if sucess,0 if failed 
//********************************************/
int uart_commInfo(long icdev,int slen,unsigned char* sdata,
	unsigned int *rlen,unsigned char* rdata)
{
	unsigned char OutReport[256]={0};
	int flag ;
	int i;
	int nReaded = 0;
	int counter = 0;
	int userDataLen = 0;
	int userDataReaded = 0;
	unsigned char  fCmdSuit = 1;
	unsigned int cmdSend;
	unsigned int cmdRev;
	unsigned int RevHeader;
	unsigned char revPackageIndex;
	unsigned char  fPackageIndexValid = 1;
	unsigned char revSt = 0;
	unsigned char revCRC;
	unsigned char crcGener;
	unsigned char   fCRCvalid = 1;
	unsigned int tmpUI;

	_multiByteToUL(&sdata[UART_TX_ADR_CMD], UART_TX_CMDLEN, 1, &cmdSend);

	//send data
	for( i=0;i<slen;i++) 
	{
		flag=_uart_send(icdev,&sdata[i],1);
		if(flag)
			return flag;
	}

	RE_REV:
	flag=_uart_receive(icdev,&OutReport[counter ],1,&nReaded);
	if(flag)
	{
		return flag;
	}

	_multiByteToUL(&OutReport[UART_RX_ADR_STX], UART_RX_STXLEN, 1, &RevHeader);
	if(RevHeader != UART_RX_VAL_STX )
	{
		goto RE_REV;//
	}
	counter++;

	//Get package index
	flag=_uart_receive(icdev,&OutReport[counter ],1,&nReaded);
	if(flag)
		return flag;
	_multiByteToUL(&OutReport[UART_RX_ADR_INX], UART_RX_INXLEN, 1, &tmpUI);
	revPackageIndex = (unsigned char) (tmpUI & 0xff);
	if(revPackageIndex == gl_packageIndex)
	{
		gl_packageIndex++;
	}
	else
	{
		fPackageIndexValid = 0;
	}
	counter++;

	//get len
	for(i=0;i< UART_RX_LENLEN;i++)
	{
		flag=_uart_receive(icdev,&OutReport[counter ],1,&nReaded);
		if(flag)
			return flag;

		counter++;
	}

	_multiByteToUL(&OutReport[UART_RX_ADR_LEN], UART_RX_LENLEN, 1, rlen);

	userDataLen = *rlen - UART_RX_DEVLEN - UART_RX_CMDLEN - UART_RX_STLEN;

	//Get Device Bytes
	for(i=0;i< UART_RX_DEVLEN;i++)
	{
		flag=_uart_receive(icdev,&OutReport[counter ],1,&nReaded);
		if(flag)
			return flag;
		counter++;
	}

	//Check command
	for(i=0;i< UART_RX_CMDLEN;i++)
	{
		flag=_uart_receive(icdev,&OutReport[counter ],1,&nReaded);
		if(flag)
			return flag;
		counter++;
	}
	_multiByteToUL(&OutReport[UART_RX_ADR_CMD], UART_RX_CMDLEN, 1, &cmdRev);
	if(cmdSend != cmdRev)
		fCmdSuit = 0;
	else 
		fCmdSuit = 1;

	//Get Status
	for(i=0;i< UART_RX_STLEN;i++)
	{
		flag=_uart_receive(icdev,&OutReport[counter ],1,&nReaded);
		if(flag)
			return flag;
		counter++;
	}
	_multiByteToUL(&OutReport[UART_RX_ADR_ST], UART_RX_STLEN, 1, &tmpUI);
	revSt = tmpUI & 0xff;

	//Get user data
	for(i=0;i<userDataLen;i++)
	{
		flag=_uart_receive(icdev,&OutReport[counter ],1,&nReaded);
		if(flag) 
			return flag;

		userDataReaded++;
		*(rdata++) = OutReport[counter];
		counter++;
	}

	//Check CRC Byte
	for(i=0;i< UART_RX_CHKLEN;i++)
	{
		flag=_uart_receive(icdev,&OutReport[counter ],1,&nReaded);
		if(flag)
			return flag;
		counter++;
	}
	_multiByteToUL(&OutReport[UART_RX_ADR_DATA + userDataReaded], UART_RX_CHKLEN, 1, &tmpUI);
	revCRC = tmpUI & 0xff;

	crcGener = genXor(&OutReport[UART_RX_ADR_INX], UART_RX_MIN_LEN + userDataLen - UART_RX_STXLEN - UART_RX_CHKLEN);
	if(crcGener != revCRC)
	{
		fCRCvalid = 0;
	}

	*rlen = userDataReaded;

	if(0 == fCmdSuit) {flag = ERR_CMD; goto _TRANS_EXIT;}
	if(0 ==fCRCvalid) {flag = ERR_CRC; goto _TRANS_EXIT;}
	if(0 == fPackageIndexValid){flag = ERR_TRANS; goto _TRANS_EXIT;}
	if(revSt != 0){flag = revSt; goto _TRANS_EXIT;}

	_TRANS_EXIT:
	return flag;
}

int pub_CommonTransfer(int icdev, void* _pProData,unsigned char* pRev, unsigned int* lenRev)
{
	unsigned char	outBuf[512];
	int	lenAll;
	int    rel;

	PROTOCOL_CMM *pProData_serial = (PROTOCOL_CMM*)_pProData;

	mf30w_capOutputBuf_serial(pProData_serial,outBuf,&lenAll);

	gl_curUartBufferPointer = 0;//Reset buffer pointer
	UART_RX_CNT = 0;//Reset buffer receive counter
	
	rel = uart_commInfo(icdev,lenAll,outBuf,lenRev,pRev);

	return rel;
}







