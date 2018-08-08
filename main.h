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

#ifndef _HEADER_MAIN_
#define _HEADER_MAIN_

//
#define CMD_NO_ACTION 0
#define CMD_BOX1SCOOP 1
#define CMD_BOX2SCOOP 2
#define CMD_TICKETSELL 3
#define CMD_TICKETRECYCLE 4

//cmd
#define WXDLE 0X10        //控制符
#define WXSTX 0X02        //数据包开始标志
#define WXETX 0X03        //数据包结束标志
#define WXEOT 0X04        //通讯中止标志
#define WXENQ 0X05        //命令执行确认
#define WXACK 0X06        //接收正确回应
#define WXNAK 0X15        //接收错误回应

//E2地址
#define E2ERR_ADDR 0x22	//E2故障存储的地址
#define E2BOXA_STATUS 0x23	//票箱装卸存储地址
#define E2BOXB_STATUS 0x24	//票箱装卸存储地址
#define E2BOXC_STATUS 0x25	//票箱装卸存储地址
#define ABOX_TICKETS_ADDR 0x30       //A票卡计数基地址
#define BBOX_TICKETS_ADDR 0x80       //B票卡计数基地址
#define CBOX_TICKETS_ADDR 0xD0       //C票卡计数基地址
#define MAX_EE_AREA 10
#define AREA_A 1
#define AREA_B 2
#define AREA_C 3

//落票时间
#define DROP_T1  1000
#define DROP_T2  50
#define DCT_T1     20
#define DCT_T2     20
// 读取信息时间
#define READ_MAS  3   //2//读状态超时是60ms
#define INTI_OVER_TIME 250
//一秒时间
#define SECOND  50

typedef struct//结构体
{
	uint32  limit_cnt;
	uint8	limit_en;
}CNT;

typedef union//共用体、联合体
{
	uint8	status[7];
	struct
	{
		uint8   checkticks1;//票卡到天线区检测     0-无票:1-有票
		uint8   checkticks2;//票卡到出币口检测     0-无票:1-有票
		uint8   checkticks3;//票卡到废票箱检测     0-无票:1-有票
		uint8   checkticks4;//电磁铁1检测                    1-打开:0-关断
		uint8   checkticks5;//电磁铁2检测                    1-打开:0-关断
		uint8   checkticks6;//无用
		uint8   checkticks7;//hopper1到位检测                1-到位:0-未到位(备用)
		uint8   checkticks8;//hopper2到位检测                1-到位:0-未到位(备用)
	}SENSORS_STATUS;
}SENSORS;

typedef struct
{
	uint8	addr;
	uint8	data[4];
}EE_SAVE;

typedef union
{
    uint8   code[53];
    struct
    {
        uint8   len;        //当前包的长度
    	uint8	act_code;   //响应码
    	uint8	result;     //返回结果:'e'   'w'   's'
        uint8   err_code;   //故障代码
        uint8   info[49];   //各种信息
    }MESSAGE;
}RETURN_CODE;

typedef enum //枚举
{
	com_ok = 0,					    //无错误
	no_card_at_RW_area,		    //无卡在天线区
	read_clearnum_be_clear,      //未清除币读取清币数量
	card_at_RW_area,              //有卡在天线区告警
	box1_non_existent = 0x39,			//A票箱未到位
	box2_non_existent,			//B票箱未到位
	boxA_empty = 0x3c,			    //A票箱空
	boxB_empty,		            //B票箱空
	card_block_at_RW_area = 0x3f,//票卡在天线区卡票
	card_block_at_exit_area,		//票卡在出票口卡票
	card_block_at_Aexit_area,	//票卡在A出票口卡票
	AWK_no_card,					//A挖卡轮挖不出票卡
	BWK_no_card,					//B挖卡轮挖不出票卡
	equ_busy = 0x4a,				        //设备忙
	clr_err,                        //清空失败
	card_block_at_Bexit_area = 0x62,	//票卡在B出票口卡票
	checkticks_err,				//通道传感器故障
	sole1_err,                     //电磁铁1故障
	sole2_err,                     //电磁铁2故障
	rf232A_err,                    //串口A故障
	rf232B_err,                    //串口B故障
    invalid_parameter=0x31,//参数无效
}CMD_STATUS;

typedef struct
{
    uint8 re_data[20];              //接收到的数据
    uint8 re_index;                 //接收计数
    uint8 re_flag;                  //是否接收完成标志1:接收完成0:未完成
}RESEIVE;




#endif

