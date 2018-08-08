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

#ifndef _HEADER_REG_
#define _HEADER_REG_

//reg
#define  SRADD_8125    PINC & 0x7   
#define  SETB_8125MS   PORTC |= (1 << PC6)
#define  CLR_8125MS    PORTC &= ~(1 << PC6)
#define  SETB_STADD0   PORTC |= (1 << PC5)
#define  CLR_STADD0    PORTC &= ~(1 << PC5)
#define  SETB_STADD1   PORTC |= (1 << PC4)
#define  CLR_STADD1    PORTC &= ~(1 << PC4)
#define  SETB_STADD2   PORTC |= (1 << PC3)
#define  CLR_STADD2    PORTC &= ~(1 << PC3)
#define  SETB_8125RST  PORTD |= (1 << PD1)
#define  CLR_8125RST   PORTD &= ~(1 << PD1)

//#define  SOLE2_ON       PORTA |= (1 << PA6)
//#define  SOLE2_OFF      PORTA &= ~(1 << PA6)
//#define  SOLE1_ON       PORTA |= (1 << PA4)
//#define  SOLE1_OFF      PORTA &= ~(1 << PA4)

#define  SOLE2_ON_2       PORTA |= (1 << PA7)
#define  SOLE2_OFF_2      PORTA &= ~(1 << PA7)
#define  SOLE2_ON_1       PORTA |= (1 << PA6)
#define  SOLE2_OFF_1      PORTA &= ~(1 << PA6)

#define  SOLE1_ON_1      PORTA |= (1 << PA4)
#define  SOLE1_OFF_1      PORTA &= ~(1 << PA4)
#define  SOLE1_ON_2      PORTA |= (1 << PA5)
#define  SOLE1_OFF_2      PORTA &= ~(1 << PA5)

#define  SensorP_ON     PORTB &= ~(1 << PB5)
#define  SensorP_OFF    PORTB |= (1 << PB5)

//定时器2开启关闭中断定义
#define  Timer2_Start  TIMSK |= (1<<7)
#define  Timer2_Close  TIMSK &= ~(1<<7)

//心跳灯引脚
#define  WORK_LIGHT_ON  PORTE |= (1 << PE2)
#define  WORK_LIGHT_OFF PORTE &= ~(1 << PE2)

//天线区有票指示
#define  antenna_LED_ON    PORTA |= (1 << PA1)
#define  antenna_LED_OFF   PORTA &= ~(1 << PA1)

//hopper1回复挖票成功指示
#define  HOPPER1_LED_ON    PORTA |= (1 << PA2)
#define  HOPPER1_LED_OFF   PORTA &= ~(1 << PA2)

//hopper2回复挖票成功指示
#define  HOPPER2_LED_ON    PORTA |= (1 << PA3)
#define  HOPPER2_LED_OFF   PORTA &= ~(1 << PA3)

#endif

