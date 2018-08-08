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
// 函数原型:    unsigned char PiccRequest(unsigned char ucReqCode,unsigned char *pATQ)
// 函数功能:    请求
// 输入参数:    unsigned char ucReqCode			// 请求代码		
// 输出参数:    unsigned char *pATQ				// 请求回应
// 返 回 值:    命令执行结果
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
// 函数原型:    unsigned char PiccAnticoll( unsigned char ucSelCode,unsigned char ucBcnt,
//											unsigned char *pUID)
// 函数功能:    防碰撞
// 输入参数:    unsigned char ucSelCode			// 防碰撞等级
//												// SELCODE1	0x93	等级1
//												// SELCODE2	0x95	等级2
//												// SELCODE3	0x97	等级3
//				unsigned char ucBcnt			// 已知卡号的位数，通常设置为0
//				unsigned char *pSnr				// 已知的卡号，若不知道，则不用理会
// 输出参数:    unsigned char *pSnr				// 卡号
// 返 回 值:    命令执行结果
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
// 函数原型:    unsigned char PiccSelect(unsigned char ucSelCode,unsigned char *pUID,
//										 unsigned char *pSAK)
// 函数功能:    选择卡
// 输入参数:    unsigned char ucSelCode			// 选择(防碰撞等级)
//												// SELCODE1	0x93	等级1
//												// SELCODE2	0x95	等级2
//												// SELCODE3	0x97	等级3
//				unsigned char *pUID				// 卡号
// 输出参数:    unsigned char *pSAK				// 选择应答
// 返 回 值:    命令执行结果
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
// 函数原型:    unsigned char PiccHalt()
// 函数功能:    将激活的卡挂起
// 输入参数:    -	
// 输出参数:    -
// 返 回 值:    命令执行结果
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
// 函数原型:    unsigned char PiccAuthE2(unsigned char ucKeyType, unsigned char *pUID, 
//										  unsigned char ucKeySector, unsigned char ucBlock)
// 函数功能:    Mifare1卡验证命令，验证成功后，以后的通信被加密。
// 入口参数:    unsigned char ucKeyType			// 密钥类型：KEY_A -- 密钥A;	KEY_B -- 密钥B;
//				unsigned char *pUID				// 4字节UID
//				unsigned char ucKeySector		// 密钥存放扇区
//				unsigned char ucBlock			// 验证的块号
// 出口参数:    -
// 返 回 值:    STATUS_SUCCESS -- 成功；其它值 -- 失败。
// 说    明:	验证后，访问该块所在的扇区(相同权限)均不用再验证密钥    
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
// 函数原型:    unsigned char PiccAuthKey(unsigned char ucKeyType, unsigned char *pUID, 
//										  unsigned char *pKey, unsigned char ucBlock)
// 函数功能:    Mifare1卡验证命令，验证成功后，以后的通信被加密。
// 入口参数:    unsigned char ucKeyType			// 密钥类型：KEY_A -- 密钥A;	KEY_B -- 密钥B;
//				unsigned char *pUID				// 4字节UID
//				unsigned char *pKey				// 6字节密钥
//				unsigned char ucBlock			// 验证的块号
// 出口参数:    -
// 返 回 值:    STATUS_SUCCESS -- 成功；其它值 -- 失败。
// 说    明:	验证后，访问该块所在的扇区(相同权限)均不用再验证密钥    
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
// 函数原型:    unsigned char PiccRead(unsigned char ucBlock, unsigned char *pBuf)
// 函数功能:    Mifare读命令
// 入口参数:    unsigned char ucBlock			; 读的块号
// 出口参数:    unsigned char *pBuf				; 读出的16字节数据
// 返 回 值:    STATUS_SUCCESS -- 成功；其它值 -- 失败。
// 说    明:	-   
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
// 函数原型:    unsigned char PiccWrite( unsigned char ucBlock, unsigned char *pBfr)
// 函数功能:    Mifare写命令
// 入口参数:    unsigned char ucBlock			; 写入的块地址。
//				unsigned char *pBfr				; 16字节写数据缓冲区首址。
// 出口参数:    -
// 返 回 值:    STATUS_SUCCESS -- 成功；其它值 -- 失败。
// 说    明:	-   
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
// 函数原型:    unsigned char PiccULWrite( unsigned char ucBlock, unsigned char *pBuf)
// 函数功能:    Mifare写命令
// 入口参数:    unsigned char ucBlock			; 写入的块地址。
//				unsigned char *pBfr				; 4字节写数据缓冲区首址。
// 出口参数:    -
// 返 回 值:    STATUS_SUCCESS -- 成功；其它值 -- 失败。
// 说    明:	-   
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
// 函数原型:    unsigned char PiccValueOper(unsigned char ucOperMode, unsigned char ucSBlock, 
//									unsigned char *pValue, unsigned char ucDBlock)
// 函数功能:    Mifare值操作命令
// 入口参数:    unsigned char ucOperMode,		; 值操作模式
//				unsigned char ucSBlock			; 要操作的块地址。
//				unsigned char *pValue,			; 4字节要操作的值，低字节在低地址。
//				unsigned char ucDBlock			; 值操作的目地块
// 出口参数:    -
// 返 回 值:    STATUS_SUCCESS -- 成功；其它值 -- 失败。  
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
// 函数原型:    unsigned char PiccActiveTypeA(	unsigned char unMode, unsigned char ucReqCode, 
//							  					unsigned char *pATQ, unsigned char *pSAK,
//						      					unsigned char *pUIDLen, unsigned char *pUID))
// 函数功能:    模块信息配置
// 输入参数:    unsigned char unMode			// 0 -- 执行防碰撞循环，1 -- 只执行一次防碰撞
//				unsigned char ucReqCode			// 请求码	
// 输出参数:    unsigned char *pATQ				// 请求回应
//				unsigned char *pSAK				// 最后一级选择应答
//				unsigned char *pUIDLen			// 卡号长度
//				unsigned char *pUID				// 卡号
// 返 回 值:    命令执行结果
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





