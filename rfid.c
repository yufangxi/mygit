/*****************************************************************************/
/*                                                                                                                                                      */
/*    Copyright (C) - LEGATE Intelligent Equipment - All rights reserved                                                */
/*                                                                                                                                                      */
/*****************************************************************************/
/*                                                                                                                                                      */
/*  Except if expressly provided in a dedicated License Agreement, you are                                           */
/*  not authorized to:                                                                                                                         */
/*                                                                                                                                                      */
/*  1. Use, copy, modify or transfer this software component, module or                                             */
/*  product, including any accompanying electronic or paper documentation                                          */
/*  (together, the "Software").                                                                                                            */
/*                                                                                                                                                       */
/*  2. Remove any product identification, copyright, proprietary notices or                                            */
/*  labels from the Software.                                                                                                               */
/*                                                                                                                                                      */
/*  3. Modify, reverse engineer, decompile, disassemble or otherwise attempt                                      */
/*  to reconstruct or discover the source code, or any parts of it, from the                                           */
/*  binaries of the Software.                                                                                                                */
/*                                                                                                                                                       */
/*  4. Create derivative works based on the Software (e.g. incorporating the                                        */
/*  Software in another software or commercial product or service without a                                        */
/*  proper license).                                                                                                                              */
/*                                                                                                                                                      */
/*  By installing or using the "Software", you confirm your acceptance of the                                        */
/*  hereabove terms and conditions.                                                                                                   */
/*                                                                                                                                                      */
/*****************************************************************************/

/*****************************************************************************/
/*  History:                                                                                                                                        */
/*****************************************************************************/
/*  Date       * Author          * Changes                                                                                               */
/*****************************************************************************/
/*  2014-4-15 * qiao.chen      * Creation of the file                                                                         */
/*             *                 *                                                                                                                    */
/*****************************************************************************/
/*  Target : M64A                                                                                                                               */
/*  Crystal: 11.0592Mhz                                                                                                                              */
/*****************************************************************************/


/*****************************************************************************/
/*                                                                                                                                                      */
/*  Include Files                                                                                                                                   */
/*                                                                                                                                                      */
/*****************************************************************************/

#include "rfid.h"
//#include "zlg500B.h"
#include "main.h"
#include "ZLG522S_Mifare.h"
#include "StatusCode.h"
#include "Reg.h"
#include <string.h>

unsigned char Nkey_a[6]    = {0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5};
unsigned char Nkey_b[6]    = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

/*****************************************************************************/
/* Function Description:                                                                                                                      */
/*****************************************************************************/
/*  选择 串口通道                                                                                                               */
/*                                                                                                                                                      */
/*****************************************************************************/
/* Parameters:                                                                                                                                  */
/*****************************************************************************/
/*                                                                                                                                                      */
/*  number  串口通道                                                                                                               */
/*                                                                                                                                                      */
/*****************************************************************************/
/* Return Values:          是否成功                                                                                             */
/*****************************************************************************/
/*                                                                                                                                                      */
/*   NULL                                                                                                                                           */
/*                                                                                                                                                      */
/*****************************************************************************/
unsigned char select_8125(unsigned char number)//有5个串口供选择
{
    switch(number)
    {
        case 1:                     //HOP1
            SETB_STADD0;
            SETB_STADD1;
            CLR_STADD2;
            break;
        case 2:                     //HOP2
            SETB_STADD0;
            CLR_STADD1;
            CLR_STADD2;
            break;
        case 3:                     //TAG1
            CLR_STADD0;
            SETB_STADD1;
            CLR_STADD2;
            break;
        case 4:                     //TAG2
            CLR_STADD0;
            SETB_STADD1;
            CLR_STADD2;
            break;  
        default:
            break;
    }
    if(number>0 && number<5) 
        return 1;
    else
        return 0;
}



/*****************************************************************************/
/* Function Description:                                                                                                                      */
/*****************************************************************************/
//在指定票箱的RFID的指定数据块写入数据
//参数:box_id  票箱号，取值范围1，2，3，4
//参数:block   指定的数据块号
//             0--表示写票箱编号，数据块中长度为4byte，执行成功返回值为1，写之前数据存放在RFID_info[0]--RFID_info[3]中，RFID_info数组其他无效	
//             1--表示写数据块A， 数据块中长度为48byte，执行成功返回值为1，写之前数据存放在RFID_info[0]--RFID_info[47]中	
//             2--表示写数据块B， 数据块中长度为48byte，执行成功返回值为1，写之前数据存放在RFID_info[0]--RFID_info[47]中	 		   
//执行失败，返回值为0

