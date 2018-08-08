
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

#ifndef _HEADER_HOPPER_
#define _HEADER_HOPPER_

#define hopper1 1
#define hopper2 2
typedef enum            //ECU �����
{
    SDP_CMD_START = 0,//���ʼ
    SDP_CMD_SW_RESET,//�����λ������
    SDP_CMD_BUILD_VERSION_TIME = 0x10,//�̼�����汾�����ڵ�����
    SDP_CMD_ADDRESS_QUERY,//��ַ��ѯ������
    SDP_CMD_STATE_QUERY,//״̬��ѯ������
    SDP_CMD_VERSION_QUERY,//�̼��汾��ѯ������
    SDP_CMD_LIMIT_QUERY,//���޲�����ѯ������
    SDP_CMD_REALTIME_QUERY,//ʵʱ������ѯ������
    SDP_CMD_ADDRESS_MODIFY = 0x21,//��ַ���ĵ�����
    SDP_CMD_LIMIT_MODIFY = 0x24,//���޲����޸ĵ�����
    SDP_CMD_REALTIME_MODIFY,//ʵʱ�����޸ĵ�����
    SDP_CMD_HD_SELF = 0x40,//Ӳ���Լ������
    SDP_CMD_STOP_HD_SELF,   //ֹͣ�Լ�
    SDP_CMD_CHG = 0x60,//Ӳ�����������
    SDP_CMD_CLR,//Token Ӳ����ҵ�����
    SDP_CMD_STOP_CLR,//ֹͣ�������
    ARR_SDP_CMD_END = 0x7F,//
} enumARR_SDP_CMD;

typedef enum            //HTU ���������
{
    SDP_ACK_START = 0x80,//������Ӧ�����ʼ
    SDP_ACK_CMD_ACK = 0x90,//������Ӧ�������
    SDP_ACK_CMD_INTIME = 0xA0,//��ʱ������Ӧ�������
    SDP_ACK_CMD_UNTIME,//����ʱ������Ӧ�������
    SDP_ACK_ERR = 0xE0,//���ϵ������
    SDP_ACK_MSG_VALID_CHK,//�������ȷ��У���뷴��
    ARR_SDP_ACK_END = 0xFF,//
} enumARR_SDP_ACK;

typedef enum            //HTU ����/״̬����
{
    SDP_ACK_ERR_START = 0,//Ԥ������/״̬
    SDP_ACK_ERR_ADDR_SAME,//��ַ��ͬ����/״̬
    SDP_ACK_ERR_MSG_CHK,//Э��У�����/״̬
    SDP_ACK_ERR_CMD_INVALID,//������Ч�Ĺ���/״̬
    SDP_ACK_ERR_CMD_HOPPER_BUSY,//�����æ����/״̬
    SDP_ACK_ERR_CMD_NOCMD,//�����޷�ʶ�����/״̬
    ARR_SDP_ACK_ERR_END,//��������/״̬
} enumARR_SDP_ACK_ERR;

#define HOP_STX 0x7f     //֡��ʼ��
#define HOP_ETX 0x80     //֡������
typedef struct
{
    //const uint8 HOP_STX = 0x7f;     //֡��ʼ��
    uint8 RSEQ;                 //��ˮ��
    uint8 DESA;              //Ŀ���ַ
    uint8 SRCA;               //Դ��ַ
    uint8 DLEN;                     //���ݳ���
    uint8 INFO;                 //����/ Ӧ��/��Ϣ
    uint8 DAT[50];                  //����
    uint8 BCC;                  //У��
    //const uint8 HOP_ETX = 0x80;    //֡������
}CMD_HOPPER;

#endif
