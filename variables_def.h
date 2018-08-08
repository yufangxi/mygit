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
/*  2014-4-15 * qiao.chen      * Creation of the file                                                                         */
/*             *                 *                                                                                                                    */
/*****************************************************************************/
/*  Target : M64A                                                                                                                               */
/*  Crystal: 11.0592Mhz                                                                                                                              */
/*****************************************************************************/


/*****************************************************************************/
/*                                                                                                                                                      */
/*  Include Files                                                                                                                                   */
/*                                                                                                                                                      */
/*****************************************************************************/

#include "types.h"

#ifndef _HEADER_VARIABLES_
#define _HEADER_VARIABLES_

extern uint16 g_cbWaitRespDly;
extern unsigned char g_ucSerBuf[];
extern unsigned char g_ucSerBufIdx;	// 串行数据缓冲区索引
extern unsigned char SerDTvalid;				// 串行数据接收有效位
extern unsigned char SEQ;				// 包号,见通信协议
extern unsigned char g_ucIICAddr;		// IIC通信地址
extern unsigned char g_ucBaudNum;		// UART通信波特率编号

extern unsigned char g_bUART;					// 使用UART做通信总线(只有在硬件设置模式下,有效)
extern unsigned char g_bI2C;					// 使用I2C做通信总线


extern uint8 WriteRFIDBLOCK(unsigned char box_id,unsigned char block,unsigned char *data);
extern uint8 ReadRFIDBLOCK(unsigned char box_id,unsigned char block,unsigned char *data);
extern uint8 WriteRFIDSECTOR(unsigned char box_id,unsigned char sector,unsigned char len,unsigned char *data);
extern uint8 ReadRFIDSECTOR(unsigned char box_id,unsigned char sector,unsigned char *data);
extern uint8 ReadRFID_Serial_Number(unsigned char box_id,unsigned char *data);

extern void WriteHopper(uint8 hop_id, uint8 SDP_CMD);
extern void SendTX1(unsigned char txdata);
extern uint8 select_8125(unsigned char number);//有5个串口供选择

extern void delay(uint16 time);//11.0592M,time=1表示延时1ms
extern void delay_us(uint16 time);//11.0592M, Nus延时函数

extern unsigned char PCDConfig(void);
extern unsigned char PiccRequest(unsigned char ucReqCode,unsigned char *pATQ);
extern unsigned char PiccAnticoll(unsigned char ucSelCode,unsigned char ucBcnt,unsigned char *pUID);
extern unsigned char PiccSelect(unsigned char ucSelCode,unsigned char *pUID,unsigned char *pSAK);
extern unsigned char PiccHalt(void);
extern unsigned char PiccActiveTypeA(unsigned char unMode, unsigned char ucReqCode, 
							  unsigned char *pATQ, unsigned char *pSAK,
						      unsigned char *pUIDLen, unsigned char *pUID);
extern unsigned char PiccReadADDT( unsigned char ucMode, unsigned char *pTxDrv, unsigned char *pATQ, 
							unsigned char *pSAK, unsigned char *pUIDLen, 
							unsigned char *pUID, unsigned char *pDataBuf);
extern unsigned char PiccAuthE2(unsigned char ucKeyType, unsigned char *pUID,
						 unsigned char ucKeySector, unsigned char ucBlock);
extern unsigned char PiccAuthKey(unsigned char ucKeyType, unsigned char *pUID, 
						  unsigned char *pKey, unsigned char ucBlock);
extern unsigned char PiccRead(unsigned char ucBlock, unsigned char *pBuf);
extern unsigned char PiccWrite(unsigned char ucBlock,unsigned char *pBuf);
extern unsigned char PiccULWrite(unsigned char ucBlock, unsigned char *pBuf);
extern unsigned char PiccValueOper(unsigned char ucOperMode, unsigned char ucSBlock, 
							unsigned char *pValue, unsigned char ucDBlock);
extern unsigned char PiccSetTX( unsigned char ucSelTX);
extern unsigned char PCDReadReg(unsigned char ucRegAddr,unsigned char *pRegValue);
extern unsigned char PCDWriteReg(unsigned char ucRegAddr,unsigned char ucRegValue);
extern unsigned char PiccReset(unsigned char _1ms);

#endif

