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
//============= 函数剪裁 ====================================================================================
#define GET_DVC_INFO_EN				1			// 获取模块信息
#define PCD_CONFIG_EN				1			// 配置读写芯片
#define PCD_CLOSE_EN				1			// 关闭读写芯片
#define PCD_LOAD_KEY_EN				1			// 装载6字节密钥
#define PCD_LOAD_KEY_16_EN			1			// 装载16字节密钥
#define PCD_WRITE_REG_EN			1			// 写寄存器
#define PCD_READ_REG_EN				1			// 读寄存器
#define PCD_SET_BAUD_EN				1			// 设置模块UART通信波特率
#define PCD_BIND_EN					1			// 模块绑定

#define PICC_RESET_EN				1			// 卡片复位(停止载波一段时间)
#define PICC_AUTO_DETEGT_EN			1			// 自动检测命令(6字节密钥)
#define PICC_AUTO_DETEGT_16_EN		0			// 自动检测命令(16字节密钥)
#define PICC_AD_RCV_EN				1			// 中断产生后的读自动检测的数据
#define PICC_READ_AD_DT_EN			1			// 读自动检测数据的命令
#define PICC_Set_TX_EN                1         //设置天线

//============= 常量定义 ====================================================================================
//定义A型卡命令
#define KEY_A						0x60
#define KEY_B						0x61
#define ISO14443A					0x00
#define ISO14443B					0x80

//============= 全局变量/函数声明 =================================================================
///////////////////////////////////////////////////////////////////////////////////////////////////
// 函数原型:    unsigned char GetDvcInfo(unsigned char *pDvcInfo)
// 函数功能:    获取模块信息
// 输入参数:    -		
// 输出参数:    unsigned char *pDvcInfo			// 模块信息
// 返 回 值:    命令执行结果
///////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char GetDvcInfo(unsigned char *pDvcInfo);

///////////////////////////////////////////////////////////////////////////////////////////////////
// 函数原型:    unsigned char PCDConfig()
// 函数功能:    配置读写卡芯片
// 输入参数:    -		
// 输出参数:    
// 返 回 值:    命令执行结果
///////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char PCDConfig(void);

///////////////////////////////////////////////////////////////////////////////////////////////////
// 函数原型:    unsigned char PCDClose()
// 函数功能:    模块信息配置
// 输入参数:    -		
// 输出参数:    
// 返 回 值:    命令执行结果
///////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char PCDClose(void);

///////////////////////////////////////////////////////////////////////////////////////////////////
// 函数原型:    unsigned char PCDLoadKey(unsigned char ucKeyMode, unsigned char ucKeySNr,
//										 unsigned char *pKey)
// 函数功能:    装载密钥
// 输入参数:    unsigned char ucKeyMode			// 密钥模式	KEY_A;KEY_B	
//				unsigned char ucKeySNr			// 密钥存放扇区0~3
//				unsigned char *pKey				// 6字节密钥
// 输出参数:    -
// 返 回 值:    命令执行结果
// 说    明:	若输入的密钥为6字节，则模块会自动扩展为16字节
//				Key[16] = pKey[0:5] | pKey[0:5] | pKey[0:3]
///////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char PCDLoadKey(unsigned char ucKeyMode, unsigned char ucKeySNr,
									 unsigned char *pKey);

///////////////////////////////////////////////////////////////////////////////////////////////////
// 函数原型:    unsigned char PCDLoadKey16(unsigned char ucKeyMode, unsigned char ucKeySNr,
//										 unsigned char *pKey)
// 函数功能:    装载密钥
// 输入参数:    unsigned char ucKeyMode			// 密钥模式	KEY_A;KEY_B	
//				unsigned char ucKeySNr			// 密钥存放扇区0~3
//				unsigned char *pKey				// 16字节密钥
// 输出参数:    -
// 返 回 值:    命令执行结果
///////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char PCDLoadKey16(unsigned char ucKeyMode, unsigned char ucKeySNr,
									   unsigned char *pKey);

///////////////////////////////////////////////////////////////////////////////////////////////////
// 函数原型:    unsigned char PCDWriteReg(unsigned char ucRegAddr,unsigned char ucRegValue)
// 函数功能:    装载密钥
// 输入参数:    unsigned char ucRegAddr			// 寄存器地址
//				unsigned char ucRegValue		// 写入的值
// 输出参数:    -
// 返 回 值:    命令执行结果
///////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char PCDWriteReg(unsigned char ucRegAddr,unsigned char ucRegValue);

