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
#ifndef __ZLG522S_H 
#define __ZLG522S_H
//===========================================================================================================
#ifdef __cplusplus
	extern "C" {
#endif
//===========================================================================================================
//#include "Config.h"
#include "variables_def.h"

//===========================================================================================================
#ifdef ZLG522S_GLOBALS
	#define ZLG522S_EXT
#else
	#define ZLG522S_EXT	extern
#endif
//============= �������� ====================================================================================
#define GET_DVC_INFO_EN				1			// ��ȡģ����Ϣ
#define PCD_CONFIG_EN				1			// ���ö�доƬ
#define PCD_CLOSE_EN				1			// �رն�доƬ
#define PCD_LOAD_KEY_EN				1			// װ��6�ֽ���Կ
#define PCD_LOAD_KEY_16_EN			1			// װ��16�ֽ���Կ
#define PCD_WRITE_REG_EN			1			// д�Ĵ���
#define PCD_READ_REG_EN				1			// ���Ĵ���
#define PCD_SET_BAUD_EN				1			// ����ģ��UARTͨ�Ų�����
#define PCD_BIND_EN					1			// ģ���

#define PICC_RESET_EN				1			// ��Ƭ��λ(ֹͣ�ز�һ��ʱ��)
#define PICC_AUTO_DETEGT_EN			1			// �Զ��������(6�ֽ���Կ)
#define PICC_AUTO_DETEGT_16_EN		0			// �Զ��������(16�ֽ���Կ)
#define PICC_AD_RCV_EN				1			// �жϲ�����Ķ��Զ���������
#define PICC_READ_AD_DT_EN			1			// ���Զ�������ݵ�����
#define PICC_Set_TX_EN                1         //��������

//============= �������� ====================================================================================
//����A�Ϳ�����
#define KEY_A						0x60
#define KEY_B						0x61
#define ISO14443A					0x00
#define ISO14443B					0x80

//============= ȫ�ֱ���/�������� =================================================================
///////////////////////////////////////////////////////////////////////////////////////////////////
// ����ԭ��:    unsigned char GetDvcInfo(unsigned char *pDvcInfo)
// ��������:    ��ȡģ����Ϣ
// �������:    -		
// �������:    unsigned char *pDvcInfo			// ģ����Ϣ
// �� �� ֵ:    ����ִ�н��
///////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char GetDvcInfo(unsigned char *pDvcInfo);

///////////////////////////////////////////////////////////////////////////////////////////////////
// ����ԭ��:    unsigned char PCDConfig()
// ��������:    ���ö�д��оƬ
// �������:    -		
// �������:    
// �� �� ֵ:    ����ִ�н��
///////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char PCDConfig(void);

///////////////////////////////////////////////////////////////////////////////////////////////////
// ����ԭ��:    unsigned char PCDClose()
// ��������:    ģ����Ϣ����
// �������:    -		
// �������:    
// �� �� ֵ:    ����ִ�н��
///////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char PCDClose(void);

///////////////////////////////////////////////////////////////////////////////////////////////////
// ����ԭ��:    unsigned char PCDLoadKey(unsigned char ucKeyMode, unsigned char ucKeySNr,
//										 unsigned char *pKey)
// ��������:    װ����Կ
// �������:    unsigned char ucKeyMode			// ��Կģʽ	KEY_A;KEY_B	
//				unsigned char ucKeySNr			// ��Կ�������0~3
//				unsigned char *pKey				// 6�ֽ���Կ
// �������:    -
// �� �� ֵ:    ����ִ�н��
// ˵    ��:	���������ԿΪ6�ֽڣ���ģ����Զ���չΪ16�ֽ�
//				Key[16] = pKey[0:5] | pKey[0:5] | pKey[0:3]
///////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char PCDLoadKey(unsigned char ucKeyMode, unsigned char ucKeySNr,
									 unsigned char *pKey);

///////////////////////////////////////////////////////////////////////////////////////////////////
// ����ԭ��:    unsigned char PCDLoadKey16(unsigned char ucKeyMode, unsigned char ucKeySNr,
//										 unsigned char *pKey)
// ��������:    װ����Կ
// �������:    unsigned char ucKeyMode			// ��Կģʽ	KEY_A;KEY_B	
//				unsigned char ucKeySNr			// ��Կ�������0~3
//				unsigned char *pKey				// 16�ֽ���Կ
// �������:    -
// �� �� ֵ:    ����ִ�н��
///////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char PCDLoadKey16(unsigned char ucKeyMode, unsigned char ucKeySNr,
									   unsigned char *pKey);

///////////////////////////////////////////////////////////////////////////////////////////////////
// ����ԭ��:    unsigned char PCDWriteReg(unsigned char ucRegAddr,unsigned char ucRegValue)
// ��������:    װ����Կ
// �������:    unsigned char ucRegAddr			// �Ĵ�����ַ
//				unsigned char ucRegValue		// д���ֵ
// �������:    -
// �� �� ֵ:    ����ִ�н��
///////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char PCDWriteReg(unsigned char ucRegAddr,unsigned char ucRegValue);

///////////////////////////////////////////////////////////////////////////////////////////////////
// ����ԭ��:    unsigned char PCDReadReg(unsigned char ucRegAddr,unsigned char *pRegValue)
// ��������:    ����доƬ�Ĵ���
// �������:    unsigned char ucRegAddr			// �Ĵ�����ַ			
// �������:    unsigned char *pRegValue		// ������ֵ
// �� �� ֵ:    ����ִ�н��
///////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char PCDReadReg(unsigned char ucRegAddr,unsigned char *pRegValue);

