#include "protocol.h"
#include "ErrCode.h"
#include <string.h>

//------------------------------------------------------ Command functions ----------------------------------
int lc_getver(int icdev,unsigned char *buff)
{
	int rlen = 0;
	PROTOCOL_CMM proData_serial;
	int flag = 0;

	proData_serial.CMD = (unsigned int)COMGETVER;
	proData_serial.DATALEN = 0;

	flag = pub_CommonTransfer((int)icdev, &proData_serial , (unsigned char*)buff, (unsigned int*)&rlen);
	if(ERR_OK == flag) buff[rlen] = '\0';

	return flag;
}
//------------------------------------------------------ Simple Device functions ----------------------------------
int  lc_beep(int icdev,unsigned int _Msec)
{
	int rlen = 0;
	PROTOCOL_CMM proData_serial;
	unsigned char inBuf[255];
	int		flag, datalen;

	datalen = 1;

	proData_serial.CMD = (unsigned int)COMBEEP;
	proData_serial.DATALEN = datalen;
	
	proData_serial.pData[0] = _Msec;

	flag = pub_CommonTransfer((int)icdev,&proData_serial, (unsigned char*)inBuf, (unsigned int*)&rlen);

	return flag;
}
//------------------------------------------------------ RFID functions ----------------------------------
int  lc_card(int icdev,unsigned char _Mode,unsigned char *_Snr, unsigned char* _outSnrSize, unsigned int* pTag, unsigned char* pSak)
{
	unsigned int rlen = 0;
	PROTOCOL_CMM proData_serial;
	int		flag, datalen;
	unsigned char inBuf[255];
	int i=0;

	datalen = 1;

	proData_serial.CMD = COMREQUEST;
	proData_serial.DATALEN = datalen;
	
	(0 == _Mode)?(_Mode = 0x26):(_Mode = 0x52);

	proData_serial.pData[0] = _Mode;

	flag =  pub_CommonTransfer(icdev,&proData_serial, inBuf, &rlen);

	if(flag) return flag;//ִʧܣֱӷش

	//ִгɹжԷصݽзظӦ

	*pTag = 0;
	for(i = 0; i<2; i++)
	{
		*pTag  += (unsigned long) (inBuf[1-i] << 8* (1-i));
	}
	*pSak = inBuf[2];

	*_outSnrSize = rlen -3;
	memcpy(_Snr, &inBuf[3], *_outSnrSize);

	return ERR_OK;
}
int lc_authentication(int icdev,unsigned char _Mode,
									   unsigned char sector, unsigned char* pKey)
{
	unsigned int rlen = 0;
	PROTOCOL_CMM proData_serial;
	int		flag;
	unsigned char inBuf[255];

	proData_serial.CMD = COMM1AUTHENPASS;

	proData_serial.DATALEN = 8;
	proData_serial.pData[0]  = _Mode;
	proData_serial.pData[1] = sector;
	memcpy(&proData_serial.pData[2], pKey, 6);

	flag =  pub_CommonTransfer(icdev,&proData_serial, inBuf, &rlen);

	if(flag) return flag;//ִʧܣֱӷش

	//ִгɹжԷصݽзظӦ

	return ERR_OK;

}
int lc_read(int icdev,unsigned char blk,unsigned char *_Data)
{
	unsigned int rlen = 0;
	PROTOCOL_CMM proData_serial;
	int		flag, datalen;
	unsigned char inBuf[255];
	
	datalen = 1;
	
	proData_serial.CMD = COMM1READ;
	proData_serial.DATALEN = datalen;
	proData_serial.pData[0] = blk;
	
	flag =  pub_CommonTransfer(icdev,&proData_serial, inBuf, &rlen);
	
	if(flag) return flag;//ִʧܣֱӷش
	
	//ִгɹжԷصݽзظӦ
	
	memcpy(_Data, inBuf, rlen);

	return ERR_OK;
}

int lc_read_convenient(int icdev, unsigned char blkAddr, unsigned char keyMode, unsigned char* pKey, unsigned char* pData_out)
{
	unsigned int rlen = 0;
	PROTOCOL_CMM proData_serial;
	int		flag, datalen;
	unsigned char inBuf[255];
	
	datalen = 9;
	
	proData_serial.CMD = COMM1READ_CONV;
	proData_serial.DATALEN = datalen;
	
	proData_serial.pData[0] = keyMode;
	proData_serial.pData[1] = blkAddr;
	proData_serial.pData[2] = 1;//Need find card

	memcpy(&proData_serial.pData[3], pKey, 6);
	
	flag =  pub_CommonTransfer(icdev,&proData_serial, inBuf, &rlen);

	if(flag) return flag;//ִʧܣֱӷش
	
	//ִгɹжԷصݽзظӦ

	memcpy(pData_out, inBuf, rlen);

	return ERR_OK;
}

