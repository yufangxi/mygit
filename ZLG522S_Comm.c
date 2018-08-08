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
#define ZLG522S_COMM_GLOBALS
#include "ZLG522S_Comm.h"

#include "ZLG522S.h"
#include "StatusCode.h"


//============= 全局变量定义 ================================================================================
// 不支持的波特率都用19200代替
unsigned char BaudRateTab[BAUD_CNT] = {0,	0, 0,	0,
										 	0,	0, 0, 0};
unsigned char g_ucSerBuf[MAX_SER_SIZE];// 串行数据缓冲区
unsigned char g_ucSerBufIdx;	// 串行数据缓冲区索引
unsigned char SEQ;				// 包号,见通信协议
unsigned char g_ucIICAddr;		// IIC通信地址
unsigned char g_ucBaudNum;		// UART通信波特率编号

unsigned char SerDTvalid;				// 串行数据接收有效位
unsigned char g_bUART;					// 使用UART做通信总线(只有在硬件设置模式下,有效)
unsigned char g_bI2C;					// 使用I2C做通信总线


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数原型:    void ChangeBaud(unsigned char ucBaudNum)
// 函数功能:    改变与模块通信的波特率
// 输入参数:    unsigned char ucBaudNum			// 波特率编号0～7		
// 输出参数:    -
// 说    明:    由于硬件限制，该函数只能使用0、1、2、4编号的波特率
//				0--9600；1--19200；2--28800；3--；4--57600
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SetBaud(unsigned char ucBaudNum)
{
	
	g_ucBaudNum = ucBaudNum;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数原型:    unsigned char  SetModeBaud(void)
// 函数功能:    设置模块的波特率
// 输入参数:    -		
// 输出参数:    -
// 返 回 值:    1--执行成功；0--执行失败
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char  SetModeBaud(void)
{
	/*unsigned char temp;
	unsigned char SetCunt = 3;

	while(SetCunt)
	{
		SBUF = STX;
		while(TI == 0);	TI = 0;
		for(temp= 60;temp != 0;temp--);			// 延时30us
		SBUF = STX;
		while(TI == 0);	TI = 0;

		g_cbWaitRespDly = ZLG522S_DELAY_20MS;	// 设置20ms超时
		while(RI == 0 && g_cbWaitRespDly);	
		RI = 0;
		if(g_cbWaitRespDly == 0)
		{
			SetCunt--;
			continue;
		}
		else
		{
			temp = SBUF;
			if(temp == ACK)
				return TRUE;
			else
			{
				SetCunt--;
				continue;
			}
		}
	}*/
	return FALSE;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数原型:    unsigned char ZLG522S_CommInit(void))
// 函数功能:    ZLG522S主控通信接口初始化
// 输入参数:    -		
// 输出参数:    
// 返 回 值:    命令执行结果
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char ZLG522S_CommInit(void)
{

	if (g_bI2C)									// IIC模式，直接退出
		return STATUS_COMM_OK;
/*	ES = 0;
	PCON =  0x80;              					// SMOD = 1;
	SCON =  0x50;              					// Mode 1, 8-bit UART, enable receiption
	TMOD &= 0x0f;
	TMOD |= 0x20;	      						// Timer 1, mode 2, 8-bit auto reload,*/
	SetBaud(g_ucBaudNum);

	if (g_bUART)								// 硬件设置波特率模式。
	{
		//ES = 1;
		return STATUS_COMM_OK;
	}

    SerDTvalid = FALSE;
	if (SetModeBaud())
	{
		//ES = 1;
		return STATUS_COMM_OK;
	}
	return 	STATUS_COMM_ERR;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数原型:    unsigned char Ser_Rcv(void)
// 函数功能:    接收程序
// 输入参数:    -		
// 输出参数:    -
// 返 回 值:    TRUE--接收成功；FALSE--接收失败
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char Ser_Rcv(void)
{
	unsigned char i,BCC;

    
	if (SerDTvalid)
	{											// 已接收一帧数据,进行数据校验
		if(g_ucSerBuf[g_ucSerBuf[FRAMELEN]-1] == ETX && g_ucSerBuf[FRAMELEN] == (g_ucSerBuf[LENGTH]+PRTCLEN))
		{// 正确接收到ETX,及帧长度等于数据长度加协议长度,则数据有效
			BCC = 0;
			for(i=0; i<(g_ucSerBuf[FRAMELEN]-1); i++)
			{
				BCC ^= g_ucSerBuf[i];
			}
			if(BCC == 0xff)
			{
				SerDTvalid = FALSE;				// BCC校验通过
				return TRUE;				
			}
		}
		SerDTvalid = FALSE;
	}
	return FALSE;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数原型:    bit Ser_Send(void)
// 函数功能:    发送程序
// 输入参数:    -		
// 输出参数:    -
// 返 回 值:    TRUE--发送成功；FALSE--发送失败
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
uint8 Ser_Send(void)
{
    unsigned char i,BCC;

	g_ucSerBuf[FRAMELEN] = g_ucSerBuf[LENGTH] + PRTCLEN;	//帧长度等于数据长度加协议长度
	BCC = 0;
	for(i=0; i<(g_ucSerBuf[FRAMELEN]-2); i++)
		BCC ^= g_ucSerBuf[i];
	g_ucSerBuf[g_ucSerBuf[FRAMELEN]-2] = ~BCC;
	g_ucSerBuf[g_ucSerBuf[FRAMELEN]-1] = ETX;	
	g_ucSerBufIdx = FRAMELEN;						// 设置帧起始地址
	/*///////////////////////////////////////
    g_ucSerBuf[0] = 0xb2;
    g_ucSerBuf[1] = 0x00;
    g_ucSerBuf[2] = 0x00;
    g_ucSerBuf[3] = 0x01;
    g_ucSerBuf[4] = 0x00;
    g_ucSerBuf[5] = 0x41;
    g_ucSerBuf[6] = 0x00;
    g_ucSerBuf[7] = 0x00;
    g_ucSerBuf[8] = 0xff;
    g_ucSerBuf[9] = 0x0b;
    ////////////////////////////////////////*/
    for(i=0; i<(g_ucSerBuf[FRAMELEN]); i++)
    //for(i=0; i<10; i++)
        SendTX1(g_ucSerBuf[i]);
	SerDTvalid = FALSE;						// 接收的数据无效
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数原型:    unsigned char ZLG522S_Cmd(void)
// 函数功能:    ZLG522S模块命令执行函数
// 输入参数:    -		
// 输出参数:    -
// 返 回 值:    -
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char ZLG522S_Cmd(void)
{
	unsigned char ucStatus;
		
	//SEQ += 0x10;
	//g_ucSerBuf[CMDTYPE] |= SEQ;						// 命令类型与包号组成一个字节

	if(!Ser_Send())	
		return STATUS_COMM_ERR;
		
	g_cbWaitRespDly = ZLG522S_DELAY_500MS;		// 延时500ms
	while(g_cbWaitRespDly)						// 等待响应
	{
		if(Ser_Rcv())
			break;
	}

	if(g_cbWaitRespDly == 0)
	{											// 500ms内未收到响应
		ucStatus = STATUS_COMM_ERR;
	}
	else
	{	
		if(SEQ == (g_ucSerBuf[CMDTYPE]&0xf0))
		{										// 包号匹配
			ucStatus = STATUS_COMM_OK;
		}
		else
			ucStatus = STATUS_COMM_SEQ_ERR;		// 包号不匹配
	}
	return ucStatus;
}


