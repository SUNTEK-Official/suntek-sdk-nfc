//package examples;

import java.util.Arrays;

import lc.comproCall;

public class ndefTest {
	
	public static void showBinData(byte[] pData, int dataLen)
	{
		char[] szData = new char[dataLen + 1];
		int i;
		String hexStr;
		
		for(i =0;i< dataLen; i++)
			szData[i] = (char)pData[i];
		
		System.out.print("\n");
		for(i = 0; i< dataLen; i++)
		{
			hexStr = String.format("%02X", pData[i]);
			System.out.print(hexStr+ " ");
		}
		String strData = new String(szData);
		System.out.println("\n" + strData );
		System.out.print("\n");
	}
	
	public static  void main(String[] args)
	{
        int status;
        int i;
        int lDevice = -1;
        int serverListenPort = 51006;
        int iTermNum = -1;
        char[] pSBuffer = new char[1024];
        char[] pRBuffer = new char[1024];
        short lSlen;
        short[] pRlen = new short[1];
        char[] pRcpuBuffer = new char[255];
        byte[] pShowBuf = new byte[1024];
        char[] pShowChars = new char[1024];
        int result = 0;
        char[] pModVer = new char[512];
        char[] pPwd = new char[32];
        byte[] bt_buf = new byte[1024];
        int[] pPayloadType =new int[2];
        int tagType = 0x09;//0-M1, 9-NTAG213, card Types ,Defined See compro_nfch.h
        int textFormat = 0x01;//0x01-GBK,0x02-Unicode,0x03-UTF8, Defined see compro_nfch.h
        int validDataLength = 0;
        String strForTest = new String("abc123");
        String strOut="";
        
        char[] pNetReaderEnt = new char[256];
        int tryCnt = 0;

        try {
        	
        	/*
        	//Try to link net reader
        	status = comproCall.lc_net_serverStart(serverListenPort);
        	if(status != 0)
        	{
        		System.out.print("lc_net_serverStart error!\n");
        	}
        	else
        	{
        		System.out.print("lc_net_serverStart +++\n");
        		
        		
        		do{
        			iTermNum = comproCall.lc_net_termList(pNetReaderEnt);
        			System.out.printf("termlist- term number:%d\n", iTermNum);
        			if(iTermNum !=  0)
        			{//There is client linked
        				System.out.print(String.valueOf(pNetReaderEnt) + "\n");
        				lDevice = comproCall.lc_init_ex(4, pNetReaderEnt, 0);
        				break;
        			}
        			else
        			{
        				tryCnt++;
        				if(tryCnt >= 5)
        				{//Report Error
        					comproCall.lc_net_serverExit();
        					System.out.print("lc_net_serverExit ---\n");
        					break;
        				}
        				try{
        					Thread.sleep(1000);
        				}catch(Exception e){};
        				
        			}
        			
        		}while(iTermNum == 0);
        	}
        	*/
        	

        	
        	if(lDevice == -1)
        	{
        		//lDevice = comproCall.lc_init_ex(2,"COM3".toCharArray(), 115200);//COM port
        		lDevice = comproCall.lc_init_ex(2, " ".toCharArray(), 115200);//USB port
        	}
            
            if (lDevice == -1) {
                System.out.print("lc_init error!\n");
                return;
            }
            System.out.print("lc_init ok!\n");
            
            status = comproCall.lc_beep(lDevice, 10);
            if (status != 0) {
                System.out.print("lc_beep error!\n");
                comproCall.lc_exit(lDevice);
                return;
            } else {
                System.out.print("lc_beep ok!\n");
            }
            
        	//----------------------------------------------------------------------- test multiple records
            //--- Write
        	comproCall.Ndef_message[] objNdefMsg_w= new comproCall.Ndef_message[1];
        	objNdefMsg_w[0] = new comproCall.Ndef_message();
        	objNdefMsg_w[0].mmRecsNum = 2;//Define a maximum record number you want to get!
        	objNdefMsg_w[0].arrNum = objNdefMsg_w[0].mmRecsNum;
        	
        	comproCall.Ndef_record[] objNdefRecs_w= new comproCall.Ndef_record[objNdefMsg_w[0].mmRecsNum];
        	for(i=0; i< objNdefMsg_w[0].mmRecsNum; i++)
        	{
        		objNdefRecs_w[i] = new comproCall.Ndef_record();
        		objNdefRecs_w[i].szType = new byte[128];
        	}
        	//-record1
        	objNdefRecs_w[0].tnf_type = 0x01;//TNF_TYPE_WELL_KNOWN;
        	objNdefRecs_w[0].typeLength = 0x01;
        	objNdefRecs_w[0].szType[0] = 'U';
        	objNdefRecs_w[0].idLength = 0x00;
    		objNdefRecs_w[0].payloadMemorySize = 128; //Assign a memory larger enough to put the payload data 
    		objNdefRecs_w[0].bufPayLoad = new byte[objNdefRecs_w[0].payloadMemorySize];
        	String strURL = "weixin://dl/business/?t=RjLSFhYQQrl";
        	byte[] bytesURL = new byte[strURL.length() + 1];
        	bytesURL = strURL.getBytes();
        	System.arraycopy(bytesURL, 0, objNdefRecs_w[0].bufPayLoad, 1, strURL.length());
        	objNdefRecs_w[0].bufPayLoad[0] = 0x00;
        	objNdefRecs_w[0].payLoadLen =  1 + bytesURL.length;
        	objNdefRecs_w[0].nestRecNum = 0;
        	//-record2
        	objNdefRecs_w[1].tnf_type = 0x04;//TNF_TYPE_WELL_KNOWN
        	String strType_rec2 = "android.com:pkg";
        	objNdefRecs_w[1].typeLength = (byte)(strType_rec2.length() & 0xff);
        	objNdefRecs_w[1].szType = strType_rec2.getBytes();
        	objNdefRecs_w[1].idLength = 0x00;
    		objNdefRecs_w[1].payloadMemorySize = 128; //Assign a memory larger enough to put the payload data 
    		objNdefRecs_w[1].bufPayLoad = new byte[objNdefRecs_w[1].payloadMemorySize];
        	String strApp = "com.tencent.mm";
        	objNdefRecs_w[1].bufPayLoad = strApp.getBytes();
        	objNdefRecs_w[1].payLoadLen =  strApp.length();
        	objNdefRecs_w[1].nestRecNum = 0;
        	
        	result = comproCall.lc_NFC_FormatTag_Ex(lDevice, tagType, objNdefMsg_w, objNdefRecs_w, "".toCharArray(), false);
        	
        	if(result != 0)
        	{
        		System.out.print("lc_NFC_FormatTag_Ex fail\n");
        		comproCall.lc_exit(lDevice);
        		return;
        	}
        	System.out.print("lc_NFC_FormatTag_Ex ok\n");

            
            //--- Read
        	comproCall.Ndef_message[] objNdefMsg_r= new comproCall.Ndef_message[1];
        	objNdefMsg_r[0] = new comproCall.Ndef_message();
        	objNdefMsg_r[0].mmRecsNum = 10;//Define a maximum record number you want to get!
        	//objNdefMsg[0].pRec = objNdefRecs;
        	
        	comproCall.Ndef_record[] objNdefRecs_r= new comproCall.Ndef_record[objNdefMsg_r[0].mmRecsNum];
        	for(i=0; i< objNdefMsg_r[0].mmRecsNum; i++)
        	{
        		objNdefRecs_r[i] = new comproCall.Ndef_record();
        		objNdefRecs_r[i].payloadMemorySize = 512; //Assign a memory larger enough to put the payload data 
        		byte[]  payloadBuf = new byte[objNdefRecs_r[i].payloadMemorySize];
        		objNdefRecs_r[i].bufPayLoad = payloadBuf;
        		objNdefRecs_r[i].szType = new byte[128];
        		objNdefRecs_r[i].bufPayLoad = new byte[128];
        	}
        	
        	result = comproCall.lc_NFC_ReadTag_Ex(lDevice, tagType,  textFormat, "".toCharArray(), objNdefMsg_r, objNdefRecs_r);
        	
        	if(result != 0)
        	{
        		System.out.print("lc_NFC_ReadTag fail\n");
        		comproCall.lc_exit(lDevice);
        		return;
        	}
        	System.out.println("arrnum: "+ objNdefMsg_r[0].arrNum);
        	
        	for(i=0; i< objNdefMsg_r[0].arrNum; i++)
        	{
        		System.out.println("---------------------------------"+"Record: " + i);
            	System.out.println("tnf_type: "+ objNdefRecs_r[i].tnf_type);
            	System.out.println("typeLength: "+ objNdefRecs_r[i].typeLength);
            	if(objNdefRecs_r[i].typeLength > 0)
            	{
            		showBinData(objNdefRecs_r[i].szType, objNdefRecs_r[i].typeLength);
            	}
            	System.out.println("idLength: "+ objNdefRecs_r[i].idLength);
            	if(objNdefRecs_r[i].idLength > 0)
            	{
            		showBinData(objNdefRecs_r[i].bufIdentifier, objNdefRecs_r[i].idLength);
            	}
            	System.out.println("payLoadLen: "+ objNdefRecs_r[i].payLoadLen);
            	if(objNdefRecs_r[i].payLoadLen > 0)
            	{
            		showBinData(objNdefRecs_r[i].bufPayLoad, objNdefRecs_r[i].payLoadLen);
            	}
        	}
        	
        	
        	//---------------------------------------------------------------------- test single record

        	/*
            //Write NDEF(Text)
            bt_buf = strForTest.getBytes();
            for(i=0; i< bt_buf.length; i++)pSBuffer[i] = (char)(bt_buf[i] & 0xff);
            result = comproCall.lc_NFC_FormatCard_WithText(lDevice, tagType, "zh".toCharArray(), pSBuffer,textFormat,"".toCharArray(), false);
            if (result != 0) {
            	System.out.print("Write text error!\n");
                comproCall.lc_exit(lDevice);
                return;
            } else {
            	System.out.print("Write text ok!\n");
            }

            //Read NDEF(Text)
            result = comproCall.lc_NFC_ReadTag(lDevice, tagType, textFormat, pPwd, pPayloadType, pRBuffer);
            if (result != 0) {
            	System.out.print("Read text error!\n");
                comproCall.lc_exit(lDevice);
                return;
            } else {
            	System.out.print("Read text ok!\n");
            	System.out.print("Text[ASC]: " + String.valueOf(pRBuffer) + "\n");
                while(pRBuffer[validDataLength] != 0)
                {
                    bt_buf[validDataLength]=(byte) pRBuffer[validDataLength];
                    validDataLength++;
                    if(validDataLength == pRBuffer.length)
                        break;
                }

                try{strOut = new String(bt_buf, "UTF-8");}catch(Exception e){}
                System.out.print("Text[UTF8]: " + strOut + "\n");
            }
            */

            status = comproCall.lc_exit(lDevice);
            if (status != 0) {
                System.out.print("lc_exit error!\n");
            } else {
                System.out.print("lc_exit ok!\n");
            }
            
            

        } catch (Exception e) {
            System.err.println("Exception caught: " + e.getMessage());
        }
        
	}

}