int lc_write(int icdev,unsigned char blk,unsigned char *_Data)
{
	unsigned int rlen = 0;
	PROTOCOL_CMM proData_serial;
	int		flag, datalen;
	unsigned char inBuf[255];
	
	datalen = 17;
	
	proData_serial.CMD = COMM1WRITE;
	proData_serial.DATALEN = datalen;

	
	proData_serial.pData[0] = blk;
	memcpy(&proData_serial.pData[1], _Data, 16);

	flag =  pub_CommonTransfer(icdev,&proData_serial, inBuf, &rlen);
	
	if(flag) return flag;//ִʧܣֱӷش
	
	//ִгɹжԷصݽзظӦ
	return ERR_OK;
}
int lc_write_convenient(int icdev, unsigned char blkAddr, unsigned char keyMode, unsigned char* pKey, unsigned char* pData_in)
{
	unsigned int rlen = 0;
	PROTOCOL_CMM proData_serial;
	int		flag, datalen;
	unsigned char inBuf[255];
	
	datalen = 25;//24;
	
	proData_serial.CMD = COMM1WRITE_CONV;
	proData_serial.DATALEN = datalen;

	proData_serial.pData[0] = keyMode;
	proData_serial.pData[1] = blkAddr;

	memcpy(&proData_serial.pData[2], pKey, 6);
	memcpy(&proData_serial.pData[8], pData_in, 16);
	proData_serial.pData[24] =  1; //Need find card first
	
	flag =  pub_CommonTransfer(icdev,&proData_serial, inBuf, &rlen);;

	if(flag) return flag;//ִʧܣֱӷش
	
	//ִгɹжԷصݽзظӦ

	return ERR_OK;
}
int lc_readTag(int icdev,unsigned char page,unsigned char *_Data)
{
	unsigned int rlen = 0;
	PROTOCOL_CMM proData_serial;
	int		flag, datalen;
	unsigned char inBuf[255];
	
	datalen = 1;
	
	proData_serial.CMD = CMD_READ_TAG;
	proData_serial.DATALEN = datalen;
	
	proData_serial.pData[0] = page;
	
	flag =  pub_CommonTransfer(icdev,&proData_serial, inBuf, &rlen);
	
	if(flag) return flag;//ִʧܣֱӷش
	
	//ִгɹжԷصݽзظӦ
	
	memcpy(_Data, inBuf, rlen);

	return ERR_OK;
}
int lc_writeTag(int icdev,unsigned char page,unsigned char *_Data)
{
	unsigned int rlen = 0;
	PROTOCOL_CMM proData_serial;
	int		flag, datalen;
	unsigned char inBuf[255];
	
	datalen = 5;
	
	proData_serial.CMD = CMD_WRITE_TAG;
	proData_serial.DATALEN = datalen;

	
	proData_serial.pData[0] = page;
	memcpy(&proData_serial.pData[1], _Data, 4);

	flag =  pub_CommonTransfer(icdev,&proData_serial, inBuf, &rlen);
	
	if(flag) return flag;//ִʧܣֱӷش
	
	//ִгɹжԷصݽзظӦ
	return ERR_OK;
}

