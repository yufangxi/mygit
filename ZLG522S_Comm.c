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


//============= ȫ�ֱ������� ================================================================================
// ��֧�ֵĲ����ʶ���19200����
unsigned char BaudRateTab[BAUD_CNT] = {0,	0, 0,	0,
										 	0,	0, 0, 0};
unsigned char g_ucSerBuf[MAX_SER_SIZE];// �������ݻ�����
unsigned char g_ucSerBufIdx;	// �������ݻ���������
unsigned char SEQ;				// ����,��ͨ��Э��
unsigned char g_ucIICAddr;		// IICͨ�ŵ�ַ
unsigned char g_ucBaudNum;		// UARTͨ�Ų����ʱ��

unsigned char SerDTvalid;				// �������ݽ�����Чλ
unsigned char g_bUART;					// ʹ��UART��ͨ������(ֻ����Ӳ������ģʽ��,��Ч)
unsigned char g_bI2C;					// ʹ��I2C��ͨ������


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����ԭ��:    void ChangeBaud(unsigned char ucBaudNum)
// ��������:    �ı���ģ��ͨ�ŵĲ�����
// �������:    unsigned char ucBaudNum			// �����ʱ��0��7		
// �������:    -
// ˵    ��:    ����Ӳ�����ƣ��ú���ֻ��ʹ��0��1��2��4��ŵĲ�����
//				0--9600��1--19200��2--28800��3--��4--57600
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SetBaud(unsigned char ucBaudNum)
{
	
	g_ucBaudNum = ucBaudNum;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����ԭ��:    unsigned char  SetModeBaud(void)
// ��������:    ����ģ��Ĳ�����
// �������:    -		
// �������:    -
// �� �� ֵ:    1--ִ�гɹ���0--ִ��ʧ��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char  SetModeBaud(void)
{
	/*unsigned char temp;
	unsigned char SetCunt = 3;

	while(SetCunt)
	{
		SBUF = STX;
		while(TI == 0);	TI = 0;
		for(temp= 60;temp != 0;temp--);			// ��ʱ30us
		SBUF = STX;
		while(TI == 0);	TI = 0;

		g_cbWaitRespDly = ZLG522S_DELAY_20MS;	// ����20ms��ʱ
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
// ����ԭ��:    unsigned char ZLG522S_CommInit(void))
// ��������:    ZLG522S����ͨ�Žӿڳ�ʼ��
// �������:    -		
// �������:    
// �� �� ֵ:    ����ִ�н��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char ZLG522S_CommInit(void)
{

	if (g_bI2C)									// IICģʽ��ֱ���˳�
		return STATUS_COMM_OK;
/*	ES = 0;
	PCON =  0x80;              					// SMOD = 1;
	SCON =  0x50;              					// Mode 1, 8-bit UART, enable receiption
	TMOD &= 0x0f;
	TMOD |= 0x20;	      						// Timer 1, mode 2, 8-bit auto reload,*/
	SetBaud(g_ucBaudNum);

	if (g_bUART)								// Ӳ�����ò�����ģʽ��
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
// ����ԭ��:    unsigned char Ser_Rcv(void)
// ��������:    ���ճ���
// �������:    -		
// �������:    -
// �� �� ֵ:    TRUE--���ճɹ���FALSE--����ʧ��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char Ser_Rcv(void)
{
	unsigned char i,BCC;

    
	if (SerDTvalid)
	{											// �ѽ���һ֡����,��������У��
		if(g_ucSerBuf[g_ucSerBuf[FRAMELEN]-1] == ETX && g_ucSerBuf[FRAMELEN] == (g_ucSerBuf[LENGTH]+PRTCLEN))
		{// ��ȷ���յ�ETX,��֡���ȵ������ݳ��ȼ�Э�鳤��,��������Ч
			BCC = 0;
			for(i=0; i<(g_ucSerBuf[FRAMELEN]-1); i++)
			{
				BCC ^= g_ucSerBuf[i];
			}
			if(BCC == 0xff)
			{
				SerDTvalid = FALSE;				// BCCУ��ͨ��
				return TRUE;				
			}
		}
		SerDTvalid = FALSE;
	}
	return FALSE;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����ԭ��:    bit Ser_Send(void)
// ��������:    ���ͳ���
// �������:    -		
// �������:    -
// �� �� ֵ:    TRUE--���ͳɹ���FALSE--����ʧ��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
uint8 Ser_Send(void)
{
    unsigned char i,BCC;

	g_ucSerBuf[FRAMELEN] = g_ucSerBuf[LENGTH] + PRTCLEN;	//֡���ȵ������ݳ��ȼ�Э�鳤��
	BCC = 0;
	for(i=0; i<(g_ucSerBuf[FRAMELEN]-2); i++)
		BCC ^= g_ucSerBuf[i];
	g_ucSerBuf[g_ucSerBuf[FRAMELEN]-2] = ~BCC;
	g_ucSerBuf[g_ucSerBuf[FRAMELEN]-1] = ETX;	
	g_ucSerBufIdx = FRAMELEN;						// ����֡��ʼ��ַ
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
	SerDTvalid = FALSE;						// ���յ�������Ч
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����ԭ��:    unsigned char ZLG522S_Cmd(void)
// ��������:    ZLG522Sģ������ִ�к���
// �������:    -		
// �������:    -
// �� �� ֵ:    -
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char ZLG522S_Cmd(void)
{
	unsigned char ucStatus;
		
	//SEQ += 0x10;
	//g_ucSerBuf[CMDTYPE] |= SEQ;						// ����������������һ���ֽ�

	if(!Ser_Send())	
		return STATUS_COMM_ERR;
		
	g_cbWaitRespDly = ZLG522S_DELAY_500MS;		// ��ʱ500ms
	while(g_cbWaitRespDly)						// �ȴ���Ӧ
	{
		if(Ser_Rcv())
			break;
	}

	if(g_cbWaitRespDly == 0)
	{											// 500ms��δ�յ���Ӧ
		ucStatus = STATUS_COMM_ERR;
	}
	else
	{	
		if(SEQ == (g_ucSerBuf[CMDTYPE]&0xf0))
		{										// ����ƥ��
			ucStatus = STATUS_COMM_OK;
		}
		else
			ucStatus = STATUS_COMM_SEQ_ERR;		// ���Ų�ƥ��
	}
	return ucStatus;
}


