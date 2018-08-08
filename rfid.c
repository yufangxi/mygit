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
/*  ѡ�� ����ͨ��                                                                                                               */
/*                                                                                                                                                      */
/*****************************************************************************/
/* Parameters:                                                                                                                                  */
/*****************************************************************************/
/*                                                                                                                                                      */
/*  number  ����ͨ��                                                                                                               */
/*                                                                                                                                                      */
/*****************************************************************************/
/* Return Values:          �Ƿ�ɹ�                                                                                             */
/*****************************************************************************/
/*                                                                                                                                                      */
/*   NULL                                                                                                                                           */
/*                                                                                                                                                      */
/*****************************************************************************/
unsigned char select_8125(unsigned char number)//��5�����ڹ�ѡ��
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
//��ָ��Ʊ���RFID��ָ�����ݿ�д������
//����:box_id  Ʊ��ţ�ȡֵ��Χ1��2��3��4
//����:block   ָ�������ݿ��
//             0--��ʾдƱ���ţ����ݿ��г���Ϊ4byte��ִ�гɹ�����ֵΪ1��д֮ǰ���ݴ����RFID_info[0]--RFID_info[3]�У�RFID_info����������Ч	
//             1--��ʾд���ݿ�A�� ���ݿ��г���Ϊ48byte��ִ�гɹ�����ֵΪ1��д֮ǰ���ݴ����RFID_info[0]--RFID_info[47]��	
//             2--��ʾд���ݿ�B�� ���ݿ��г���Ϊ48byte��ִ�гɹ�����ֵΪ1��д֮ǰ���ݴ����RFID_info[0]--RFID_info[47]��	 		   
//ִ��ʧ�ܣ�����ֵΪ0

/*****************************************************************************/
/* Parameters:                                                                                                                                  */
/*****************************************************************************/
/*   *data  д����ָ��                                                                                                          */
/*   box_id   Ʊ����                                                                                                              */
/*   block   ���                                                                                                                            */
/*****************************************************************************/
/* Return Values:          �Ƿ�ɹ�                                                                                             */
/*****************************************************************************/
/*                                                                                                                                                      */
/*   NULL                                                                                                                                           */
/*                                                                                                                                                      */
/*****************************************************************************/
unsigned char WriteRFIDBLOCK(unsigned char box_id,unsigned char block,unsigned char *data)
{
    unsigned char timeout=3;        //����3�Σ�����������޿��򱨴�
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
    PiccSelect(SEL_CODE_LV1,card_snr,&i);//������󣬷���ֵ����temp_ak;
    if(i&0x04)
    {
        PiccAnticoll(SEL_CODE_LV2,0,card_snr+4); 
        PiccSelect(SEL_CODE_LV2,card_snr+4,&i);
	}
    //if(mifs_authentication(KEYA,block>>2) != MI_OK)     //�˴��轫����Ŀ��Ϊ��Ӧ������
    if(PiccAuthKey(KEYA,card_snr,Nkey_b,block) != STATUS_COMM_OK)     //�˴��轫����Ŀ��Ϊ��Ӧ������
        return RFID_iden_err;      //��֤��ǰ���Ӧ������
    if(PiccWrite(block,data) != STATUS_COMM_OK)	
        return RW_RFID_err;

    return com_ok;
}


/*****************************************************************************/
/* Function Description:                                                                                                                      */
/*****************************************************************************/
//��ȡָ��Ʊ���RFID��ָ�����ݿ������
//����:box_id  Ʊ��ţ�ȡֵ��Χ1��2��3
//����:block   ָ�������ݿ��
//             0--��ʾ��ȡƱ���ţ����ݿ��г���Ϊ4byte��ִ�гɹ�����ֵΪ1����ȡ�����ݴ����RFID_info[0]--RFID_info[3]�У�RFID_info����������Ч	
//             1--��ʾ��ȡ���ݿ�A�� ���ݿ��г���Ϊ48byte��ִ�гɹ�����ֵΪ1����ȡ�����ݴ����RFID_info[0]--RFID_info[47]��	
//             2--��ʾ��ȡ���ݿ�B�� ���ݿ��г���Ϊ48byte��ִ�гɹ�����ֵΪ1����ȡ�����ݴ����RFID_info[0]--RFID_info[47]��	 		   
//ִ��ʧ�ܣ�����ֵΪ0
/*****************************************************************************/
/* Parameters:                                                                                                                                  */
/*****************************************************************************/
/*   box_id   Ʊ����                                                                                                              */
/*   block   ���                                                                                                                            */
/*   *data   ����Ŀ�����                                                                                                   */
/*****************************************************************************/
/* Return Values:          �Ƿ�ɹ�                                                                                             */
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
    PiccSelect(SEL_CODE_LV1,card_snr,&i);//������󣬷���ֵ����temp_ak;
    if(i&0x04)
    {
        PiccAnticoll(SEL_CODE_LV2,0,card_snr+4); 
        PiccSelect(SEL_CODE_LV2,card_snr+4,&i);
    }
   // if(mifs_authentication(KEYA,block>>2) != MI_OK)     //�˴��轫����Ŀ��Ϊ��Ӧ������
    if(PiccAuthKey(KEYA,card_snr,Nkey_b,block) != STATUS_COMM_OK)     //�˴��轫����Ŀ��Ϊ��Ӧ������
        return RFID_iden_err;      //��֤��ǰ���Ӧ������
    //���϶�����˳����ɺ󷽿ɽ��ж�д
    if(PiccRead(block,data) != STATUS_COMM_OK)
        return RW_RFID_err;

    return com_ok;
}