///////////////////////////////////////////////////////////////////////////////////////////////////
// 函数原型:    unsigned char PCDReadReg(unsigned char ucRegAddr,unsigned char *pRegValue)
// 函数功能:    读读写芯片寄存器
// 输入参数:    unsigned char ucRegAddr			// 寄存器地址			
// 输出参数:    unsigned char *pRegValue		// 读出的值
// 返 回 值:    命令执行结果
///////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char PCDReadReg(unsigned char ucRegAddr,unsigned char *pRegValue);

///////////////////////////////////////////////////////////////////////////////////////////////////
// 函数原型:    unsigned char PCDSetBaud(ucBaudNum)
// 函数功能:    改变模块的通信波特率
// 输入参数:    unsigned char ucBaudNum			// 波特率编号0～7			
// 输出参数:    -
// 返 回 值:    命令执行结果
// 说    明:	若
///////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char PCDSetBaud(unsigned char ucBaudNum);

///////////////////////////////////////////////////////////////////////////////////////////////////
// 函数原型:    unsigned char PCDBind(const INT8U *pUserID,  INT8U *pPCDID)
// 函数功能:    模块绑定 
// 输入参数:    INT8U *pUserID					// 			
// 输出参数:    INT8U *pPCDID
// 返 回 值:    命令执行结果
///////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char PCDBind(const unsigned char *pUserID,  unsigned char *pPCDID);
//=================================================================================================
//   以下是TypeA的命令，命令码为2
//=================================================================================================

///////////////////////////////////////////////////////////////////////////////////////////////////
// 函数原型:    unsigned char PiccReset(unsigned char _1ms)
// 函数功能:    卡片复位(关闭天线载波)
// 输入参数:    unsigned char _1ms				// 关闭载波的时间			
// 输出参数:    -
// 返 回 值:    命令执行结果
///////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char PiccReset(unsigned char _1ms);

///////////////////////////////////////////////////////////////////////////////////////////////////
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
///////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char PiccAutoDetect(unsigned char ucADMode, unsigned char ucTxMode, 
							 			 unsigned char ucReqCode, unsigned char ucAuthMode, 
							 			 unsigned char ucKeyType, unsigned char *pKey, 
							 			 unsigned char ucBlock);
///////////////////////////////////////////////////////////////////////////////////////////////////
// 函数原型:    unsigned char PiccAutoDetect(unsigned char ucADMode, unsigned char ucTxMode, 
//							 				 unsigned char ucReqCode, unsigned char ucAuthMode, 
//							 				 unsigned char ucKeyType, unsigned char *pKey, 
//							 				 unsigned char ucBlock)
// 函数功能:    A型卡自动检测命令
// 输入参数:    -
// 输出参数:    unsigned char *pTxDrv			// 那个天线检测到的卡
//												// 0x01--仅TX1;	0x02--仅TX2;	0x03--TX1、TX2
//				unsigned char *pATQ				// 请求回应(2字节)
//				unsigned char *pSAK				// 选择应答(1字节)
//				unsigned char *pUIDLen			// UID长度
//				unsigned char *pUID				// UID
//				unsigned char *pDataBuf			// 读出的数据
// 返 回 值:    命令执行结果
// 说    明:	若PiccAutoDetect()的认证模式为0则，本函数的pDataBuf返回值为none
///////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char PiccADRcv(unsigned char *pTxDrv, unsigned char *pATQ, 
									unsigned char *pSAK,unsigned char *pUIDLen, 
									unsigned char *pUID, unsigned char *pDataBuf);
///////////////////////////////////////////////////////////////////////////////////////////////////
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
// 说    明:	若PiccAutoDetect()的认证模式为0则，本函数的pDataBuf返回值为none		
///////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char PiccReadADDT( unsigned char ucMode, unsigned char *pTxDrv, 
										unsigned char *pATQ, unsigned char *pSAK, 
										unsigned char *pUIDLen, unsigned char *pUID, 
										unsigned char *pDataBuf);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数原型:    unsigned char PiccSetTX( unsigned char ucSelTX)
// 函数功能:    设置天线
// 输入参数:    unsigned char ucSelTX			// 0x01——仅TX1 驱动天线
                                                    // 0x02——仅TX2 驱动天线
                                                    // 0x03——TX1、TX2 同时驱动天线
                                                    // 0x00——同时关闭TX1、TX2
// 返 回 值:    0x00 -- 成功;	0xFF -- 未检测到卡;	0x9C -- 函数未执行			
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char PiccSetTX( unsigned char ucSelTX);

//=================================================================================================
#ifdef __cplusplus
	}
#endif

#endif				// __ZLG522S_H__

