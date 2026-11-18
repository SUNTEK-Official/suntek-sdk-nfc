#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H


int	lc_getver(int icdev,unsigned char *buff);
int	lc_beep(int icdev,unsigned int _Msec);

int	lc_card(int icdev,unsigned char _Mode,unsigned char *_Snr, unsigned char* _outSnrSize, unsigned int* pTag, unsigned char* pSak);
int	lc_authentication(int icdev,unsigned char _Mode,
									   unsigned char sector, unsigned char* pKey);
int lc_read(int icdev,unsigned char blk,unsigned char *_Data);
int lc_read_convenient(int icdev, unsigned char blkAddr, unsigned char keyMode, unsigned char* pKey, unsigned char* pData_out);
int lc_write(int icdev,unsigned char blk,unsigned char *_Data);
int lc_write_convenient(int icdev, unsigned char blkAddr, unsigned char keyMode, unsigned char* pKey, unsigned char* pData_in);
int lc_initval(int icdev,unsigned char _Adr,unsigned int _Value);
int lc_increment(int icdev,unsigned char _Adr,unsigned int _Value);
int lc_decrement(int icdev,unsigned char _Adr,unsigned int _Value);
int lc_restore(int icdev,unsigned char _fromAdr, unsigned char _toAdr);
int lc_readval(int icdev,unsigned char _Adr,unsigned int *_Value);
int lc_readTag(int icdev,unsigned char page,unsigned char *_Data);
int lc_writeTag(int icdev,unsigned char page,unsigned char *_Data);
int lc_authenTag(int icdev,unsigned char *pKey);
int lc_rawExchange(int icdev,unsigned char slen,unsigned char * sbuff,unsigned char *rrlen,unsigned char * rbuff);
int lc_halt(int icdev);
int lc_rfReset(int icdev,unsigned int _Msec);
int lc_pro_reset(int ICDev,unsigned char *rlen,unsigned char * rbuff);
int lc_pro_commandlink(int ICDev,unsigned int slen,unsigned char * sbuff,unsigned int *rlen,
 unsigned char * rbuff,
 unsigned char tt,
 unsigned char FG
 );
 
//----------------------------- ISO15693 --------------
/* reqMode: The mode when finding card, 0x36-Single card mode, 0x16-Multiple card mode*/
int lc_find15693(
	int icdev,
	unsigned char reqMode, 
	unsigned char *response_out, 
	unsigned char* resLen_out);
int lc_15693_command
(
 int ICDev,//Handle of device
 unsigned char cmd, //The command to send
 unsigned char* pUID, //The id of card (8 bytes)
 unsigned int sParaLen,//The length of paramter 
 unsigned char * psPara,//Paramter 
 unsigned int *rParaLen,//The length of paramter received
 unsigned char * rPara//The parater received
 );
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
 );
int lc_15693_command_ex
(
 int ICDev,//Handle of device
 unsigned int sRequestLen,//The length of request frame 
 unsigned char * psRequest,//Request 
 unsigned int *rResLen,//The length of response received
 unsigned char * rRes//The response received
 );
int lc_15693_stay_quiet(
	int icdev,
	unsigned char *pUID);
int lc_15693_select_uid(
	int icdev,
	unsigned char *pUID);
int lc_15693_reset_to_ready(
	int icdev,
	unsigned char *pUID);
int lc_15693_readBlock(
	int icdev,
	unsigned char *pUID,
	unsigned char startBlock,
	unsigned char blockNum,
	unsigned char *rlen,
	unsigned char *rbuffer);
int lc_15693_writeBlock(
	int icdev,
	unsigned char *pUID,
	unsigned char startBlock,
	unsigned char blockNum, 
	unsigned char wlen,
	unsigned char *wbuffer);
int lc_15693_lock_block(
	int icdev,
	unsigned char *pUID,
	unsigned char block);
int lc_15693_write_afi(
	int icdev,
	unsigned char *pUID,
	unsigned char AFI);
int lc_15693_lock_afi(
	int icdev,
	unsigned char *pUID);
int lc_15693_write_dsfid(
	int icdev,
	unsigned char *pUID,
	unsigned char DSFID);
int lc_15693_lock_dsfid(
	int icdev,
	unsigned char *pUID);
int lc_15693_get_systemInfo(
	int icdev,
	unsigned char *pUID,
	unsigned char *rlen,
	unsigned char *rbuffer);
int lc_15693_get_securityInfo(
	int icdev,
	unsigned char *pUID,
	unsigned char startBlock,
	unsigned char blockNum,
	unsigned char *rlen,
	unsigned char *rbuffer);
/* pwdType:01h-Read, 02h-Write, 04h-Privacy,08h-Destroy SLI-L, 10h-EAS */
int lc_15693set_password(
	int icdev,
	unsigned char *pUID, 
	unsigned char pwdType, 
	unsigned char* pPwd);
/* pwdType:01h-Read, 02h-Write,04h-Privacy,08h-Destroy SLI-L, 10h-EAS , and privacy is default used*/
int lc_15693_write_password(
	int icdev,
	unsigned char *pUID, 
	unsigned char pwdType, 
	unsigned char* pPwd);
int lc_15693_icode_64bitProtect(int icdev,unsigned char *pUID);
/*protectStatus:00h-Public,01h-Read and write protect by read-pass, 10h-Write protect by wirte pass. 
	11h-Read protect by the read pass, and Write protect by write pass*/
int lc_15693_protect_page(
	int icdev,
	unsigned char *pUID, 
	unsigned char iPage, 
	unsigned char protectStatus);

int lc_iccSelCardType
(
 int ICDev,//Handle of device
 unsigned char slot,
 unsigned int cardType
 );
int  lc_iccGetATR(int icdev,unsigned char slot, unsigned char *response_out, unsigned char* resLen_out);
int  lc_icc_APDU
(
 int ICDev,//Handle of device
 unsigned char slot,
 unsigned int slen,//The length of data to send
 unsigned char * sbuff,//Data to send
 unsigned int *rlen,//The length of data received
 unsigned char * rbuff//The data received
 );

#endif //_FUNCTIONS_H

