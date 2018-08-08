
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

#ifndef _HEADER_HOPPER_
#define _HEADER_HOPPER_

#define hopper1 1
#define hopper2 2
typedef enum            //ECU 命令常量
{
    SDP_CMD_START = 0,//命令开始
    SDP_CMD_SW_RESET,//软件复位的命令
    SDP_CMD_BUILD_VERSION_TIME = 0x10,//固件编译版本和日期的命令
    SDP_CMD_ADDRESS_QUERY,//地址查询的命令
    SDP_CMD_STATE_QUERY,//状态查询的命令
    SDP_CMD_VERSION_QUERY,//固件版本查询的命令
    SDP_CMD_LIMIT_QUERY,//极限参数查询的命令
    SDP_CMD_REALTIME_QUERY,//实时参数查询的命令
    SDP_CMD_ADDRESS_MODIFY = 0x21,//地址更改的命令
    SDP_CMD_LIMIT_MODIFY = 0x24,//极限参数修改的命令
    SDP_CMD_REALTIME_MODIFY,//实时参数修改的命令
    SDP_CMD_HD_SELF = 0x40,//硬件自检的命令
    SDP_CMD_STOP_HD_SELF,   //停止自检
    SDP_CMD_CHG = 0x60,//硬币找零的命令
    SDP_CMD_CLR,//Token 硬币清币的命令
    SDP_CMD_STOP_CLR,//停止清币命令
    ARR_SDP_CMD_END = 0x7F,//
} enumARR_SDP_CMD;

typedef enum            //HTU 命令反馈常量
{
    SDP_ACK_START = 0x80,//命令响应的命令开始
    SDP_ACK_CMD_ACK = 0x90,//命令响应的命令反馈
    SDP_ACK_CMD_INTIME = 0xA0,//及时命令响应的命令反馈
    SDP_ACK_CMD_UNTIME,//不定时命令响应的命令反馈
    SDP_ACK_ERR = 0xE0,//故障的命令反馈
    SDP_ACK_MSG_VALID_CHK,//命令反馈正确的校验码反馈
    ARR_SDP_ACK_END = 0xFF,//
} enumARR_SDP_ACK;

typedef enum            //HTU 故障/状态常量
{
    SDP_ACK_ERR_START = 0,//预留故障/状态
    SDP_ACK_ERR_ADDR_SAME,//地址相同故障/状态
    SDP_ACK_ERR_MSG_CHK,//协议校验故障/状态
    SDP_ACK_ERR_CMD_INVALID,//命令无效的故障/状态
    SDP_ACK_ERR_CMD_HOPPER_BUSY,//命令斗正忙故障/状态
    SDP_ACK_ERR_CMD_NOCMD,//命令无法识别故障/状态
    ARR_SDP_ACK_ERR_END,//结束故障/状态
} enumARR_SDP_ACK_ERR;

#define HOP_STX 0x7f     //帧起始符
#define HOP_ETX 0x80     //帧结束符
typedef struct
{
    //const uint8 HOP_STX = 0x7f;     //帧起始符
    uint8 RSEQ;                 //流水号
    uint8 DESA;              //目标地址
    uint8 SRCA;               //源地址
    uint8 DLEN;                     //数据长度
    uint8 INFO;                 //命令/ 应答/消息
    uint8 DAT[50];                  //数据
    uint8 BCC;                  //校验
    //const uint8 HOP_ETX = 0x80;    //帧结束符
}CMD_HOPPER;

#endif
