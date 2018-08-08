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
/*  2013-11-15 * qiao.chen      * Creation of the file                                                                         */
/*             *                 *                                                                                                                    */
/*****************************************************************************/
/*  Target : M64A                                                                                                                               */
/*  Crystal: 16Mhz                                                                                                                              */
/*****************************************************************************/

/*****************************************************************************/
/*                                                                                                                                                      */
/*  Include Files                                                                                                                                   */
/*                                                                                                                                                      */
/*****************************************************************************/
#ifndef __ZLG522S_COMM_H 
#define __ZLG522S_COMM_H
//===========================================================================================================
#ifdef __cplusplus
	extern "C" {
#endif
//===========================================================================================================
//#include "Config.h"
#include "variables_def.h"

//===========================================================================================================
#ifdef ZLG522S_COMM_GLOBALS
	#define	ZLG522S_COMM_EXT
#else
	#define	ZLG522S_COMM_EXT	extern
#endif

#ifndef TRUE
#define TRUE  1
#endif

#ifndef FALSE
#define FALSE 0
#endif

//============= �������� ====================================================================================
// ͨ����������
#define CMD_TYPE_DVC_CONTROL		1			// �豸����������
#define CMD_TYPE_TYPE_A				2			// TypeA(����Mifare��)������				
#define CMD_TYPE_ISO7816			5			// ISO7816������
#define CMD_TYPE_COMM_PROT			6			// ͨ��Э��(����ISO14443-4)������
#define CMD_TYPE_PLUS_CPU			7			// PLUS CPU��(������Mifare��)������
// ����������
#define BAUD_CNT 					8


// ���建������С
#define MAX_SER_SIZE      			64+2+6

#define ZLG522S_DELAY_20MS			2
#define ZLG522S_DELAY_500MS			30
// ͨ����������
#define CMD_TYPE_DVC_CONTROL		1			// �豸����������
#define CMD_TYPE_TYPE_A				2			// TypeA(����Mifare��)������				
#define CMD_TYPE_ISO7816			5			// ISO7816������
#define CMD_TYPE_COMM_PROT			6			// ͨ��Э��(����ISO14443-4)������
#define CMD_TYPE_PLUS_CPU			7			// PLUS CPU��(������Mifare��)������

// ���崮�����ݻ��������ַ���Ԫ����ֵ
#define FRAMELEN					0			// ֡����
#define CMDTYPE						1			// ����
#define COMMAND						2			// ����
#define STATUS						2			// ��Ӧ״̬
#define LENGTH      				3			// ���ݳ���
#define DATA        				4			// ������ʼλ��
#define PRTCLEN						6			// Э���ַ�����

// ͨ��Э�鳣��
#define STX     					0x20
#define ETX     					0x03
#define ACK							0x06

//#define FALSE                      0
//#define TRUE                       1
//===========================================================================================================

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����ԭ��:    void ChangeBaud(unsigned char ucBaudNum)
// ��������:    �ı���ģ��ͨ�ŵĲ�����
// �������:    unsigned char ucBaudNum			// �����ʱ��0��7		
// �������:    -
// ˵    ��:    ����Ӳ�����ƣ��ú���ֻ��ʹ��0��1��2��4��ŵĲ�����
//				0--9600��1--19200��2--28800��3--��4--57600
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SetBaud(unsigned char ucBaudNum);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����ԭ��:    unsigned char ZLG522S_CommInit(void))
// ��������:    ZLG522S����ͨ�Žӿڳ�ʼ��
// �������:    -		
// �������:    
// �� �� ֵ:    ����ִ�н��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char ZLG522S_CommInit(void);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����ԭ��:    bit Ser_Rcv(void)
// ��������:    ���ճ���
// �������:    -		
// �������:    -
// �� �� ֵ:    TRUE--���ճɹ���FALSE--����ʧ��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char Ser_Rcv(void);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����ԭ��:    bit Ser_Send(void)
// ��������:    ���ͳ���
// �������:    -		
// �������:    -
// �� �� ֵ:    TRUE--���ͳɹ���FALSE--����ʧ��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char Ser_Send(void);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����ԭ��:    unsigned char ZLG522S_Cmd(void)
// ��������:    ZLG522Sģ������ִ�к���
// �������:    -		
// �������:    -
// �� �� ֵ:    -
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char ZLG522S_Cmd(void);

//===========================================================================================================
#ifdef __cplusplus
	}
#endif

#endif              // __ZLG522S_COMM_H