int lc_authenTag(int icdev,unsigned char *pKey)
{
	unsigned int rlen = 0;
	PROTOCOL_CMM proData_serial;
	int		flag, datalen;
	unsigned char inBuf[255];
	
	datalen = 4;
	
	proData_serial.CMD = CMD_AUTHEN_TAG;
	proData_serial.DATALEN = datalen;

	memcpy(&proData_serial.pData[0], pKey, 4);

	flag =  pub_CommonTransfer(icdev,&proData_serial, inBuf, &rlen);
	
	if(flag) return flag;//ִʧܣֱӷش
	
	//ִгɹжԷصݽзظӦ
	return ERR_OK;
}
int lc_rawExchange(int icdev,unsigned char slen,unsigned char * sbuff,unsigned char *rrlen,unsigned char * rbuff)
{
	unsigned int rlen = 0;
	PROTOCOL_CMM proData_serial;
	int		flag, datalen;
	unsigned char inBuf[255];
	
	datalen = slen;
	
	proData_serial.CMD = CMD_RAW_EXC;
	proData_serial.DATALEN = datalen;

	memcpy(&proData_serial.pData[0], sbuff, datalen);

	flag =  pub_CommonTransfer(icdev,&proData_serial, inBuf, &rlen);
	if(0 == flag)
	{
		*rrlen =  rlen;
		memcpy(rbuff, inBuf, rlen);
	}
	
	if(flag) return flag;//ִʧܣֱӷش
	
	//ִгɹжԷصݽзظӦ
	return ERR_OK;
}
int lc_initval(int icdev,unsigned char _Adr,unsigned int _Value)
{
	unsigned int rlen = 0;
	PROTOCOL_CMM proData_serial;
	int		flag, datalen;
	unsigned char inBuf[255];

	datalen = 5;

	proData_serial.CMD = COMINITVAL;
	proData_serial.DATALEN = datalen;
	
	proData_serial.pData[0] = _Adr;

	ULToMultiByte(_Value, &proData_serial.pData[1], 4, 1);

	flag = pub_CommonTransfer(icdev,&proData_serial, inBuf, &rlen);

	if(flag) return flag;//ִʧܣֱӷش

	//ִгɹжԷصݽзظӦ

	return ERR_OK;
}
int  lc_increment(int icdev,unsigned char _Adr,unsigned int _Value)
{
	unsigned int rlen = 0;
	PROTOCOL_CMM proData_serial;
	int		flag, datalen;
	unsigned char inBuf[255];

	datalen = 5;

	proData_serial.CMD = COMINCREMENT;
	proData_serial.DATALEN = datalen;

	proData_serial.pData[0] = _Adr;

	ULToMultiByte(_Value, &proData_serial.pData[1], 4, 1);

	flag =  pub_CommonTransfer(icdev,&proData_serial, inBuf, &rlen);

	if(flag) return flag;//ִʧܣֱӷش

	//ִгɹжԷصݽзظӦ

	return ERR_OK;

}
int lc_decrement(int icdev,unsigned char _Adr,unsigned long _Value)
{
	unsigned int rlen = 0;
	PROTOCOL_CMM proData_serial;
	int		flag, datalen;
	unsigned char inBuf[255];

	datalen = 5;

	proData_serial.CMD = COMDECREMENT;
	proData_serial.DATALEN = datalen;

	proData_serial.pData[0] = _Adr;

	ULToMultiByte(_Value, &proData_serial.pData[1], 4, 1);

	flag =  pub_CommonTransfer(icdev,&proData_serial, inBuf, &rlen);

	if(flag) return flag;//ִʧܣֱӷش

	//ִгɹжԷصݽзظӦ
	return ERR_OK;
}
int lc_readval(int icdev,unsigned char _Adr,unsigned int *_Value)
{
	unsigned int rlen = 0;
	PROTOCOL_CMM proData_serial;
	int		flag, datalen;
	unsigned char inBuf[255];

	datalen = 1;

	proData_serial.CMD = COMREADVAL;
	proData_serial.DATALEN = datalen;

	proData_serial.pData[0] = _Adr;

	flag =  pub_CommonTransfer(icdev,&proData_serial, inBuf, &rlen);

	if(flag) return flag;//ִʧܣֱӷش

	//ִгɹжԷصݽзظӦ
	if(rlen != 4)
		return ERR_TIMEOUT;

	_multiByteToUL(inBuf, 4, 1, _Value);

	return ERR_OK;
}
int lc_restore(int icdev,unsigned char _fromAdr, unsigned char _toAdr)
{
	unsigned int rlen = 0;
	PROTOCOL_CMM proData_serial;
	int		flag, datalen;
	unsigned char inBuf[255];

	datalen = 2;

	proData_serial.CMD = COMRESTORE;
	proData_serial.DATALEN = datalen;

	proData_serial.pData[0] = _toAdr;
	proData_serial.pData[1] = _fromAdr;

	flag =  pub_CommonTransfer(icdev,&proData_serial, inBuf, &rlen);

	if(flag) return flag;//ִʧܣֱӷش

	//ִгɹжԷصݽзظӦ

	return ERR_OK;
}
int  lc_halt(int icdev)
{
	unsigned int rlen = 0;
	PROTOCOL_CMM proData_serial;
	int		flag, datalen;
	unsigned char inBuf[255];

	datalen = 0;

	proData_serial.CMD = COMHALT;
	proData_serial.DATALEN = datalen;

	flag = pub_CommonTransfer(icdev,&proData_serial, inBuf, &rlen);

	if(flag) return flag;//ִʧܣֱӷش

	//ִгɹжԷصݽзظӦ

	return ERR_OK;
}
int lc_pro_reset
(
 int ICDev,//˿ڱʶ
 unsigned char *rlen,//ظλϢĳ
 unsigned char * rbuff//ŷصĸλϢ
 )
{
	unsigned int _rlen = 0;
	PROTOCOL_CMM proData_serial;
	unsigned char inBuf[255];
	int		flag, datalen;

	datalen = 0;

	proData_serial.CMD = (unsigned int)FCPURESETCOM;
	proData_serial.DATALEN = datalen;
	
	flag = pub_CommonTransfer((int)ICDev,&proData_serial, (unsigned char*)inBuf, (unsigned int*)&_rlen);

	if(0 == flag)
	{
		*rlen = (unsigned char)(_rlen & 0xff);
		memcpy(rbuff, inBuf, _rlen);
	}

	return flag;
}
int lc_rfReset(int icdev,unsigned int _Msec)
{
	unsigned int rlen = 0;
	PROTOCOL_CMM proData_serial;
	unsigned char inBuf[255];
	int		flag, datalen;
	
	datalen = 2;

	proData_serial.CMD = (unsigned int)COMRESET;
	proData_serial.DATALEN = datalen;
	
	ULToMultiByte(_Msec, proData_serial.pData, 2, 1);

	flag = pub_CommonTransfer((int)icdev,&proData_serial, (unsigned char*)inBuf, (unsigned int*)&rlen);

	return flag;
}
//2
int 
lc_pro_commandlink
(
 int ICDev,//˿ڱʶ
 unsigned int slen,//͵Ϣ
 unsigned char * sbuff,//Ҫ͵Ϣ
 unsigned int *rlen,//Ϣĳ
 unsigned char * rbuff,//ŷصϢ
 unsigned char tt,//ӳʱ䣬λΪ10ms
 unsigned char FG//ָȡֵС64
 )
{
	unsigned int _rlen;
	int flag;
	PROTOCOL_CMM proData_serial;
	unsigned char inBuf[255];
	int		 datalen_serial;
	
	datalen_serial = slen + 2;
	
	proData_serial.CMD = (unsigned int)FCPUCOMMANDCOM;
	proData_serial.DATALEN = datalen_serial;
	
	proData_serial.pData [0] = tt;
	proData_serial.pData [1] = FG;
	memcpy(&proData_serial.pData [2], sbuff, slen);
	
	flag = pub_CommonTransfer((int)ICDev,&proData_serial, (unsigned char*)inBuf, (unsigned int*)&_rlen);
	
	if(flag)return flag;
	
	*rlen = _rlen;
	memcpy(rbuff, inBuf, _rlen);

	return flag;
}

