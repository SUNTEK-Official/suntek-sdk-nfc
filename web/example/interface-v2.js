var READER_TYPE = {
	_reader_type_contactLess:1,
	_reader_type_contact:2,
	_reader_type_keyBoard:3,
	_reader_type_compro:4,
};

var FUNCIDS = {
	_fid_adaptReader:0,
	_fid_initialcom:1,
	_fid_exit:2,
	_fid_beep:3,
	_fid_GetDevSN:4,
	_fid_srd_eeprom:5,
	_fid_swr_eeprom:6,
	_fid_setBright:7,
	_fid_dispstr_ex:8,
	_fid_dispClear:9,
	_fid_passInReady:10,
	_fid_getPassPressed:11,
	_fid_getPassConfirmed:12,
	_fid_passInEnd:13,
    _fid_led:14,
    _fid_ioCtrl:15,
	_fid_init_ex:16,
	_fid_authenClassEx:29,
	_fid_loadKey:30,
	_fid_findCard:31,
	_fid_findCardStr:32,
	_fid_findCardHex:33,
	_fid_authenClass:34,
	_fid_readAsStr:35,
	_fid_readAsHex:36,
	_fid_writeAsStr:37,
	_fid_writeAsHex:38,
	_fid_initVal:39,
	_fid_increment:40,
	_fid_decrement:41,
	_fid_readVal:42,
	_fid_transfer:43,
	_fid_changeKey:44,
	_fid_halt:45,
	_fid_resetRF:46,
	_fid_tagSetPwd:47,
	_fid_tagAuthenPwd:48,
	_fid_fcpuReset:50,
	_fid_fcpuAPDU:51,
	_fid_mifareProReset:52,
	_fid_mifareProAPDU:53,
    _fid_findCard_ex:54,
    _fid_identifyTypeA:55,
	_fid_fmCosSelectApp:60,
	_fid_fmCosCreateMainApp:61,
	_fid_fmCosDeleteFileSys:62,
	_fid_fmCosVerifyKey:63,
	_fid_fmCosCreateDirectory:64,
	_fid_fmCosSelectDirectory:65,
	_fid_fmCosCreateKeyFile:66,
	_fid_fmCosAddKey:67,
	_fid_fmCosAddKeyEx:68,
	_fid_fmFWCosCreateBinaryFile:69,
	_fid_fmFWCosCreateRecordFile:70,
	_fid_fmCosCreateADF:71,
	_fid_fmCosActiveDirectory:72,
	_fid_fmCosReadBinaryFile:73,
	_fid_fmCosUpdateBinaryFile:74,
	_fid_fmCosAppendRecord:75,
	_fid_fmCosUpdateRecord:76,
	_fid_fmCosReadRecord:77,
	_fid_fmCosCredit:78,
	_fid_fmCosPurchase:79,
	_fid_fmCosGetBalance:80,
	_fid_fmCosUpdateKey:81,
	_fid_fmCosUpdatePin:82,
	_fid_fmCosPinReload:83,
	_fid_fmCosPinUnlock:84,
	_fid_icode_inventory:85,
	_fid_icode_select_uid:86,
	_fid_icode_readblockAsStr:87,
	_fid_icode_readblockAsHex:88,
	_fid_icode_writeblockAsStr:89,
	_fid_icode_writeblockAsHex:90,
	_fid_icode_lock_block:91,
	_fid_icode_get_systemInfo:92,
	_fid_desfire_authen:100,
	_fid_desfire_authen_aes:101,
	_fid_desfire_getVer:102,
	_fid_desfire_getAIDs:103,
	_fid_desfire_selectApp:104,
	_fid_desfire_getKeySetting:105,
	_fid_desfire_getKeyVer:106,
	_fid_desfire_createApp:107,
	_fid_desfire_delAID:108,
	_fid_desfire_changeKeySetting:109,
	_fid_desfire_changeKey:110,
	_fid_desfire_changeKey_aes:111,
	_fid_desfire_getFileIDs:112,
	_fid_desfire_getFileProper:113,
	_fid_desfire_changeFileSetting:114,
	_fid_desfire_createDataFile:115,
	_fid_desfire_createBackupDataFile:116,
	_fid_desfire_createValueFile:117,
	_fid_desfire_createCsyRecord:118,
	_fid_desfire_delFile:119,
	_fid_desfire_write:120,
	_fid_desfire_read:121,
	_fid_desfire_getValue:122,
	_fid_desfire_credit:123,
	_fid_desfire_debit:124,
	_fid_desfire_writeRecord:125,
	_fid_desfire_readRecord:126,
	_fid_desfire_clearRecord:127,
	_fid_desfire_commitTransfer:128,
	_fid_desfire_abortTransfer:129,
	_fid_desfire_formatPICC:130,
	_fid_request_b:150,
	_fid_CommandLink_at:151,
    _fid_uhf_inventory:160,
    _fid_uhf_writeTag:161,
    _fid_uhf_readTag:162,
	_fid_config_card:399,
	_fid_getIDCardSN:400,
	_fid_writeNFCTag_MiniAppLanucher:401,
    _fid_writeNFCTag_Text:402,
    _fid_writeNFCTag_URI:403,
    _fid_readNFCTag:408,
    _fid_writeNFCTag_ex:409,
    _fid_readNFCTag_ex:410,
	_fid_getAutoReturnData:450,
	_fid_strToHex:500,
	_fid_hexToStr:501,
    _fid_getHWVer:502,
    _fid_crypt:503,
    _fid_iccGetCardState:600,
    _fid_iccSelCardType:601,
    _fid_iccReadErrorCounter:602,
    _fid_iccVerifyUserPass:603,
    _fid_iccReadMem:604,
    _fid_iccWriteMem:605,
    _fid_iccUpdateUserPass:606,
    _fid_iccGetATR:607,
    _fid_iccAPDU:608,
    _fid_iccSetBaud:609,
    _fid_iccPPS:610,
};

