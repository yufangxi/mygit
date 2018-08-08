
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

#ifndef _HEADER_RFID_
#define _HEADER_RFID_
#define KEYA			0x60
#define KEYB			0x61


//RFIDÄ£¿é³õÊ¼»¯
void rfid_init(void);
//8125Ð¾Æ¬Ñ¡Ôñº¯Êý
uint8 select_8125(uint8 number);

typedef enum 
{
    RFID_OK = 0,                    //Õý³£
    no_RFID_card = 0xa1,          //ÎÞ·¨¼ì²âµ½¿¨ÏäµÄ RFID ¿¨
    RFID_iden_err,                //¿¨Ïä RFID ¿¨ÈÏÖ¤Ê§°Ü
    RW_RFID_err,                  //¶ÁÐ´¿¨Ïä RFID ¿¨²ÎÊý´í
    read_SN_err,                  //¶Á¿¨Ïä SN ºÅ´í
    write_SN_err,                 //Ð´¿¨Ïä SN ºÅ´í
}RFID_COM;

#endif
