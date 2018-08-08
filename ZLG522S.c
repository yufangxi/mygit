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
// 函数原型:    unsigned char GetDvcInfo(unsigned char *DvcInfo)
// 函数功能:    获取模块信息
// 输入参数:    -		
// 输出参数:    unsigned char *DvcInfo			// 模块信息
// 返 回 值:    命令执行结果
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
// 函数原型:    unsigned char PCDConfig()
// 函数功能:    配置读写卡芯片
// 输入参数:    -		
// 输出参数:    
// 返 回 值:    命令执行结果
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
// 函数原型:    unsigned char PCDClose()
// 函数功能:    模块信息配置
// 输入参数:    -		
// 输出参数:    
// 返 回 值:    命令执行结果
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
// 函数原型:    unsigned char PCDLoadKey(unsigned char ucKeyType, unsigned char ucKeySNr,
//										 unsigned char *pKey)
// 函数功能:    装载密钥
// 输入参数:    unsigned char ucKeyType			// 密钥类型	KEY_A;KEY_B	
//				unsigned char ucKeySNr			// 密钥存放扇区0~3
//				unsigned char *pKey				// 6字节密钥
// 输出参数:    -
// 返 回 值:    命令执行结果
// 说    明:	若输入的密钥为6字节，则模块会自动扩展为16字节
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
// 函数原型:    unsigned char PCDLoadKey16(unsigned char ucKeyType, unsigned char ucKeySNr,
//										 unsigned char *pKey)
// 函数功能:    装载密钥
// 输入参数:    unsigned char ucKeyType			// 密钥模式	KEY_A;KEY_B	
//				unsigned char ucKeySNr			// 密钥存放扇区0~3
//				unsigned char *pKey				// 16字节密钥
// 输出参数:    -
// 返 回 值:    命令执行结果
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
// 函数原型:    unsigned char PCDWriteReg(unsigned char ucRegAddr,unsigned char ucRegValue)
// 函数功能:    写读写芯片寄存器
// 输入参数:    unsigned char ucRegAddr			// 寄存器地址
//				unsigned char ucRegValue		// 写入的值
// 输出参数:    -
// 返 回 值:    命令执行结果
// 说    明:	
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
// 函数原型:    unsigned char PCDReadReg(unsigned char ucRegAddr,unsigned char *pRegValue)
// 函数功能:    读读写芯片寄存器
// 输入参数:    unsigned char ucRegAddr			// 寄存器地址			
// 输出参数:    unsigned char *pRegValue		// 读出的值
// 返 回 值:    命令执行结果
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
// 函数原型:    unsigned char PCDSetBaud(ucBaudNum)
// 函数功能:    改变模块的通信波特率
// 输入参数:    unsigned char ucBaudNum			// 波特率编号0～7			
// 输出参数:    -
// 返 回 值:    命令执行结果
// 说    明:	若
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
// 函数原型:    unsigned char PCDBind(const INT8U *pUserID,  INT8U *pPCDID)
// 函数功能:    模块绑定 
// 输入参数:    INT8U *pUserID					// 			
// 输出参数:    INT8U *pPCDID
// 返 回 值:    命令执行结果
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
//   以下是TypeA的命令，命令码为2
/////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数原型:    unsigned char PiccReset(unsigned char _1ms)
// 函数功能:    卡片复位(关闭天线载波)
// 输入参数:    unsigned char _1ms				// 关闭载波的时间			
// 输出参数:    -
// 返 回 值:    命令执行结果
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
// 函数原型:    unsigned char PiccAutoDetect(unsigned char ucADMode, unsigned char ucTxMode, 
//							 				 unsigned char ucReqCode, unsigned char ucAuthMode, 
//							 				 unsigned char ucKeyType, unsigned char *pKey, 
//							 				 unsigned char ucBlock)
// 函数功能:    A型卡自动检测命令
// 输入参数:    unsigned char ucADMode			// 自动检测模式
//				unsigned char ucTxMode			// 天线驱动模式
//				unsigned char ucReqCode			// 请求模式
//				unsigned char ucAuthMode		// 认证模式
//				unsigned char ucKeyType			// 密钥类型
//				unsigned char *pKey				// 密钥
//				unsigned char ucBlock			// 读的块号
// 输出参数:    unsigned char *pRegValue		// 读出的值
// 返 回 值:    命令执行结果
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
	{// 设置读数据
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
// 函数原型:    unsigned char PiccADRcv(unsigned char *pTxDrv, unsigned char *pATQ, 
//										unsigned char *pSAK, unsigned char *pUIDLen, 
//										unsigned char *pUID, unsigned char *pDataBuf)
// 函数功能:    读主动上传的自动检测的数据
// 输入参数:    -
// 输出参数:    unsigned char *pTxDrv			// 那个天线检测到的卡
//												// 0x01--仅TX1;	0x02--仅TX2;	0x03--TX1、TX2
//				unsigned char *pATQ				// 请求回应
//				unsigned char *pSAK				// 选择应答
//				unsigned char *pUIDLen			// UID长度
//				unsigned char *pUID				// UID
//				unsigned char *pDataBuf			// 读出的数据
// 返 回 值:    命令执行结果
// 说    明:	该函数用于自动读取模块自动检测时主动发送的数据
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if PICC_AD_RCV_EN
unsigned char PiccADRcv(unsigned char *pTxDrv, unsigned char *pATQ, unsigned char *pSAK,
						unsigned char *pUIDLen, unsigned char *pUID, unsigned char *pDataBuf)
{
	unsigned char Status = STATUS_IO_TIMEOUT;

	if(Ser_Rcv())
	{	
		if(SEQ == (g_ucSerBuf[CMDTYPE] & 0xF0))
		{//包号匹配
			Status = STATUS_SUCCESS;
			*pTxDrv = g_ucSerBuf[DATA];
			memcpy(pATQ, &g_ucSerBuf[DATA+1], 2);
			*pSAK = g_ucSerBuf[DATA+3];
			*pUIDLen = g_ucSerBuf[DATA+4];
			memcpy(pUID, &g_ucSerBuf[DATA+5], g_ucSerBuf[DATA+4]);

		// 若没有使能读数据，则不用处理下面的数据
			if(g_ucSerBuf[LENGTH] == g_ucSerBuf[DATA+4] + 21)
				memcpy(pDataBuf, &g_ucSerBuf[DATA+5+g_ucSerBuf[DATA+4]], 16);
		}
		else
			Status = STATUS_COMM_SEQ_ERR;	//包号不匹配
	}
	return Status;
}
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数原型:    unsigned char PiccReadADDT( unsigned char ucMode, unsigned char *pTxDrv, 
//											unsigned char *pATQ, unsigned char *pSAK, 
//											unsigned char *pUIDLen, unsigned char *pUID, 
//											unsigned char *pDataBuf)
// 函数功能:    读自动检测的数据
// 输入参数:    unsigned char ucMode			// 0x00 -- 停止检测；	0x01 -- 继续检测
// 输出参数:    unsigned char *pTxDrv			// 那个天线检测到的卡
//												// 0x01--仅TX1;	0x02--仅TX2;	0x03--TX1、TX2
//				unsigned char *pATQ				// 请求回应
//				unsigned char *pSAK				// 选择应答
//				unsigned char *pUIDLen			// UID长度
//				unsigned char *pUID				// UID
//				unsigned char *pDataBuf			// 读出的数据
// 返 回 值:    0x00 -- 成功;	0xFF -- 未检测到卡;	0x9C -- 函数未执行			
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
// 函数原型:    unsigned char PiccSetTX( unsigned char ucSelTX)
// 函数功能:    设置天线
// 输入参数:    unsigned char ucSelTX			// 0x01——仅TX1 驱动天线
                                                    // 0x02——仅TX2 驱动天线
                                                    // 0x03——TX1、TX2 同时驱动天线
                                                    // 0x00——同时关闭TX1、TX2
// 返 回 值:    0x00 -- 成功;	0xFF -- 未检测到卡;	0x9C -- 函数未执行			
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