function ParseSocketResult(str){

	var id  = str.substr(0, 1);
	var separator = str.indexOf("|");
	var funcid = "";
	var arg1 = "";

	if(separator != -1)
	{
		funcid = str.substr(1, separator-1);
		arg1 = str.substr(separator+1);
	}
	else
		funcid = str.substr(1);				

    var resultData = {
        type:"Result",
		FunctionID:parseInt(funcid),
		RePara_Int:parseInt( _getCmdResult(arg1)),
		RePara_Str:_getResultPara(arg1)
    };
			
	return resultData;
};

 class ws  {
  constructor(wsServer,readerClassID){
    this.wsServer = wsServer
    this.wSock = null;
    this.pool = {}; 
    this.adaptedID = readerClassID;
    this.SocketOpen=false;
  }
  init = async (onMessage, onError, onClose) => {
    return new Promise((resolve, reject) => {
      if (!window.WebSocket) { reject('Browser do not support WebSocket'); }
      try {
          this.wSock= new WebSocket(this.wsServer);
      } catch(err) {
          reject(err);
      }
      this.wSock.onopen = this._onOpen(resolve);
      this.wSock.onmessage = this._onMessage(onMessage);
      this.wSock.onclose = this._onClose(onClose);
      this.wSock.onerror = this._onError(onError);
    })
  }
  _onOpen = resolve => (e) => {

    resolve(e) 

    const req = {};
    const res = this.login(req);

    this.adaptReader(this.adaptedID);
    this.SocketOpen=true;

    //console.log("Server is ready, you can start now!"); //////////////// You can change this tip for yourself!!!
  }
  _onMessage = onMessage => (e) => {

	var str = "";
	str = e.data;
	var id  = str.substr(0, 1);
	var separator = str.indexOf("|");
	var funcid = "";
	var arg1 = "";

	if(separator != -1)
	{
		funcid = str.substr(1, separator-1);
		arg1 = str.substr(separator+1);
	}
	else
		funcid = str.substr(1);				
					
			
    var resultData = {
        type:"Result",
		FunctionID:parseInt(funcid),
		RePara_Int:parseInt( _getCmdResult(arg1)),
		RePara_Str:_getResultPara(arg1)
    };

    const key = resultData.FunctionID;

    //Delete message if it in pool 
    if (this.pool[key]) {
      this.pool[key].resolve(e.data);
      delete this.pool[key];
      return;
    }
    //Dispatch to onMessage
    onMessage(e);
  }
  _onClose = onClose => (e) => { onClose(e) }
  _onError = onError => (e) => {console.log('class ws ->onError' ); alert("Server not running");onError(e) }

  _send = (reqFrame, cmdID) => {
    //console.log('class ws ->_send, req=' + reqFrame + 'cmdID=' + cmdID);
    this.wSock.send(reqFrame);
    if (typeof cmdID !== '') {
      return new Promise((resolve, reject) => {
        this.pool[cmdID] = {
          reqFrame,
          resolve,
          reject,
          //...
        }
      })
    }
  }

  login = async (req) => {
	var pseudoName = "webReader";
	var curTime = new Date();
	var lTime = Date.parse(curTime);
	var ms = curTime.getMilliseconds();
	var cmdFrame = '0'+pseudoName+lTime+ms;
    return await this._send(cmdFrame);
  }

  adaptReader =async (adaptReaderID) => {
    return await this._send("10|adaptReader|"+ adaptReaderID, 0)
  }

  SendCmd = async (cmdFrame, cmdID) => {
    return await this._send(cmdFrame, cmdID)
  }

}
function _getCmdResult(relPara)
{
	var iRel;
	var separator = relPara.indexOf(",");
	if(separator != -1)
	{
		iRel = relPara.substr(0, separator);
	}
	else
		iRel = relPara.substr(0);	

	return iRel;
}
function _getResultPara(relPara)
{
	var szPara="";
	var separator = relPara.indexOf(",");
	if(separator != -1)
	{
		szPara = relPara.substr(separator+1);
	}
	return szPara;
}

class SmartReader {
  constructor(readerClassID){
    var reader={};
    var adaptedID = readerClassID;

    this.notifyEvent = new CustomEvent('webReaderServerNotifyEvent',{
        detail: {message: 'Server is ready, you can start now!'},
        bubbles:true,
        cancelable:true
    });

    this.ws = new ws('ws://localhost:81/webReaderServer',adaptedID);

    this.init();
  }
  init = async () => {
    await this.ws.init(this.onMessage, this.onError, this.onClose);

    var resultData = {
        type:"Result",
		FunctionID:FUNCIDS._fid_adaptReader,
		RePara_Int:0,
		RePara_Str:''
    };
    document.dispatchEvent(this.notifyEvent);
  }