/*****************************************************************************/
/* Function Description:                                                                                                                      */
/*****************************************************************************/
//��ȡָ��Ʊ���RFID��ָ�����ݿ������
//����:box_id  Ʊ��ţ�ȡֵ��Χ1��2��3
//����:block   ָ�������ݿ��
//             0--��ʾ��ȡƱ���ţ����ݿ��г���Ϊ4byte��ִ�гɹ�����ֵΪ1����ȡ�����ݴ����RFID_info[0]--RFID_info[3]�У�RFID_info����������Ч	
//             1--��ʾ��ȡ���ݿ�A�� ���ݿ��г���Ϊ48byte��ִ�гɹ�����ֵΪ1����ȡ�����ݴ����RFID_info[0]--RFID_info[47]��	
//             2--��ʾ��ȡ���ݿ�B�� ���ݿ��г���Ϊ48byte��ִ�гɹ�����ֵΪ1����ȡ�����ݴ����RFID_info[0]--RFID_info[47]��	 		   
//ִ��ʧ�ܣ�����ֵΪ0
/*****************************************************************************/
/* Parameters:                                                                                                                                  */
/*****************************************************************************/
/*   box_id   Ʊ����                                                                                                              */
/*   sector   ���                                                                                                                          */
/*   *data   д������                                                                                                               */
/*****************************************************************************/
/* Return Values:          �Ƿ�ɹ�                                                                                             */
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
//��ȡָ��Ʊ���RFID��ָ�����ݿ������
//����:box_id  Ʊ��ţ�ȡֵ��Χ1��2��3
//����:block   ָ�������ݿ��
//             0--��ʾ��ȡƱ���ţ����ݿ��г���Ϊ4byte��ִ�гɹ�����ֵΪ1����ȡ�����ݴ����RFID_info[0]--RFID_info[3]�У�RFID_info����������Ч	
//             1--��ʾ��ȡ���ݿ�A�� ���ݿ��г���Ϊ48byte��ִ�гɹ�����ֵΪ1����ȡ�����ݴ����RFID_info[0]--RFID_info[47]��	
//             2--��ʾ��ȡ���ݿ�B�� ���ݿ��г���Ϊ48byte��ִ�гɹ�����ֵΪ1����ȡ�����ݴ����RFID_info[0]--RFID_info[47]��	 		   
//ִ��ʧ�ܣ�����ֵΪ0
/*****************************************************************************/
/* Parameters:                                                                                                                                  */
/*****************************************************************************/
/*   box_id   Ʊ����                                                                                                              */
/*   sector   ���                                                                                                                           */
/*   *data  ��������                                                                                                                */
/*****************************************************************************/
/* Return Values:          �Ƿ�ɹ�                                                                                             */
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
//��ȡָ��Ʊ���RFID��ָ�����ݿ������
//����:box_id  Ʊ��ţ�ȡֵ��Χ1��2��3
//����:block   ָ�������ݿ��
//             0--��ʾ��ȡƱ���ţ����ݿ��г���Ϊ4byte��ִ�гɹ�����ֵΪ1����ȡ�����ݴ����RFID_info[0]--RFID_info[3]�У�RFID_info����������Ч	
//             1--��ʾ��ȡ���ݿ�A�� ���ݿ��г���Ϊ48byte��ִ�гɹ�����ֵΪ1����ȡ�����ݴ����RFID_info[0]--RFID_info[47]��	
//             2--��ʾ��ȡ���ݿ�B�� ���ݿ��г���Ϊ48byte��ִ�гɹ�����ֵΪ1����ȡ�����ݴ����RFID_info[0]--RFID_info[47]��	 		   
//ִ��ʧ�ܣ�����ֵΪ0
/*****************************************************************************/
/* Parameters:                                                                                                                                  */
/*****************************************************************************/
/*   box_id   Ʊ����                                                                                                              */
/*   *data   д������                                                                                                               */
/*****************************************************************************/
/* Return Values:          �Ƿ�ɹ�                                                                                             */
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