/*****************************************************************************/
/* Parameters:                                                                                                                                  */
/*****************************************************************************/
/*   *data  写数据指针                                                                                                          */
/*   box_id   票箱编号                                                                                                              */
/*   block   块号                                                                                                                            */
/*****************************************************************************/
/* Return Values:          是否成功                                                                                             */
/*****************************************************************************/
/*                                                                                                                                                      */
/*   NULL                                                                                                                                           */
/*                                                                                                                                                      */
/*****************************************************************************/
unsigned char WriteRFIDBLOCK(unsigned char box_id,unsigned char block,unsigned char *data)
{
    unsigned char timeout=3;        //请求3次，如果都发现无卡则报错
    unsigned char card_snr[8];
    unsigned char i;
    unsigned char tagType[2];
    if(select_8125(box_id) == 0) 
        return RW_RFID_err;
    PCDConfig();
    PiccSetTX(box_id-2);
    while(PiccRequest(REQ_STD, tagType) != STATUS_COMM_OK)
    {
        timeout--;
        if(timeout == 0)
        {
            return no_RFID_card;
        }
    }
    PiccAnticoll(SEL_CODE_LV1,0,card_snr);
    PiccSelect(SEL_CODE_LV1,card_snr,&i);//调用完后，返回值放在temp_ak;
    if(i&0x04)
    {
        PiccAnticoll(SEL_CODE_LV2,0,card_snr+4); 
        PiccSelect(SEL_CODE_LV2,card_snr+4,&i);
	}
    //if(mifs_authentication(KEYA,block>>2) != MI_OK)     //此处需将申请的块变为对应的扇区
    if(PiccAuthKey(KEYA,card_snr,Nkey_b,block) != STATUS_COMM_OK)     //此处需将申请的块变为对应的扇区
        return RFID_iden_err;      //验证当前块对应的扇区
    if(PiccWrite(block,data) != STATUS_COMM_OK)	
        return RW_RFID_err;

    return com_ok;
}


/*****************************************************************************/
/* Function Description:                                                                                                                      */
/*****************************************************************************/
//读取指定票箱的RFID的指定数据块的数据
//参数:box_id  票箱号，取值范围1，2，3
//参数:block   指定的数据块号
//             0--表示读取票箱编号，数据块中长度为4byte，执行成功返回值为1，读取的数据存放在RFID_info[0]--RFID_info[3]中，RFID_info数组其他无效	
//             1--表示读取数据块A， 数据块中长度为48byte，执行成功返回值为1，读取的数据存放在RFID_info[0]--RFID_info[47]中	
//             2--表示读取数据块B， 数据块中长度为48byte，执行成功返回值为1，读取的数据存放在RFID_info[0]--RFID_info[47]中	 		   
//执行失败，返回值为0
/*****************************************************************************/
/* Parameters:                                                                                                                                  */
/*****************************************************************************/
/*   box_id   票箱编号                                                                                                              */
/*   block   块号                                                                                                                            */
/*   *data   读完的块数据                                                                                                   */
/*****************************************************************************/
/* Return Values:          是否成功                                                                                             */
/*****************************************************************************/
/*                                                                                                                                                      */
/*   NULL                                                                                                                                           */
/*                                                                                                                                                      */
/*****************************************************************************/
unsigned char ReadRFIDBLOCK(unsigned char box_id,unsigned char block,unsigned char *data)
{
    unsigned char i;
    unsigned char timeout=3;
    unsigned char card_snr[8];
    unsigned char tagType[2];
    if(select_8125(box_id) == 0) 
        return RW_RFID_err;
    PiccSetTX(box_id-2);
    while(PiccRequest(REQ_STD, tagType) != STATUS_COMM_OK)
    {
        timeout--;
        if(timeout == 0)
        {
            return no_RFID_card;
        }
    }
    PiccAnticoll(SEL_CODE_LV1,0,card_snr);
    PiccSelect(SEL_CODE_LV1,card_snr,&i);//调用完后，返回值放在temp_ak;
    if(i&0x04)
    {
        PiccAnticoll(SEL_CODE_LV2,0,card_snr+4); 
        PiccSelect(SEL_CODE_LV2,card_snr+4,&i);
    }
   // if(mifs_authentication(KEYA,block>>2) != MI_OK)     //此处需将申请的块变为对应的扇区
    if(PiccAuthKey(KEYA,card_snr,Nkey_b,block) != STATUS_COMM_OK)     //此处需将申请的块变为对应的扇区
        return RFID_iden_err;      //验证当前块对应的扇区
    //以上都按照顺序完成后方可进行读写
    if(PiccRead(block,data) != STATUS_COMM_OK)
        return RW_RFID_err;

    return com_ok;
}