  onMessage = () => {}
  onError = () => {}
  onClose = () => {}

  adaptReader = async () => {
        const req = {};
        const res = await this.ws.adaptReader();
        return await res;
  }
  

    /////////////////////////////////////////////////////////////
    SendCmd = async (FuncName, FunctionID, ParamStr) => {
	    var entryCmd;
	    if(true == this.ws.SocketOpen)
	    {
		    entryCmd = '1' + FunctionID + "|" + FuncName+"|"+ParamStr;

            const res = await this.ws.SendCmd(entryCmd, FunctionID);

            return new Promise((resolve, reject)=>{
                    resolve(ParseSocketResult(res));
		    });
        }//if(true == this.ws.SocketOpen)
        else
        {
            return new Promise((resolve, reject)=>{
                    resolve(null);
		    });
        }
    }//SendCmd = async (FuncName, FunctionID, ParamStr) => {


    ////////////////////////////////////////////////////////////////////// I N T E R F A C E S ///////////////////////////////////////////
    initialcom = function(portType, baud){return this.SendCmd("initialcom",FUNCIDS._fid_initialcom,portType+","+ baud); }
    init_ex = function(portType,path, baud){return this.SendCmd("init_ex",FUNCIDS._fid_init_ex,portType+","+path+","+ baud); }
    exit = function(hdev){return this.SendCmd("exit",FUNCIDS._fid_exit,hdev);}
    GetDevSN=function(hdev){return this.SendCmd("GetDevSN", FUNCIDS._fid_GetDevSN, hdev);}
    getHW = function(hdev){return this.SendCmd("getHWVer",FUNCIDS._fid_getHWVer,hdev);}
    beep = function(hdev, delay){return this.SendCmd("beep",FUNCIDS._fid_beep,hdev+","+ delay);}
	srd_eeprom = function(hdev,offset, length){return this.SendCmd("srd_eeprom", FUNCIDS._fid_srd_eeprom, hdev+","+offset+","+length);}
	swr_eeprom = function(hdev,offset,length,wData){return this.SendCmd("swr_eeprom", FUNCIDS._fid_swr_eeprom, hdev+","+offset+","+length+","+wData);}
	lcd_setBright=function(hdev,fBright){return this.SendCmd("lcd_setBright",FUNCIDS._fid_setBright,hdev+","+fBright);}
	lcd_dispstr_ex=function(hdev,str,line,offset,str_len,flag){return this.SendCmd("lcd_dispstr_ex",FUNCIDS._fid_dispstr_ex,hdev+","+str+","+line+","+offset+","+str_len+","+flag);}
	lcd_dispclear=function(hdev){return this.SendCmd("lcd_dispclear",FUNCIDS._fid_dispClear,hdev);}
	passInReady=function(hdev,waitTime){return this.SendCmd("passInReady",FUNCIDS._fid_passInReady,hdev+","+waitTime);}
	getPassPressed=function(hdev){return this.SendCmd("getPassPressed",FUNCIDS._fid_getPassPressed, hdev);}
	getPassConfirmed=function(hdev){return this.SendCmd("getPassConfirmed",FUNCIDS._fid_getPassConfirmed, hdev);}
	passInEnd=function(hdev){return this.SendCmd("passInEnd",FUNCIDS._fid_passInEnd,hdev);}
    led = function(hdev, iLed, action){return this.SendCmd("led",FUNCIDS._fid_led,hdev+","+ iLed + ","+ action);}
    ioCtrl = function(hdev, ioNo, action){return this.SendCmd("ioCtrl",FUNCIDS._fid_ioCtrl,hdev+","+ ioNo + ","+ action);}

