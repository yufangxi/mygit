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

//============= 常量定义 ====================================================================================
// 通信命令类型
#define CMD_TYPE_DVC_CONTROL		1			// 设备控制类命令
#define CMD_TYPE_TYPE_A				2			// TypeA(包括Mifare卡)类命令				
#define CMD_TYPE_ISO7816			5			// ISO7816类命令
#define CMD_TYPE_COMM_PROT			6			// 通信协议(包括ISO14443-4)类命令
#define CMD_TYPE_PLUS_CPU			7			// PLUS CPU卡(不包括Mifare卡)类命令
// 波特率设置
#define BAUD_CNT 					8


// 定义缓冲区大小
#define MAX_SER_SIZE      			64+2+6

#define ZLG522S_DELAY_20MS			2
#define ZLG522S_DELAY_500MS			30
// 通信命令类型
#define CMD_TYPE_DVC_CONTROL		1			// 设备控制类命令
#define CMD_TYPE_TYPE_A				2			// TypeA(包括Mifare卡)类命令				
#define CMD_TYPE_ISO7816			5			// ISO7816类命令
#define CMD_TYPE_COMM_PROT			6			// 通信协议(包括ISO14443-4)类命令
#define CMD_TYPE_PLUS_CPU			7			// PLUS CPU卡(不包括Mifare卡)类命令

// 定义串行数据缓冲区各字符单元索引值
#define FRAMELEN					0			// 帧长度
#define CMDTYPE						1			// 包号
#define COMMAND						2			// 命令
#define STATUS						2			// 响应状态
#define LENGTH      				3			// 数据长度
#define DATA        				4			// 数据起始位置
#define PRTCLEN						6			// 协议字符长度

// 通信协议常量
#define STX     					0x20
#define ETX     					0x03
#define ACK							0x06

//#define FALSE                      0
//#define TRUE                       1
//===========================================================================================================

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数原型:    void ChangeBaud(unsigned char ucBaudNum)
// 函数功能:    改变与模块通信的波特率
// 输入参数:    unsigned char ucBaudNum			// 波特率编号0～7		
// 输出参数:    -
// 说    明:    由于硬件限制，该函数只能使用0、1、2、4编号的波特率
//				0--9600；1--19200；2--28800；3--；4--57600
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SetBaud(unsigned char ucBaudNum);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数原型:    unsigned char ZLG522S_CommInit(void))
// 函数功能:    ZLG522S主控通信接口初始化
// 输入参数:    -		
// 输出参数:    
// 返 回 值:    命令执行结果
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char ZLG522S_CommInit(void);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数原型:    bit Ser_Rcv(void)
// 函数功能:    接收程序
// 输入参数:    -		
// 输出参数:    -
// 返 回 值:    TRUE--接收成功；FALSE--接收失败
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char Ser_Rcv(void);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数原型:    bit Ser_Send(void)
// 函数功能:    发送程序
// 输入参数:    -		
// 输出参数:    -
// 返 回 值:    TRUE--发送成功；FALSE--发送失败
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char Ser_Send(void);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数原型:    unsigned char ZLG522S_Cmd(void)
// 函数功能:    ZLG522S模块命令执行函数
// 输入参数:    -		
// 输出参数:    -
// 返 回 值:    -
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char ZLG522S_Cmd(void);

//===========================================================================================================
#ifdef __cplusplus
	}
#endif

#endif              // __ZLG522S_COMM_H
