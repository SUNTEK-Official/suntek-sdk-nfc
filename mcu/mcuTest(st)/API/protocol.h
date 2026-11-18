#ifndef _PROTOCOL_H
#define _PROTOCOL_H


#define UART_TX_ADR_STX	0
#define UART_TX_STXLEN	0x01
#define UART_TX_ADR_INX	(UART_TX_ADR_STX + UART_TX_STXLEN)
#define UART_TX_INXLEN	0x01
#define UART_TX_ADR_LEN	(UART_TX_ADR_INX + UART_TX_INXLEN)
#define UART_TX_LENLEN	0x02
#define UART_TX_ADR_DEV	(UART_TX_ADR_LEN + UART_TX_LENLEN)
#define UART_TX_DEVLEN	0x02
#define UART_TX_ADR_CMD	(UART_TX_ADR_DEV + UART_TX_DEVLEN)
#define	UART_TX_CMDLEN	0x02

#define UART_TX_ADR_DATA (UART_TX_ADR_CMD + UART_TX_CMDLEN)
#define UART_TX_CHKLEN	0x01
#define UART_TX_VAL_STX	0xAA
#define UART_TX_VAL_DEV	0x0000

#define UART_RX_ADR_STX	0
#define UART_RX_STXLEN	0x01
#define UART_RX_ADR_INX	(UART_RX_ADR_STX + UART_RX_STXLEN)
#define UART_RX_INXLEN	0x01
#define UART_RX_ADR_LEN	(UART_RX_ADR_INX + UART_RX_INXLEN)
#define UART_RX_LENLEN	0x02
#define UART_RX_ADR_DEV	(UART_RX_ADR_LEN + UART_RX_LENLEN)
#define UART_RX_DEVLEN	0x02
#define UART_RX_ADR_CMD	(UART_RX_ADR_DEV + UART_RX_DEVLEN)
#define	UART_RX_CMDLEN	0x02
#define UART_RX_ADR_ST	(UART_RX_ADR_CMD + UART_RX_CMDLEN)
#define UART_RX_STLEN		0x01

#define UART_RX_ADR_DATA (UART_RX_ADR_ST + UART_RX_STLEN)
#define UART_RX_CHKLEN	0x01
#define UART_RX_VAL_STX	0xAA

#define UART_RX_MIN_LEN	(UART_RX_STXLEN + UART_RX_INXLEN + UART_RX_LENLEN + UART_RX_DEVLEN + UART_RX_CMDLEN + UART_RX_STLEN + UART_RX_CHKLEN)

#define UART_MASK		0xAA


/////////////////////////////////////////////////// COMMANDS ///////////////////
#define COMGETVER				0x0000 //getver
#define COMBEEP         0xFF00 //beep
#define COMREQUEST      0x1000 //Find card
#define COMM1AUTHENPASS 0x1001 //authentication
#define COMM1READ       0x1002 //mf read
#define COMM1READ_CONV	0x1005
#define COMM1WRITE      0x1003 //m1 write
#define COMM1WRITE_CONV	0x1006
#define COMINITVAL			0x1007
#define COMREADVAL			0x100A
#define COMINCREMENT    0x1008 //m1 increament
#define COMDECREMENT    0x1009 //m1 decrement
#define COMRESTORE      0x100B //restore
#define CMD_READ_TAG		0x1010 //NTag read
#define CMD_WRITE_TAG		0x1011 //NTag Write
#define CMD_AUTHEN_TAG	0x1012 //NTag authen key
#define CMD_RAW_EXC			0x1020 //Raw command exchange
#define COMHALT         0x1004 //halt
#define FCPURESETCOM    0x101E//Com type reset
#define FCPUCOMMANDCOM  0x101F  //Command COM type
#define COMRESET        0x102E //reset

#define CMD_ICC_SELCARD     0x1801 //icc select card type
#define CMD_ICC_GETATR      0x1880 //icc getatr
#define CMD_ICC_APDU        0x1881 //icc apdu

#define CMD_15693_REQ														0x1060
#define CMD_15693_EXCH_COMMOM										0x1061
#define CMD_15693_EXCH_CUSTOM										0x1062
#define CMD_15693_EXCH_EX												0x1063

//ISO15693 Commands ---
#define	ISO15693_INVENTORY                      0x01
#define	ISO15693_STAY_QUIET                     0x02
#define	ISO15693_READ_SINGLE_BLOCK              0x20
#define	ISO15693_WRITE_SINGLE_BLOCK             0x21
#define	ISO15693_LOCK_BLOCK                     0x22
#define	ISO15693_READ_MULTIPLE_BLOCKS           0x23
#define	ISO15693_WRITE_MULTIPLE_BLOCKS          0x24
#define	ISO15693_SELECT                         0x25
#define	ISO15693_RESET_TO_READY                 0x26
#define	ISO15693_WRITE_AFI                      0x27
#define	ISO15693_LOCK_AFI                       0x28
#define	ISO15693_WRITE_DSFID                    0x29
#define	ISO15693_LOCK_DSFID                     0x2A
#define	ISO15693_GET_SYSTEM_INFO                0x2B
#define	ISO15693_GET_MULTIPLE_BLOCK_SECURITY    0x2C
#define ISO15693_GET_RANDDOM										0xB2 
#define ISO15693_SET_PASS												0xB3 
#define ISO15693_WRITE_PASS											0xB4 
#define ISO15693_LOCK_PASS											0xB5 
#define ISO15693_PROTECT_PAGE										0xB6 
#define ISO15693_PROTECT_64BIT									0xBB 

typedef struct 
{
	unsigned int STX;
	unsigned int AD;
	unsigned int CMD;
	unsigned int DATALEN;
	unsigned char pData[256];
	unsigned int CHK;
	unsigned int TYPECMDLEN;
}PROTOCOL_CMM;


int _multiByteToUL(unsigned char* pByte, int lenBytes, int iType, unsigned int* pVal);
void  ULToMultiByte(unsigned long val, unsigned char* pArr, int lenArr, int bInv);

int pub_CommonTransfer(int icdev, void* _pProData,unsigned char* pRev, unsigned int* lenRev);


#endif //_PROTOCOL_H