/*****************************************************************************/
/* Function Description:                                                                                                                      */
/*****************************************************************************/
//读取指定票箱的RFID的指定数据块的数据
//参数:box_id  票箱号，取值范围1，2，3
//参数:block   指定的数据块号
//             0--表示读取票箱编号，数据块中长度为4byte，执行成功返回值为1，读取的数据存放在RFID_info[0]--RFID_info[3]中，RFID_info数组其他无效	
//             1--表示读取数据块A， 数据块中长度为48byte，执行成功返回值为1，读取的数据存放在RFID_info[0]--RFID_info[47]中	
//             2--表示读取数据块B， 数据块中长度为48byte，执行成功返回值为1，读取的数据存放在RFID_info[0]--RFID_info[47]中	 		   
//执行失败，返回值为0
/*****************************************************************************/
/* Parameters:                                                                                                                                  */
/*****************************************************************************/
/*   box_id   票箱编号                                                                                                              */
/*   sector   块号                                                                                                                          */
/*   *data   写块数据                                                                                                               */
/*****************************************************************************/
/* Return Values:          是否成功                                                                                             */
/*****************************************************************************/
/*                                                                                                                                                      */
/*   NULL                                                                                                                                           */
/*                                                                                                                                                      */
/*****************************************************************************/
unsigned char WriteRFIDSECTOR(unsigned char box_id,unsigned char sector,unsigned char len,unsigned char *data)
{
    unsigned char i;
    unsigned char err;
    unsigned char num;
    if(len == 0)
    {
        return RW_RFID_err;
    }
    if(len>0 && len <=16)
        num = 1;
    else if(len > 16 && len <= 32)
        num = 2;
    else if(len > 32)
        num = 3;
    for(i=0;i<num;i++)
    {
        err = WriteRFIDBLOCK(box_id,(sector<<2)+i,data+i*16);
        if(err != com_ok)
            break;
    }
    return err;
}


/*****************************************************************************/
/* Function Description:                                                                                                                      */
/*****************************************************************************/
//读取指定票箱的RFID的指定数据块的数据
//参数:box_id  票箱号，取值范围1，2，3
//参数:block   指定的数据块号
//             0--表示读取票箱编号，数据块中长度为4byte，执行成功返回值为1，读取的数据存放在RFID_info[0]--RFID_info[3]中，RFID_info数组其他无效	
//             1--表示读取数据块A， 数据块中长度为48byte，执行成功返回值为1，读取的数据存放在RFID_info[0]--RFID_info[47]中	
//             2--表示读取数据块B， 数据块中长度为48byte，执行成功返回值为1，读取的数据存放在RFID_info[0]--RFID_info[47]中	 		   
//执行失败，返回值为0
/*****************************************************************************/
/* Parameters:                                                                                                                                  */
/*****************************************************************************/
/*   box_id   票箱编号                                                                                                              */
/*   sector   块号                                                                                                                           */
/*   *data  读块数据                                                                                                                */
/*****************************************************************************/
/* Return Values:          是否成功                                                                                             */
/*****************************************************************************/
/*                                                                                                                                                      */
/*   NULL                                                                                                                                           */
/*                                                                                                                                                      */
/*****************************************************************************/
unsigned char ReadRFIDSECTOR(unsigned char box_id,unsigned char sector,unsigned char *data)
{
    unsigned char Read_data[48]={0};
    unsigned char i;
    unsigned char err;
    for(i=0;i<3;i++)
    {
        err = ReadRFIDBLOCK(box_id,(sector<<2)+i,&Read_data[i*16]);
        if(err != com_ok)
            break;
    }
    memcpy(data,Read_data,48);
    return err;
}


/*****************************************************************************/
/* Function Description:                                                                                                                     */
/*****************************************************************************/
//读取指定票箱的RFID的指定数据块的数据
//参数:box_id  票箱号，取值范围1，2，3
//参数:block   指定的数据块号
//             0--表示读取票箱编号，数据块中长度为4byte，执行成功返回值为1，读取的数据存放在RFID_info[0]--RFID_info[3]中，RFID_info数组其他无效	
//             1--表示读取数据块A， 数据块中长度为48byte，执行成功返回值为1，读取的数据存放在RFID_info[0]--RFID_info[47]中	
//             2--表示读取数据块B， 数据块中长度为48byte，执行成功返回值为1，读取的数据存放在RFID_info[0]--RFID_info[47]中	 		   
//执行失败，返回值为0
/*****************************************************************************/
/* Parameters:                                                                                                                                  */
/*****************************************************************************/
/*   box_id   票箱编号                                                                                                              */
/*   *data   写块数据                                                                                                               */
/*****************************************************************************/
/* Return Values:          是否成功                                                                                             */
/*****************************************************************************/
/*                                                                                                                                                      */
/*   NULL                                                                                                                                           */
/*                                                                                                                                                      */
/*****************************************************************************/
unsigned char ReadRFID_Serial_Number(unsigned char box_id,unsigned char *data)
{
    unsigned char timeout=3;
    unsigned char tagType[2];
    unsigned char card_snr[6];
    if(select_8125(box_id) == 0) 
        return RW_RFID_err;
    PiccSetTX(box_id-2);
    while(PiccRequest(REQ_STD, &card_snr[4]) != STATUS_COMM_OK)
    {
        timeout--;
        if(timeout == 0)
        {
            return no_RFID_card;
        }
    }
    PiccAnticoll(SEL_CODE_LV1,0,card_snr);
    memcpy(data,card_snr,6);
    return com_ok;
}

