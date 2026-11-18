
#ifndef __FM1208_H__
#define __FM1208_H__

#if defined(linux) || defined(__LYNX) || defined(__unix) || defined(_AIX)
#define _stdcall 
#define __stdcall
#endif

// ȫȨ
#ifndef MWTOKEN_SEC
	#define	MWTOKEN_SEC
	#define	FWCOS_SEC_ALW				((unsigned long)0x00000000)	// Զ
	#define	FWCOS_SEC_USER				((unsigned long)0x00000001)	// ûȨ
	#define FWCOS_SEC_SO				((unsigned long)0x0000000A) // ԱȨ
	#define FWCOS_SEC_NEVER				((unsigned long)0x000000EF) // Զ
#endif

#ifndef	MWTOKEN_ALGID
	#define	MWTOKEN_ALGID
	#define	TOKEN_ALGID_DES				((unsigned long)0x00000000)
	#define	TOKEN_ALGID_SSF				((unsigned long)0x00000001)
	#define	TOKEN_ALGID_SCB2			((unsigned long)0x00000002)
	#define	TOKEN_ALGID_SHA1			((unsigned long)0x00000030)
	#define TOKEN_ALID_ANY				((unsigned long)0xFFFFFFFF)
#endif

//Կͱʶ
#ifndef FWCOS_KEYTYPE
   #define FWCOS_KEYTYPE
   #define FW_KEYTYPE_FILEPROTECT       (0x01)//ļ·Կ
   #define FW_KEYTYPE_EXVERIFY          (0x02)//ⲿ֤Կ
   #define FW_KEYTYPE_PIN               (0x03)//Կ
   #define FW_KEYTYPE_UNLOCK            (0x04)//Կ
   #define FW_KEYTYPE_CREDIT			(0x05)//ȦԿ
   #define FW_KEYTYPE_DEBIT				(0x06)//ȦԿ
   #define FW_KEYTYPE_PURCHASE			(0x07)//Կ
   #define FW_KEYTYPE_OVERDRAWLIMIT     (0x08)//޸͸֧޶
   #define FW_KEYTYPE_INTERNAL			(0x09)//ڲԿ
   #define FW_KEYTYPE_RELOADPIN			(0x0A)//װԿ
#endif 


#define FT_READ_MSG			0x00
#define FT_WRITE_MSG		0x01
#define FT_READ_ACK			0x02

#define MAX_PACKET_SIZE_READ		(64 *1024 )

#define READ_LEN_ONETIME	(59)//add by cdt ÿֽ
#define WRITE_LEN_ONETIME	(54)//add by cdt ÿдֽ
#define SIZE_ONEPAGE		(512)//528//ÿһҳ
#define MAX_SIZE_FALSH		(2*1024*1024) // falseĴ (2M)
#define MAX_LENGTH_PAGES	(MAX_SIZE_FALSH/SIZE_ONEPAGE)//õҳ
#define MAX_LENGTH_AUTHEN   (32) //֤󳤶

#define OFFSET_USERPIN      (33)//ûҳƫƵַ
#define OFFSET_SOPIN		(40)//ԱҳƫƵַ
#define OFFSET_AUTHENKEY	(47)//֤õԿҳƫƵַ
#define OFFSET_MAINTAINKEY  (97)//ӦάԿҳƫƵַÿԿϢռ51ֽڣ 7 άԿ


// Return codes
#define		F32x_SUCCESS				0x00
#define		F32x_DEVICE_NOT_FOUND		0xFF
#define		F32x_INVALID_HANDLE			0x01
#define		F32x_READ_ERROR				0x02
#define		F32x_RX_QUEUE_NOT_READY		0x03
#define		F32x_WRITE_ERROR			0x04
#define		F32x_RESET_ERROR			0x05
#define		F32x_INVALID_PARAMETER		0x06
#define		F32x_INVALID_REQUEST_LENGTH	0x07
#define		F32x_DEVICE_IO_FAILED		0x08
#define		F32x_INVALID_PAGE_ADDRESS	0x09
#define		F32x_INVALID_OFFSET_ADDRESS	0x0a

// RX Queue status flags
#define		F32x_RX_NO_OVERRUN			0x00
#define		F32x_RX_OVERRUN				0x01
#define		F32x_RX_READY				0x02