	loadkey = function(hdev, mode, sector, strKey){return this.SendCmd("loadkey",FUNCIDS._fid_loadKey, hdev+","+mode+","+sector+","+strKey);}
	findcard = function(hdev,mode){return this.SendCmd("findcard",FUNCIDS._fid_findCard, hdev+","+mode);}
    findCard_ex = function(hdev,find_mode, outMode){return this.SendCmd("findCardEx",FUNCIDS._fid_findCard_ex, hdev+","+find_mode+","+outMode);}
	findcardStr=function(hdev,mode){return this.SendCmd("findcardStr",FUNCIDS._fid_findCardStr,hdev+","+mode);}
	findcardHex=function(hdev,mode){return this.SendCmd("findcardHex",FUNCIDS._fid_findCardHex, hdev + ","+mode);}
    identifyTypeA = function(hdev,find_mode){return this.SendCmd("identifyTypeA",FUNCIDS._fid_identifyTypeA, hdev+","+find_mode);}
	authentication=function(hdev,mode, sector){return this.SendCmd("authentication",FUNCIDS._fid_authenClass, hdev+","+mode+","+sector);}
	authenticationEx=function(hdev,mode, sector,key){return this.SendCmd("authenticationEx",FUNCIDS._fid_authenClassEx, hdev+","+mode+","+sector+","+key);}
	read =function(hdev, block){return this.SendCmd("read", FUNCIDS._fid_readAsStr, hdev+","+block);}
	directRead=function(hdev,block){return this.SendCmd("directRead",FUNCIDS._fid_readAsHex, hdev+","+block);}
	write=function(hdev, block, wdata){return this.SendCmd("write",FUNCIDS._fid_writeAsStr, hdev+","+block+","+wdata);}
	directWrite=function(hdev,block,wdata){return this.SendCmd("directWrite", FUNCIDS._fid_writeAsHex,hdev+","+block+","+wdata);}
	initialval=function(hdev,block,value){return this.SendCmd("initval",FUNCIDS._fid_initVal,hdev+","+block+","+value);}
	increment=function(hdev,block,value){return this.SendCmd("increment",FUNCIDS._fid_increment,hdev+","+block+","+value);}
	decrement=function(hdev,block,value){return this.SendCmd("decrement",FUNCIDS._fid_decrement,hdev+","+block+","+value);}
	readval=function(hdev,block){return this.SendCmd("readval",FUNCIDS._fid_readVal,hdev+","+block);}
	transfer=function(hdev,block){return this.SendCmd("transfer",FUNCIDS._fid_transfer, hdev+","+block);}
	changkey=function(hdev,sector,strKeyA,strCtrlW,bk,strKeyB){return this.SendCmd("changekey",FUNCIDS._fid_changeKey,hdev+","+sector+","+strKeyA+","+strCtrlW+","+bk+","+strKeyB);}
	halt=function(hdev){return this.SendCmd("halt",FUNCIDS._fid_halt,hdev);}
	reset=function(hdev,ms){return this.SendCmd("reset",FUNCIDS._fid_resetRF,hdev+","+ms);}
	tagSetPwd=function(hdev,tagType,pwd,protectType,startAddrToProtect,maxErrorVerify,lockConfig){return this.SendCmd("tagSetPwd",FUNCIDS._fid_tagSetPwd,hdev+","+tagType+","+pwd+","+protectType+","+startAddrToProtect+","+maxErrorVerify+","+lockConfig);}
	tagAuthenPwd=function(hdev,pwd){return this.SendCmd("tagAuthenPwd",FUNCIDS._fid_tagAuthenPwd,hdev+","+pwd);}
	mifareproReset=function(hdev){return this.SendCmd("mifareProReset",FUNCIDS._fid_mifareProReset, hdev);}
	mifareproCommandlink=function(hdev, strCmd){return this.SendCmd("mifareproCommandlink",FUNCIDS._fid_mifareProAPDU, hdev+","+strCmd);}
	fcpureset=function(hdev,rlen){return this.SendCmd("fcpureset", FUNCIDS._fid_fcpuReset, hdev+","+rlen);}
	fcpuCommandlink=function(hdev,slen, strSendCmd,ftt,fFG){return this.SendCmd("cpuCommand",FUNCIDS._fid_fcpuAPDU, hdev+","+slen+","+strSendCmd+","+ftt+","+fFG);}
	GetIDCardSN=function(hdev){return this.SendCmd("getIDCardSN", FUNCIDS._fid_getIDCardSN, hdev);}