int lc_iccSelCardType
(
 int ICDev,//Handle of device
 unsigned char slot,
 unsigned int cardType
 )
{
	unsigned int _rlen;
	int flag;
	PROTOCOL_CMM proData_serial;
	unsigned char inBuf[255];
	int		 datalen_serial;
	
	datalen_serial = 2;
	
	proData_serial.CMD = (unsigned int)CMD_ICC_SELCARD;
	proData_serial.DATALEN = datalen_serial;

	proData_serial.pData [0] = slot;
	proData_serial.pData [1] = cardType;
	
	flag = pub_CommonTransfer((int)ICDev,&proData_serial, (unsigned char*)inBuf, (unsigned int*)&_rlen);
	
	if(flag)return flag;

	return flag;
}
int  lc_iccGetATR(int icdev,unsigned char slot, unsigned char *response_out, unsigned char* resLen_out)
{
	unsigned int _rlen;
	int flag;
	PROTOCOL_CMM proData_serial;
	unsigned char inBuf[255];
	int		 datalen_serial;
	
	datalen_serial = 1;
	
	proData_serial.CMD = (unsigned int)CMD_ICC_GETATR;
	proData_serial.DATALEN = datalen_serial;

	proData_serial.pData [0] = slot;
	
	flag = pub_CommonTransfer((int)icdev,&proData_serial, (unsigned char*)inBuf, (unsigned int*)&_rlen);
	
	if(flag)return flag;
	
	*resLen_out = _rlen;
	memcpy(response_out, inBuf, _rlen);

	return flag;
}
int  lc_icc_APDU
(
 int ICDev,//Handle of device
 unsigned char slot,
 unsigned int slen,//The length of data to send
 unsigned char * sbuff,//Data to send
 unsigned int *rlen,//The length of data received
 unsigned char * rbuff//The data received
 )
{
	unsigned int _rlen;
	int flag;
	PROTOCOL_CMM proData_serial;
	unsigned char inBuf[256];
	int		 datalen_serial;
	
	datalen_serial = slen + 1;
	
	proData_serial.CMD = (unsigned int)CMD_ICC_APDU;
	proData_serial.DATALEN = datalen_serial;

	proData_serial.pData [0] = slot;
	
	memcpy(&proData_serial.pData [1], sbuff, slen);
	
	flag = pub_CommonTransfer((int)ICDev,&proData_serial, (unsigned char*)inBuf, (unsigned int*)&_rlen);
	
	if(flag)return flag;
	
	*rlen = _rlen;
	memcpy(rbuff, inBuf, _rlen);

	return flag;
}
int lc_readSIM(int icdev, unsigned char slot, char* pSIM_Info_out)
{
	unsigned int _rlen;
	int flag;
	PROTOCOL_CMM proData_serial;
	unsigned char inBuf[256];
	int		 datalen_serial;
	
	datalen_serial = 1;
	
	proData_serial.CMD = 0x18A0;//(unsigned int)CMD_GET_SIM_INFO;//0x18A0
	proData_serial.DATALEN = datalen_serial;

	proData_serial.pData [0] = slot;
	
	//memcpy(&proData_serial.pData [1], sbuff, slen);
	
	flag = pub_CommonTransfer((int)icdev,&proData_serial, (unsigned char*)inBuf, (unsigned int*)&_rlen);
	
	if(flag)return flag;
	
	//*rlen = _rlen;
	memcpy(pSIM_Info_out, inBuf, _rlen);

	return flag;
}

