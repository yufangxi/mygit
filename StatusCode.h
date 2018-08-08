////////////////////////////////////////////Copyright (c)//////////////////////////////////////////
//                                   ������������Ƭ����չ���޹�˾
//                                         ��    ��    ��
//                                           �𿨲�Ʒ��
//
//                                     http://www.zlgmcu.com
//
//-------------- �ļ���Ϣ--------------------------------------------------------------------------
// �� �� ��:    StatusCode.h
// �ļ�����:    ״̬����
// ��    ��:    V1.0 
// �� �� ��:    ����ɭ
// ��������:    2008.01.09
//=================================================================================================
//-------------- �޸ļ�¼--------------------------------------------------------------------------
// �޸�����:	���з�������Ϊ�޷�����
// ��ǰ�汾:    
// �� �� ��:	����ɭ
// �޸�����:	2009.06.24
// ע    ��: 
///////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef __STATUS_CODE_H
#define __STATUS_CODE_H

//=================================================================================================
#define STATUS_SUCCESS                  (0)		// �����ɹ�

#define STATUS_IO_TIMEOUT               0xFF	// ��Ӧ�����
#define STATUS_CRC_ERROR                0xFE	// CRCУ�����
#define STATUS_PARITY_ERROR             0xFD	// ��żУ�����
#define STATUS_BITCOUNT_ERROR           0xFC	// ����λ����������
#define STATUS_FRAMING_ERROR            0xFB	// ֡����
#define STATUS_COLLISION_ERROR          0xFA	// λ��ͻ����
#define STATUS_BUFFER_TOO_SMALL         0xF9	// ��������С
#define STATUS_ACCESS_DENIED            0xF8	// д��ֹ
#define STATUS_BUFFER_OVERFLOW          0xF7	// BUF�������
#define STATUS_PROTOCOL_ERROR           0xF6	// ͨ��Э������
#define STATUS_ERROR_NY_IMPLEMENTED     0xF5	// δִ��
#define STATUS_FIFO_WRITE_ERROR         0xF4	// FIFOд����
#define STATUS_USERBUFFER_FULL          0xF3	// �û���������
#define STATUS_INVALID_PARAMETER        0xF2	// ��Ч����
#define STATUS_UNSUPPORTED_PARAMETER    0xF1	// ��֧�ֵĲ���
#define STATUS_UNSUPPORTED_COMMAND      0xF0	// ��֧�ֵ�����
#define STATUS_INTERFACE_ERROR          0xEF	// �����ӿڴ���
#define STATUS_INVALID_FORMAT           0xEE	// ��Ч��ʽ
#define STATUS_INTERFACE_NOT_ENABLED    0xED	// �ӿ�δ����
#define STATUS_AUTHENT_ERROR            0xEC	// ��֤����
#define STATUS_ACK_SUPPOSED             0xEB	// NACK
#define STATUS_BLOCKNR_NOT_EQUAL        0xEA	// ͨ�ſ����

#define STATUS_TARGET_DEADLOCKED        0xE9	// Ŀ������
#define STATUS_TARGET_SET_TOX           0xE8	// Ŀ�����ó�ʱ
#define STATUS_TARGET_RESET_TOX         0xE7	// Ŀ�긴λ
#define STATUS_WRONG_UID_CHECKBYTE      0xE6	// Ŀ��UID������
#define STATUS_WRONG_HALT_FORMAT        0xE5	// �����ʽ����

#define STATUS_ID_ALREADY_IN_USE        0xE4	// ID�ѱ�ʹ��
#define STATUS_INSTANCE_ALREADY_IN_USE  0xE3	// INSTANCE �ѱ�ʹ��
#define STATUS_ID_NOT_IN_USE            0xE2	// ָ����ID������
#define STATUS_NO_ID_AVAILABLE          0xE1	// �޿���ID����

#define STATUS_OTHER_ERROR              0xE0	// ��������
#define STATUS_INSUFFICIENT_RESOURCES   0xDF	// ϵͳ��Դ����
#define STATUS_INVALID_DEVICE_STATE     0xDE	// ��������
#define STATUS_TEMP_ERROR        	    0xDD	// �¶�����

