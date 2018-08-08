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
#define ZLG522S_MIFARE_GLOBALS
#include "ZLG522S_Mifare.h"

#include "ZLG522S_Comm.h"
#include "StatusCode.h"


#include <string.h>
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����ԭ��:    unsigned char PiccRequest(unsigned char ucReqCode,unsigned char *pATQ)
// ��������:    ����
// �������:    unsigned char ucReqCode			// �������		
// �������:    unsigned char *pATQ				// �����Ӧ
// �� �� ֵ:    ����ִ�н��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if PICC_REQUEST_EN
unsigned char PiccRequest(unsigned char ucReqCode,unsigned char *pATQ)
{
	unsigned char Status;
	
	g_ucSerBuf[CMDTYPE] = CMD_TYPE_TYPE_A;
	g_ucSerBuf[COMMAND] = 'A';
	g_ucSerBuf[LENGTH] = 1;
	g_ucSerBuf[DATA] = ucReqCode;
	
	Status = ZLG522S_Cmd();
	
	if(Status == STATUS_COMM_OK)
	{
		Status = g_ucSerBuf[STATUS];
		if(Status == STATUS_SUCCESS)
			memcpy(pATQ, &g_ucSerBuf[DATA], 2);
	}
	return Status;
}
#endif
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
#if PICC_ANTICOLL_EN
unsigned char PiccAnticoll(unsigned char ucSelCode,unsigned char ucBcnt,unsigned char *pUID)
{
	unsigned char Status;
	
	g_ucSerBuf[CMDTYPE] = CMD_TYPE_TYPE_A;
	g_ucSerBuf[COMMAND] = 'B';
	g_ucSerBuf[LENGTH]  = 6;
	g_ucSerBuf[DATA] 	= ucSelCode;
	g_ucSerBuf[DATA + 1] = ucBcnt;
	memcpy(&g_ucSerBuf[DATA + 2], pUID, 4);
	
	Status = ZLG522S_Cmd();
	
	if(Status == STATUS_COMM_OK)
	{
		Status = g_ucSerBuf[STATUS];
		if(Status == STATUS_SUCCESS)
		{
			memcpy(pUID, &g_ucSerBuf[DATA], 4);
		}
	}
	return Status;
}
#endif
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
#if PICC_SELECT_EN
unsigned char PiccSelect(unsigned char ucSelCode,unsigned char *pUID,unsigned char *pSAK)
{
	unsigned char Status;
	
	g_ucSerBuf[CMDTYPE] = CMD_TYPE_TYPE_A;
	g_ucSerBuf[COMMAND] = 'C';
	g_ucSerBuf[LENGTH] = 5;
	g_ucSerBuf[DATA]   = ucSelCode;
	memcpy(&g_ucSerBuf[DATA + 1], pUID, 4);
	
	Status = ZLG522S_Cmd();
	
	if(Status == STATUS_COMM_OK)
	{
		Status = g_ucSerBuf[STATUS];
		if(Status == STATUS_SUCCESS)
		{
			*pSAK = g_ucSerBuf[DATA];
		}
	}
	return Status;
}
#endif
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����ԭ��:    unsigned char PiccHalt()
// ��������:    ������Ŀ�����
// �������:    -	
// �������:    -
// �� �� ֵ:    ����ִ�н��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if PICC_HALT_EN
unsigned char PiccHalt(void)
{
	unsigned char Status;
	
	g_ucSerBuf[CMDTYPE] = CMD_TYPE_TYPE_A;
	g_ucSerBuf[COMMAND] = 'D';
	g_ucSerBuf[LENGTH] = 0;
	
	Status = ZLG522S_Cmd();
	
	if(Status == STATUS_COMM_OK)
	{
		Status = g_ucSerBuf[STATUS];
	}
	return Status;
}
#endif
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
#if PICC_AUTH_E2_EN
unsigned char PiccAuthE2(unsigned char ucKeyType, unsigned char *pUID,
						 unsigned char ucKeySector, unsigned char ucBlock)
{
	unsigned char Status;
	
	g_ucSerBuf[CMDTYPE] = CMD_TYPE_TYPE_A;
	g_ucSerBuf[COMMAND] = 'E';
	g_ucSerBuf[LENGTH] = 7;
	g_ucSerBuf[DATA] = ucKeyType;
	memcpy(&g_ucSerBuf[DATA+1],pUID,4);
	g_ucSerBuf[DATA+5] = ucKeySector;
	g_ucSerBuf[DATA+6] = ucBlock;	

	Status = ZLG522S_Cmd();
	
	if(Status == STATUS_COMM_OK)
	{
		Status = g_ucSerBuf[STATUS];
	}
	return Status;
}
#endif				// PICC_AUTH_E2_EN
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
#if PICC_AUTH_KEY_EN
unsigned char PiccAuthKey(unsigned char ucKeyType, unsigned char *pUID, 
						  unsigned char *pKey, unsigned char ucBlock)
{
	unsigned char Status;
	
	g_ucSerBuf[CMDTYPE] = CMD_TYPE_TYPE_A;
	g_ucSerBuf[COMMAND] = 'F';
	g_ucSerBuf[LENGTH] = 12;
	g_ucSerBuf[DATA] = ucKeyType;
	memcpy(&g_ucSerBuf[DATA+1], pUID, 4);
	memcpy(&g_ucSerBuf[DATA+5], pKey, 6);
	g_ucSerBuf[DATA+11] = ucBlock;	

	Status = ZLG522S_Cmd();
	
	if(Status == STATUS_COMM_OK)
	{
		Status = g_ucSerBuf[STATUS];
	}
	return Status;
}
#endif				// PICC_AUTH_KEY_EN
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����ԭ��:    unsigned char PiccRead(unsigned char ucBlock, unsigned char *pBuf)
// ��������:    Mifare������
// ��ڲ���:    unsigned char ucBlock			; ���Ŀ��
// ���ڲ���:    unsigned char *pBuf				; ������16�ֽ�����
// �� �� ֵ:    STATUS_SUCCESS -- �ɹ�������ֵ -- ʧ�ܡ�
// ˵    ��:	-   
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if	PICC_READ_EN
unsigned char PiccRead(unsigned char ucBlock, unsigned char *pBuf)
{
	unsigned char Status;
	
	g_ucSerBuf[CMDTYPE] = CMD_TYPE_TYPE_A;
	g_ucSerBuf[COMMAND] = 'G';
	g_ucSerBuf[LENGTH] = 1;
	g_ucSerBuf[DATA] = ucBlock;
		
	Status = ZLG522S_Cmd();
	
	if(Status == STATUS_COMM_OK)
	{
		Status = g_ucSerBuf[STATUS];
		if(Status == STATUS_SUCCESS)
		{
			memcpy(pBuf, &g_ucSerBuf[DATA], 16);
		}
	}
	return Status;
}
#endif				// PICC_READ_EN
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����ԭ��:    unsigned char PiccWrite( unsigned char ucBlock, unsigned char *pBfr)
// ��������:    Mifareд����
// ��ڲ���:    unsigned char ucBlock			; д��Ŀ��ַ��
//				unsigned char *pBfr				; 16�ֽ�д���ݻ�������ַ��
// ���ڲ���:    -
// �� �� ֵ:    STATUS_SUCCESS -- �ɹ�������ֵ -- ʧ�ܡ�
// ˵    ��:	-   
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if PICC_WRITE_EN
unsigned char PiccWrite(unsigned char ucBlock,unsigned char *pBuf)
{
	unsigned char Status;
	
	g_ucSerBuf[CMDTYPE] = CMD_TYPE_TYPE_A;
	g_ucSerBuf[COMMAND] = 'H';
	g_ucSerBuf[LENGTH] = 17;
	g_ucSerBuf[DATA] = ucBlock;
	memcpy(&g_ucSerBuf[DATA+1], pBuf, 16);
		
	Status = ZLG522S_Cmd();
	
	if(Status == STATUS_COMM_OK)
	{
		Status = g_ucSerBuf[STATUS];
	}
	return Status;
}
#endif				// PICC_WRITE_EN
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����ԭ��:    unsigned char PiccULWrite( unsigned char ucBlock, unsigned char *pBuf)
// ��������:    Mifareд����
// ��ڲ���:    unsigned char ucBlock			; д��Ŀ��ַ��
//				unsigned char *pBfr				; 4�ֽ�д���ݻ�������ַ��
// ���ڲ���:    -
// �� �� ֵ:    STATUS_SUCCESS -- �ɹ�������ֵ -- ʧ�ܡ�
// ˵    ��:	-   
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if PICC_UL_WRITE_EN
unsigned char PiccULWrite(unsigned char ucBlock, unsigned char *pBuf)
{
	unsigned char Status;
	
	g_ucSerBuf[CMDTYPE] = CMD_TYPE_TYPE_A;
	g_ucSerBuf[COMMAND] = 'I';
	g_ucSerBuf[LENGTH] = 5;
	g_ucSerBuf[DATA] = ucBlock;
	memcpy(&g_ucSerBuf[DATA+1],pBuf,4);
		
	Status = ZLG522S_Cmd();
	
	if(Status == STATUS_COMM_OK)
	{
		Status = g_ucSerBuf[STATUS];
	}
	return Status;
}
#endif				// PICC_UL_WRITE_EN
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
#if PICC_VALUE_OPER_EN
unsigned char PiccValueOper(unsigned char ucOperMode, unsigned char ucSBlock, 
							unsigned char *pValue, unsigned char ucDBlock)
{
	unsigned char Status;
	
	g_ucSerBuf[CMDTYPE] = CMD_TYPE_TYPE_A;
	g_ucSerBuf[COMMAND] = 'J';
	g_ucSerBuf[LENGTH] = 7;
	g_ucSerBuf[DATA] = ucOperMode;
	g_ucSerBuf[DATA+1] = ucSBlock;
	memcpy(&g_ucSerBuf[DATA+2], pValue, 4);
	g_ucSerBuf[DATA+6] = ucDBlock;
		
	Status = ZLG522S_Cmd();
	
	if(Status == STATUS_COMM_OK)
	{
		Status = g_ucSerBuf[STATUS];
	}
	return Status;
}
#endif				// PICC_VALUE_OPER_EN
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
#if PICC_ACTIVE_TYPEA_EN
unsigned char PiccActiveTypeA(unsigned char unMode, unsigned char ucReqCode, 
							  unsigned char *pATQ, unsigned char *pSAK,
						      unsigned char *pUIDLen, unsigned char *pUID)
{
	unsigned char Status;
	
	g_ucSerBuf[CMDTYPE] = CMD_TYPE_TYPE_A;
	g_ucSerBuf[COMMAND] = 'M';
	g_ucSerBuf[LENGTH] = 2;
	g_ucSerBuf[DATA] = unMode;
	g_ucSerBuf[DATA+1] = ucReqCode;
		
	Status = ZLG522S_Cmd();
	
	if(Status == STATUS_COMM_OK)
	{
		Status = g_ucSerBuf[STATUS];
		if(Status == STATUS_SUCCESS)
		{
			memcpy(pATQ, &g_ucSerBuf[DATA], 2);
			*pSAK = g_ucSerBuf[DATA+2];
			*pUIDLen = g_ucSerBuf[DATA+3];
			memcpy(pUID, &g_ucSerBuf[DATA+4], *pUIDLen);
		}
	}
	return Status;
}
#endif
//============ The end ======================================================================================





