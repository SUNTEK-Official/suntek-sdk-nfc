//package examples;

import lc.comproCall;

public class comProDemo {
	
	public static  void main(String[] args)
	{
		
		
        int status;
        int i;
        int lDevice = 0;
        short tblk = 8;
        short tsector = 2;
        short findCardMode = 1; //set to 1 if multiply card mode, set to 0 if single card mode
        short keyMode = 0x60;// refer to manual doc

        byte[] pSnrM1 = new byte[9];//M1 card serial number string
        byte[] pSnrSize = new byte[2];
        int[]  pTag = new int[2];
        byte[] pSak = new byte[2];
        int[] pSnr=new int[1];
        int[] pval = new int[1];

        byte[] pSBuffer = new byte[16];
        byte[] pRBuffer = new byte[16];

        short lSlen;
        char[] pScupBuffer = {'0', '0', 'A', '4', '0', '0', '0', '0', '0',
                             '2', '2', 'F', '0', '2'};

        short[] pRlen = new short[1];
        char[] pRcpuBuffer = new char[255];
        byte[] pShowBuf = new byte[1024];
        char[] pShowChars = new char[1024];
        byte[] pNewKeyA = {(byte)0xff,(byte)0xff,(byte)0xff,  (byte)0xff, (byte)0xff, (byte)0xff};
        byte[] pNewCtrlW = {(byte)0xff,(byte)0x07, (byte)0x80, (byte)0x69};
        byte[] pNewKeyB = {(byte)0xff,(byte)0xff,(byte)0xff,  (byte)0xff, (byte)0xff, (byte)0xff};
        
        

        try {
            //lDevice = comproCall.lc_init_ex(2,"COM3".toCharArray(), 115200);//COM port
            lDevice = comproCall.lc_init_ex(2, "/dev/usb/hiddev0".toCharArray(), 115200);//USB port
            
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

            
            status = comproCall.lc_card(lDevice, (byte) findCardMode, pSnrM1,pSnrSize, pTag, pSak);//
            if (status != 0) {
                System.out.print("lc_card error!\n");
                System.out.print(status + "\n");
                comproCall.lc_exit(lDevice);
                return;

            } else {
                System.out.print("lc_card ok!\n");
                for(i=0; i< pSnrSize[0]; i++){
                	System.out.printf("%02X", pSnrM1[i]);
                }
                System.out.print("\n");
            }

            pSBuffer[0] = (byte)0xFF;
            pSBuffer[1] = (byte)0xFF;
            pSBuffer[2] = (byte)0xFF;
            pSBuffer[3] = (byte)0xFF;
            pSBuffer[4] = (byte)0xFF;
            pSBuffer[5] = (byte)0xFF;

 
            status = comproCall.lc_authentication(lDevice, (byte) keyMode, (byte) tsector, pSBuffer);
            if (status != 0) {
                System.out.print("lc_authentication error!\n");
                System.out.print(status + "\n");
                comproCall.lc_exit(lDevice);
                return;
 
            } else {
                System.out.print("lc_authentication ok!\n");
            }
 
            //lc_initval
            status = comproCall.lc_initval(lDevice, (byte)tblk , (short) 1000);
            if (status != 0) {
                System.out.print("lc_initval error!\n");
                comproCall.lc_exit(lDevice);
                return;
   
            } else {
                System.out.print("lc_initval ok!\n");
            }
            
            //lc_increment
            status = comproCall.lc_increment(lDevice, (byte) tblk, (short) 100);

            if (status != 0) {
                System.out.print("lc_increment error!\n");
                comproCall.lc_exit(lDevice);
                return;

            } else {
                System.out.print("lc_increment ok!\n");
            }
            //lc_decrement
            status = comproCall.lc_decrement(lDevice, (byte) tblk, (short) 50);
            if (status != 0) {
                System.out.print("lc_decrement error!\n");
                comproCall.lc_exit(lDevice);
                return;

            } else {
                System.out.print("lc_decrement ok!\n");
            }
            //lc_readval
            status = comproCall.lc_readval(lDevice, (byte) tblk, pval);
            if (status != 0) {
                System.out.print("lc_readval error!\n");
                comproCall.lc_exit(lDevice);
                return;

            } else {
                System.out.print("lc_readval ok!\n");
                System.out.println(pval[0]);
            }

            for(i=0;i<16;i++)pSBuffer[i] = (byte)(1+i);//Prepare data for writting
            status = comproCall.lc_write(lDevice, (byte) tblk, pSBuffer);
            if (status != 0) {
                System.out.print("lc_write error!\n");
                comproCall.lc_exit(lDevice);
                return;

            } else {
                System.out.print("lc_write ok!\n");
            }

            status = comproCall.lc_read(lDevice, (byte) tblk, pRBuffer);
            if (status != 0) {
                System.out.print("lc_read error!\n");
                comproCall.lc_exit(lDevice);
                return;

            } else {
                System.out.print("lc_read ok!\n");
                //System.out.println(pRBuffer);
                for(i=0; i< 16; i++){
                	System.out.printf("%02X", pRBuffer[i]);
                }
                System.out.print("\n");
            }
            //--- Change Key
            status = comproCall.lc_updateKey(lDevice, (byte) tsector, pNewKeyA, pNewCtrlW, pNewKeyB);
            if (status != 0) {
                System.out.print("Update key error!\n");
                comproCall.lc_exit(lDevice);
                return;

            } else {
                System.out.print("Update key ok!\n");
            }
            

            /*
            //lc_srd_eeprom
            char[] loutchar = new char[255];

            status = comproCall.lc_srd_eeprom(lDevice, 12, 5, loutchar);
            if (status != 0) {
                System.out.print("lc_srd_eeprom error!\n");
                comproCall.lc_exit(lDevice);
                return;

            } else {
                System.out.print("lc_srd_eeprom ok!\n");
            }
			*/
			
            /*
            //-----------------------------------------------
            //*******  FCPU card   *************************
             //-----------------------------------------------
             char[] rlenbuf = new char[4];
             char[] sdbuf={0x00,0x84,0x00,0x00,0x08};
             char[] rbuffcpu = new char[255];
             char[] showrbuf_fcpu=new char[255];
             //lc_reset
             status = comproCall.lc_rfReset(lDevice,10);
             if(status != 0){
             	System.out.print("lc_reset Error!\n");
                comproCall.lc_exit(lDevice);
                return;
             }else{
             	System.out.print("lc_reset Ok!\n");
             }
             //lc_card
             status = comproCall.lc_card(lDevice, (byte) findCardMode, pSnrM1,pSnrSize, pTag, pSak);
            if (status != 0) {
                System.out.print("lc_card error!\n");
                System.out.print(status + "\n");
                comproCall.lc_exit(lDevice);
                return;
            } else {
                System.out.print("lc_card ok!\n");
                
                for(i=0; i< pSnrSize[0]; i++){
                	System.out.printf("%02X", pSnrM1[i]);
                }
                System.out.print("\n");
            }
             //lc_pro_reset
             status = comproCall.lc_pro_reset(lDevice,rlenbuf,rbuffcpu);
             if(status!=0){
             	System.out.print("lc_pro_reset error!\n");
                comproCall.lc_exit(lDevice);
                return;
             }else{
             	System.out.print("lc_pro_reset Ok!\n");
                for(i=0; i< (int)rlenbuf[0]; i++){
                	System.out.printf("%02X", (byte)rbuffcpu[i]);
                }
             	System.out.print("\n");
             }             
             //lc_pro_commandlink
             status=comproCall.lc_pro_commandlink(lDevice,(short)5,sdbuf,rlenbuf,
             rbuffcpu,
             (short)07,(short)59);
             if(status!=0){
             	System.out.print("lc_pro_commandlink error!\n");
                comproCall.lc_exit(lDevice);
                return;
             }else{
             	System.out.print("lc_pro_commandlink Ok!\n");

                for(i=0; i< (int)rlenbuf[0]; i++){
                	System.out.printf("%02X", (byte)rbuffcpu[i]);
                }
                System.out.print("\n");
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