	FWCosSelecteApp=function(hdev){return this.SendCmd("FMCosSelectApp",FUNCIDS._fid_fmCosSelectApp, hdev);}
	FWCosCreateMainApp=function(hdev){return this.SendCmd("FMCosCreateMainApp", FUNCIDS._fid_fmCosCreateMainApp,hdev);}
	FWCosDeleteFileSys=function(hdev){return this.SendCmd("FMCosDeleteFileSys", FUNCIDS._fid_fmCosDeleteFileSys, hdev);}
	FWCosVerifyKey=function(hdev, pbKey, ulKeyType){return this.SendCmd("FMCosVerifyKey",FUNCIDS._fid_fmCosVerifyKey,hdev+","+pbKey+","+ulKeyType);}
	FWCosCreateDirectory=function(hdev,usDirFileID,usDirSize,ulCreateSec,ulDeleteSec){return this.SendCmd("FMCosCreateDirectory",FUNCIDS._fid_fmCosCreateDirectory,
		hdev+","+usDirFileID+","+usDirSize+","+ulCreateSec+","+ulDeleteSec);}
	FWCosSelectDirectory=function(hdev,usDirID){return this.SendCmd("FMCosSelectDirectory",FUNCIDS._fid_fmCosSelectDirectory,hdev+","+usDirID);}
	FWCosCreateKeyFile=function(hdev,usDirFileID,usFileID,uFileLen,ulGenSec){return this.SendCmd("FMCosCreateKeyFile",FUNCIDS._fid_fmCosCreateKeyFile,
		hdev+","+usDirFileID+","+usFileID+","+uFileLen+","+ulGenSec);}
	FWCosAddKey=function(hdev,bKeyType,pbKeyValue){return this.SendCmd("FMCosAddKey",FUNCIDS._fid_fmCosAddKey,hdev+","+bKeyType+","+pbKeyValue);}
	FWCosAddKeyEx=function(hdev,bKeyType,ucKeyID,pbKeyValue,ucSecUpdate,ucNextSt,ucMaxCntError,cryptType){return this.SendCmd("FMCosAddKeyEx",FUNCIDS._fid_fmCosAddKeyEx,
		hdev+","+bKeyType+","+ucKeyID+","+pbKeyValue+","+ucSecUpdate+","+ucNextSt+","+ucMaxCntError+","+cryptType);}
	FWCosCreateBinaryFile=function(hdev,usDirFileID,usFileID,usFileLen,cryptType,ulReadSec,ulUpdateSec,ulDeleteSec){return this.SendCmd("FMCosCreateBinaryFile",
		FUNCIDS._fid_fmFWCosCreateBinaryFile,hdev+","+usDirFileID+","+usFileID+","+usFileLen+","+cryptType+","+ulReadSec+","+ulUpdateSec);}
	FWCosCreateRecordFile=function(hdev,usDirFileID,ucFRecord,usFileID,bRecordNum,bRecordLen,cryptType,ulReadSec,ulUpdateSec,ulDeleteSec){
		return this.SendCmd("FMCosCreateRecordFile",FUNCIDS._fid_fmFWCosCreateRecordFile,hdev+","+usDirFileID+","+ucFRecord+","+usFileID+","+bRecordNum+","+bRecordLen+","+
			cryptType+","+ulReadSec+","+ulUpdateSec+","+ulDeleteSec);}
	FWCosCreateADF=function(hdev,usDirFileID,ulCreateSec,ulDeleteSec,pbDirName){return this.SendCmd("FMCosCreateADF",FUNCIDS._fid_fmCosCreateADF,hdev+","+usDirFileID+","+ulCreateSec+","+ulDeleteSec+","+pbDirName);}
	FWCosActiveDirectory=function(hdev,usDirFileID){return this.SendCmd("FMCosActiveDirectory",FUNCIDS._fid_fmCosActiveDirectory,hdev+","+usDirFileID);}
	FWCosReadBinaryFile=function(hdev,usFileID,usOffset,usReadLen,cryptType,pProKey){return this.SendCmd("FMCosReadBinaryFile",FUNCIDS._fid_fmCosReadBinaryFile,
		hdev+","+usFileID+","+usOffset+","+usReadLen+","+cryptType+","+pProKey);}
	FWCosUpdateBinaryFile=function(hdev,usFileID,usOffset,pbBinData,cryptType,pProKey){return this.SendCmd("FMCosUpdateBinaryFile",FUNCIDS._fid_fmCosUpdateBinaryFile,
		hdev+","+usFileID+","+usOffset+","+pbBinData+","+cryptType+","+pProKey);}
	FWCosAppendRecord=function(hdev,bRecordFileID,pbRecData,cryptType,pProKey){return this.SendCmd("FMCosAppendRecord",FUNCIDS._fid_fmCosAppendRecord,
		hdev+","+bRecordFileID+","+pbRecData+","+cryptType+","+pProKey);}
	FWCosUpdateRecord=function(hdev,ucRecord,bRecordFileID,bRecordNum,pbRecData,cryptType,pProKey){return this.SendCmd("FMCosUpdateRecord",FUNCIDS._fid_fmCosUpdateRecord,
		hdev+","+ucRecord+","+bRecordFileID+","+bRecordNum+","+pbRecData+","+cryptType+","+pProKey);}
	FWCosReadRecord=function(hdev,ucFRecord,bRecordFileID,bRecordNum,bRecordLen){return this.SendCmd("FMCosReadRecord",FUNCIDS._fid_fmCosReadRecord,
		hdev+","+ucFRecord+","+bRecordFileID+","+bRecordNum+","+bRecordLen);}
	FWCosCredit=function(hdev,ucKeyID,value,terminalID,pbCreditKey){return this.SendCmd("FMCosCredit",FUNCIDS._fid_fmCosCredit,
		hdev+","+ucKeyID+","+value+","+terminalID+","+pbCreditKey);}
	FWCosPurchase=function(hdev,ucKeyID,value,terminalID,pbPurchaseKey){return this.SendCmd("FMCosPurchase",FUNCIDS._fid_fmCosPurchase,
		hdev+","+ucKeyID+","+value+","+terminalID+","+pbPurchaseKey);}
	FWCosGetBalance=function(hdev){return this.SendCmd("FMCosGetBalance",FUNCIDS._fid_fmCosGetBalance,hdev);}
	FWCosUpdateKey=function(hdev,pbOldKey,pbNewKey,bKeyType){return this.SendCmd("FMCosUpdateKey",FUNCIDS._fid_fmCosUpdateKey,
		hdev+","+pbOldKey+","+pbNewKey+","+bKeyType);}
	FWCosUpdatePin=function(hdev,pbOldPin,pbNewPin){return this.SendCmd("FMCosUpdatePin",FUNCIDS._fid_fmCosUpdatePin, 
		hdev+","+pbOldPin+","+pbNewPin);}
	FWCosPinReload=function(hdev,pbNewPin,pbReloadKey){return this.SendCmd("FMCosPinReload",FUNCIDS._fid_fmCosPinReload,
		hdev+","+pbNewPin+","+pbReloadKey);}
	FWCosPinUnlock=function(hdev,pbPin,pbUnlockKey){return this.SendCmd("FMCosPinUnlock",FUNCIDS._fid_fmCosPinUnlock,
		hdev+","+pbPin+","+pbUnlockKey);}

