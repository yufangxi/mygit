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
//============= 函数剪裁 ====================================================================================
#define PICC_REQUEST_EN 			1			// 请求
#define PICC_ANTICOLL_EN			1			// 防碰撞
#define PICC_SELECT_EN				1			// 选择
#define PICC_HALT_EN				1			// 挂起
#define PICC_ACTIVE_TYPEA_EN		1			// A型卡激活

#define PICC_AUTH_E2_EN				1			// Mifare卡验证密钥(E2中密钥验证)
#define PICC_AUTH_KEY_EN			1			// Mifare卡验证密钥(直接密钥验证)
#define PICC_READ_EN				1			// 读数据
#define PICC_WRITE_EN				1			// 写数据
#define PICC_UL_WRITE_EN			1			// UL写
#define PICC_VALUE_OPER_EN			1			// 值块操作

#define PICC_RESET_EN				1			// 卡片复位(停止载波一段时间)
#define PICC_AUTO_DETEGT_EN			1			// 自动检测命令(6字节密钥)
#define PICC_AUTO_DETEGT_16_EN		0			// 自动检测命令(16字节密钥)
#define PICC_AD_RCV_EN				1			// 中断产生后的读自动检测的数据
#define PICC_READ_AD_DT_EN			1			// 读自动检测数据的命令
//============= 常量定义 ====================================================================================
//定义A型卡命令
#define REQ_STD						0x26		// 请求(IDLE 卡)命令码	
#define REQ_ALL						0x52		// 请求(ALL  卡)命令码
#define SEL_CODE_LV1				0x93		// 防碰撞/选择等级1命令码
#define SEL_CODE_LV2				0x95		// 防碰撞/选择等级2命令码
#define SEL_CODE_LV3				0x97		// 防碰撞/选择等级3命令码
#define MIFARE_INCREMENT            0xC1		// 值增命令
#define MIFARE_DECREMENT            0xC0		// 值减命令

#define KEY_A            			0x60		// 密钥A
#define KEY_B            			0x61		// 密钥B
//============= A型卡自动检测参数定义 =======================================================================
#define AD_SERIALOUT				0x01		// 串口主动输出
#define AD_INTENABLE				0x02		// 中断使能
#define AD_CONTINUE					0x04		// 串口输出之后继续检测
#define AD_HALT						0x08		// 最后将卡挂起

#define AD_TX_ALERT					0x00		// TX1,TX2交替输出
#define AD_TX_ONLYTX1				0x01		// 仅TX1输出
#define AD_TX_ONLYTX2				0x02		// 仅TX2输出
#define AD_TX_ALL					0x03		// TX1,TX2同时输出

#define AD_STOP						0x00		// 停止检测	
#define AD_REENABLE					0x01		// 继续检测
/*
//============= 全局变量/函数声明 ===========================================================================
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数原型:    unsigned char PiccRequest(unsigned char ucReqCode,unsigned char *pATQ)
// 函数功能:    请求
// 输入参数:    unsigned char ucReqCode			// 请求代码		
// 输出参数:    unsigned char *pATQ				// 请求回应
// 返 回 值:    命令执行结果
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char PiccRequest(unsigned char ucReqCode,unsigned char *pATQ);

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
unsigned char PiccAnticoll(unsigned char ucSelCode,unsigned char ucBcnt,unsigned char *pUID);

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
unsigned char PiccSelect(unsigned char ucSelCode,unsigned char *pUID,unsigned char *pSAK);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数原型:    unsigned char PiccHalt()
// 函数功能:    将激活的卡挂起
// 输入参数:    -	
// 输出参数:    -
// 返 回 值:    命令执行结果
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char PiccHalt(void);

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
unsigned char PiccActiveTypeA(unsigned char unMode, unsigned char ucReqCode, 
							  unsigned char *pATQ, unsigned char *pSAK,
						      unsigned char *pUIDLen, unsigned char *pUID);

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
unsigned char PiccReadADDT( unsigned char ucMode, unsigned char *pTxDrv, unsigned char *pATQ, 
							unsigned char *pSAK, unsigned char *pUIDLen, 
							unsigned char *pUID, unsigned char *pDataBuf);
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
unsigned char PiccAuthE2(unsigned char ucKeyType, unsigned char *pUID,
						 unsigned char ucKeySector, unsigned char ucBlock);
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
unsigned char PiccAuthKey(unsigned char ucKeyType, unsigned char *pUID, 
						  unsigned char *pKey, unsigned char ucBlock);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数原型:    unsigned char PiccRead(unsigned char ucBlock, unsigned char *pBuf)
// 函数功能:    Mifare读命令
// 入口参数:    unsigned char ucBlock			; 读的块号
// 出口参数:    unsigned char *pBuf				; 读出的16字节数据
// 返 回 值:    STATUS_SUCCESS -- 成功；其它值 -- 失败。
// 说    明:	-   
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char PiccRead(unsigned char ucBlock, unsigned char *pBuf);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数原型:    unsigned char PiccWrite( unsigned char ucBlock, unsigned char *pBfr)
// 函数功能:    Mifare写命令
// 入口参数:    unsigned char ucBlock			; 写入的块地址。
//				unsigned char *pBfr				; 16字节写数据缓冲区首址。
// 出口参数:    -
// 返 回 值:    STATUS_SUCCESS -- 成功；其它值 -- 失败。  
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char PiccWrite(unsigned char ucBlock,unsigned char *pBuf);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数原型:    unsigned char PiccULWrite( unsigned char ucBlock, unsigned char *pBuf)
// 函数功能:    Mifare写命令
// 入口参数:    unsigned char ucBlock			; 写入的块地址。
//				unsigned char *pBfr				; 4字节写数据缓冲区首址。
// 出口参数:    -
// 返 回 值:    STATUS_SUCCESS -- 成功；其它值 -- 失败。   
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char PiccULWrite(unsigned char ucBlock, unsigned char *pBuf);

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
unsigned char PiccValueOper(unsigned char ucOperMode, unsigned char ucSBlock, 
							unsigned char *pValue, unsigned char ucDBlock);*/
//===========================================================================================================
#ifdef __cplusplus
	}
#endif

#endif			// __ZLG522S_MIFARE_H__

