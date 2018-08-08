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

#include "Hopper.h"
#include "variables_def.h"
/*****************************************************************************/
/* Function Description:                                                                                                                      */
/*****************************************************************************/
//发送指定数据到hopper
//参数:*dat   指定的数据
/*****************************************************************************/
/* Parameters:                                                                                                                                  */
/*****************************************************************************/
/*                                                                                                                                                     */
/*                                                                                                                                                     */
/*                                                                                                                                                     */
/*****************************************************************************/
/* Return Values:          是否成功                                                                                             */
/*****************************************************************************/
/*                                                                                                                                                      */
/*   NULL                                                                                                                                           */
/*                                                                                                                                                      */
/*****************************************************************************/

void send_hop_dat(uint8 *dat)
{
    uint8 i;
    CMD_HOPPER cmd_hop;
    SendTX1(HOP_STX);
    for(i=0;i<4+dat[3];i++)
    {
        if(dat[i] == HOP_STX || dat[i] == HOP_ETX)
        {
            SendTX1(HOP_STX);
            SendTX1(dat[i]);
        }
        else
        {
            SendTX1(dat[i]);
        }
    }
    SendTX1(dat[sizeof(cmd_hop)-1]);
    SendTX1(HOP_ETX);
}
/*****************************************************************************/
/* Function Description:                                                                                                                      */
/*****************************************************************************/
//生成发送到hopper的数据
//参数:box_id  票箱号，取值范围1，2
//参数:SDP_CMD   命令
/*****************************************************************************/
/* Parameters:                                                                                                                                  */
/*****************************************************************************/
/*                                                                                                                                                     */
/*                                                                                                                                                     */
/*                                                                                                                                                     */
/*****************************************************************************/
/* Return Values:          是否成功                                                                                             */
/*****************************************************************************/
/*                                                                                                                                                      */
/*   NULL                                                                                                                                           */
/*                                                                                                                                                      */
/*****************************************************************************/

void WriteHopper(uint8 hop_id, uint8 SDP_CMD)
{
    static CMD_HOPPER cmd_hop = {0,1,0};
    select_8125(hop_id);

    switch(SDP_CMD)
    {
        case SDP_CMD_STATE_QUERY:
            cmd_hop.DLEN = 1;
            cmd_hop.INFO = SDP_CMD_STATE_QUERY;
            cmd_hop.BCC = cmd_hop.RSEQ + cmd_hop.DESA + cmd_hop.SRCA + cmd_hop.DLEN + cmd_hop.INFO;
            send_hop_dat((uint8*)&cmd_hop);//结构体转换成一个数组的指针
            //cmd_hop.RSEQ++;
            break;
        case SDP_CMD_CHG:
            cmd_hop.DLEN = 3;
            cmd_hop.INFO = SDP_CMD_CHG;
            cmd_hop.DAT[0] = 0;
            cmd_hop.DAT[1] = 1;
            cmd_hop.BCC = cmd_hop.RSEQ + cmd_hop.DESA + cmd_hop.SRCA + cmd_hop.DLEN + cmd_hop.INFO
                         + cmd_hop.DAT[0] + cmd_hop.DAT[1];
            send_hop_dat((uint8*)&cmd_hop);
            //cmd_hop.RSEQ++;
            break;
        case SDP_CMD_CLR:
            cmd_hop.DLEN = 3;
            cmd_hop.INFO = SDP_CMD_CLR;
            cmd_hop.DAT[0] = 0;
            cmd_hop.DAT[1] = 0;
            cmd_hop.BCC = cmd_hop.RSEQ + cmd_hop.DESA + cmd_hop.SRCA + cmd_hop.DLEN + cmd_hop.INFO;
            send_hop_dat((uint8*)&cmd_hop);
            //cmd_hop.RSEQ++;
            break;
        case SDP_CMD_HD_SELF:
            cmd_hop.DLEN = 3;
            cmd_hop.INFO = SDP_CMD_HD_SELF;
            cmd_hop.DAT[0] = 0x04;
            cmd_hop.DAT[1] = 0x01;
            cmd_hop.BCC = cmd_hop.RSEQ + cmd_hop.DESA + cmd_hop.SRCA + cmd_hop.DLEN + cmd_hop.INFO
                         + cmd_hop.DAT[0] + cmd_hop.DAT[1];
            send_hop_dat((uint8*)&cmd_hop);
            //cmd_hop.RSEQ++;
            break;
        case SDP_CMD_STOP_HD_SELF:
            cmd_hop.DLEN = 3;
            cmd_hop.INFO = SDP_CMD_HD_SELF;
            cmd_hop.DAT[0] = 0x04;
            cmd_hop.DAT[1] = 0x00;
            cmd_hop.BCC = cmd_hop.RSEQ + cmd_hop.DESA + cmd_hop.SRCA + cmd_hop.DLEN + cmd_hop.INFO
                         + cmd_hop.DAT[0] + cmd_hop.DAT[1];
            send_hop_dat((uint8*)&cmd_hop);
            //cmd_hop.RSEQ++;
            break;
        case SDP_CMD_VERSION_QUERY:
            cmd_hop.DLEN = 1;
            cmd_hop.INFO = SDP_CMD_VERSION_QUERY;
            cmd_hop.BCC = cmd_hop.RSEQ + cmd_hop.DESA + cmd_hop.SRCA + cmd_hop.DLEN + cmd_hop.INFO;
            send_hop_dat((uint8*)&cmd_hop);//
            //cmd_hop.RSEQ++;
            break;
        case SDP_CMD_STOP_CLR:
            cmd_hop.DLEN = 3;
            cmd_hop.INFO = SDP_CMD_STOP_CLR;
            cmd_hop.DAT[0] = 0;
            cmd_hop.DAT[1] = 0;
            cmd_hop.BCC = cmd_hop.RSEQ + cmd_hop.DESA + cmd_hop.SRCA + cmd_hop.DLEN + cmd_hop.INFO;
            send_hop_dat((uint8*)&cmd_hop);
            //cmd_hop.RSEQ++;
            break;
        default:
            break;
    }
    if(cmd_hop.RSEQ == 0x7f)
        cmd_hop.RSEQ = 0;
}