    authen_desfire=function(hdev,keyNo,key){return this.SendCmd("authen_desfire",FUNCIDS._fid_desfire_authen,
		hdev+","+keyNo+","+key);}
    authen_desfire_aes=function(hdev,keyNo,key){return this.SendCmd("authen_desfire_aes",FUNCIDS._fid_desfire_authen_aes,
		hdev+","+keyNo+","+key);}
    desfire_getVer=function(hdev){return this.SendCmd("desfire_getVer",FUNCIDS._fid_desfire_getVer,hdev);}
    desfire_getAIDs=function(hdev){return this.SendCmd("desfire_getAIDs",FUNCIDS._fid_desfire_getAIDs,hdev);}
    desfire_selectApp=function(hdev,strAID){return this.SendCmd("desfire_selectApp",FUNCIDS._fid_desfire_selectApp,
		hdev+","+strAID);}
    desfire_getKeySetting=function(hdev){return this.SendCmd("desfire_getKeySetting",FUNCIDS._fid_desfire_getKeySetting,hdev);}
    desfire_getKeyVer=function(hdev,keyNo){return this.SendCmd("desfire_getKeyVer",FUNCIDS._fid_desfire_getKeyVer,
		hdev+","+keyNo);}
    desfire_createApp=function(hdev,strAID,keySetting,numberOfKey){return this.SendCmd("desfire_createApp",FUNCIDS._fid_desfire_createApp,
		hdev+","+strAID+","+keySetting+","+numberOfKey);}
    desfire_delAID=function(hdev,strAID){return this.SendCmd("desfire_delAID",FUNCIDS._fid_desfire_delAID,
		hdev+","+strAID);}
    desfire_changeKeySetting=function(hdev,keySetting,strSessionKey){return this.SendCmd("desfire_changeKeySetting",FUNCIDS._fid_desfire_changeKeySetting,
		hdev+","+keySetting+","+strSessionKey);}
    desfire_changeKey=function(hdev,strSessionKey,strCurKey, iKeyNo, strNewKey){return this.SendCmd("desfire_changeKey",FUNCIDS._fid_desfire_changeKey,
		hdev+","+strSessionKey+","+strCurKey+","+iKeyNo+","+strNewKey);}
    desfire_changeKey_aes=function(hdev,strSessionKey,strCurKey, iKeyNo, strNewKey,iKeyVer){return this.SendCmd("desfire_changeKey_aes",FUNCIDS._fid_desfire_changeKey_aes,
		hdev+","+strSessionKey+","+strCurKey+","+iKeyNo+","+strNewKey+","+iKeyVer);}
    desfire_getFileIDs=function(hdev){return this.SendCmd("desfire_getFileIDs",FUNCIDS._fid_desfire_getFileIDs,
		hdev);}
    desfire_getFileProper=function(hdev,iFileID){return this.SendCmd("desfire_getFileProper",FUNCIDS._fid_desfire_getFileProper,
		hdev+","+iFileID);}
    desfire_changeFileSetting=function(hdev,iFileNo,iSetting,strAccessRight,strSessionKey){return this.SendCmd("desfire_changeFileSetting",FUNCIDS._fid_desfire_changeFileSetting,
		hdev+","+iFileNo+","+iSetting+","+strAccessRight+","+strSessionKey);}
    desfire_createDataFile=function(hdev,iFileNo,iSetting,strAccessRight,iFileSize){return this.SendCmd("desfire_createDataFile",FUNCIDS._fid_desfire_createDataFile,
		hdev+","+iFileNo+","+iSetting+","+strAccessRight+","+iFileSize);}
    desfire_createBackupDataFile=function(hdev,iFileNo,iSetting,strAccessRight,iFileSize){return this.SendCmd("desfire_createBackupDataFile",FUNCIDS._fid_desfire_createBackupDataFile,
		hdev+","+iFileNo+","+iSetting+","+strAccessRight+","+iFileSize);}
    desfire_createValueFile=function(hdev,iFileNo,iSetting,strAccessRight,iMinLimit,iMaxLimit,iInitVal,iCreditEn){return this.SendCmd("desfire_createValueFile",FUNCIDS._fid_desfire_createValueFile,
		hdev+","+iFileNo+","+iSetting+","+strAccessRight+","+iMinLimit+","+iMaxLimit+","+iInitVal+","+iCreditEn);}
    desfire_createCsyRecord=function(hdev,iFileNo,iSetting,strAccessRight,iRecordSize,iMaxNum){return this.SendCmd("desfire_createCsyRecord",FUNCIDS._fid_desfire_createCsyRecord,
		hdev+","+iFileNo+","+iSetting+","+strAccessRight+","+iRecordSize+","+iMaxNum);}
    desfire_delFile=function(hdev,iFileNo){return this.SendCmd("desfire_delFile",FUNCIDS._fid_desfire_delFile,
		hdev+","+iFileNo);}
    desfire_write=function(hdev,iFileNo,iOffset,strData,strSessionKey){return this.SendCmd("desfire_write",FUNCIDS._fid_desfire_write,
		hdev+","+iFileNo+","+iOffset+","+strData+","+strSessionKey);}
    desfire_read=function(hdev,iFileNo,iOffset,iDataLen,strSessionKey){return this.SendCmd("desfire_read",FUNCIDS._fid_desfire_read,
		hdev+","+iFileNo+","+iOffset+","+iDataLen+","+strSessionKey);}
    desfire_getValue=function(hdev,iFileNo,strSessionKey){return this.SendCmd("desfire_getValue",FUNCIDS._fid_desfire_getValue,
		hdev+","+iFileNo+","+strSessionKey);}
    desfire_credit=function(hdev,iFileNo,iValue,strSessionKey){return this.SendCmd("desfire_credit",FUNCIDS._fid_desfire_credit,
		hdev+","+iFileNo+","+iValue+","+strSessionKey);}
    desfire_debit=function(hdev,iFileNo,iValue,strSessionKey){return this.SendCmd("desfire_debit",FUNCIDS._fid_desfire_debit,
		hdev+","+iFileNo+","+iValue+","+strSessionKey);}
    desfire_writeRecord=function(hdev,iFileNo,iOffset,strData,strSessionKey){return this.SendCmd("desfire_writeRecord",FUNCIDS._fid_desfire_writeRecord,
		hdev+","+iFileNo+","+iOffset+","+strData+","+strSessionKey);}
    desfire_readRecord=function(hdev,iFileNo,iOffset,iNumRec,strSessionKey){return this.SendCmd("desfire_readRecord",FUNCIDS._fid_desfire_readRecord,
		hdev+","+iFileNo+","+iOffset+","+iNumRec+","+strSessionKey);}
    desfire_clearRecord=function(hdev,iFileNo){return this.SendCmd("desfire_clearRecord",FUNCIDS._fid_desfire_clearRecord,
		hdev+","+iFileNo);}
    desfire_commitTransfer=function(hdev){return this.SendCmd("desfire_commitTransfer",FUNCIDS._fid_desfire_commitTransfer,
		hdev);}
    desfire_abortTransfer=function(hdev){return this.SendCmd("desfire_abortTransfer",FUNCIDS._fid_desfire_abortTransfer,
		hdev);}
    desfire_formatPICC=function(hdev){return this.SendCmd("desfire_formatPICC",FUNCIDS._fid_desfire_formatPICC,
		hdev);}

