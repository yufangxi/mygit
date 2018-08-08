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

#include "types.h"

#ifndef _HEADER_MAIN_
#define _HEADER_MAIN_

//
#define CMD_NO_ACTION 0
#define CMD_BOX1SCOOP 1
#define CMD_BOX2SCOOP 2
#define CMD_TICKETSELL 3
#define CMD_TICKETRECYCLE 4

//cmd
#define WXDLE 0X10        //���Ʒ�
#define WXSTX 0X02        //���ݰ���ʼ��־
#define WXETX 0X03        //���ݰ�������־
#define WXEOT 0X04        //ͨѶ��ֹ��־
#define WXENQ 0X05        //����ִ��ȷ��
#define WXACK 0X06        //������ȷ��Ӧ
#define WXNAK 0X15        //���մ����Ӧ

//E2��ַ
#define E2ERR_ADDR 0x22	//E2���ϴ洢�ĵ�ַ
#define E2BOXA_STATUS 0x23	//Ʊ��װж�洢��ַ
#define E2BOXB_STATUS 0x24	//Ʊ��װж�洢��ַ
#define E2BOXC_STATUS 0x25	//Ʊ��װж�洢��ַ
#define ABOX_TICKETS_ADDR 0x30       //AƱ����������ַ
#define BBOX_TICKETS_ADDR 0x80       //BƱ����������ַ
#define CBOX_TICKETS_ADDR 0xD0       //CƱ����������ַ
#define MAX_EE_AREA 10
#define AREA_A 1
#define AREA_B 2
#define AREA_C 3

//��Ʊʱ��
#define DROP_T1  1000
#define DROP_T2  50
#define DCT_T1     20
#define DCT_T2     20
// ��ȡ��Ϣʱ��
#define READ_MAS  3   //2//��״̬��ʱ��60ms
#define INTI_OVER_TIME 250
//һ��ʱ��
#define SECOND  50

typedef struct//�ṹ��
{
	uint32  limit_cnt;
	uint8	limit_en;
}CNT;

typedef union//�����塢������
{
	uint8	status[7];
	struct
	{
		uint8   checkticks1;//Ʊ�������������     0-��Ʊ:1-��Ʊ
		uint8   checkticks2;//Ʊ�������ҿڼ��     0-��Ʊ:1-��Ʊ
		uint8   checkticks3;//Ʊ������Ʊ����     0-��Ʊ:1-��Ʊ
		uint8   checkticks4;//�����1���                    1-��:0-�ض�
		uint8   checkticks5;//�����2���                    1-��:0-�ض�
		uint8   checkticks6;//����
		uint8   checkticks7;//hopper1��λ���                1-��λ:0-δ��λ(����)
		uint8   checkticks8;//hopper2��λ���                1-��λ:0-δ��λ(����)
	}SENSORS_STATUS;
}SENSORS;

typedef struct
{
	uint8	addr;
	uint8	data[4];
}EE_SAVE;

typedef union
{
    uint8   code[53];
    struct
    {
        uint8   len;        //��ǰ���ĳ���
    	uint8	act_code;   //��Ӧ��
    	uint8	result;     //���ؽ��:'e'   'w'   's'
        uint8   err_code;   //���ϴ���
        uint8   info[49];   //������Ϣ
    }MESSAGE;
}RETURN_CODE;

typedef enum //ö��
{
	com_ok = 0,					    //�޴���
	no_card_at_RW_area,		    //�޿���������
	read_clearnum_be_clear,      //δ����Ҷ�ȡ�������
	card_at_RW_area,              //�п����������澯
	box1_non_existent = 0x39,			//AƱ��δ��λ
	box2_non_existent,			//BƱ��δ��λ
	boxA_empty = 0x3c,			    //AƱ���
	boxB_empty,		            //BƱ���
	card_block_at_RW_area = 0x3f,//Ʊ������������Ʊ
	card_block_at_exit_area,		//Ʊ���ڳ�Ʊ�ڿ�Ʊ
	card_block_at_Aexit_area,	//Ʊ����A��Ʊ�ڿ�Ʊ
	AWK_no_card,					//A�ڿ����ڲ���Ʊ��
	BWK_no_card,					//B�ڿ����ڲ���Ʊ��
	equ_busy = 0x4a,				        //�豸æ
	clr_err,                        //���ʧ��
	card_block_at_Bexit_area = 0x62,	//Ʊ����B��Ʊ�ڿ�Ʊ
	checkticks_err,				//ͨ������������
	sole1_err,                     //�����1����
	sole2_err,                     //�����2����
	rf232A_err,                    //����A����
	rf232B_err,                    //����B����
    invalid_parameter=0x31,//������Ч
}CMD_STATUS;

typedef struct
{
    uint8 re_data[20];              //���յ�������
    uint8 re_index;                 //���ռ���
    uint8 re_flag;                  //�Ƿ������ɱ�־1:�������0:δ���
}RESEIVE;




#endif

