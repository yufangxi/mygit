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
#ifndef __ZLG522S_MIFARE_H 
#define __ZLG522S_MIFARE_H
//===========================================================================================================
#ifdef __cplusplus
	extern "C" {
#endif
//===========================================================================================================
//#include "Config.h"
#include "variables_def.h"

//===========================================================================================================
#ifdef ZLG522S_MIFARE_GLOBALS
	#define ZLG522S_MIFARE_EXT
#else
	#define ZLG522S_MIFARE_EXT	extern
#endif
//============= �������� ====================================================================================
#define PICC_REQUEST_EN 			1			// ����
#define PICC_ANTICOLL_EN			1			// ����ײ
#define PICC_SELECT_EN				1			// ѡ��
#define PICC_HALT_EN				1			// ����
#define PICC_ACTIVE_TYPEA_EN		1			// A�Ϳ�����

#define PICC_AUTH_E2_EN				1			// Mifare����֤��Կ(E2����Կ��֤)
#define PICC_AUTH_KEY_EN			1			// Mifare����֤��Կ(ֱ����Կ��֤)
#define PICC_READ_EN				1			// ������
#define PICC_WRITE_EN				1			// д����
#define PICC_UL_WRITE_EN			1			// ULд
#define PICC_VALUE_OPER_EN			1			// ֵ�����

#define PICC_RESET_EN				1			// ��Ƭ��λ(ֹͣ�ز�һ��ʱ��)
#define PICC_AUTO_DETEGT_EN			1			// �Զ��������(6�ֽ���Կ)
#define PICC_AUTO_DETEGT_16_EN		0			// �Զ��������(16�ֽ���Կ)
#define PICC_AD_RCV_EN				1			// �жϲ�����Ķ��Զ���������
#define PICC_READ_AD_DT_EN			1			// ���Զ�������ݵ�����
//============= �������� ====================================================================================
//����A�Ϳ�����
#define REQ_STD						0x26		// ����(IDLE ��)������	
#define REQ_ALL						0x52		// ����(ALL  ��)������
#define SEL_CODE_LV1				0x93		// ����ײ/ѡ��ȼ�1������
#define SEL_CODE_LV2				0x95		// ����ײ/ѡ��ȼ�2������
#define SEL_CODE_LV3				0x97		// ����ײ/ѡ��ȼ�3������
#define MIFARE_INCREMENT            0xC1		// ֵ������
#define MIFARE_DECREMENT            0xC0		// ֵ������

#define KEY_A            			0x60		// ��ԿA
#define KEY_B            			0x61		// ��ԿB
//============= A�Ϳ��Զ����������� =======================================================================
#define AD_SERIALOUT				0x01		// �����������
#define AD_INTENABLE				0x02		// �ж�ʹ��
#define AD_CONTINUE					0x04		// �������֮��������
#define AD_HALT						0x08		// ��󽫿�����

#define AD_TX_ALERT					0x00		// TX1,TX2�������
#define AD_TX_ONLYTX1				0x01		// ��TX1���
#define AD_TX_ONLYTX2				0x02		// ��TX2���
#define AD_TX_ALL					0x03		// TX1,TX2ͬʱ���

#define AD_STOP						0x00		// ֹͣ���	
#define AD_REENABLE					0x01		// �������
/*
//============= ȫ�ֱ���/�������� ===========================================================================
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����ԭ��:    unsigned char PiccRequest(unsigned char ucReqCode,unsigned char *pATQ)
// ��������:    ����
// �������:    unsigned char ucReqCode			// �������		
// �������:    unsigned char *pATQ				// �����Ӧ
// �� �� ֵ:    ����ִ�н��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char PiccRequest(unsigned char ucReqCode,unsigned char *pATQ);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����ԭ��:    unsigned char PiccAnticoll( unsigned char ucSelCode,unsigned char ucBcnt,
//											unsigned char *pUID)
// ��������:    ����ײ
// �������:    unsigned char ucSelCode			// ����ײ�ȼ�
//												// SELCODE1	0x93	�ȼ�1
//												// SELCODE2	0x95	�ȼ�2
//												// SELCODE3	0x97	�ȼ�3
//				unsigned char ucBcnt			// ��֪���ŵ�λ����ͨ������Ϊ0
//				unsigned char *pSnr				// ��֪�Ŀ��ţ�����֪�����������
// �������:    unsigned char *pSnr				// ����
// �� �� ֵ:    ����ִ�н��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char PiccAnticoll(unsigned char ucSelCode,unsigned char ucBcnt,unsigned char *pUID);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����ԭ��:    unsigned char PiccSelect(unsigned char ucSelCode,unsigned char *pUID,
//										 unsigned char *pSAK)
// ��������:    ѡ��
// �������:    unsigned char ucSelCode			// ѡ��(����ײ�ȼ�)
//												// SELCODE1	0x93	�ȼ�1
//												// SELCODE2	0x95	�ȼ�2
//												// SELCODE3	0x97	�ȼ�3
//				unsigned char *pUID				// ����
// �������:    unsigned char *pSAK				// ѡ��Ӧ��
// �� �� ֵ:    ����ִ�н��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char PiccSelect(unsigned char ucSelCode,unsigned char *pUID,unsigned char *pSAK);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����ԭ��:    unsigned char PiccHalt()
// ��������:    ������Ŀ�����
// �������:    -	
// �������:    -
// �� �� ֵ:    ����ִ�н��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char PiccHalt(void);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����ԭ��:    unsigned char PiccActiveTypeA(	unsigned char unMode, unsigned char ucReqCode, 
//							  					unsigned char *pATQ, unsigned char *pSAK,
//						      					unsigned char *pUIDLen, unsigned char *pUID))
// ��������:    ģ����Ϣ����
// �������:    unsigned char unMode			// 0 -- ִ�з���ײѭ����1 -- ִֻ��һ�η���ײ
//				unsigned char ucReqCode			// ������	
// �������:    unsigned char *pATQ				// �����Ӧ
//				unsigned char *pSAK				// ���һ��ѡ��Ӧ��
//				unsigned char *pUIDLen			// ���ų���
//				unsigned char *pUID				// ����
// �� �� ֵ:    ����ִ�н��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char PiccActiveTypeA(unsigned char unMode, unsigned char ucReqCode, 
							  unsigned char *pATQ, unsigned char *pSAK,
						      unsigned char *pUIDLen, unsigned char *pUID);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����ԭ��:    unsigned char PiccReadADDT( unsigned char ucMode, unsigned char *pTxDrv, 
//											unsigned char *pATQ, unsigned char *pSAK, 
//											unsigned char *pUIDLen, unsigned char *pUID, 
//											unsigned char *pDataBuf)
// ��������:    ���Զ���������
// �������:    unsigned char ucMode			// 0x00 -- ֹͣ��⣻	0x01 -- �������
// �������:    unsigned char *pTxDrv			// �Ǹ����߼�⵽�Ŀ�
//												// 0x01--��TX1;	0x02--��TX2;	0x03--TX1��TX2
//				unsigned char *pATQ				// �����Ӧ
//				unsigned char *pSAK				// ѡ��Ӧ��
//				unsigned char *pUIDLen			// UID����
//				unsigned char *pUID				// UID
//				unsigned char *pDataBuf			// ����������
// �� �� ֵ:    0x00 -- �ɹ�;	0xFF -- δ��⵽��;	0x9C -- ����δִ��			
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char PiccReadADDT( unsigned char ucMode, unsigned char *pTxDrv, unsigned char *pATQ, 
							unsigned char *pSAK, unsigned char *pUIDLen, 
							unsigned char *pUID, unsigned char *pDataBuf);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����ԭ��:    unsigned char PiccAuthE2(unsigned char ucKeyType, unsigned char *pUID, 
//										  unsigned char ucKeySector, unsigned char ucBlock)
// ��������:    Mifare1����֤�����֤�ɹ����Ժ��ͨ�ű����ܡ�
// ��ڲ���:    unsigned char ucKeyType			// ��Կ���ͣ�KEY_A -- ��ԿA;	KEY_B -- ��ԿB;
//				unsigned char *pUID				// 4�ֽ�UID
//				unsigned char ucKeySector		// ��Կ�������
//				unsigned char ucBlock			// ��֤�Ŀ��
// ���ڲ���:    -
// �� �� ֵ:    STATUS_SUCCESS -- �ɹ�������ֵ -- ʧ�ܡ�
// ˵    ��:	��֤�󣬷��ʸÿ����ڵ�����(��ͬȨ��)����������֤��Կ    
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char PiccAuthE2(unsigned char ucKeyType, unsigned char *pUID,
						 unsigned char ucKeySector, unsigned char ucBlock);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����ԭ��:    unsigned char PiccAuthKey(unsigned char ucKeyType, unsigned char *pUID, 
//										  unsigned char *pKey, unsigned char ucBlock)
// ��������:    Mifare1����֤�����֤�ɹ����Ժ��ͨ�ű����ܡ�
// ��ڲ���:    unsigned char ucKeyType			// ��Կ���ͣ�KEY_A -- ��ԿA;	KEY_B -- ��ԿB;
//				unsigned char *pUID				// 4�ֽ�UID
//				unsigned char *pKey				// 6�ֽ���Կ
//				unsigned char ucBlock			// ��֤�Ŀ��
// ���ڲ���:    -
// �� �� ֵ:    STATUS_SUCCESS -- �ɹ�������ֵ -- ʧ�ܡ�
// ˵    ��:	��֤�󣬷��ʸÿ����ڵ�����(��ͬȨ��)����������֤��Կ    
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char PiccAuthKey(unsigned char ucKeyType, unsigned char *pUID, 
						  unsigned char *pKey, unsigned char ucBlock);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����ԭ��:    unsigned char PiccRead(unsigned char ucBlock, unsigned char *pBuf)
// ��������:    Mifare������
// ��ڲ���:    unsigned char ucBlock			; ���Ŀ��
// ���ڲ���:    unsigned char *pBuf				; ������16�ֽ�����
// �� �� ֵ:    STATUS_SUCCESS -- �ɹ�������ֵ -- ʧ�ܡ�
// ˵    ��:	-   
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char PiccRead(unsigned char ucBlock, unsigned char *pBuf);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����ԭ��:    unsigned char PiccWrite( unsigned char ucBlock, unsigned char *pBfr)
// ��������:    Mifareд����
// ��ڲ���:    unsigned char ucBlock			; д��Ŀ��ַ��
//				unsigned char *pBfr				; 16�ֽ�д���ݻ�������ַ��
// ���ڲ���:    -
// �� �� ֵ:    STATUS_SUCCESS -- �ɹ�������ֵ -- ʧ�ܡ�  
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char PiccWrite(unsigned char ucBlock,unsigned char *pBuf);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����ԭ��:    unsigned char PiccULWrite( unsigned char ucBlock, unsigned char *pBuf)
// ��������:    Mifareд����
// ��ڲ���:    unsigned char ucBlock			; д��Ŀ��ַ��
//				unsigned char *pBfr				; 4�ֽ�д���ݻ�������ַ��
// ���ڲ���:    -
// �� �� ֵ:    STATUS_SUCCESS -- �ɹ�������ֵ -- ʧ�ܡ�   
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char PiccULWrite(unsigned char ucBlock, unsigned char *pBuf);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����ԭ��:    unsigned char PiccValueOper(unsigned char ucOperMode, unsigned char ucSBlock, 
//									unsigned char *pValue, unsigned char ucDBlock)
// ��������:    Mifareֵ��������
// ��ڲ���:    unsigned char ucOperMode,		; ֵ����ģʽ
//				unsigned char ucSBlock			; Ҫ�����Ŀ��ַ��
//				unsigned char *pValue,			; 4�ֽ�Ҫ������ֵ�����ֽ��ڵ͵�ַ��
//				unsigned char ucDBlock			; ֵ������Ŀ�ؿ�
// ���ڲ���:    -
// �� �� ֵ:    STATUS_SUCCESS -- �ɹ�������ֵ -- ʧ�ܡ�  
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char PiccValueOper(unsigned char ucOperMode, unsigned char ucSBlock, 
							unsigned char *pValue, unsigned char ucDBlock);*/
//===========================================================================================================
#ifdef __cplusplus
	}
#endif

#endif			// __ZLG522S_MIFARE_H__