	icode_inventory=function(hdev,findMode,AFI,maskLen){return this.SendCmd("icode_inventory",FUNCIDS._fid_icode_inventory,
		hdev+","+findMode+","+AFI+","+maskLen);}
	icode_select_uid=function(hdev,flags,UID){return this.SendCmd("icode_select_uid",FUNCIDS._fid_icode_select_uid,
		hdev+","+flags+","+UID);}
	icode_readblock=function(hdev,flags,startblock,blocknum,UID){return this.SendCmd("icode_readblock",FUNCIDS._fid_icode_readblockAsStr,
		hdev+","+flags+","+startblock+","+blocknum+","+UID);}
	icode_readblock_hex=function(hdev,flags,startblock,blocknum,UID){return this.SendCmd("icode_readblock_hex",FUNCIDS._fid_icode_readblockAsHex,
		hdev+","+flags+","+startblock+","+blocknum+","+UID);}
	icode_writeblock=function(hdev,flags,startblock,blocknum,UID,wbuffer){return this.SendCmd("icode_writeblock",FUNCIDS._fid_icode_writeblockAsStr,
		hdev+","+flags+","+startblock+","+blocknum+","+UID+","+wbuffer);}
	icode_writeblock_hex=function(hdev,flags,startblock,blocknum,UID,wbuffer){return this.SendCmd("icode_writeblock_hex",FUNCIDS._fid_icode_writeblockAsHex,
		hdev+","+flags+","+startblock+","+blocknum+","+UID+","+wbuffer);}
	icode_lock_block=function(hdev,flags,block,UID){return this.SendCmd("icode_lock_block",FUNCIDS._fid_icode_lock_block,
		hdev+","+flags+","+block+","+UID);}
	icode_get_systemInfo=function(hdev,flags,UID){return this.SendCmd("icode_get_systemInfo",FUNCIDS._fid_icode_get_systemInfo,
		hdev+","+flags+","+UID);}
      
	request_b=function(hdev,mode,aid,channalNum){return this.SendCmd("request_b",FUNCIDS._fid_request_b, hdev + ","+mode+","+aid+","+channalNum);}
	CommandLink_at=function(hdev,slen, strSendCmd){return this.SendCmd("CommandLink_at",FUNCIDS._fid_CommandLink_at, hdev+","+slen+","+strSendCmd);}

