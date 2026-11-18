//package com.ykrj.archives.cabinet.lock;

//import com.ykrj.archives.cabinet.dao.entity.cab.CabinetCard;
//import com.ykrj.archives.cabinet.dao.entity.cab.CabinetLog;
//import com.ykrj.archives.cabinet.service.cab.CabinetCardService;
//import com.ykrj.archives.cabinet.service.cab.CabinetLogService;
//import com.ykrj.archives.cabinet.storage.rxtx.Serial;
import lc.comproCall;
//import org.springframework.beans.factory.annotation.Autowired;
//import org.springframework.stereotype.Component;

import java.util.Date;

public class IcCardTest {


    static int lDevice = 0;

    public static void main(String[] args) {
        //        lDevice = comproCall.lc_init_ex(2, " ".toCharArray(), 115200);//USB port
        lDevice = comproCall.lc_init_ex(2, "/dev/usb/hiddev0".toCharArray(), 115200);//USB port
        System.out.println(lDevice);
        if (lDevice != -1) {
            System.out.println("-------------读卡程序启动:" + lDevice + "--------------");
            byte[] reader = new byte[1];
            byte re = 1;
            int i1 = comproCall.lc_setReaderMode(lDevice, re);
            System.out.println("------------设置只读模式:" + i1 + "----------");
            int i = comproCall.lc_getReaderMode(lDevice, reader);
            System.out.println(reader[0]);

            byte[] pSBuffer = new byte[16];
            pSBuffer[0] = (byte) 0xFF;
            pSBuffer[1] = (byte) 0xFF;
            pSBuffer[2] = (byte) 0xFF;
            pSBuffer[3] = (byte) 0xFF;
            pSBuffer[4] = (byte) 0xFF;
            pSBuffer[5] = (byte) 0xFF;
            byte[] pRBuffer = new byte[16];
            byte keyMode = 0x60;
            byte dd = 8;
            byte[] pRData = new byte[9];
            byte[] pRLen = new byte[2];
            while (true) {
                int status = comproCall.lc_getAutoReturnedData(lDevice, pRData, pRLen);
//                System.out.println(status);
                if (status == 0) {
                    System.out.println(status + "-------------检测到卡片------");
                    int status2 = comproCall.lc_read_convenient(lDevice, dd, keyMode, pSBuffer, pRBuffer);
                    System.out.println(status + "-------------读取卡片------");
                    if (status2 != 0) {
                        System.out.println("识别卡错误 error!\n");
                    } else {
                        System.out.println(status + "-------------卡片读取成功----------------");
                        String data2 = new String(pRBuffer);
                        System.out.println("-----------检测卡片信息--------------");
                        System.out.println(data2);
                    }
                }
            }
        }else {
            System.out.println("读卡器启动失败,请联系管理员");
        }
    }

    public void run() throws InterruptedException {

    }

}