///////////////////////////////////////////////////////////////////////////////////////////////////
// ����ԭ��:    unsigned char PCDSetBaud(ucBaudNum)
// ��������:    �ı�ģ���ͨ�Ų�����
// �������:    unsigned char ucBaudNum			// �����ʱ��0��7			
// �������:    -
// �� �� ֵ:    ����ִ�н��
// ˵    ��:	��
///////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char PCDSetBaud(unsigned char ucBaudNum);

///////////////////////////////////////////////////////////////////////////////////////////////////
// ����ԭ��:    unsigned char PCDBind(const INT8U *pUserID,  INT8U *pPCDID)
// ��������:    ģ��� 
// �������:    INT8U *pUserID					// 			
// �������:    INT8U *pPCDID
// �� �� ֵ:    ����ִ�н��
///////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char PCDBind(const unsigned char *pUserID,  unsigned char *pPCDID);
//=================================================================================================
//   ������TypeA�����������Ϊ2
//=================================================================================================

///////////////////////////////////////////////////////////////////////////////////////////////////
// ����ԭ��:    unsigned char PiccReset(unsigned char _1ms)
// ��������:    ��Ƭ��λ(�ر������ز�)
// �������:    unsigned char _1ms				// �ر��ز���ʱ��			
// �������:    -
// �� �� ֵ:    ����ִ�н��
///////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char PiccReset(unsigned char _1ms);

///////////////////////////////////////////////////////////////////////////////////////////////////
// ����ԭ��:    unsigned char PiccAutoDetect(unsigned char ucADMode, unsigned char ucTxMode, 
//							 				 unsigned char ucReqCode, unsigned char ucAuthMode, 
//							 				 unsigned char ucKeyType, unsigned char *pKey, 
//							 				 unsigned char ucBlock)
// ��������:    A�Ϳ��Զ��������
// �������:    unsigned char ucADMode			// �Զ����ģʽ
//				unsigned char ucTxMode			// ��������ģʽ
//				unsigned char ucReqCode			// ����ģʽ
//				unsigned char ucAuthMode		// ��֤ģʽ
//				unsigned char ucKeyType			// ��Կ����
//				unsigned char *pKey				// ��Կ
//				unsigned char ucBlock			// ���Ŀ��
// �������:    unsigned char *pRegValue		// ������ֵ
// �� �� ֵ:    ����ִ�н��
///////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char PiccAutoDetect(unsigned char ucADMode, unsigned char ucTxMode, 
							 			 unsigned char ucReqCode, unsigned char ucAuthMode, 
							 			 unsigned char ucKeyType, unsigned char *pKey, 
							 			 unsigned char ucBlock);
///////////////////////////////////////////////////////////////////////////////////////////////////
// ����ԭ��:    unsigned char PiccAutoDetect(unsigned char ucADMode, unsigned char ucTxMode, 
//							 				 unsigned char ucReqCode, unsigned char ucAuthMode, 
//							 				 unsigned char ucKeyType, unsigned char *pKey, 
//							 				 unsigned char ucBlock)
// ��������:    A�Ϳ��Զ��������
// �������:    -
// �������:    unsigned char *pTxDrv			// �Ǹ����߼�⵽�Ŀ�
//												// 0x01--��TX1;	0x02--��TX2;	0x03--TX1��TX2
//				unsigned char *pATQ				// �����Ӧ(2�ֽ�)
//				unsigned char *pSAK				// ѡ��Ӧ��(1�ֽ�)
//				unsigned char *pUIDLen			// UID����
//				unsigned char *pUID				// UID
//				unsigned char *pDataBuf			// ����������
// �� �� ֵ:    ����ִ�н��
// ˵    ��:	��PiccAutoDetect()����֤ģʽΪ0�򣬱�������pDataBuf����ֵΪnone
///////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char PiccADRcv(unsigned char *pTxDrv, unsigned char *pATQ, 
									unsigned char *pSAK,unsigned char *pUIDLen, 
									unsigned char *pUID, unsigned char *pDataBuf);
///////////////////////////////////////////////////////////////////////////////////////////////////
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
// ˵    ��:	��PiccAutoDetect()����֤ģʽΪ0�򣬱�������pDataBuf����ֵΪnone		
///////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char PiccReadADDT( unsigned char ucMode, unsigned char *pTxDrv, 
										unsigned char *pATQ, unsigned char *pSAK, 
										unsigned char *pUIDLen, unsigned char *pUID, 
										unsigned char *pDataBuf);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����ԭ��:    unsigned char PiccSetTX( unsigned char ucSelTX)
// ��������:    ��������
// �������:    unsigned char ucSelTX			// 0x01������TX1 ��������
                                                    // 0x02������TX2 ��������
                                                    // 0x03����TX1��TX2 ͬʱ��������
                                                    // 0x00����ͬʱ�ر�TX1��TX2
// �� �� ֵ:    0x00 -- �ɹ�;	0xFF -- δ��⵽��;	0x9C -- ����δִ��			
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char PiccSetTX( unsigned char ucSelTX);

//=================================================================================================
#ifdef __cplusplus
	}
#endif

#endif				// __ZLG522S_H__