#define STATUS_INIT_ERROR				0xDC	// ��ʼ������
#define STATUS_NO_BITWISE_ANTICOLL		0xDB	// ��֧��Bit֡����ͻ
#define STATUS_SERNR_ERROR				0xDA	// ��֧�ֵķ���ײ�ȼ�
#define STATUS_NY_IMPLEMENTED			0xD9	// ��֧�ֵ�����
#define STATUS_ACCESS_TIMEOUT			0xD8	// ���ʳ�ʱ
#define STATUS_NO_RF_FIELD	            0xD7   	// ��RF������
#define STATUS_NO_TARGET                0xD5   	// ��Ŀ��
#define STATUS_BCC_ERROR	            0xD4 	// BCCУ�����
#define STATUS_MEM_ACCESS_ERROR			0xD3 	// �洢�����ʴ���

// ISO14443 ����������
#define STATUS_ATS_ERROR			    0xCE	// ATS����
#define STATUS_PPS_ERROR  			    0xCD	// PPSS����
#define STATUS_BLOCK_FORMAT_ERROR       0xCC	// ����֡��ʽ���� 
#define STATUS_CID_ERROR  			    0xCB	// CID����
#define STATUS_PCB_ERROR				0xCA	// PCB����
#define STATUS_NAK_ERROR				0xC9	// NAK����
#define STATUS_LEN_ERROR				0xC8	// ���ȴ���
#define STATUS_SEND_ERROR				0xC7	// ���ʹ���
#define STATUS_APDU_ERROR				0xC6	// APDU�������
#define STATUS_PERORM_ERROR				0xC4	// ����ִ�н������
#define STATUS_INVALID_VALUE			0xC3	// ֵ���ʽ����

// PLUS���������
#define STATUS_PLUS_GENERAL_ERROR		0xBF	// ��ͨ��������
#define STATUS_PLUS_LENGTH_ERROR		0xBC	// ���ȴ���
#define STATUS_PLUS_NOT_SATISFIED		0xBB	// ��ȫ�ȼ�����
#define STATUS_PLUS_NO_BNR				0xBA	// �����ڵĿ�
#define STATUS_PLUS_BNR_INVALID			0xB9	// ��Ч�Ŀ��ַ
#define STATUS_PLUS_MAC_INVALID			0xB8	// ��Ч��MAC
#define STATUS_PLUS_CMD_OVERFLOW		0xB7	// ����(����)���
#define STATUS_PLUS_AUTH_ERROR			0xB6	// ��֤����

#define STATUS_PLUS_NOT_SUPPORT_VC		0xB5	// ��֧�����⿨����
#define STATUS_PLUS_VPC_TIMEOUT			0xB4	// �����м̹���

#define STATUS_PLUS_PCD_CAP_ERROR		0xAF	// PCD��������

#define STATUS_INVALID_COMMAND			0x9C	// ��Ч����/��֧�ֵ�����
#define STATUS_FUNCTION_ERR				0x9B	// ���ܴ���
//============= ��д����״̬ ======================================================================
#define STATUS_COMM_OK					0x00
#define STATUS_COMM_ERR					0x01
#define STATUS_COMM_SEQ_ERR				0x02
#define STATUS_COMM_BCC_ERR				0x04
#define STATUS_COMM_INVALID_PARAMETER	0x05	// ��Ч����

#define STATUS_MEM_ACCESS_OVER			0x10	// �洢������Խ��
#define STATUS_MEM_WRITE_ERR			0x11	// �洢��д����
#define STATUS_MEM_BANNED				0x12	// ��ֹ����
#define STATUS_MEM_INVALID_PARAMETER	0x13	// ��Ч����

#define STATUS_7816_OVERTIME_ERR		0x20	// ��ʱ��
#define STATUS_7816_STARTE_ERR			0x21	// ��ʼλ��
#define STATUS_7816_PARITY_ERR			0x22	// У���
#define STATUS_7816_STOP_ERR			0x23	// ֹͣλ��
#define STATUS_7816_ATRE_ERR			0x24	// ��λӦ���
#define STATUS_7816_PPS_ERR				0x25	// PPS����
#define STATUS_7816_CARDNOE_ERR			0x26	// δѡ�񿨴���
#define STATUS_7816_NAD_ERR				0x27	// NAD����
#define STATUS_7816_RCV_ERR				0x28	// ���մ���
#define STATUS_7816_RCV_LEN_ERR			0x29	// ���ճ��ȴ���
#define STATUS_7816_EDC_ERR				0x2A	// У���ֽ�����
#define STATUS_7816_OTHER_ERR			0x2B	// ��������
//=================================================================================================
#endif          // __STATUS_CODE_H