    uhf_inventory=function(hdev,scanTime){return this.SendCmd("uhf_inventory",FUNCIDS._fid_uhf_inventory, hdev+","+scanTime);}
    uhf_writeTag=function(hdev,bTagBank,addrWord,lenWord,strPass,strData){return this.SendCmd("uhf_writeTag",FUNCIDS._fid_uhf_writeTag, 
        hdev+","+bTagBank+","+addrWord+","+lenWord+","+strPass+","+strData);}
    uhf_readTag=function(hdev,bTagBank,addrWord,lenWord,strPass){return this.SendCmd("uhf_readTag",FUNCIDS._fid_uhf_readTag, 
        hdev+","+bTagBank+","+addrWord+","+lenWord+","+strPass);}

	config_card = function(hdev,cardType){return this.SendCmd("config_card", FUNCIDS._fid_config_card,
		hdev+","+cardType);}
	writeNFCTag_MiniAppLanucher = function(hdev, tagType, pNFC_message, strPwd, fLock){return this.SendCmd("writeNFCTag",FUNCIDS._fid_writeNFCTag_MiniAppLanucher,
		hdev+","+tagType+","+pNFC_message+","+strPwd+","+fLock);}
	writeNFCTag_Text = function(hdev, tagType, strIANA, strText, textFormat, strPwd, fLock){return this.SendCmd("writeNFCTag_Text",FUNCIDS._fid_writeNFCTag_Text,
		hdev+","+tagType+","+strIANA+","+strText+","+textFormat+","+strPwd+","+fLock);}
	writeNFCTag_URI = function(hdev, tagType, URIType, strURI, strPwd, fLock){return this.SendCmd("writeNFCTag_URI",FUNCIDS._fid_writeNFCTag_URI,
		hdev+","+tagType+","+URIType+","+strURI+","+strPwd+","+fLock);}
	readNFCTag = function(hdev, tagType, textFormat, strPwd){return this.SendCmd("readNFCTag",FUNCIDS._fid_readNFCTag,
		hdev+","+tagType+","+textFormat+","+strPwd);}
	writeNFCTag_ex = function(hdev, tagType, recNum, arrRecs, strPwd, fLock){return this.SendCmd("writeNFCTag_ex",FUNCIDS._fid_writeNFCTag_ex,
		hdev+","+tagType+","+recNum +","+arrRecs+","+strPwd+","+fLock);}
	readNFCTag_ex = function(hdev, tagType, textFormat, strPwd){return this.SendCmd("readNFCTag_ex",FUNCIDS._fid_readNFCTag_ex,
		hdev+","+tagType+","+textFormat+","+strPwd);}

	hexTochar=function(str,strLen){return this.SendCmd("strToHex",FUNCIDS._fid_strToHex, str+","+strLen);}
	charToHex=function(hex,hexLen){return this.SendCmd("hexToStr",FUNCIDS._fid_hexToStr, hex+","+hexLen);}
    crypt=function(hdev,fEn_De,algorithm,src_in_hexStr,iv_hexStr){return this.SendCmd("crypt",FUNCIDS._fid_crypt,hdev+","+fEn_De+","+algorithm+","+src_in_hexStr+","+iv_hexStr);}
	getAutoReturnData=function(hdev,dataFormat){return this.SendCmd("getAutoReturnData", FUNCIDS._fid_getAutoReturnData, hdev+","+dataFormat);}

    iccGetCardState=function(hdev,slot){return this.SendCmd("iccGetCardState",FUNCIDS._fid_iccGetCardState,hdev+","+slot);}
    iccSelCardType=function(hdev,slot,cardType){return this.SendCmd("iccSelCardType",FUNCIDS._fid_iccSelCardType,hdev+","+slot+","+cardType);}
	iccReadErrorCounter=function(hdev,slot){return this.SendCmd("iccReadErrorCounter",FUNCIDS._fid_iccReadErrorCounter,hdev+","+slot);}
    iccVerifyUserPass=function(hdev,slot,strPass){return this.SendCmd("iccVerifyUserPass",FUNCIDS._fid_iccVerifyUserPass,hdev+","+slot+","+strPass);}
    iccReadMem=function(hdev,slot,address,rlen){return this.SendCmd("iccReadMem",FUNCIDS._fid_iccReadMem,hdev+","+slot+","+address+","+rlen);}
    iccWriteMem=function(hdev,slot,address,strHexData){return this.SendCmd("iccWriteMem",FUNCIDS._fid_iccWriteMem,hdev+","+slot+","+address+","+strHexData);}
    iccUpdateUserPass=function(hdev,slot,strPass){return this.SendCmd("iccUpdateUserPass",FUNCIDS._fid_iccUpdateUserPass,hdev+","+slot+","+strPass);}
    iccGetATR=function(hdev,slot){return this.SendCmd("iccGetATR",FUNCIDS._fid_iccGetATR,hdev+","+slot);}
    iccAPDU=function(hdev,slot,strCmd){return this.SendCmd("iccAPDU",FUNCIDS._fid_iccAPDU,hdev+","+slot+","+strCmd);}
    iccSetBaud=function(hdev,slot,baud){return this.SendCmd("iccSetBaud",FUNCIDS._fid_iccSetBaud,hdev+","+slot+","+baud);}
    iccPPS=function(hdev,slot,strPara){return this.SendCmd("iccPPS",FUNCIDS._fid_iccPPS,hdev+","+slot+","+strPara);}

}//class SmartReader {


/////////////////////////////////////////////////////////////////// 2024.7.12 ----------------