//----------------------------- ISO15693 --------------
int lc_find15693(int icdev, unsigned char reqMode, unsigned char *response_out, unsigned char* resLen_out)
{
	int _rlen = 0;
	int userLen = 0;
	PROTOCOL_CMM proData_serial;
	unsigned char inBuf[255];
	int		flag;

	userLen = 1;

	proData_serial.CMD = (unsigned int)CMD_15693_REQ;
	proData_serial.DATALEN = userLen;

	proData_serial.pData[0] = reqMode;

	flag = pub_CommonTransfer((int)icdev,&proData_serial, (unsigned char*)inBuf, (unsigned int*)&_rlen);
	
	if(flag == 0)
	{
		if(_rlen > 1) 
		{
			*resLen_out = _rlen;
			memcpy(response_out, inBuf, _rlen);
		}
		else
			flag = ERR_TRANS;
	}

	return flag;
}
int lc_15693_command
(
 int ICDev,//Handle of device
 unsigned char cmd, //The command to send
 unsigned char* pUID, //The id of card (8 bytes)
 unsigned int sParaLen,//The length of paramter 
 unsigned char * psPara,//Paramter 
 unsigned int *rParaLen,//The length of paramter received
 unsigned char * rPara//The parater received
 )
{
	int _rlen = 0;
	int  dataLen ;
	PROTOCOL_CMM proData_serial;
	unsigned char inBuf[256];
	int		flag;

	dataLen = 9 + sParaLen;

	proData_serial.CMD = (unsigned int)CMD_15693_EXCH_COMMOM;
	proData_serial.DATALEN = dataLen;

	//--- Command byte
	proData_serial.pData[0] = cmd;
	//--- UID bytes
	memcpy(&proData_serial.pData[1], pUID, 8);
	//--- Paramters
	memcpy(&proData_serial.pData[9], psPara, sParaLen);

	flag = pub_CommonTransfer((int)ICDev,&proData_serial, (unsigned char*)inBuf, (unsigned int*)&_rlen);
	if(0 == flag)
	{
		*rParaLen = _rlen;
		memcpy(rPara, inBuf, _rlen);
	}
	return flag;
}
int lc_15693_command_custom
(
 int ICDev,//Handle of device
 unsigned char cmd, //The command to send
 unsigned char MfgCode, //IC Mfg code
 unsigned char* pUID, //The id of card (8 bytes)
 unsigned int sParaLen,//The length of paramter 
 unsigned char * psPara,//Paramter 
 unsigned int *rParaLen,//The length of paramter received
 unsigned char * rPara//The parater received
 )
{
	int _rlen = 0;
	int  dataLen ;
	PROTOCOL_CMM proData_serial;
	unsigned char inBuf[256];
	int		flag;

	dataLen = 10 + sParaLen;

	proData_serial.CMD = (unsigned int)CMD_15693_EXCH_CUSTOM;
	proData_serial.DATALEN = dataLen;

	//--- Command byte
	proData_serial.pData[0] = cmd;
	//--- Mfg code
	proData_serial.pData[1] = MfgCode;
	//--- UID bytes
	memcpy(&proData_serial.pData[2], pUID, 8);

	//--- Paramters
	memcpy(&proData_serial.pData[10], psPara, sParaLen);

	flag = pub_CommonTransfer((int)ICDev,&proData_serial, (unsigned char*)inBuf, (unsigned int*)&_rlen);
	if(0 == flag)
	{
		*rParaLen = _rlen;
		memcpy(rPara, inBuf, _rlen);
	}
	return flag;
}
int lc_15693_command_ex
(
 int ICDev,//Handle of device
 unsigned int sRequestLen,//The length of request frame 
 unsigned char * psRequest,//Request 
 unsigned int *rResLen,//The length of response received
 unsigned char * rRes//The response received
 )
{
	//return _compro_15693_command_ex(ICDev, sRequestLen, psRequest, rResLen, rRes);
	int _rlen = 0;
	int  dataLen ;
	PROTOCOL_CMM proData_serial;
	unsigned char inBuf[256];
	int		flag;

	dataLen = sRequestLen;

	proData_serial.CMD = (unsigned int)CMD_15693_EXCH_EX;
	proData_serial.DATALEN = dataLen;

	//--- Paramters
	memcpy(&proData_serial.pData[0], psRequest, sRequestLen);

	//flag = mf30w_CommonTransfer((int)ICDev,&proData, (unsigned char*)inBuf/*inBuf*/, (int*)&_rlen);
	flag = pub_CommonTransfer((int)ICDev,&proData_serial, (unsigned char*)inBuf, (unsigned int*)&_rlen);
	if(0 == flag)
	{
		*rResLen = _rlen;
		memcpy(rRes, inBuf, _rlen);
	}
	return flag;
}
int lc_15693_stay_quiet(int icdev,unsigned char *pUID)
{
	int		status;
	unsigned char _cmd;
	unsigned int _paraLen;
	unsigned char _para[27];
	unsigned int _rParaLen;
	unsigned char _rPara[16];

	//---------------- Check paramter ---
	//---- Set command
	_cmd = ISO15693_STAY_QUIET;

	//---- Set Paramters

	//---- Set paramters length
	_paraLen = 0;

	status  = lc_15693_command(icdev, 
		_cmd,
		pUID,
		_paraLen,
		_para,
		&_rParaLen,
		_rPara);

	return status;
}
int lc_15693_select_uid(int icdev,unsigned char *pUID)
{
	int		status;
	unsigned char _cmd;
	unsigned int _paraLen;
	unsigned char _para[27];
	unsigned int _rParaLen;
	unsigned char _rPara[16];

	//---------------- Check paramter ---
	//---- Set command
	_cmd = ISO15693_SELECT;

	//---- Set Paramters

	//---- Set paramters length
	_paraLen = 0;

	status  = lc_15693_command(icdev, 
		_cmd,
		pUID,
		_paraLen,
		_para,
		&_rParaLen,
		_rPara);

	return status;
}
int lc_15693_reset_to_ready(int icdev,unsigned char *pUID)
{
	int		status;
	unsigned char _cmd;
	unsigned int _paraLen;
	unsigned char _para[27];
	unsigned int _rParaLen;
	unsigned char _rPara[16];

	//---------------- Check paramter ---
	//---- Set command
	_cmd = ISO15693_RESET_TO_READY;

	//---- Set Paramters

	//---- Set paramters length
	_paraLen = 0;

	status  = lc_15693_command(icdev, 
		_cmd,
		pUID,
		_paraLen,
		_para,
		&_rParaLen,
		_rPara);

	return status;
}
int lc_15693_readBlock(int icdev,unsigned char *pUID,unsigned char startBlock,unsigned char blockNum,
							   unsigned char *rlen,unsigned char *rbuffer)
{
	int		status;
	unsigned char _cmd;
	unsigned int _paraLen;
	unsigned char _para[27];
	unsigned int _rParaLen;

	//---------------- Check paramter ---
	//if(blocknum<=0||blocknum>6) //-2023.9.4
	if(blockNum <= 0) //+2023.9.4
		return ERR_PARA;//parameter error

	//---- Set command
	if(blockNum > 1)
		_cmd = ISO15693_READ_MULTIPLE_BLOCKS;
	else
		_cmd = ISO15693_READ_SINGLE_BLOCK;

	//---- Set Paramters
	_para[0] = startBlock;
	if(blockNum > 1)
		_para[1] = blockNum;

	//---- Set paramters length
	if(blockNum > 1)
		_paraLen = 2;
	else
		_paraLen = 1;

	status  = lc_15693_command(icdev, 
		_cmd,
		pUID,
		_paraLen,
		_para,
		&_rParaLen,
		rbuffer);
	if(0 == status)
	{
		//+2023.3.21 +++
		if(_rParaLen < 4)
		{
			status = ERR_PARA;
		}else{
		//+2023.3.21 ---
			*rlen = (unsigned char)_rParaLen;
		}
	}

	return status;
}
int lc_15693_writeBlock(int icdev,unsigned char *pUID,unsigned char startBlock,unsigned char blockNum, 
								unsigned char wlen,unsigned char *wbuffer)
{
	int		status;
	unsigned char _cmd;
	unsigned int _paraLen;
	unsigned char _para[257];
	unsigned int _rParaLen;
	unsigned char _rPara[17];

	//---------------- Check paramter ---
	if( (blockNum > 6)  )
		return ERR_PARA;//parameter error

	if(  (wlen != 4*blockNum) && (wlen != 8*blockNum) )
		return ERR_PARA;//parameter error

	//---- Set command
	if(blockNum > 1)
		_cmd = ISO15693_WRITE_MULTIPLE_BLOCKS;
	else
		_cmd = ISO15693_WRITE_SINGLE_BLOCK;

	//---- Set Paramters
	_para[0] = startBlock;
	if(blockNum == 1)
	{
		memcpy(&_para[1], wbuffer, wlen);
	}
	else
	{
		_para[1] = blockNum;
		//if(blocknum > 1)
		//{
		//	_para[1] = blocknum -1;//test
		//}
		memcpy(&_para[2], wbuffer, wlen);
	}

	//---- Set paramters length
	if(blockNum == 1)
		_paraLen = 1 + wlen;
	else
		_paraLen = 2 + wlen;

	status  = lc_15693_command(icdev, 
		_cmd,
		pUID,
		_paraLen,
		_para,
		&_rParaLen,
		_rPara);

	//+2023.3.21 +++ 
	if(_rParaLen > 0)
	{//Should not return any data if success
		status = ERR_PARA;
	}
	//+2023.3.21 ---

	return status;
}
int lc_15693_lock_block(int icdev,unsigned char *pUID,unsigned char block)
{
	int		status;
	unsigned char _cmd;
	unsigned int _paraLen;
	unsigned char _para[27];
	unsigned int _rParaLen;
	unsigned char _rPara[16];

	//---------------- Check paramter ---
	//---- Set command
	_cmd = ISO15693_LOCK_BLOCK;

	//---- Set Paramters
	_para[0] = block;

	//---- Set paramters length
	_paraLen = 1;

	status  = lc_15693_command(icdev, 
		_cmd,
		pUID,
		_paraLen,
		_para,
		&_rParaLen,
		_rPara);

	return status;
}
int lc_15693_write_afi(int icdev,unsigned char *pUID,unsigned char AFI)
{
	int		status;
	unsigned char _cmd;
	unsigned int _paraLen;
	unsigned char _para[27];
	unsigned int _rParaLen;
	unsigned char _rPara[16];

	//---------------- Check paramter ---
	//---- Set command
	_cmd = ISO15693_WRITE_AFI;

	//---- Set Paramters
	_para[0] = AFI;

	//---- Set paramters length
	_paraLen = 1;

	status  = lc_15693_command(icdev, 
		_cmd,
		pUID,
		_paraLen,
		_para,
		&_rParaLen,
		_rPara);

	return status;
}
int lc_15693_lock_afi(int icdev,unsigned char *pUID)
{
	int		status;
	unsigned char _cmd;
	unsigned int _paraLen;
	unsigned char _para[27];
	unsigned int _rParaLen;
	unsigned char _rPara[16];

	//---------------- Check paramter ---
	//---- Set command
	_cmd = ISO15693_LOCK_AFI;

	//---- Set Paramters
	_para[0] = 0;//AFI;

	//---- Set paramters length
	_paraLen = 0;

	status  = lc_15693_command(icdev, 
		_cmd,
		pUID,
		_paraLen,
		_para,
		&_rParaLen,
		_rPara);

	return status;
}
int lc_15693_write_dsfid(int icdev,unsigned char *pUID,unsigned char DSFID)
{
	int		status;
	unsigned char _cmd;
	unsigned int _paraLen;
	unsigned char _para[27];
	unsigned int _rParaLen;
	unsigned char _rPara[16];

	//---------------- Check paramter ---
	//---- Set command
	_cmd = ISO15693_WRITE_DSFID;

	//---- Set Paramters
	_para[0] = DSFID;

	//---- Set paramters length
	_paraLen = 1;

	status  = lc_15693_command(icdev, 
		_cmd,
		pUID,
		_paraLen,
		_para,
		&_rParaLen,
		_rPara);

	return status;
}
int lc_15693_lock_dsfid(int icdev,unsigned char *pUID)
{
	int		status;
	unsigned char _cmd;
	unsigned int _paraLen;
	unsigned char _para[27];
	unsigned int _rParaLen;
	unsigned char _rPara[16];

	//---------------- Check paramter ---
	//---- Set command
	_cmd = ISO15693_LOCK_DSFID;

	//---- Set Paramters
	//_para[0] = DSFID;

	//---- Set paramters length
	_paraLen = 0;

	status  = lc_15693_command(icdev, 
		_cmd,
		pUID,
		_paraLen,
		_para,
		&_rParaLen,
		_rPara);

	return status;
}
int lc_15693_get_systemInfo(int icdev,unsigned char *pUID,unsigned char *rlen,unsigned char *rbuffer)
{
	int		status;
	unsigned char _cmd;
	unsigned int _paraLen;
	unsigned char _para[27];
	unsigned int _rParaLen;
	unsigned char _rPara[16];

	//---------------- Check paramter ---
	//---- Set command
	_cmd = ISO15693_GET_SYSTEM_INFO;

	//---- Set Paramters

	//---- Set paramters length
	_paraLen = 0;

	status  = lc_15693_command(icdev, 
		_cmd,
		pUID,
		_paraLen,
		_para,
		&_rParaLen,
		rbuffer);

	if(0 == status)
	{
		*rlen = _rParaLen;
	}

	return status;
}
int lc_15693_get_securityInfo(int icdev,unsigned char *pUID,
									  unsigned char startBlock,unsigned char blockNum,
									  unsigned char *rlen,unsigned char *rbuffer)
{
	int		status;
	unsigned char _cmd;
	unsigned int _paraLen;
	unsigned char _para[27];
	unsigned int _rParaLen;
	unsigned char _rPara[16];

	//---------------- Check paramter ---
	//---- Set command
	_cmd = ISO15693_GET_MULTIPLE_BLOCK_SECURITY;

	//---- Set Paramters
	_para[0] = startBlock;
	_para[1] = blockNum;
	//---- Set paramters length
	_paraLen = 2;

	status  = lc_15693_command(icdev, 
		_cmd,
		pUID,
		_paraLen,
		_para,
		&_rParaLen,
		rbuffer);

	if(0 == status)
	{
		*rlen = _rParaLen;
	}

	return status;
}

