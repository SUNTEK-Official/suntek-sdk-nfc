import lc.comproCall;
import jRF.FM1208;

public class comPro_FM1208Demo {
    
    public static void main(String[] args) {
    	
    	// TODO, add your application code
       	long status;
        int lDevice = 0;
        short findCardMode = 1; //set to 1 if multiply card mode, set to 0 if single card mode
        byte[] pSnrM1 = new byte[9];//M1 card serial number string
        byte[] pSnrSize = new byte[2];
        int[]  pTag = new int[2];
        byte[] pSak = new byte[2];
        
        int[] pval = new int[1];
        char[] pChVal = new char[2];
        char[] pRBuffer = new char[1024];
		byte[] btTmp = new byte[1204];
        
        String strToWrite = "this is a test!";
      	short lenToRW;
      	char[] pWriteBuffer;

        char[] pShowBuf=new char[1024];
        
        char[] pExKey ={0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};//External Key
		char[] pFileProKey={0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};//File Protect Key
		char[] pPurchaseKey={0x20,0x28,0x9d,0x08,0x52,0xc9,0x61,0x60,0x5b,0x92,0xb6,0x07,0xca,0xa3,0xcc,0xd9};//Consumption Key
		char[] pCreditKey ={0xda,0x40,0x4f,0x59,0xe9,0xf7,0x30,0x05,0xa8,0xb9,0x79,0x35,0x73,0xa8,0xbd,0x92};//Credit Key
		char[] pPin = {0x11,0x22,0x33,0x44,0x55,0x66};
		char[] pTerminal = {0x00,0x00,0x00,0x00,0x00,0x01};//Terminal SN
		char[] pDirName = {'a',' ','T','e','s','t',' ','D','i','r'};
		
		

        try {
        	
        	pWriteBuffer = strToWrite.toCharArray();
        	lenToRW = (short)strToWrite.length();
        	
            lDevice = comproCall.lc_init_ex((short)2, "/dev/usb/hiddev0".toCharArray(), 115200);
            if (lDevice == -1) {
                System.out.print("_init error!\n");
                return;
            }
            System.out.print("_init ok!\n");
            
            //Test Buzzer Beep
            comproCall.lc_beep((int)lDevice,(short)10);
            comproCall.lc_rfReset((int)lDevice,(short)10);
            
            status = comproCall.lc_card((int)lDevice, (byte) findCardMode, pSnrM1,pSnrSize, pTag, pSak);
            if (status != 0) {
                System.out.print("find no card!\n");
                comproCall.lc_exit((int)lDevice);//Dislink 
                return;
            }
            
            //reset
            status = comproCall.lc_pro_reset((int)lDevice,pChVal,  btTmp);
            if (status != 0) {
                System.out.print("_pro_reset error!\n");
                comproCall.lc_exit((int)lDevice);//Dislink
                return;
            } else {
                System.out.print("_pro_reset ok!\n");
            }

			//Select Main App
            status = FM1208.FWCosSelecteApp(lDevice);
            if (status != 0) {
                System.out.print("FWCosSelecteApp error!\n");
                comproCall.lc_exit((int)lDevice);//Dislink
                return;
            } else {
                System.out.print("FWCosSelecteApp ok!\n");
            }
            
			//Create Key File to save kinds of keys
            status = FM1208.FWCosCreateKeyFile(lDevice, 
            	(short)0x0000,//The directory to create, 0 indicate current dir
            	(short)0x0001,//Identifier of file
            	(short)0x0040,//Length of file
            	0);//Authority of  Install key
            if (status != 0) {
                System.out.print("FWCosCreateKeyFile error!\n");
                System.out.print(status + "\n");
                FM1208.FWCosDeleteFileSys(lDevice);//Delete this test app
                comproCall.lc_exit((int)lDevice);//dislink
                return;

            } else {
                System.out.print("FWCosCreateKeyFile ok!\n");
            }
            
           	//Install external key
            status = FM1208.FWCosAddKey(lDevice, 
            	(char)2,//Key type
            	pExKey,
            	16);
            if (status != 0) {
                System.out.print("FWCosAddKey[ExKey] error!\n");
                System.out.print(status + "\n");
                FM1208.FWCosDeleteFileSys(lDevice);//Delete this test app
                comproCall.lc_exit((int)lDevice);//dislink
                return;

            } else {
                System.out.print("FWCosAddKey[ExKey] ok!\n");
            }
            
           	//Install file protect key
            status = FM1208.FWCosAddKey(lDevice, 
            	(char)1,//Key type
            	pFileProKey,
            	16);
            if (status != 0) {
                System.out.print("FWCosAddKey[FileProKey] error!\n");
                System.out.print(status + "\n");
                FM1208.FWCosSelecteApp(lDevice);
                FM1208.FWCosVerifyKey(lDevice, pExKey,16,(char)2);//Verify external key
                FM1208.FWCosDeleteFileSys(lDevice);//Delete this test app
                comproCall.lc_exit((int)lDevice);//dislink
                return;

            } else {
                System.out.print("FWCosAddKey[FileProKey] ok!\n");
            }
            
           	//Install Pin
            status = FM1208.FWCosAddKey(lDevice, 
            	(char)3,//Key type
            	pPin,
            	6);
            if (status != 0) {
                System.out.print("FWCosAddKey[Pin] error!\n");
                System.out.print(status + "\n");
                FM1208.FWCosSelecteApp(lDevice);
                FM1208.FWCosVerifyKey(lDevice, pExKey,16,(char)2);//Verify external key
                FM1208.FWCosDeleteFileSys(lDevice);//Delete this test app
                comproCall.lc_exit((int)lDevice);//dislink
                return;

            } else {
                System.out.print("FWCosAddKey[Pin] ok!\n");
            }
            
           	//Create a binary file for testing
            status = FM1208.FWCosCreateBinaryFile(lDevice, 
            	(short)0x0000,//Current directory
            	(short)0x0002,//file ID
            	(short)0x0080,//length of file
            	(char)1,//0-Context, 1-Context with MAC, 2-Crypt with MAC
            	0,//Read not need verify key
            	1,//Update need verify pin
            	0);
            if (status != 0) {
                System.out.print("FWCosCreateBinaryFile error!\n");
                System.out.print(status + "\n");
                FM1208.FWCosSelecteApp(lDevice);
                FM1208.FWCosVerifyKey(lDevice, pExKey,16,(char)2);//Verify external key
                FM1208.FWCosDeleteFileSys(lDevice);//Delete test app
                comproCall.lc_exit((int)lDevice);//dislink
                return;

            } else {
                System.out.print("FWCosCreateBinaryFile ok!\n");
            }
            

           	//Verify Pin
            status = FM1208.FWCosVerifyKey(lDevice, 
            	pPin,
            	6,
            	(char)3);//Key type
            if (status != 0) {
                System.out.print("FWCosVerifyKey error!\n");
                System.out.print(status + "\n");
                FM1208.FWCosSelecteApp(lDevice);
                FM1208.FWCosDeleteFileSys(lDevice);//Delete this test app
                comproCall.lc_exit((int)lDevice);//Dislink
                return;

            } else {
                System.out.print("FWCosVerifyKey ok!\n");
            }
            
           	//Update binary file
            status = FM1208.FWCosUpdateBinaryFile(lDevice, 
            	(short)0x0002,//File ID
            	(short)0x00,//Stary Address
            	pWriteBuffer,//Data
            	(short)lenToRW,//Length of data
            	(char)1,//0-Context, 1-Context with MAC, 2-Crypt with MAC
            	pFileProKey,//File protect key
            	16);//File protect key's length
            if (status != 0) {
                System.out.print("FWCosUpdateBinaryFile error!\n");
                System.out.print(status + "\n");
                FM1208.FWCosSelecteApp(lDevice);
                FM1208.FWCosVerifyKey(lDevice, pExKey,16,(char)2);//Verify external key
                FM1208.FWCosDeleteFileSys(lDevice);//Delete test app
                comproCall.lc_exit((int)lDevice);//dislink
                return;

            } else {
                System.out.print("FWCosUpdateBinaryFile ok!\n");
            }
            
           	//Read binary file
            status = FM1208.FWCosReadBinaryFile(lDevice, 
            	(short)0x0002,//File ID
            	pRBuffer,
            	(short)0x00,//Start address 
            	(short)lenToRW,//length of data for reading
            	(char)1,//0-Context, 1-Context with MAC, 2-Crypt with MAC
            	pFileProKey,//File protect key
            	16);//File protect key's length
            if (status != 0) {
                System.out.print("FWCosReadBinaryFile error!\n");
                System.out.print(status + "\n");
                FM1208.FWCosSelecteApp(lDevice);
                FM1208.FWCosVerifyKey(lDevice, pExKey,16,(char)2);//Verify with external key
                FM1208.FWCosDeleteFileSys(lDevice);//Delete test app
                comproCall.lc_exit((int)lDevice);//dislink
                return;

            } else {
                System.out.print("FWCosReadBinaryFile ok!\n");
                
                System.out.print(pRBuffer);
            }
            
            //***********************************************************************///
            //      Wallet Test 
            //**************************************************************************//
			//Create financial directory
            status = FM1208.FWCosCreateADF(lDevice,
            	(short)0xDF01,//Direcory ID
            	(long)0,//Authority when Create files
            	(long)0,//Authority when delete files
            	pDirName,//Name of direcotry
            	(char)10);//length of name
            if (status != 0) {
                System.out.print("FWCosCreateADF error!\n");
                System.out.print(status + "\n");
                FM1208.FWCosSelecteApp(lDevice);
                FM1208.FWCosVerifyKey(lDevice, pExKey,16,(char)2);//Verify with external key
                FM1208.FWCosDeleteFileSys(lDevice);//Delete test app
                comproCall.lc_exit((int)lDevice);//Dislink
                return;

            } else {
                System.out.print("\rFWCosCreateADF ok!\n");
            }
            
           	//Install external key under financial directory
            status = FM1208.FWCosAddKey(lDevice, 
            	(char)2,//Key type
            	pExKey,
            	16);
            if (status != 0) {
                System.out.print("FWCosAddKey[ExKey] error!\n");
                System.out.print(status + "\n");
                FM1208.FWCosSelecteApp(lDevice);
                FM1208.FWCosVerifyKey(lDevice, pExKey,16,(char)2);//Verify with external key
                FM1208.FWCosDeleteFileSys(lDevice);//Delete the test app
                comproCall.lc_exit((int)lDevice);//dislink
                return;

            } else {
                System.out.print("FWCosAddKey[ExKey] ok!\n");
            }
            
           	//Install Pin
            status = FM1208.FWCosAddKey(lDevice, 
            	(char)3,//Key type
            	pPin,
            	6);
            if (status != 0) {
                System.out.print("FWCosAddKey[Pin] error!\n");
                System.out.print(status + "\n");
                FM1208.FWCosSelecteApp(lDevice);
                FM1208.FWCosVerifyKey(lDevice, pExKey,16,(char)2);
                FM1208.FWCosDeleteFileSys(lDevice);
                comproCall.lc_exit((int)lDevice);
                return;

            } else {
                System.out.print("FWCosAddKey[Pin] ok!\n");
            }
            
           	//Install Consum Key
            status = FM1208.FWCosAddKey(lDevice, 
            	(char)7,//Key Type
            	pPurchaseKey,//Content
            	16);//Length of Key
            if (status != 0) {
                System.out.print("FWCosAddKey[Purchase] error!\n");
                System.out.print(status + "\n");
                FM1208.FWCosSelecteApp(lDevice);
                FM1208.FWCosVerifyKey(lDevice, pExKey,16,(char)2);
                FM1208.FWCosDeleteFileSys(lDevice);
                comproCall.lc_exit((int)lDevice);
                return;

            } else {
                System.out.print("FWCosAddKey[Purchase] ok!\n");
            }
            
           	//Credit Key
            status = FM1208.FWCosAddKey(lDevice, 
            	(char)5,//Key type
            	pCreditKey,//Content
            	16);//Length of Key
            if (status != 0) {
                System.out.print("FWCosAddKey[Credit] error!\n");
                System.out.print(status + "\n");
                FM1208.FWCosSelecteApp(lDevice);
                FM1208.FWCosVerifyKey(lDevice, pExKey,16,(char)2);
                FM1208.FWCosDeleteFileSys(lDevice);
                comproCall.lc_exit((int)lDevice);
                return;

            } else {
                System.out.print("FWCosAddKey[Credit] ok!\n");
            }
            
           	//Verify Pin
            status = FM1208.FWCosVerifyKey(lDevice, 
            	pPin,
            	6,
            	(char)3);
            if (status != 0) {
                System.out.print("FWCosVerifyKey error!\n");
                System.out.print(status + "\n");
                FM1208.FWCosSelecteApp(lDevice);
                FM1208.FWCosVerifyKey(lDevice, pExKey,16,(char)2);
                FM1208.FWCosDeleteFileSys(lDevice);
                comproCall.lc_exit((int)lDevice);
                return;

            } else {
                System.out.print("FWCosVerifyKey ok!\n");
            }
            
           	//Credit Test
            status = FM1208.FWCosCredit(lDevice,
            	(char)0x00,//Key ID (Set 0x00 here)
            	100000,//Balance 
            	pTerminal,//Terminal ID
            	pCreditKey,//Credit Key
            	(long)16);//Key length
            if (status != 0) {
                System.out.print("FWCosCredit error!\n");
                System.out.print(status + "\n");
                FM1208.FWCosSelecteApp(lDevice);
                FM1208.FWCosVerifyKey(lDevice, pExKey,16,(char)2);
                FM1208.FWCosDeleteFileSys(lDevice);
                comproCall.lc_exit((int)lDevice);
                return;

            } else {
                System.out.print("FWCosCredit ok!\n");
            }
            
           	//Consume Test
            status = FM1208.FWCosPurchase(lDevice,
            	(char)0x01,//Key ID (Set to 0x01 here)
            	50,//Balance for consuming
            	pTerminal,//Terminal ID
            	pPurchaseKey,//Consume key
            	(long)16);//Key length
            if (status != 0) {
                System.out.print("FWCosPurchase error!\n");
                System.out.print(status + "\n");
                FM1208.FWCosSelecteApp(lDevice);
                FM1208.FWCosVerifyKey(lDevice, pExKey,16,(char)2);
                FM1208.FWCosDeleteFileSys(lDevice);
                comproCall.lc_exit((int)lDevice);
                return;

            } else {
                System.out.print("FWCosPurchase ok!\n");
            }
            
           	//Query Balance Test
            status = FM1208.FWCosGetBalance(lDevice,
            	pval);//Balance got
            if (status != 0) {
                System.out.print("FWCosGetBalance error!\n");
                System.out.print(status + "\n");
                FM1208.FWCosSelecteApp(lDevice);
                FM1208.FWCosVerifyKey(lDevice, pExKey,16,(char)2);
                FM1208.FWCosDeleteFileSys(lDevice);
                comproCall.lc_exit((int)lDevice);
                return;

            } else {
                System.out.print("FWCosGetBalance ok!\n");
                System.out.println(pval[0]);
            }
            
            //Select main app
            FM1208.FWCosSelecteApp(lDevice);
            
            //Verify the external key
            status = FM1208.FWCosVerifyKey(lDevice, 
            	pExKey,
            	16,
            	(char)2);
            if (status != 0) {
                System.out.print("FWCosVerifyKey error!\n");
                System.out.print(status + "\n");
                FM1208.FWCosDeleteFileSys(lDevice);
                comproCall.lc_exit((int)lDevice);

            } else {
                System.out.print("FWCosVerifyKey ok!\n");
            }

            
            //Delete this test app
            status = FM1208.FWCosDeleteFileSys(lDevice);
            if (status != 0) {
                System.out.print("FWCosDeleteFileSys error!\n");
                System.out.print(status + "\n");
                comproCall.lc_exit((int)lDevice);//Dislink
 
            } else {
                System.out.print("FWCosDeleteFileSys ok!\n");
            }

            comproCall.lc_exit((int)lDevice);//Dislink
            


        } catch (Exception e) {
            System.err.println("Exception caught: " + e.getMessage());
        }
    }
}