//exports functions
#ifdef __cplusplus
extern "C"{
#endif


/////////////////////////////////////////////////////////////////////////////////////
// ܣ
//	λظλϢ
// 
 // 	lDevHandle
//      pbReturnInfo:	   ŸλϢĻ
//      pulReturnInfoLen:  /ݳ
// أ
//        ɹ0ʧ
/////////////////////////////////////////////////////////////////////////////////////

long _stdcall FWCosReset(long lDevHandle,
                         void* pbReturnInfo,
			 unsigned long*	pulReturnInfoLen);

/////////////////////////////////////////////////////////////////////////////////////
// ܣ
//	Ӧãհ׿ִһδ˺гʼ
// 
 // 	lDevHandle
// أ
//        ɹ0ʧ
/////////////////////////////////////////////////////////////////////////////////////

long _stdcall FWCosCreateMainApp(long           lDevHandle);

/////////////////////////////////////////////////////////////////////////////////////
// ܣ
//	ѡӦ
// 
 // 	lDevHandle
// أ
//        ɹ0ʧ
/////////////////////////////////////////////////////////////////////////////////////

long _stdcall FWCosSelecteApp(long           lDevHandle);

/////////////////////////////////////////////////////////////////////////////////////
// ܣ
//	ɾļϵͳ
// 
 // 	lDevHandle
// أ
//        ɹ0ʧ
/////////////////////////////////////////////////////////////////////////////////////

long _stdcall FWCosDeleteFileSys(
                             long           lDevHandle);



/////////////////////////////////////////////////////////////////////////////////////
// ܣ
//	ڵǰӦĿ¼½һĿ¼ļ
// 
 // 	lDevHandle
//	usDirFileID:	Ŀ¼ļʶ
//  usDirSize:		Ŀ¼ĿռС
//	ulCreateSec:	Ŀ¼½ļȨ
//	ulDeleteSec:	ɾĿ¼Ȩ

// أ
//        ɹ0ʧ
// ע
//	ɹĿ¼ļǰĿ¼ΪĿ¼Ҳ˵ǰĿ¼Ϊ
//	Ŀ¼/ӦĿ¼/Ŀ¼
/////////////////////////////////////////////////////////////////////////////////////

long _stdcall FWCosCreateDirectory(
                             long           lDevHandle,
                             unsigned short usDirFileID,
							 unsigned short usDirSize,
                             unsigned long  ulCreateSec,
                             unsigned long  ulDeleteSec);

/////////////////////////////////////////////////////////////////////////////////////
// ܣ
//	ӦĿ¼½һרĿ¼ļ
// 
 // 	lDevHandle
//	usDirFileID:	Ŀ¼ļʶ
//	ulCreateSec:	Ŀ¼½ļȨ
//	ulDeleteSec:	ɾĿ¼Ȩ
//  pbDirName:      Ŀ¼ƣ5~16ֽ
//  ucDirNameLength:Ŀ¼Ƶĳ(5-16)
// أ
//        ɹ0ʧ
// ע
//       ǽǮӦõǰ
/////////////////////////////////////////////////////////////////////////////////////
long _stdcall FWCosCreateADF(long   lDevHandle,
							 unsigned short usDirFileID,
							 unsigned long  ulCreateSec,
                             unsigned long  ulDeleteSec,
							 void*          pbDirName,
							 unsigned char  ucDirNameLength);

/////////////////////////////////////////////////////////////////////////////////////
// ܣ
//	ѡӦõĿ¼
// 
 // 	lDevHandle
//	usDirID:		Ŀ¼ʶ
// أ

//        ɹ0ʧ
/////////////////////////////////////////////////////////////////////////////////////

long _stdcall FWCosSelectDirectory(
                             long            lDevHandle,
                             unsigned short  usDirID);
/////////////////////////////////////////////////////////////////////////////////////
// ܣ
//	ڵǰӦĿ¼»ߵǰӦĿ¼Ŀ¼½һļ
// 
 // 	lDevHandle
//	usDirFileID:	Ŀ¼ļʶ˲Ϊ0x00000000
//						ʾڵǰӦĿ¼½һļ
//	usFileID:		ҪĶļʶ
//	usFileLen:		ļ
 // cryptyType: ݴļܷʽ0ķʽ1+MACУ ʽ2+MACУ ʽ
//	ulReadSec:		ȡļȨ
//	ulUpdateSec:	ļȨ
//	ulDeleteSec:	ɾļȨ
// أ
//        ɹ0ʧ
// ע
//	
//	
/////////////////////////////////////////////////////////////////////////////////////

long _stdcall FWCosCreateBinaryFile(
                             long            lDevHandle,
                             unsigned short  usDirFileID,
                             unsigned short  usFileID,
                             unsigned short  usFileLen,
                             unsigned char   cryptyType,
                             unsigned long   ulReadSec,
			     unsigned long   ulUpdateSec,
			     unsigned long   ulDeleteSec);

/////////////////////////////////////////////////////////////////////////////////////

// ܣ
//	ڵǰӦĿ¼»ߵǰӦĿ¼Ŀ¼½һ¼ļ
// 
 // 	lDevHandle
//	usDirFileID:		Ŀ¼ļʶ˲Ϊ0x00000000
//						ʾڵǰӦĿ¼½һ¼ļ
//  ucFRecord           ¼ļͣ0->¼ļ1->ѭ¼ļ2->䳤¼ļ
//	usFileID:			ҪĶ¼ļʶ
//	bRecordNum:			¼Ŀ
//	bRecordLen:			¼
 // cryptyType: ݴļܷʽ0ķʽ1+MACУ ʽ2+MACУ ʽ
//	ulReadSec:			ȡ¼Ȩ
//	ulUpdateSec:		¼¼Ȩ
//	ulDeleteSec:		ɾ¼Ȩ
/////////////////////////////////////////////////////////////////////////////////////
long __stdcall FWCosCreateRecordFile(
									 long			lDevHandle,
									 unsigned short	usDirFileID,
									 unsigned char  ucFRecord,
									 unsigned short	usFileID,
									 unsigned char	bRecordNum,
									 unsigned short	bRecordLen,
									 unsigned char  cryptyType,
									 unsigned long	ulReadSec,
									 unsigned long	ulUpdateSec,
									 unsigned long	ulDeleteSec);

/////////////////////////////////////////////////////////////////////////////////////
// ܣ
//	ǰӦĿ¼µĿ¼
// 
 // 	lDevHandle
//	usDirFileID:		Ŀ¼ļʶ
// أ
//        ɹ0ʧ
// ע
//	ڽļļİȫûзãֻڼļİȫȨ޲
/////////////////////////////////////////////////////////////////////////////////////

long _stdcall FWCosActiveDirectory(
                             long            lDevHandle,
                             unsigned short  usDirFileID);

/////////////////////////////////////////////////////////////////////////////////////
// ܣ
//	ڵǰӦĿ¼»ߵǰӦĿ¼Ŀ¼ѡһļ
// 
 // 	lDevHandle
//	usFileID:		ļʶ
// أ
//        ɹ0ʧ
// ע
//	ֻѡļ󣬲ܽждļ
/////////////////////////////////////////////////////////////////////////////////////

long _stdcall FWCosSelectFile(
                             long            lDevHandle,
                             unsigned short  usFileID);

/////////////////////////////////////////////////////////////////////////////////////
// ܣ
//	ȡļ
// 
 // 	lDevHandle
//  usFileID:       ļıʶ
//	pbBinData:		ŶȡݵĻ
//	usOffset:		ȡʼƫ
//	usReadLen:		ȡĳ
 // cryptyType: ݴļܷʽ0ķʽ1+MACУ ʽ2+MACУ ʽ
//  pProKey:        õ·ԿļΪܷʽǣӦӵ·Կһ
//  ulKeyLen:       , ·Կĳ
// أ
//        ɹ0ʧ
/////////////////////////////////////////////////////////////////////////////////////

long _stdcall FWCosReadBinaryFile(
                             long           lDevHandle,
							 unsigned short usFileID,
                             void*			pbBinData,
                             unsigned short usOffset,
                             unsigned short usReadLen,
							 unsigned char			cryptyType,
							 void*          pProKey,
							 unsigned long  ulKeyLen);

/////////////////////////////////////////////////////////////////////////////////////
// ܣ
//	¼¼ļ
// 
 // 	lDevHandle
//  usFileID:       ļıʶ
//	usOffset:		ȡʼƫ
//	pbBinData:		µĶ
//	usUpdateLen:	µĳ
 // cryptyType: ݴļܷʽ0ķʽ1+MACУ ʽ2+MACУ ʽ
//  pProKey:        õ·ԿļΪܷʽǣӦӵ·Կһ
//  ulKeyLen:       , ·Կĳ
// أ
//        ɹ0ʧ
/////////////////////////////////////////////////////////////////////////////////////

long _stdcall FWCosUpdateBinaryFile(
                             long            lDevHandle,
							 unsigned short  usFileID,
                             unsigned short  usOffset,
                             const void*     pbBinData,
                             unsigned short  usUpdateLen,
                             unsigned char            cryptyType,
							 void*           pProKey,
							 unsigned long   ulKeyLen);

/////////////////////////////////////////////////////////////////////////////////////
// ܣ
//	Ӽ¼
// 
 // 	lDevHandle
//  bRecordFileID:      ¼ļıʶ
//	pbRecData:			Ҫӵļ¼
//	bAppendLen;			Ҫӵļ¼
 // cryptyType: ݴļܷʽ0ķʽ1+MACУ ʽ2+MACУ ʽ
//  pProKey:            õ·ԿļΪܷʽǣӦӵ·Կһ
//  ulKeyLen:           , ·Կĳ
/////////////////////////////////////////////////////////////////////////////////////
long __stdcall FWCosAppendRecord(
								 long			lDevHandle,
								 unsigned char  bRecordFileID,
								 const void*		pbRecData,
								 unsigned short	bAppendLen,
								 unsigned char            cryptyType,
								 void*           pProKey,
								 unsigned long   ulKeyLen);

/////////////////////////////////////////////////////////////////////////////////////
// ܣ
//	¼¼ļ
// 
 // 	lDevHandle
//  ucFRecord           ¼ļֻͣȡֵ010->¼ļ1->䳤¼ļ
//  bRecordFileID:      ¼ļıʶ
//	bRecordNum:			Ҫµļ¼
//	pbRecData:			µļ¼
//	bUpdateLen;			µļ¼
 // cryptyType: ݴļܷʽ0ķʽ1+MACУ ʽ2+MACУ ʽ
//  pProKey:            õ·ԿļΪܷʽǣӦӵ·Կһ
//  ulKeyLen:           , ·Կĳ
/////////////////////////////////////////////////////////////////////////////////////
long __stdcall FWCosUpdateRecord(
								 long			lDevHandle,
								 unsigned char  ucRecord,
								 unsigned char  bRecordFileID,
								 unsigned char	bRecordNum,
								 const void*		pbRecData,
								 unsigned short	bUpdateLen,
								 unsigned char            cryptyType,
								 void*           pProKey,
								 unsigned long   ulKeyLen);

/////////////////////////////////////////////////////////////////////////////////////
// ܣ
//	֤ûԿ߹ԱԿ
// 
 // 	lDevHandle
//	pbKey:			ûԿ߹ԱԿ
//	ulKeyLen:		Կ
//	ulKeyType:		Կ FW_KEYTYPE_EXVERIFYⲿ֤Կ
//                            FW_KEYTYPE_PINû

//
// أ
//        ɹ0ʧ
/////////////////////////////////////////////////////////////////////////////////////

long _stdcall FWCosVerifyKey(
                             long            lDevHandle,
                             const void*     pbKey,
                             unsigned long   ulKeyLen,
                             unsigned long   ulKeyType);

/////////////////////////////////////////////////////////////////////////////////////
// ܣ
//	޸ûԿ߹ԱԿ
// 
 // 	lDevHandle
//	pbOldPin:		Կ
//  ulOldKeyLen   Կ
//  pbNewKey:       Կ
//  ulNewKeyLen:    Կ
//	bKeyType:		Կͱʶ
//                       FW_KEYTYPE_FILEPROTECT : ļ·Կ
//                       FW_KEYTYPE_EXVERIFY    : ⲿ֤Կ
//                       FW_KEYTYPE_PIN         : Կ
//                       FW_KEYTYPE_UNLOCK      : Կ
//                       FW_KEYTYPE_PURCHASE    : Կ
//                       FW_KEYTYPE_CREDIT      : ȦԿ
// 
// أ
//        ɹ0ʧ
/////////////////////////////////////////////////////////////////////////////////////

long _stdcall FWCosUpdateKey(
                             long            lDevHandle,
                             const void*     pbOldKey,
                             unsigned long   ulOldKeyLen,
                             const void*     pbNewKey,
                             unsigned long   ulNewKeyLen,
                             unsigned long   bKeyType);


/////////////////////////////////////////////////////////////////////////////////////
// ܣ
//	ȡ¼ļ
// 
 // 	lDevHandle
//  ucFRecord           ¼ļֻͣȡֵ010->¼ļ1->䳤¼ļ
//  bRecordFileID:      ¼ļıʶ
//	bRecordNum:			Ҫȡļ¼
//	pbRecData:			Ŷȡ¼ݵĻ
//	bRecordLen;			Ҫȡļ¼
/////////////////////////////////////////////////////////////////////////////////////
long __stdcall FWCosReadRecord(
								 long			lDevHandle,
								 unsigned char  ucFRecord,
								 unsigned char  bRecordFileID,
								 unsigned char	bRecordNum,
								 void*			pbRecData,
								 unsigned short	bRecordLen);

/////////////////////////////////////////////////////////////////////////////////////
// ܣ
//	Կļ
// 
 // 	lDevHandle
//  usDirFileID         Ŀ¼ļĶ̱ʶ
//  usFileID:			¼ļıʶ
//	uFileLen:			Կļĳ
//	ulGenSec:			ԿļаװԿȨ
/////////////////////////////////////////////////////////////////////////////////////

long __stdcall FWCosCreateKeyFile(
			long			lTokenHandle,
			unsigned short	usDirFileID,
			unsigned short	usFileID,
			unsigned short  uFileLen,
			unsigned long	ulGenSec);



	/////////////////////////////////////////////////////////////////////////////////////
	// ܣ
	//	Կ
	// 
 // 	lDevHandle: ͨ FWCosConnect ȡ
	//	bKeyType:			Կͱʶ
    //                       FW_KEYTYPE_FILEPROTECT : ļ·Կ
	//                       FW_KEYTYPE_EXVERIFY    : ⲿ֤Կ
	//                       FW_KEYTYPE_PIN         : Կ
	//                       FW_KEYTYPE_UNLOCK      : Կ
	//                       FW_KEYTYPE_PURCHASE    : Կ
	//                       FW_KEYTYPE_CREDIT      : ȦԿ
	//	pbKeyValue:			Կֵ
	//	ulKeyValueLen:		Կֵĳ
	// ע
	//	1	ִд˺ǰȷǰĿ¼ӦĿ¼
	/////////////////////////////////////////////////////////////////////////////////////
	long __stdcall FWCosAddKey(
					long			lDevHandle,
					unsigned char	bKeyType,
					const void*		pbKeyValue,
					unsigned long	ulKeyValueLen);

/////////////////////////////////////////////////////////////////////////////////////
// ܣ
//	Կǿ
// 
 // 	lDevHandle: ͨ FWCosConnect ȡ
//	bKeyType:			Կͱʶ
//                       FW_KEYTYPE_FILEPROTECT : ļ·Կ
//                       FW_KEYTYPE_EXVERIFY    : ⲿ֤Կ
//                       FW_KEYTYPE_PIN         : Կ
//                       FW_KEYTYPE_UNLOCK      : Կ
 // FW_KEYTYPE_CREDIT : Ȧ ǮԿ
//                       FW_KEYTYPE_PURCHASE    : Կ
//  ucKeyID:            Կıʶ(ID)
//	pbKeyValue:			Կֵ
//	ulKeyValueLen:		Կֵĳ
//  ucSecUpdate:        ¸ԿȨ
//  ucNextSt:           ֤Կĺ״̬ⲿ֤ԿΪFWCOS_SEC_SOΪԿΪFWCOS_SEC_USERΪ 0
//	ucMaxCntError:		(1-15)òļ·Կⲿ֤ԿԿԿЧ
//  cryptyType:         ˲ЧΪ0

// ע
//	1	ִд˺ǰȷǰĿ¼ӦĿ¼
/////////////////////////////////////////////////////////////////////////////////////
long __stdcall FWCosAddKeyEx(
						   long			lDevHandle,
						   unsigned char	bKeyType,
						   unsigned char    ucKeyID,
						   const void*		pbKeyValue,
						   unsigned long	ulKeyValueLen,
						   unsigned char    ucSecUpdate,
						   unsigned char    ucNextSt,
						   unsigned char	ucMaxCntError,
						   unsigned char    cryptyType);

/////////////////////////////////////////////////////////////////////////////////////
// ܣ
//	޸û
// 
 // 	lDevHandle: ͨ FWCosConnect ȡ
//	pbOldPin:			ɿ
//	ulOldPinLen:		ɿ
//	pbNewPin:			¿
//	ulNewPinLen:		¿
/////////////////////////////////////////////////////////////////////////////////////
long __stdcall FWCosUpdatePin(
							  long			lDevHandle,
							  const void*		pbOldPin,
							  unsigned long	ulOldPinLen,
							  const void*		pbNewPin,
							  unsigned long	ulNewPinLen);

/////////////////////////////////////////////////////////////////////////////////////
// ܣ
//	ͬ
// 
//	lDevHandle:		TOKENͨ FWCosConnect ȡ
//  pinBuf:             ҪĿ
//  lenPin:             ĳ
//  pUnlockKey:         Կ
//  ulKeyLen:           , Կĳ
// ע
/////////////////////////////////////////////////////////////////////////////////////
long __stdcall FWCosPinUnlock(
							  long				lDevHandle,
							  void*				pinBuf,
							  unsigned long		pinLen,
							  void*				pUnlockKey,
							  unsigned long		ulKeyLen
							 );

/////////////////////////////////////////////////////////////////////////////////////
// ܣ
//	ͬ
// 
//	lDevHandle:		TOKENͨ FWCosConnect ȡ
//  newPinBuf:       Ҫװ¿
//  newPinLen:             ¿ĳ
//  pReloadKey:         װԿ
//  ulReloadKeyLen:           , װԿĳ
// ע
/////////////////////////////////////////////////////////////////////////////////////
long __stdcall FWCosPinReload(
							  long				lDevHandle,
							  void*				newPinBuf,
							  unsigned long		newPinLen,
							  void*				pReloadKey,
							  unsigned long		ulReloadKeyLen
							 );
/////////////////////////////////////////////////////////////////////////////////////
// ܣ
// һǮļڴ
// 
 // lDevHandle: д
// ucKeyID:		ȦԿʶ
// value:		ȦĽ
// terminalID:	ն˻
// pbCreditKey: ѰװȦԿ
// ulCreditKeyLen:װȦԿĳ
////////////////////////////////////////////////////////////////////////////////////
long __stdcall FWCosCredit(
						   long lDevHandle,
						   unsigned char ucKeyID,//Կʶ
						   unsigned int  value,//Ȧ(32λ)
						   unsigned char* terminalID,//ն˻ţ6ֽڳ)
						   void*     pbCreditKey,
						   unsigned long ulCreditKeyLen);

/////////////////////////////////////////////////////////////////////////////////////
// ܣ
// Ǯ
// 
 // lDevHandle: д
// ucKeyID:		Կʶ
// value:		ѵĽ
// terminalID:	ն˻
// pbPurchaseKey: ѰװԿ
// ulPurchaseKeyLen:װԿĳ
////////////////////////////////////////////////////////////////////////////////////
long __stdcall FWCosPurchase(
						   long lDevHandle,
						   unsigned char ucKeyID,//Կʶ
						   unsigned int  value,//ѽ(32λ)
						   unsigned char* terminalID,//ն˻ţ6ֽڳ)
						   void*     pbPurchaseKey,
						   unsigned long ulPurchaseKeyLen);

	/////////////////////////////////////////////////////////////////////////////////////
	// ܣ
	// õǮе
	// 
 // lDevHandle: д
	// balance:		Ǯе
	////////////////////////////////////////////////////////////////////////////////////
	long __stdcall FWCosGetBalance(
		long lDevHandle,
		unsigned int* balance);



#ifdef __cplusplus
}//end of extern "C"
#endif


#endif //__FM1208_H__

