#ifndef COMPRO_NFC_IF_H
#define COMPRO_NFC_IF_H


//ERROR CODE
#define NFC_ERR_CARD_INVALID	0xF1
#define NFC_ERR_CARD_FORMAT		0xF2
#define NFC_ERR_CARD_LACK_MEM	0xF3

//card types
#define NFC_TYPE_MFCLS_1K		0x00
#define NFC_TYPE_MFCLS_4K		0x01
#define NFC_TYPE_MFPLUS_2K		0x02
#define NFC_TYPE_MFPLUS_4K		0x03
#define NFC_TYPE_ULT			0x04
#define NFC_TYPE_ULTC			0x05
#define NFC_TYPE_NTAG203		0x06
#define NFC_TYPE_NTAG210		0x07
#define NFC_TYPE_NTAG212		0x08
#define NFC_TYPE_NTAG213		0x09
#define NFC_TYPE_NTAG215		0x0A
#define NFC_TYPE_NTAG216		0x0B
#define NFC_TYPE_ICODE_SLI		0x0C
#define NFC_TYPE_ICODE_SLI_S	0x0D
#define NFC_TYPE_ICODE_SLI_L	0x0E
#define NFC_TYPE_ICODE_DNA		0x0F
#define NFC_TYPE_MF_MINI		0x10
#define NFC_TYPE_MF_DESFIRE		0x11
#define NFC_TYPE_TAG2			0x12
#define NFC_TYPE_NTAG_424		0x13
#define NFC_TYPE_MF_DESFIRE_EV2	0x14
#define NFC_TYPE_MF_DESFIRE_EV3	0x15
#define NFC_TYPE_ULT_EV1_MF0UL1X	0x16
#define NFC_TYPE_ULT_EV1_MF0UL2X	0x17
#define NFC_TYPE_14443_4		0xF0
#define NFC_TYPE_UNKONWN		0xFF

//NFC Record types
#define NFC_REC_TYPE_URI		0 //URI
#define NFC_REC_TYPE_TEXT		1 //Text 
#define NFC_REC_TYPE_SP			2 //SmartPoster
#define NFC_REC_TYPE_CONTACT	3 //contact
#define NFC_REC_TYPE_BT			4 //Bluetooth

//URI Types
#define URI_ID_NULL			0x00 //N/A
#define URI_ID_HTTP_WWW		0x01 //http://www.
#define URI_ID_HTTPS_WWW	0x02 //https://www.
#define URI_ID_HTTP			0x03 //http://
#define URI_ID_HTTPS		0x04 //https://
#define URI_ID_TEL			0x05 //tel:
#define URI_ID_MAILTO		0x06 //mailto:
#define URI_ID_FTP_ANONYMOUS	0x07 //ftp://anonymous:anonymous@
#define URI_ID_FTP_FTP		0x08 //ftp://ftp.
#define URI_ID_FTPS			0x09 //ftps://
#define URI_ID_SFTP			0x0A //sftp://
#define URI_ID_SMB			0x0B //smb://
#define URI_ID_NFS			0x0C //nfs://
#define URI_ID_FTP			0x0D //ftp://
#define URI_ID_DAV			0x0E //dav://
#define URI_ID_NEWS			0x0F //news:
#define URI_ID_TELNET		0x10 //telnet://
#define URI_ID_IMAP			0x11 //imap:
#define URI_ID_RTSP			0x12 //rtsp://
#define URI_ID_URN			0x13 //urn:
#define URI_ID_POP			0x14 //pop:
#define URI_ID_SIP			0x15 //sip:
#define URI_ID_SIPS			0x16 //sips:
#define URI_ID_TFTP			0x17 //tftp:
#define URI_ID_BTSPP		0x18 //btspp://
#define URI_ID_BTL2CAP		0x19 //btl2cap://
#define URI_ID_BTGOEP		0x1A //btgoep://
#define URI_ID_TCPOBEX		0x1B //tcpobex://
#define URI_ID_IRDAOBEX		0x1C //irdaobex://
#define URI_ID_FILE			0x1D //file://
#define URI_ID_URN_EPC_ID	0x1E //urn:epc:id:
#define URI_ID_URN_EPC_TAG	0x1F //urn:epc:tag:
#define URI_ID_URN_EPC_PAT	0x20 //urn:epc:pat:
#define URI_ID_URN_EPC_RAW	0x21 //urn:epc:raw
#define URI_ID_URN_EPC		0x22 //urn:epc:
#define URI_ID_URN_NFC		0x23 //urn:nfc:

//Text format
#define TEXT_FORMAT_GBK		0x01 //
#define TEXT_FORMAT_UNICODE	0x02
#define TEXT_FORMAT_UTF8	0x03

//TNF types
#define TNF_TYPE_WELL_KNOWN		0x01
#define TNF_TYPE_MEDIA			0x02
#define	TNF_TYPE_ABSOLUTE_URI	0x03
#define TNF_TYPE_EXT			0x04


//define a base NDEF unit
typedef struct NDEF_RECORD
{
	unsigned char	tnf_type; //Type Name Format 1~4
	unsigned char	typeLength;//The string length of szType
	char			szType[128];// 'U','T',"Sp","text/vcard","android.com:pkg"...
	unsigned char	idLength;//The string length of bufIdentifier, always zero 
	unsigned char	bufIdentifier[128];//Optional payload identifier,always null
	unsigned int	payLoadLen;//The string length of payload
	unsigned int	payloadMemorySize;//The max memory size for bufPayLoad
	unsigned char*	bufPayLoad;//Payload string
	unsigned char	nestRecNum;//Nestification records number
	void*	pNestRecs;//Pointer to nest records
	void*	pPreRec;//Pointer to front records
	void*	pNextRec;//Pointer to next records
}Ndef_record;

//NDEF message
typedef struct NDEF_MESSAGE
{
	int arrNum;
	int	mmRecsNum;//The number of records system alloc
	Ndef_record*	pRec;
}Ndef_message;


#ifdef __cplusplus
extern "C"
{
#endif

//NFC app functions
//Note: The parameter szPwd should be set null string if no use.
int _stdcall lc_NFC_FormatCard_WithURI(int icdev, int cardType, unsigned char URItype, char* szURI, char* szPwd, BOOL fLock);
int _stdcall lc_NFC_FormatCard_WithText(int icdev, int cardType,char* szIANA, char* szText,int textFormat,char* szPwd, BOOL fLock);
int _stdcall lc_NFC_FormatCard_WithSmartPoster(int icdev, int cardType,char* szIANA, char* szText, int textFormat, unsigned char URItype, 
											   char* szURI,char* szPwd,BOOL fLock);
int _stdcall lc_NFC_FormatCard_WithContact(int icdev, int cardType,
											   char* szName, 
											   char* szTelCell,
											   char* szTelWork,
											   char* szTelFax,
											   char* szTelHome,
											   char* szOrg,
											   char* szDepart,
											   char* szWorkAdr,
											   char* szEmail,
											   char* szURL,
											   char* szXQQ,
											   char* szWeibo,
											   char* szWeixin,
											   int textFormat,
											   char* szPwd,
											   BOOL fLock);
int _stdcall lc_NFC_FormatCard_WithBluetooth(int icdev, int cardType,
											   unsigned char * bufMAC, //6-byte 
											   char* szName, //32 bytes maximum
											   unsigned char*  bufDeviceClass,//4-byte, 00 indicate useless
											   unsigned short* bufUUID,//4-short, 0000 indicate useless
											   unsigned char   EIRData_Type, //Extended Inquiry Response(EIR) data type
											   unsigned char   EIRDataLen, //Lenght of DIRData (In byte)
											   unsigned char*  bufEIRData,//32 bytes maximum
											   char* szPwd,
											   BOOL fLock);
int _stdcall lc_NFC_ReadTag(int icdev, int tagType,int textFormat, char* szPwd,  int* pPayloadType, char* pContent_out);

int _stdcall lc_NFC_FormatTag_Ex(int icdev, int tagType, Ndef_message* pInRec,char* szPwd, BOOL fLock);
int _stdcall lc_NFC_ReadTag_Ex(int icdev, int tagType, int textFormat, char* szPwd, Ndef_message* pOutRec);

#ifdef __cplusplus
}
#endif

#endif

