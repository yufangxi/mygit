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
#define ZLG522S_GLOBALS
#include "ZLG522S.h"

#include "ZLG522S_Comm.h"
#include "StatusCode.h"


#include <string.h>


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����ԭ��:    unsigned char GetDvcInfo(unsigned char *DvcInfo)
// ��������:    ��ȡģ����Ϣ
// �������:    -		
// �������:    unsigned char *DvcInfo			// ģ����Ϣ
// �� �� ֵ:    ����ִ�н��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if GET_DVC_INFO_EN
unsigned char GetDvcInfo(unsigned char *pDvcInfo)
{
	unsigned char Status;
	
	g_ucSerBuf[CMDTYPE] = CMD_TYPE_DVC_CONTROL;
	g_ucSerBuf[COMMAND] = 'A';
	g_ucSerBuf[LENGTH] = 0;
	
	Status = ZLG522S_Cmd();
	
	if(Status == STATUS_COMM_OK)
	{
		Status = g_ucSerBuf[STATUS];
		if(Status == STATUS_SUCCESS)
			memcpy(pDvcInfo, &g_ucSerBuf[DATA], g_ucSerBuf[LENGTH]);
	}
	return Status;
}
#endif
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����ԭ��:    unsigned char PCDConfig()
// ��������:    ���ö�д��оƬ
// �������:    -		
// �������:    
// �� �� ֵ:    ����ִ�н��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if PCD_CONFIG_EN
unsigned char PCDConfig(void)
{
	unsigned char Status;
	
	g_ucSerBuf[CMDTYPE] = CMD_TYPE_DVC_CONTROL;
	g_ucSerBuf[COMMAND] = 'B';
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
// ����ԭ��:    unsigned char PCDClose()
// ��������:    ģ����Ϣ����
// �������:    -		
// �������:    
// �� �� ֵ:    ����ִ�н��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if PCD_CLOSE_EN

unsigned char PCDClose(void)
{
	unsigned char Status;
	
	g_ucSerBuf[CMDTYPE] = CMD_TYPE_DVC_CONTROL;
	g_ucSerBuf[COMMAND] = 'C';
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
// ����ԭ��:    unsigned char PCDLoadKey(unsigned char ucKeyType, unsigned char ucKeySNr,
//										 unsigned char *pKey)
// ��������:    װ����Կ
// �������:    unsigned char ucKeyType			// ��Կ����	KEY_A;KEY_B	
//				unsigned char ucKeySNr			// ��Կ�������0~3
//				unsigned char *pKey				// 6�ֽ���Կ
// �������:    -
// �� �� ֵ:    ����ִ�н��
// ˵    ��:	���������ԿΪ6�ֽڣ���ģ����Զ���չΪ16�ֽ�
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if PCD_LOAD_KEY_EN
unsigned char PCDLoadKey(unsigned char ucKeyType,unsigned char ucKeySNr,unsigned char *pKey)
{
	unsigned char Status;
	
	g_ucSerBuf[CMDTYPE] = CMD_TYPE_DVC_CONTROL;
	g_ucSerBuf[COMMAND] = 'E';
	g_ucSerBuf[LENGTH] = 8;
	g_ucSerBuf[DATA] = ucKeyType;
	g_ucSerBuf[DATA+1] = ucKeySNr;
	memcpy(&g_ucSerBuf[DATA+2], pKey, 6);
	
	Status = ZLG522S_Cmd();
	
	if(Status == STATUS_COMM_OK)
	{
		Status = g_ucSerBuf[STATUS];
	}
	return Status;
}
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����ԭ��:    unsigned char PCDLoadKey16(unsigned char ucKeyType, unsigned char ucKeySNr,
//										 unsigned char *pKey)
// ��������:    װ����Կ
// �������:    unsigned char ucKeyType			// ��Կģʽ	KEY_A;KEY_B	
//				unsigned char ucKeySNr			// ��Կ�������0~3
//				unsigned char *pKey				// 16�ֽ���Կ
// �������:    -
// �� �� ֵ:    ����ִ�н��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if PCD_LOAD_KEY_16_EN
unsigned char PCDLoadKey16(unsigned char ucKeyType,unsigned char ucKeySNr,unsigned char *pKey)
{
	unsigned char Status;
	
	g_ucSerBuf[CMDTYPE] = CMD_TYPE_DVC_CONTROL;
	g_ucSerBuf[COMMAND] = 'E';
	g_ucSerBuf[LENGTH] = 18;
	g_ucSerBuf[DATA] = ucKeyType;
	g_ucSerBuf[DATA+1] = ucKeySNr;
	memcpy(&g_ucSerBuf[DATA+2], pKey, 16);
	
	Status = ZLG522S_Cmd();
	
	if(Status == STATUS_COMM_OK)
	{
		Status = g_ucSerBuf[STATUS];
	}
	return Status;
}
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����ԭ��:    unsigned char PCDWriteReg(unsigned char ucRegAddr,unsigned char ucRegValue)
// ��������:    д��доƬ�Ĵ���
// �������:    unsigned char ucRegAddr			// �Ĵ�����ַ
//				unsigned char ucRegValue		// д���ֵ
// �������:    -
// �� �� ֵ:    ����ִ�н��
// ˵    ��:	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if PCD_WRITE_REG_EN
unsigned char PCDWriteReg(unsigned char ucRegAddr,unsigned char ucRegValue)
{
	unsigned char Status;
	
	g_ucSerBuf[CMDTYPE] = CMD_TYPE_DVC_CONTROL;
	g_ucSerBuf[COMMAND] = 'F';
	g_ucSerBuf[LENGTH] = 2;
	g_ucSerBuf[DATA] = ucRegAddr;
	g_ucSerBuf[DATA+1] = ucRegValue;
	
	Status = ZLG522S_Cmd();
	
	if(Status == STATUS_COMM_OK)
	{
		Status = g_ucSerBuf[STATUS];
	}
	return Status;
}
#endif
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����ԭ��:    unsigned char PCDReadReg(unsigned char ucRegAddr,unsigned char *pRegValue)
// ��������:    ����доƬ�Ĵ���
// �������:    unsigned char ucRegAddr			// �Ĵ�����ַ			
// �������:    unsigned char *pRegValue		// ������ֵ
// �� �� ֵ:    ����ִ�н��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if PCD_READ_REG_EN
unsigned char PCDReadReg(unsigned char ucRegAddr,unsigned char *pRegValue)
{
	unsigned char Status;
	
	g_ucSerBuf[CMDTYPE] = CMD_TYPE_DVC_CONTROL;
	g_ucSerBuf[COMMAND] = 'G';
	g_ucSerBuf[LENGTH] = 1;
	g_ucSerBuf[DATA] = ucRegAddr;
	
	Status = ZLG522S_Cmd();
	
	if(Status == STATUS_COMM_OK)
	{
		Status = g_ucSerBuf[STATUS];
		if(Status == STATUS_SUCCESS)
			*pRegValue = g_ucSerBuf[DATA];
	}
	return Status;
}
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����ԭ��:    unsigned char PCDSetBaud(ucBaudNum)
// ��������:    �ı�ģ���ͨ�Ų�����
// �������:    unsigned char ucBaudNum			// �����ʱ��0��7			
// �������:    -
// �� �� ֵ:    ����ִ�н��
// ˵    ��:	��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if PCD_SET_BAUD_EN
unsigned char PCDSetBaud(unsigned char ucBaudNum)
{
	unsigned char Status;
	
	g_ucSerBuf[CMDTYPE] = CMD_TYPE_DVC_CONTROL;
	g_ucSerBuf[COMMAND] = 'H';
	g_ucSerBuf[LENGTH] = 1;
	g_ucSerBuf[DATA] = ucBaudNum;
	
	Status = ZLG522S_Cmd();
	
	if(Status == STATUS_COMM_OK)
	{
		Status = g_ucSerBuf[STATUS];
		if(Status == STATUS_SUCCESS)
			SetBaud(ucBaudNum);
	}
	return Status;
}
#endif
///////////////////////////////////////////////////////////////////////////////////////////////////
// ����ԭ��:    unsigned char PCDBind(const INT8U *pUserID,  INT8U *pPCDID)
// ��������:    ģ��� 
// �������:    INT8U *pUserID					// 			
// �������:    INT8U *pPCDID
// �� �� ֵ:    ����ִ�н��
///////////////////////////////////////////////////////////////////////////////////////////////////
#if PCD_BIND_EN
unsigned char PCDBind(const unsigned char *pUserID,  unsigned char *pPCDID)
{
	unsigned char Status;
	
	g_ucSerBuf[CMDTYPE] = 1;
	g_ucSerBuf[COMMAND] = 'Z';
	g_ucSerBuf[LENGTH] = 4;
	memcpy(&g_ucSerBuf[DATA], pUserID, 4);
	
	Status = ZLG522S_Cmd();
	
	if(Status == STATUS_SUCCESS)
	{
		Status = g_ucSerBuf[STATUS];
 		if(Status == STATUS_SUCCESS)
		{
			memcpy(pPCDID,&g_ucSerBuf[DATA],g_ucSerBuf[LENGTH]);
		}
	} 
	return Status;
}
#endif				// 	PCD_BIND_EN
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   ������TypeA�����������Ϊ2
/////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����ԭ��:    unsigned char PiccReset(unsigned char _1ms)
// ��������:    ��Ƭ��λ(�ر������ز�)
// �������:    unsigned char _1ms				// �ر��ز���ʱ��			
// �������:    -
// �� �� ֵ:    ����ִ�н��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if PICC_RESET_EN
unsigned char PiccReset(unsigned char _1ms)
{
	unsigned char Status;
	
	g_ucSerBuf[CMDTYPE] = CMD_TYPE_TYPE_A;
	g_ucSerBuf[COMMAND] = 'L';
	g_ucSerBuf[LENGTH] = 1;
	g_ucSerBuf[DATA] = _1ms;
			
	Status = ZLG522S_Cmd();
	
	if(Status == STATUS_COMM_OK)
	{
		Status = g_ucSerBuf[STATUS];
	}
	return Status;
}
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if PICC_AUTO_DETEGT_EN
unsigned char PiccAutoDetect(unsigned char ucADMode, unsigned char ucTxMode, 
							 unsigned char ucReqCode, unsigned char ucAuthMode, 
							 unsigned char ucKeyType, unsigned char *pKey, 
							 unsigned char ucBlock)
{
	unsigned char Status;
	
	g_ucSerBuf[CMDTYPE] = CMD_TYPE_TYPE_A;
	g_ucSerBuf[COMMAND] = 'N';

	if(ucAuthMode == 0)
		g_ucSerBuf[LENGTH] = 4;
	else
	{// ���ö�����
		g_ucSerBuf[DATA + 4] = ucKeyType;			// 
		if(ucAuthMode == 'E')
		{
			g_ucSerBuf[DATA + 5] = *pKey;
			g_ucSerBuf[DATA + 6] = ucBlock;
			g_ucSerBuf[LENGTH] = 7;
		}
		else if(ucAuthMode == 'F')
		{
			memcpy(&g_ucSerBuf[DATA + 5], pKey, 6);
			g_ucSerBuf[DATA + 11] = ucBlock;
			g_ucSerBuf[LENGTH] = 12;
		}
		else
			return STATUS_INVALID_PARAMETER;
	}

	g_ucSerBuf[DATA] = ucADMode;
	g_ucSerBuf[DATA + 1] = ucTxMode;
	g_ucSerBuf[DATA + 2] = ucReqCode;
	g_ucSerBuf[DATA + 3] = ucAuthMode;
	
	Status = ZLG522S_Cmd();
	
	if(Status == STATUS_COMM_OK)
	{
		Status = g_ucSerBuf[STATUS];
	}
	return Status;
}
#endif
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����ԭ��:    unsigned char PiccADRcv(unsigned char *pTxDrv, unsigned char *pATQ, 
//										unsigned char *pSAK, unsigned char *pUIDLen, 
//										unsigned char *pUID, unsigned char *pDataBuf)
// ��������:    �������ϴ����Զ���������
// �������:    -
// �������:    unsigned char *pTxDrv			// �Ǹ����߼�⵽�Ŀ�
//												// 0x01--��TX1;	0x02--��TX2;	0x03--TX1��TX2
//				unsigned char *pATQ				// �����Ӧ
//				unsigned char *pSAK				// ѡ��Ӧ��
//				unsigned char *pUIDLen			// UID����
//				unsigned char *pUID				// UID
//				unsigned char *pDataBuf			// ����������
// �� �� ֵ:    ����ִ�н��
// ˵    ��:	�ú��������Զ���ȡģ���Զ����ʱ�������͵�����
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if PICC_AD_RCV_EN
unsigned char PiccADRcv(unsigned char *pTxDrv, unsigned char *pATQ, unsigned char *pSAK,
						unsigned char *pUIDLen, unsigned char *pUID, unsigned char *pDataBuf)
{
	unsigned char Status = STATUS_IO_TIMEOUT;

	if(Ser_Rcv())
	{	
		if(SEQ == (g_ucSerBuf[CMDTYPE] & 0xF0))
		{//����ƥ��
			Status = STATUS_SUCCESS;
			*pTxDrv = g_ucSerBuf[DATA];
			memcpy(pATQ, &g_ucSerBuf[DATA+1], 2);
			*pSAK = g_ucSerBuf[DATA+3];
			*pUIDLen = g_ucSerBuf[DATA+4];
			memcpy(pUID, &g_ucSerBuf[DATA+5], g_ucSerBuf[DATA+4]);

		// ��û��ʹ�ܶ����ݣ����ô������������
			if(g_ucSerBuf[LENGTH] == g_ucSerBuf[DATA+4] + 21)
				memcpy(pDataBuf, &g_ucSerBuf[DATA+5+g_ucSerBuf[DATA+4]], 16);
		}
		else
			Status = STATUS_COMM_SEQ_ERR;	//���Ų�ƥ��
	}
	return Status;
}
#endif

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
#if PICC_READ_AD_DT_EN
unsigned char PiccReadADDT( unsigned char ucMode, unsigned char *pTxDrv, unsigned char *pATQ, 
							unsigned char *pSAK, unsigned char *pUIDLen, 
							unsigned char *pUID, unsigned char *pDataBuf)
{
	unsigned char Status;

	g_ucSerBuf[CMDTYPE] = CMD_TYPE_TYPE_A;
	g_ucSerBuf[COMMAND] = 'O';
	g_ucSerBuf[LENGTH] = 1;
	g_ucSerBuf[DATA] = ucMode;
	
	Status = ZLG522S_Cmd();

	if(Status == STATUS_COMM_OK)
	{
		Status = g_ucSerBuf[STATUS];
		if(Status == STATUS_SUCCESS)
		{
			*pTxDrv = g_ucSerBuf[DATA];
			memcpy(pATQ, &g_ucSerBuf[DATA+1], 2);
			*pSAK = g_ucSerBuf[DATA+3];
			*pUIDLen = g_ucSerBuf[DATA+4];
			memcpy(pUID, &g_ucSerBuf[DATA+5], g_ucSerBuf[DATA+4]);
			if(g_ucSerBuf[LENGTH] == g_ucSerBuf[DATA+4] + 21)
				memcpy(pDataBuf, &g_ucSerBuf[DATA+5+g_ucSerBuf[DATA+4]], 16);
		}
	}

	return Status;
}
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����ԭ��:    unsigned char PiccSetTX( unsigned char ucSelTX)
// ��������:    ��������
// �������:    unsigned char ucSelTX			// 0x01������TX1 ��������
                                                    // 0x02������TX2 ��������
                                                    // 0x03����TX1��TX2 ͬʱ��������
                                                    // 0x00����ͬʱ�ر�TX1��TX2
// �� �� ֵ:    0x00 -- �ɹ�;	0xFF -- δ��⵽��;	0x9C -- ����δִ��			
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if PICC_Set_TX_EN
unsigned char PiccSetTX( unsigned char ucSelTX)

{
	unsigned char Status;

	g_ucSerBuf[CMDTYPE] = CMD_TYPE_DVC_CONTROL;
	g_ucSerBuf[COMMAND] = 'I';
	g_ucSerBuf[LENGTH] = 1;
	g_ucSerBuf[DATA] = ucSelTX;
	
	Status = ZLG522S_Cmd();

	if(Status == STATUS_COMM_OK)
	{
		Status = g_ucSerBuf[STATUS];
	}
	return Status;
}
#endif