int  lc_15693_getRandom(int icdev,unsigned char *pUID,  unsigned char* pRandomOut)
{
	int		status;
	unsigned char _cmd;
	unsigned int _paraLen;
	unsigned char _para[17];
	unsigned int _rParaLen;
	unsigned char _rPara[16];
	unsigned char  _MfgCode = 0x04;

	//---------------- Check paramter ---
	//---- Set command
	_cmd = ISO15693_GET_RANDDOM;

	//---- Set Paramters
	//---- Set paramters length
	_paraLen = 0;

	status  = lc_15693_command_custom(icdev, 
		_cmd,
		_MfgCode,
		pUID,
		_paraLen,
		_para,
		&_rParaLen,
		pRandomOut);

	return status;
}

int lc_15693set_password(
	int icdev,
	unsigned char *pUID, 
	unsigned char pwdType, 
	unsigned char* pPwd)
{
	int		status;
	unsigned char _cmd;
	unsigned int _paraLen;
	unsigned char _para[16];
	unsigned int _rParaLen;
	unsigned char _rPara[16];
	unsigned char pRandom[5];
	unsigned char  _MfgCode = 0x04;

	status = lc_15693_getRandom(icdev, pUID, pRandom);
	if(status != 0 )
		return status;

	pPwd[0] = pRandom[0] ^ pPwd[0];
	pPwd[1] = pRandom[1] ^ pPwd[1];
	pPwd[2] = pRandom[0] ^ pPwd[2];
	pPwd[3] = pRandom[1] ^ pPwd[3];

	//---------------- Check paramter ---

	//---- Set command
	_cmd = ISO15693_SET_PASS;

	//---- Set Paramters
	_para[0] = pwdType;
	memcpy(&_para[1], pPwd, 4);

	//---- Set paramters length
	_paraLen = 5;

	status  = lc_15693_command_custom(icdev, 
		_cmd,
		_MfgCode,
		pUID,
		_paraLen,
		_para,
		&_rParaLen,
		_rPara);

	return status;
}
int lc_15693_write_password(
	int icdev,
	unsigned char *pUID, 
	unsigned char pwdType, 
	unsigned char* pPwd)
{
	int		status;
	unsigned char _cmd;
	unsigned int _paraLen;
	unsigned char _para[17];
	unsigned int _rParaLen;
	unsigned char _rPara[16];
	unsigned char  _MfgCode = 0x04;

	//---------------- Check paramter ---

	//---- Set command
	_cmd = ISO15693_WRITE_PASS;

	//---- Set Paramters
	_para[0] = pwdType;
	memcpy(&_para[1], pPwd, 4);

	//---- Set paramters length
	_paraLen = 5;

	status  = lc_15693_command_custom(icdev, 
		_cmd,
		_MfgCode,
		pUID,
		_paraLen,
		_para,
		&_rParaLen,
		_rPara);

	return status;
}
int lc_15693_icode_64bitProtect(int icdev,unsigned char *pUID)
{
	int		status;
	unsigned char _cmd;
	unsigned int _paraLen;
	unsigned char _para[27];
	unsigned int _rParaLen;
	unsigned char _rPara[16];
	unsigned char  _MfgCode = 0x04;

	//---------------- Check paramter ---

	//---- Set command
	_cmd = ISO15693_PROTECT_64BIT;

	//---- Set Paramters

	//---- Set paramters length
	_paraLen = 0;

	status  = lc_15693_command_custom(icdev, 
		_cmd,
		_MfgCode,
		pUID,
		_paraLen,
		_para,
		&_rParaLen,
		_rPara);

	return status;
}
int lc_15693_protect_page(
	int icdev,
	unsigned char *pUID, 
	unsigned char iPage, 
	unsigned char protectStatus)
{
	int		status;
	unsigned char _cmd;
	unsigned int _paraLen;
	unsigned char _para[27];
	unsigned int _rParaLen;
	unsigned char _rPara[16];
	unsigned char  _MfgCode = 0x04;

	//---------------- Check paramter ---

	//---- Set command
	_cmd = ISO15693_PROTECT_PAGE;

	//---- Set Paramters
	_para[0] = iPage;
	_para[1] = protectStatus;

	//---- Set paramters length
	_paraLen = 2;

	status  = lc_15693_command_custom(icdev, 
		_cmd,
		_MfgCode,
		pUID,
		_paraLen,
		_para,
		&_rParaLen,
		_rPara);

	return status;
}







