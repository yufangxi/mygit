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

#include "main.h"
#include "Reg.h"
#include "variables_def.h"
#include "hopper.h"
#include "ZLG522S_Comm.h"
#include "ZLG522S_Mifare.h"
#include "StatusCode.h"

void read_sensorstatus(void);
void cmd_act(uint8 cmd);
uint8 Check_LRC(uint8 *ptr, uint8 len);
void USART_Transmit(unsigned char data);
void module_init(RETURN_CODE *re_comm);
void SOLE1_ON(void);
void SOLE1_OFF(void);
void SOLE2_ON(void);
void SOLE2_OFF(void);

//版本号
uint8 MODULE_VERSION[8] = "ToIM002A";
uint8 CPU_VERSION[7] = "V1.0a02";

//看门狗定时复位
uint8   wdt_reseten = 1;
uint16  wdt_resetreg;
//uart0,与ECU通信发送接收用变量定义
//通信缓存
uint8   receive_ok;//uart0数据接收完成标志  1:成功  0:否
uint8   inbox[60];//接收数据缓存
static uint8   n = 0;
static uint8 receive_buff[60];
RESEIVE hop1_re,hop2_re;
uint8 result=0;

uint8 antenna = 0;          //天线区是否有卡标志
uint16 drop_tic_time = 0;   //落票延时,每次打开电磁铁需从定时器延时
uint16 init_over_time = 0;  //初始化hopper超时
uint16 over_time = 0;    //通信超时

//心跳灯控制  1表示启动心跳灯，频率1HZ   ；2心跳灯加速，有故障
//0停止跳动
uint8 normal_start = 0;    

//传感器状态
SENSORS sens;
SENSORS sens_last;

//ee存储票卡数量地址区间
EE_SAVE e2_Abox[MAX_EE_AREA];
EE_SAVE e2_Bbox[MAX_EE_AREA];
EE_SAVE e2_Cbox[MAX_EE_AREA];
EE_SAVE *headA;
EE_SAVE *headB;
EE_SAVE *headC;
uint32 Abox_num=0;
uint32 Bbox_num=0;
uint32 Cbox_num=0;
//通信步骤
static uint8 communication_step = 1;

//RFID超时延时
uint16 g_cbWaitRespDly = 0;

/*****************************************************************************/
/* Function Description:                                                                                                                      */
/*****************************************************************************/
//延时程序
//参数:time  延时参数
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
void delay(uint16 time)
{
 uint16 i;
 for(;time>0;time--)
    {
      for(i=0;i<1574;i++);
	     {
           asm("nop");
           asm("nop");
           asm("nop");
		 }
	}
}
/*****************************************************************************/
/* Function Description:                                                                                                                      */
/*****************************************************************************/
//延时程序
//参数:time  延时参数
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
void delay_us(uint16 time)//11.0592M, Nus延时函数
{
    uint16 i;
    for(i=0;i<time;i++)
    { 
    asm("nop"); 
    }
}

/*****************************************************************************/
/* Function Description:                                                                                                                      */
/*****************************************************************************/
//初始化
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

void port_init(void)
{
    PORTA = 0x01;
    DDRA = 0xff;
    PORTB = 0x20;
    DDRB = 0x20;
    PORTC = 0x40; //m103 output only
    DDRC = 0x78;
    PORTD = 0x02;
    DDRD = 0x0a;
    PORTE = 0x0;//0x10;
    DDRE = 0x04;
    PORTF = 0x00;
    DDRF = 0x00;
    PORTG = 0x00;
    DDRG = 0x00;
}

/*****************************************************************************/
/* Function Description:                                                                                                                      */
/*****************************************************************************/
//初始化
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
void watchdog_init(void)
{
    WDR(); //this prevents a timout on enabling
    WDTCR = 0x1F;
    WDTCR = 0x0F; //WATCHDOG ENABLED - dont forget to issue WDRs
}

/*****************************************************************************/
/* Function Description:                                                                                                                      */
/*****************************************************************************/
//初始化
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
void timer2_init(void)
{
    TCCR2 = 0x00; //stop
    //TCNT2 = 0xBB; //setup
    OCR2  = 0xd8;//0x45;
    TCCR2 = 0x0d;//1024分频ctc模式
}

/*****************************************************************************/
/* Function Description:                                                                                                                      */
/*****************************************************************************/
//初始化
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
void uart0_init(void)
{
    UCSR0B = 0x00; //disable while setting baud rate
    UCSR0A = 0x00;
    UCSR0C = 0x06;
    UBRR0L = 0x0b; //set baud rate lo       //57600
    UBRR0H = 0x00; //set baud rate hi
    UCSR0B = 0x98;
}
/*****************************************************************************/
/* Function Description:                                                                                                                      */
/*****************************************************************************/
//串口接收中断，接收上位机命令，并进行解析
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
#pragma interrupt_handler uart0_rx_isr:iv_USART0_RXC
void uart0_rx_isr(void)//--------------------------MCU与ECU通信接口，MCU作为从机,波特率9600
{
    uint8 i,j,k;
    uint8 temp;
    receive_buff[n] = UDR0;
    switch(communication_step)
    {
        case 1:
        {   if(n > 0)
            {
                if(receive_buff[0] == WXDLE && receive_buff[1] == WXEOT)
                {
                    for(i=0;i<=n;i++)
                        receive_buff[i] = 0;
                    n = 0xff;
                    cmd_act(WXEOT);
                    communication_step = 1;
                }
                else if(receive_buff[0] == WXDLE && receive_buff[1] == WXSTX)    //数据包开始
                {
                    for(i=0;i<=n;i++)
                        receive_buff[i] = 0;
                    n = 0xff;
                    communication_step = 2;
                }
                else if(receive_buff[0] == WXDLE && receive_buff[1] == WXENQ)   //收到命令确认
                {
                    for(i=0;i<=n;i++)
                        receive_buff[i] = 0;
                    n = 0xff;
                    receive_ok = 1;//重新发送命令响应数据
                }
                else 
                {
                    for(i=0;i<=n;i++)
                        receive_buff[i] = 0;
                    n = 0xff;
                }
            }
            else if(receive_buff[0] != WXDLE)
            {
                for(i=0;i<=n;i++)
                        receive_buff[i] = 0;
                n = 0xff;
            }
            break;
        }
        case 2:
        {
            over_time = 5*SECOND;       //5S时间
            if(receive_buff[0] == WXDLE && receive_buff[1] == WXSTX)    //接收开始，保持不变
            {
                for(i=0;i<=n;i++)
                    receive_buff[i] = 0;
                n = 0xff;
                communication_step = 2;
            }
            else if(receive_buff[0] == WXDLE && receive_buff[1] == WXEOT)    //通信中止
            {
                for(i=0;i<=n;i++)
                    receive_buff[i] = 0;
                n = 0xff;
                cmd_act(WXEOT);
                communication_step = 1;
            }
            else if(receive_buff[n-2] == WXDLE && receive_buff[n-1] == WXETX)
            {
                for(i=n-2,j=0;i>0;i--)
                {
                    if(receive_buff[i] == WXDLE)     //判断ETX前面有几个0x10
                        j++;
                    else
                        break;
                }
                if((j&0x1) != 0)                //如果是奇数个，表示ETX为结束，否则为数据
                {
                    for(i=0,k=0;k<n-2;i++,k++)
                    {
                        if(receive_buff[k] == WXDLE)
                        {
                              k++;
                        }
                        inbox[i] = receive_buff[k];
                    }
                    temp = Check_LRC(inbox,i);
                    if(temp != receive_buff[n])     //如果校验不对则回复接收错误,并转入状态1
                    {
                        cmd_act(WXNAK);
                        communication_step = 1;
                    }
                    else            //回复接收正确，并且转入状态3
                    {
                        cmd_act(WXACK);
                        communication_step = 3;
                    }
                    
                    for(i=0;i<=n;i++)
                        receive_buff[i] = 0;
                    n = 0xff;
                }
            }
            break;
        }
        case 3:
        {
            if(receive_buff[0] == WXDLE && receive_buff[1] == WXENQ)        //命令执行确认
            {
                receive_ok = 1;
                for(i=0;i<=n;i++)
                    receive_buff[i] = 0;
                n = 0xff;
            }
            else if(receive_buff[0] == WXDLE && receive_buff[1] == WXSTX)   //数据包开始标志
            {
                for(i=0;i<=n;i++)
                    receive_buff[i] = 0;
                n = 0xff;
                communication_step = 2;
            }
            else if(receive_buff[0] == WXDLE && receive_buff[1] == WXEOT)    //通信中止
            {
                for(i=0;i<=n;i++)
                    receive_buff[i] = 0;
                n = 0xff;
                cmd_act(WXEOT);
                communication_step = 1;
            }
            break;
        }
    }
    n++;
}
/*****************************************************************************/
/* Function Description:                                                                                                                      */
/*****************************************************************************/
//校验
//参数*ptr  数据指针
//参数 len  校验数据长度
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

uint8 Check_LRC(uint8 *ptr, uint8 len)   
{  
  uint8 i=0, lrc=0; 
  while(len--!=0)   
  { 
    lrc ^= (*ptr);
    ptr++;  
  }  
  return(lrc);  
}

/*****************************************************************************/
/* Function Description:                                                                                                                      */
/*****************************************************************************/
//命令响应函数
//参数cmd  响应的命令字节
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
void cmd_act(uint8 cmd)
{
    USART_Transmit(WXDLE);
    USART_Transmit(cmd);
}
/*****************************************************************************/
/* Function Description:                                                                                                                      */
/*****************************************************************************/
//串口发送
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
void USART_Transmit(unsigned char data)
{
    while(!(UCSR0A & (1<<UDRE0)));  //判断UDR是否为空
    //delay_ms(10);
    UDR0 = data;                      //发送数据
}
/*****************************************************************************/
/* Function Description:                                                                                                                      */
/*****************************************************************************/
//初始化
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
void uart1_init(void)
{
    UCSR1B = 0x00; //disable while setting baud rate
    UCSR1A = 0x02;
    UCSR1C = 0x06;
    UBRR1L = 0x0b; //set baud rate lo
    UBRR1H = 0x00; //set baud rate hi
    UCSR1B = 0x98;
}
/*****************************************************************************/
/* Function Description:                                                                                                                      */
/*****************************************************************************/
//串口接收中断，接收hopper和读写器的数据，并进行解析
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
#pragma interrupt_handler uart1_rx_isr:iv_USART1_RXC
void uart1_rx_isr(void)//-------------------------MCU与RFID通信接口，MCU作为主机
{
    //uart has received a character in UDR
    uint8 i=1,j=0,k=0;
    uint8 temp_bcc=0;
    static RESEIVE hop1_re_temp,hop2_re_temp;
    switch(SRADD_8125)
    {
        case 0x00:
            result = UDR1;
            break;
        case 0x06:                              //通道3，hop1
            hop1_re_temp.re_data[hop1_re_temp.re_index] = UDR1;
            hop1_re_temp.re_index++;
            break;
        case 0x04:                              //通道1，hop2
            hop2_re_temp.re_data[hop2_re_temp.re_index] = UDR1;
            hop2_re_temp.re_index++;
            break;
        case 0x01:                              //通道4，tag2
            
        case 0x02:                              //通道2，tag1
            g_ucSerBuf[g_ucSerBufIdx] = UDR1;
            if(g_ucSerBufIdx == FRAMELEN)
            {
                if(g_ucSerBuf[FRAMELEN] < PRTCLEN || g_ucSerBuf[FRAMELEN] > MAX_SER_SIZE)
                {
                    return;
                }
            }
            g_ucSerBufIdx++;

            if(g_ucSerBufIdx >= g_ucSerBuf[FRAMELEN])
            {
                SerDTvalid = TRUE;
                g_ucSerBufIdx = FRAMELEN;
            }
            break;
        default:
            break;
    }
    if(hop1_re_temp.re_data[hop1_re_temp.re_index-1] == HOP_ETX)
    {
        while(i++)
        {
            if(hop1_re_temp.re_data[hop1_re_temp.re_index-i] != HOP_STX)
                break;
            else 
                j++;
        }
        if((j & 0x01) == 0)
        {
            //如果接收完成则判断
            hop1_re.re_data[0] = hop1_re_temp.re_data[0];
            for(i=1,k=1;i<hop1_re_temp.re_index;i++,k++)
            {
                if(hop1_re_temp.re_data[i] == HOP_STX)
                {
                    i++;
                }
                hop1_re.re_data[k] = hop1_re_temp.re_data[i];
            }
            for(j=1;j<k-2;j++)
                temp_bcc += hop1_re.re_data[j];
            if(temp_bcc != hop1_re.re_data[k-2])       
            {
                //校验不正确则重新接收
                for(i=0;i<20;i++)
                    hop1_re.re_data[i] = 0;
                hop1_re_temp.re_index = 0;
            }
            else
            {
                //校验正确则正常处理
                for(i=0;i<20;i++)
                {
                    hop1_re_temp.re_data[i] = 0;
                }
                hop1_re.re_flag = 1;
                hop1_re_temp.re_index = 0;
            }
            temp_bcc = 0;
        }
    }

    if(hop2_re_temp.re_data[hop2_re_temp.re_index-1] == HOP_ETX)
    {
        while(i++)
        {
            if(hop2_re_temp.re_data[hop2_re_temp.re_index-i] != HOP_STX)
                break;
            else 
                j++;
        }
        if((j & 0x01) == 0)
        {
            //如果接收完成则判断
            hop2_re.re_data[0] = hop2_re_temp.re_data[0];
            for(i=1,k=1;i<hop2_re_temp.re_index;i++,k++)
            {
                if(hop2_re_temp.re_data[i] == HOP_STX)
                {
                    i++;
                }
                hop2_re.re_data[k] = hop2_re_temp.re_data[i];
            }
            for(j=1;j<k-2;j++)
                temp_bcc += hop2_re.re_data[j];
            if(temp_bcc != hop2_re.re_data[k-2])       
            {
                //校验不正确则重新接收
                for(i=0;i<20;i++)
                    hop2_re.re_data[i] = 0;
                hop2_re_temp.re_index = 0;
            }
            else
            {
                //校验正确则正常处理
                for(i=0;i<20;i++)
                {
                    hop2_re_temp.re_data[i] = 0;
                }
                hop2_re.re_flag = 1;
                hop2_re_temp.re_index = 0;
            }
        }
    }
}
/*****************************************************************************/
/* Function Description:                                                                                                                      */
/*****************************************************************************/
//串口发送
//参数txdata 发送的数据
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
void SendTX1(unsigned char txdata)
{
  while(!(UCSR0A & (1 << UDRE1)));  //判断UDR是否为空
  UDR1 = txdata;                    //发送数据
  delay_us(800);//写RFID延时时间
}

/*****************************************************************************/
/* Function Description:                                                                                                                      */
/*****************************************************************************/
//初始化
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
void init_devices(void)
{
    //stop errant interrupts until set up
    CLI(); //disable all interrupts
    XDIV  = 0x00; //xtal divider
    XMCRA = 0x00; //external memory
    port_init();
    watchdog_init();
    //timer0_init();
    //timer1_init();
    timer2_init();
    uart0_init();
    uart1_init();

    MCUCR = 0x00;//0x80
    XMCRB = 0x07;
    EICRA = 0x00; //extended ext ints
    EICRB = 0x01; //extended ext ints       //0x00
    EIMSK = 0x00;
    EIFR = 0x00;
    TIMSK = 0x01; //timer interrupt sources
    ETIMSK = 0x00; //extended timer interrupt sources
    SEI(); //re-enable interrupts
    //all peripherals are now initialized
}

/*****************************************************************************/
/* Function Description:                                                                                                                      */
/*****************************************************************************/
/*  初始化RFID                                                                                                                           */
/*                                                                                                                                                      */
/*****************************************************************************/
/* Parameters:                                                                                                                                  */
/*****************************************************************************/
/*                                                                                                                                                      */
/*                                                                                                                                                      */
/*                                                                                                                                                      */
/*****************************************************************************/
/* Return Values:                                                                                                                               */
/*****************************************************************************/
/*                                                                                                                                                      */
/*   NULL                                                                                                                                           */
/*                                                                                                                                                      */
/*****************************************************************************/
void rfid_init(void)
{
    uint8 i;
    UCSR1C=0x0e;    //8125复位后贞格式为11bit，与8125同步
    while(result!=0xf4)
    {
        //wd_tmer=0;
        delay(30); 
        CLR_8125MS;   //多通道 MS=1时工作在单通道模式，=0工作在多通道模式
        CLR_8125RST;   //芯片复位 rst8125-PG4 
        delay(300);
        SETB_8125RST;
        read_sensorstatus();
        delay(700);
        PORTC &= 0xc7;        //111 0,00 11 PB2、PB3、PB4置0，进行8125设置 此模式下MS=1读命令字，=0写命令字
        delay(30);
        //4800:UBRR1L=191; //7200:UBRR1L=127; //9600:UBRR1L=95;
        //19200:UBRR1L=47; //57600:UBRR1L=15; //115200:UBRR1L=7;
        //14400:UBRR1L=63; //28800:UBRR1L=31; //
        UBRR1L=191;        //7200--`120--133 60--67
        delay(2); 
        SendTX1(0xf4);        //波特率设定19200
        delay(25);
        read_sensorstatus();
        SETB_8125MS; //读设定 
        delay(300);
        
    }
    //clr_port(2,PB0);
    UBRR1L=11;   //母串口波特率要为自串口波特率的6倍 11520
    UCSR1C = 0x06;
    SETB_STADD0;
    SETB_STADD1;
    CLR_STADD2;
    CLR_8125MS;
    //read_sensorstatus();
    select_8125(3);
    //delay(1000); //初始化完要等一段时间才能对其接发数据
    //read_sensorstatus();
    SendTX1(0x20);
    delay(1000);
    read_sensorstatus();
    SendTX1(0x20);
    delay(1000);
    read_sensorstatus();
   // delay(1000);
   // read_sensorstatus();
   // delay(1000);
   // read_sensorstatus();
   // delay(1000);
    //read_sensorstatus();
    //delay(1000);
    //read_sensorstatus();
    //PiccReset(0);
    PCDConfig();
}


/*****************************************************************************/
/* Function Description:                                                                                                                      */
/*****************************************************************************/
//清狗，读取传感器状态
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
void read_sensorstatus(void)
{
    uint8 i;
    if(wdt_reseten == 1)
        WDR();
    sens_last = sens;   //SENSORS联合体变量
    for(i=0;i<sizeof(SENSORS);i++)
    {
        sens.status[i] = (PINB & (1 << i));
    }
    if(sens.SENSORS_STATUS.checkticks1 ==0x01 && sens_last.SENSORS_STATUS.checkticks1 != 0x01)
    {
        antenna = 1;
        antenna_LED_ON;
    }
    else if(sens.SENSORS_STATUS.checkticks2 == 0x02 && sens_last.SENSORS_STATUS.checkticks2 != 0x02
        || sens.SENSORS_STATUS.checkticks3 == 0x04 && sens_last.SENSORS_STATUS.checkticks3 != 0x04)
    {
        antenna = 0;
        antenna_LED_OFF;
    }
}
/*****************************************************************************/
/* Function Description:                                                                                                                      */
/*****************************************************************************/
//故障判断
//参数*re_comm 要发送的数据
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
void box_status_anto(RETURN_CODE *re_comm)
{
    uint8 temp[60];
    uint8 tagType[2];
    uint8 timeout;
    uint8 i;
    if(sens.SENSORS_STATUS.checkticks1 == 0x01 && sens.SENSORS_STATUS.checkticks2 == 0x02
        && sens.SENSORS_STATUS.checkticks3 == 0x04 && sens.SENSORS_STATUS.checkticks4 == 0
        && sens.SENSORS_STATUS.checkticks5 == 0)
    { 
        re_comm->MESSAGE.info[1] &= 0xfe;        //天线区、出票口。回收口无票//无错误
    }
    else
    {
        re_comm->MESSAGE.info[1] |= 0x01;        //天线区、出票口。回收口无票//有错误
    }
    select_8125(3);//TAG1串口
    PiccSetTX(1);//驱动天线1
    timeout = 2;
    while(PiccRequest(REQ_STD, tagType) != STATUS_COMM_OK)     //对tag1进行操作
    {
        timeout--;
        if(timeout == 0)
        {
            re_comm->MESSAGE.info[0] &= 0xfd;        //A未到位
            break;
        }
    }
    if(timeout != 0)
    {
        //如果到位
        re_comm->MESSAGE.info[0] |= 0x02;        //A到位
    }
    hop1_re.re_data[5] = 0;
    hop1_re.re_data[6] = 0;
    hop1_re.re_data[16] = 0;
    WriteHopper(hopper1,SDP_CMD_STATE_QUERY);//状态查询
    //delay(2);
    drop_tic_time = READ_MAS;
    while(drop_tic_time)//hop1_re.re_flag == 0)
    {
        read_sensorstatus();
        if(hop1_re.re_data[5] == SDP_ACK_CMD_INTIME && hop1_re.re_data[6] == SDP_CMD_STATE_QUERY && hop1_re.re_data[16] == 0x80)
            break;
    }
    //while(hop1_re.re_flag == 0);

    hop1_re.re_flag = 0;            //去掉应答7
    if(drop_tic_time != 0)
    {
        if(hop1_re.re_data[11] & 0x10)
            re_comm->MESSAGE.info[0] |= 0x10;        //A空
        else
            re_comm->MESSAGE.info[0] &= 0xef;        //A非空
        if(hop1_re.re_data[11] & 0x20)
            re_comm->MESSAGE.info[0] |= 0x01;        //A将空
        else
            re_comm->MESSAGE.info[0] &= 0xfe;        //A非空
        re_comm->MESSAGE.info[1] &= 0xfd; 
    }
    else
    {
        re_comm->MESSAGE.err_code = rf232A_err;
        re_comm->MESSAGE.info[1] |= 0x2;
    }

    select_8125(4);//TAG2串口
    PiccSetTX(2);
    timeout = 2;
    while(PiccRequest(REQ_STD, tagType) != STATUS_COMM_OK)     //对tag2进行操作
    {
        timeout--;
        if(timeout == 0)
        {
            re_comm->MESSAGE.info[0] &= 0xf7;        //B未到位
            break;
        }
    }
    if(timeout != 0)
    {
        //如果到位
        re_comm->MESSAGE.info[0] |= 0x08;        //B到位
    }
    hop2_re.re_data[5] = 0;
    hop2_re.re_data[6] = 0;
    hop1_re.re_data[16] = 0;
    WriteHopper(hopper2,SDP_CMD_STATE_QUERY);
    //delay(2);
    drop_tic_time = READ_MAS;
    while(drop_tic_time)//
    {
        read_sensorstatus();
        if(hop2_re.re_data[5] == SDP_ACK_CMD_INTIME && hop2_re.re_data[6] == SDP_CMD_STATE_QUERY && hop2_re.re_data[16] == 0x80)
            break;
    }
    //while(hop1_re.re_flag == 0);
        
    hop2_re.re_flag = 0;            //去掉应答
    if(drop_tic_time != 0)
    {
        if(hop2_re.re_data[11] & 0x10)
            re_comm->MESSAGE.info[0] |= 0x20;        //B空
        else
            re_comm->MESSAGE.info[0] &= 0xdf;        //B非空
        if(hop2_re.re_data[11] & 0x20)
            re_comm->MESSAGE.info[0] |= 0x04;        //B将空
        else
            re_comm->MESSAGE.info[0] &= 0xfb;        //B非空
        re_comm->MESSAGE.info[1] &= 0xfb;
    }
    else
    {
        re_comm->MESSAGE.err_code = rf232B_err;
        re_comm->MESSAGE.info[1] |= 0x4;
    }
    
    if(antenna == 1)
        re_comm->MESSAGE.info[0] |= 0x40;        //天线区有卡
    else
        re_comm->MESSAGE.info[0] &= 0xbf;        //天线区无卡
}
/*****************************************************************************/
/* Function Description:                                                                                                                      */
/*****************************************************************************/
//检查状态
//参数 *re_comm 要发送的数据
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
void check_sensorstatus(RETURN_CODE *re_comm)//-------------------------------传感器实时状态反馈
{
    read_sensorstatus();
    box_status_anto(re_comm);
}
/*****************************************************************************/
/* Function Description:                                                                                                                      */
/*****************************************************************************/
//检查状态
//参数 *re_comm 要发送的数据
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
void test_sensorstatus(RETURN_CODE *re_comm)
{

    SensorP_ON; //给传感器上电
    SOLE1_ON();//打开电磁铁
    SOLE2_ON();//打开电磁铁
    delay(200);
    read_sensorstatus();
    SensorP_OFF; //给传感器断电
    SOLE1_OFF();//关断电磁铁
    SOLE2_OFF();//关断电磁铁
    delay(200);
    read_sensorstatus();
    SensorP_ON; //给传感器上电
    if(sens.SENSORS_STATUS.checkticks1==sens_last.SENSORS_STATUS.checkticks1 )
        {
           re_comm->MESSAGE.info[0] |= 0x01; //票卡到天线区传感器故障
        }
    else
        {
          re_comm->MESSAGE.info[0] &= 0xfe; //票卡到天线区传感器正常
        }    
    if(sens.SENSORS_STATUS.checkticks2==sens_last.SENSORS_STATUS.checkticks2 )
        {
           re_comm->MESSAGE.info[0] |= 0x02; //票卡到出票口传感器故障
        }
    else
        {
          re_comm->MESSAGE.info[0] &= 0xfd; //票卡到出票口传感器正常
        }
    if(sens.SENSORS_STATUS.checkticks3==sens_last.SENSORS_STATUS.checkticks3 )
        {
           re_comm->MESSAGE.info[0] |= 0x04; //票卡到废票口传感器故障
        }
    else
        {
          re_comm->MESSAGE.info[0] &= 0xfb; //票卡到废票口传感器正常
        }
    if(sens.SENSORS_STATUS.checkticks4==sens_last.SENSORS_STATUS.checkticks4 )
        {
           re_comm->MESSAGE.info[0] |= 0x08; //电磁铁1打开关断故障
        }
    else
        {
          re_comm->MESSAGE.info[0] &= 0xf7; //电磁铁1打开关断正常
        }
      if(sens.SENSORS_STATUS.checkticks5==sens_last.SENSORS_STATUS.checkticks5 )
        {
           re_comm->MESSAGE.info[0] |= 0x10; //电磁铁2打开关断故障
        }
    else
        {
          re_comm->MESSAGE.info[0] &= 0xef; //电磁铁2打开关断正常
        }
    read_sensorstatus();//增加读传感器
    antenna = 0;
}
    
/*****************************************************************************/
/* Function Description:                                                                                                                      */
/*****************************************************************************/
//工作模式
//参数cmd 当前的命令
//参数*act 返回的数据指针
/*****************************************************************************/
/* Parameters:                                                                                                                                  */
/*****************************************************************************/
/*                                                                                                                                                     */
/* 出票、送票、回收       票函数                                                                                                                                             */
/*                                                                                                                                                     */
/*****************************************************************************/
/* Return Values:          是否成功                                                                                             */
/*****************************************************************************/
/*                                                                                                                                                      */
/*   NULL                                                                                                                                           */
/*                                                                                                                                                      */
/*****************************************************************************/
void normal_working(uint8 cmd,RETURN_CODE *act)
{
    uint8 time=3;
    switch(cmd)
    {
        case CMD_BOX1SCOOP://BOX1送票
        {
            if(antenna == 0)
            {
                //天线区无票
                WriteHopper(hopper1,SDP_CMD_CHG);
                drop_tic_time = DROP_T1;
                while(drop_tic_time)
                {
                    read_sensorstatus();
                    //if(antenna == 1)
                    //    break;
                    if(hop1_re.re_data[5] == SDP_ACK_CMD_UNTIME && hop1_re.re_data[8] == 1)//判断出票成功跳出
                    {
                        HOPPER1_LED_ON;
                        if(antenna == 1) //判断出票成功跳出
                            break;
                    }
                }
                /*if(antenna == 1)//出票成功
                {
                    act->MESSAGE.info[2] = 1;
                    act->MESSAGE.result = 's';
                    act->MESSAGE.err_code = com_ok;
                }
                else//出票失败
                {
                    act->MESSAGE.info[2] = 0;
                    act->MESSAGE.result = 'e';
                    act->MESSAGE.err_code = AWK_no_card;
                }*/
                if(drop_tic_time == 0)
                {
                    act->MESSAGE.info[2] = 0;
                    act->MESSAGE.result = 'e';
                    act->MESSAGE.err_code = AWK_no_card;
                }
                else
                {
                    act->MESSAGE.info[2] = 1;
                    act->MESSAGE.result = 's';
                    act->MESSAGE.err_code = com_ok;
                }
            }
            else//一上来就有票发出警告
            {
                //有票则报警
                act->MESSAGE.result = 'w';
                act->MESSAGE.err_code = card_at_RW_area;
                act->MESSAGE.info[2] = 0;
            }
            break;
        }
        case CMD_BOX2SCOOP://BOX2送票
        {
            if(antenna == 0)
            {
                //天线区无票
                WriteHopper(hopper2,SDP_CMD_CHG);
                drop_tic_time = DROP_T1;
                while(drop_tic_time)
                {
                    read_sensorstatus();
                    //if(antenna == 1)
                        //break;
                    if(hop2_re.re_data[5] == SDP_ACK_CMD_UNTIME && hop2_re.re_data[8] == 1)
                    {
                        HOPPER2_LED_ON;
                        if(antenna == 1)////判断出票成功跳出
                            break;
                    }
                }
              /*  if(antenna == 1)
                {
                    act->MESSAGE.info[2] = 1;
                    act->MESSAGE.result = 's';
                    act->MESSAGE.err_code = com_ok;
                }
                else
                {
                    act->MESSAGE.info[2] = 0;
                    act->MESSAGE.result = 'e';
                    act->MESSAGE.err_code = BWK_no_card;
                }*/
                if(drop_tic_time == 0)
                {
                    act->MESSAGE.info[2] = 0;
                    act->MESSAGE.result = 'e';
                    act->MESSAGE.err_code = BWK_no_card;
                }
                else
                {
                    act->MESSAGE.info[2] = 1;
                    act->MESSAGE.result = 's';
                    act->MESSAGE.err_code = com_ok;
                }  
            }
            else
            {
                //无票则告警
                act->MESSAGE.result = 'w';
                act->MESSAGE.err_code = card_at_RW_area;
                act->MESSAGE.info[2] = 0;
            }
            break;
        }
        case CMD_TICKETSELL://卖票
        {
            HOPPER1_LED_OFF;
            HOPPER2_LED_OFF;
            if(antenna == 1)
            {
                //天线区有票
                while(time--)
                {
                    SOLE1_ON();
                    drop_tic_time = DCT_T1;
                    while(drop_tic_time)
                    {
                        read_sensorstatus();
                        if(sens.SENSORS_STATUS.checkticks4 == 0x08)
                         break;    
                        
                    }
                    if(drop_tic_time == 0)
                    {
                        act->MESSAGE.result = 'e';
                        act->MESSAGE.err_code = sole1_err;
                        SOLE1_OFF();
                        return;
                    } 
                    drop_tic_time = DROP_T2;
                    while(drop_tic_time)
                    {
                        read_sensorstatus();
                        if(antenna == 0)
                            break;
                    }
                    SOLE1_OFF();
                    if(antenna == 0)
                        break;
                    else
                        delay(100);
                }
                if(antenna == 0)
                {
                    act->MESSAGE.info[2] = 1;
                    act->MESSAGE.result = 's';
                    act->MESSAGE.err_code = com_ok;
                }
                else
                {
                    act->MESSAGE.info[2] = 0;
                    act->MESSAGE.result = 'e';
                    act->MESSAGE.err_code = card_block_at_exit_area;
                }
            }
            else
            {
                //无票则告警
                act->MESSAGE.result = 'w';
                act->MESSAGE.err_code = no_card_at_RW_area;
                act->MESSAGE.info[2] = 0;
            }
            delay(150);
            break;
        }
        case CMD_TICKETRECYCLE://回收
        {
            HOPPER1_LED_OFF;
            HOPPER2_LED_OFF;
            if(antenna == 1)
            {
                //天线区有票
                while(time--)
                {
                    SOLE2_ON();
                    drop_tic_time = DCT_T2;
                    while(drop_tic_time)
                    {
                        read_sensorstatus();
                        if(sens.SENSORS_STATUS.checkticks5 ==0x10)//原来0x10
                            break;
                    }
                    if(drop_tic_time == 0)
                    {
                        act->MESSAGE.result = 'e';
                        act->MESSAGE.err_code = sole2_err;
                        SOLE2_OFF();
                        return;
                    }
                    drop_tic_time = DROP_T2;
                    while(drop_tic_time)
                    {
                        read_sensorstatus();
                        if(antenna == 0)
                            break;
                    }
                    SOLE2_OFF();
                    if(antenna == 0)
                        break;
                    else
                        delay(100);
                }
                if(antenna == 0)
                {
                    act->MESSAGE.info[2] = 1;
                    act->MESSAGE.result = 's';
                    act->MESSAGE.err_code = com_ok;
                }
                else
                {
                    act->MESSAGE.info[2] = 0;
                    act->MESSAGE.result = 'e';
                    act->MESSAGE.err_code = card_block_at_exit_area;
                }
            }
            else
            {
                //无票则告警
                act->MESSAGE.result = 'w';
                act->MESSAGE.err_code = no_card_at_RW_area;
                act->MESSAGE.info[2] = 0;
            }
            delay(200);
            break;
        }
            
    }
}
/*****************************************************************************/
/* Function Description:                                                                                                                      */
/*****************************************************************************/
//回复上位机数据
//参数*cmd 回复的数据指针
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
void cmd_reseive(RETURN_CODE *cmd)
{
    uint8 i,temp,len;
    uint8 *p;
    p = cmd->code;
    len = *p;
    p++;
    temp = Check_LRC(p,len);
    USART_Transmit(WXDLE);
    USART_Transmit(WXSTX);
    for(i=0;i<len;i++)
    {
        if(*p == WXDLE)
            USART_Transmit(WXDLE);
        USART_Transmit(*p);          
        p++;
    }
    USART_Transmit(WXDLE);
    USART_Transmit(WXETX);
    USART_Transmit(temp);

}

/*****************************************************************************/
/* Function Description:                                                                                                                      */
/*****************************************************************************/
//定时中断周期20ms
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
#pragma interrupt_handler timer2_ovf_isr:iv_TIM2_OVF
void timer2_ovf_isr(void)
{
    static uint8 work_light_cnt = 0;
    uint8 i;
    //通信超时计数
    if(communication_step == 2)//超时后返回错误回应
    {
        if(over_time != 0)
            over_time--;
        else
        {
            cmd_act(WXNAK);
            communication_step = 1;
            for(i=0;i<=n;i++)
                receive_buff[i] = 0;
            n = 0xff;
        }
    }
    //计数
    if(drop_tic_time != 0)//超时关闭电磁铁
        drop_tic_time--;
    if(init_over_time != 0)//初始化HOPPER超时
        init_over_time--;
    
    if(normal_start == 1)//心跳1S
    {
        if(work_light_cnt == 0)
        {
            work_light_cnt = 100;
            WORK_LIGHT_ON;
        }
        else if(work_light_cnt == 50)
        {
            WORK_LIGHT_OFF;
        }
        work_light_cnt--;
    }
    else if(normal_start == 2)//心跳加速，报故障
    {
        if(work_light_cnt == 0)
        {
            work_light_cnt = 50;
            WORK_LIGHT_ON;
        }
        else if(work_light_cnt == 25)
        {
            WORK_LIGHT_OFF;
        }
        work_light_cnt--;
    }
    else if(normal_start == 0)
        WORK_LIGHT_OFF;

    //RFID操作超时控制 
    if(g_cbWaitRespDly != 0)//RFID操作超时使能（1s内timeout自减了47次）  
    {
        g_cbWaitRespDly--;
    }
}

//外部中断
/*#pragma interrupt_handler extern_int4_isr:iv_EXT_INT4
void extern_int4_isr(void)
{

}
*/
/*****************************************************************************/
/* Function Description:                                                                                                                      */
/*****************************************************************************/
//通信命令解析
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
void check_command(void)//检查命令
{
    static RETURN_CODE re_code;
    static uint8 tic_num1[2],tic_num2[2];
    static uint8 tic_flag1=0,tic_flag2=0;
    uint8 *p;
    uint8 i=0;
    if(1 == receive_ok)
    {
        communication_step = 1;
        switch(inbox[0])
        {
            case 0x0:           //重新回复上次命令
            {
                cmd_reseive(&re_code);
                break;
            }
            case 0x81:          //初始化    
            {
                re_code.MESSAGE.act_code = inbox[0];
                re_code.MESSAGE.err_code = com_ok;
                module_init(&re_code);
                check_sensorstatus(&re_code);
                if(re_code.MESSAGE.err_code != com_ok)
                    re_code.MESSAGE.result = 'e';
                else
                    re_code.MESSAGE.result = 's';
                re_code.MESSAGE.len = 6;
                cmd_reseive(&re_code);
                normal_start = 1;
                break;
            }
            case 0x82:          //读模块状态
            {
                re_code.MESSAGE.act_code = inbox[0];
                check_sensorstatus(&re_code);
                re_code.MESSAGE.result = 's';
                re_code.MESSAGE.err_code = com_ok;
                re_code.MESSAGE.len = 5;
                cmd_reseive(&re_code);
                normal_start = 1;
                break;
            }
            case 0x83:          //通道清理
            {
                re_code.MESSAGE.act_code = inbox[0];
                re_code.MESSAGE.err_code = com_ok;
                module_init(&re_code);
                check_sensorstatus(&re_code);
                if(re_code.MESSAGE.err_code != com_ok)
                    re_code.MESSAGE.result = 'e';
                else
                    re_code.MESSAGE.result = 's';
                re_code.MESSAGE.len = 6;
                cmd_reseive(&re_code);
                normal_start = 1;
                
                break;
            }
            case 0x84:          //挖票
            {
                re_code.MESSAGE.act_code = inbox[0];
                if(1==inbox[1]||2==inbox[1])
               {
                     normal_working(inbox[1],&re_code);
                     //delay(200);
                     check_sensorstatus(&re_code);
                    if(re_code.MESSAGE.result == 's')
                        re_code.MESSAGE.err_code = com_ok;
                }
                else
                 {
                      re_code.MESSAGE.result = 'e';
                      re_code.MESSAGE.err_code =invalid_parameter;
                      normal_start = 1;
                 } 
                re_code.MESSAGE.len = 6;
                cmd_reseive(&re_code);
                break;
            }
            case 0x85:          //售票
            {
                re_code.MESSAGE.act_code = inbox[0];
                normal_working(CMD_TICKETSELL,&re_code);
                check_sensorstatus(&re_code);
                if(re_code.MESSAGE.result == 's')
                    re_code.MESSAGE.err_code = com_ok;
                re_code.MESSAGE.len = 6;
                cmd_reseive(&re_code);
                break;
            }
            case 0x86:          //回收
            {
                re_code.MESSAGE.act_code = inbox[0];
                normal_working(CMD_TICKETRECYCLE,&re_code);
                check_sensorstatus(&re_code);
                if(re_code.MESSAGE.result == 's')
                    re_code.MESSAGE.err_code = com_ok;
                re_code.MESSAGE.len = 6;
                cmd_reseive(&re_code);
                break;
            }
            case 0x87:          //复位，用于烧写程序    
            {
                re_code.MESSAGE.act_code = inbox[0];
                check_sensorstatus(&re_code);
                re_code.MESSAGE.result = 's';
                re_code.MESSAGE.err_code = com_ok;
                re_code.MESSAGE.len = 5;
                cmd_reseive(&re_code);
                wdt_reseten = 0;
                normal_start = 1;
                break;
            }
            case 0x88:          //版本号
            {
                p = re_code.MESSAGE.info;
                re_code.MESSAGE.act_code = inbox[0];
                re_code.MESSAGE.result = 's';
                re_code.MESSAGE.err_code = com_ok;
                for(i=0;i<sizeof(MODULE_VERSION);i++)
                {
                    *p = MODULE_VERSION[i];
                    p++;
                }
                for(i=0;i<sizeof(CPU_VERSION);i++)
                {
                    *p = CPU_VERSION[i];
                    p++;
                }
                re_code.MESSAGE.len = 18;
                cmd_reseive(&re_code);
                normal_start = 1;
                break;
            }
            case 0x89:          //清除token卡
            {
                re_code.MESSAGE.act_code = inbox[0];
                if(1==inbox[1]||2==inbox[1])
                {
                    WriteHopper(inbox[1],SDP_CMD_CLR);
                    delay(100);
                   if(inbox[1] == hopper1)
                    {
                        if(((hop1_re.re_data[5] == SDP_ACK_CMD_ACK) && (hop1_re.re_data[6] == SDP_CMD_CLR))
                              || ((hop1_re.re_data[5] == SDP_ACK_CMD_UNTIME) && (hop1_re.re_data[6] == SDP_CMD_CLR)))//清空下发命令
                         {
                               re_code.MESSAGE.result = 's';
                              re_code.MESSAGE.err_code = com_ok;
                              normal_start = 1;
                            }
                         else
                          {
                             re_code.MESSAGE.result = 'e';
                            re_code.MESSAGE.err_code = clr_err;
                            normal_start = 2;
                           }
                     }
                     else
                     {
                          if((hop2_re.re_data[5] == SDP_ACK_CMD_ACK && hop2_re.re_data[6] == SDP_CMD_CLR)
                               || (hop2_re.re_data[5] == SDP_ACK_CMD_UNTIME && hop2_re.re_data[6] == SDP_CMD_CLR))
                           {
                               re_code.MESSAGE.result = 's';
                               re_code.MESSAGE.err_code = com_ok;
                               normal_start = 1;
                           }
                         else
                          {
                                 re_code.MESSAGE.result = 'e';
                                re_code.MESSAGE.err_code = clr_err;
                                normal_start = 2;
                           }
                     }
                    }
                else
                    {
                      re_code.MESSAGE.result = 'e';
                      re_code.MESSAGE.err_code =invalid_parameter;
                      normal_start = 1;
                    }
                //check_sensorstatus(&re_code);
                re_code.MESSAGE.len = 3;
                cmd_reseive(&re_code);
                break;
            }
            case 0x8a:          //读取清空数量
            {   
                re_code.MESSAGE.act_code = inbox[0];
                if(1==inbox[1]||2==inbox[1])
                {
                     if(inbox[1] == hopper1)
                     {
                         if(tic_flag1 == 0)
                         {
                            re_code.MESSAGE.result = 'e';
                           re_code.MESSAGE.err_code = equ_busy;
                            normal_start = 2;
                         }
                         else
                         {
                            re_code.MESSAGE.result = 's';
                           re_code.MESSAGE.err_code = com_ok;
                           re_code.MESSAGE.info[0] = tic_num1[0];
                           re_code.MESSAGE.info[1] = tic_num1[1];
                           tic_flag1 = 0;
                           normal_start = 1;
                          }
                       }
                      else
                       {
                              if(tic_flag2 == 0)
                              {
                                  re_code.MESSAGE.result = 'e';
                                  re_code.MESSAGE.err_code = equ_busy;
                                  normal_start = 2;
                               }
                               else
                               {
                                  re_code.MESSAGE.result = 's';
                                  re_code.MESSAGE.err_code = com_ok;
                                 re_code.MESSAGE.info[0] = tic_num2[0];
                                 re_code.MESSAGE.info[1] = tic_num2[1];
                                 tic_flag2 = 0;
                                 normal_start = 1;
                                }
                          }
                    }
                 else
                    {
                      re_code.MESSAGE.result = 'e';
                      re_code.MESSAGE.err_code =invalid_parameter;
                      normal_start = 1;
                    }
                //check_sensorstatus(&re_code);
                re_code.MESSAGE.len = 5;
                cmd_reseive(&re_code);
                break;
            }
            case 0x8b:          //停止清除token卡
            {   
                re_code.MESSAGE.act_code = inbox[0];
                if(1==inbox[1]||2==inbox[1])
                {  
                   WriteHopper(inbox[1],SDP_CMD_STOP_CLR);
                    re_code.MESSAGE.result = 's';
                    re_code.MESSAGE.err_code = com_ok;
                  }
                 else
                  {
                      re_code.MESSAGE.result = 'e';
                      re_code.MESSAGE.err_code =invalid_parameter;
                      normal_start = 1;
                   }
                 re_code.MESSAGE.len = 3;
                cmd_reseive(&re_code);
                break;
            }
            case 0x97:          //设置卡箱的票卡数量
            {
               /* re_code.MESSAGE.act_code = inbox[0];
                if((inbox[1] != 0xff) && (inbox[2] != 0xff))
                    box1_tick_num = inbox[1] + (inbox[2] << 8);
                if((inbox[3] != 0xff) && (inbox[4] != 0xff))
                    box2_tick_num = inbox[3] + (inbox[4] << 8);
                if((inbox[5] != 0xff) && (inbox[6] != 0xff))
                    box3_tick_num = inbox[5] + (inbox[6] << 8);
                re_code.MESSAGE.result = 's';
                re_code.MESSAGE.err_code = com_ok;
                re_code.MESSAGE.len = 3;
                cmd_reseive(&re_code);
                //inbox[0] = 0;*/
                break;
            }
            case 0x98:          //更换票箱//暂时不用管
            {
                break;
            }
            case 0x99:              //读取票箱编号
            {
                re_code.MESSAGE.act_code = inbox[0];
                if(3==inbox[1]||4==inbox[1])
                    {
                        re_code.MESSAGE.err_code=ReadRFIDBLOCK(inbox[1],1,re_code.MESSAGE.info);    //读取票箱的票箱编号（块1）
                      if(re_code.MESSAGE.err_code == com_ok)
                        {
                          re_code.MESSAGE.result = 's';
                          normal_start = 1;
                         }
                        else
                        {
                          re_code.MESSAGE.result = 'e';
                         normal_start = 2;
                         }

                    }
                else
                    {
                      re_code.MESSAGE.result = 'e';
                      re_code.MESSAGE.err_code =invalid_parameter;
                      normal_start = 1;
                    }
                re_code.MESSAGE.len = 17;
                cmd_reseive(&re_code);
                //inbox[0] = 0;
                break;
            }
            case 0xe3:              //向 RFID 写一个 Block 数据
            {
                re_code.MESSAGE.act_code = inbox[0];
                if(3==inbox[1]||4==inbox[1])
                    {
                    
                          re_code.MESSAGE.err_code = WriteRFIDBLOCK(inbox[1],inbox[2],&inbox[3]);
                        if(re_code.MESSAGE.err_code == com_ok)
                          {
                               re_code.MESSAGE.result = 's';
                               normal_start = 1;
                           }
                       else
                         {
                            re_code.MESSAGE.result = 'e';
                             normal_start = 2;
                          }
                    }
                else
                    {
                      re_code.MESSAGE.result = 'e';
                      re_code.MESSAGE.err_code =invalid_parameter;
                      normal_start = 1;
                    }
                re_code.MESSAGE.len = 3;
                cmd_reseive(&re_code);
                //inbox[0] = 0;
                break;
            }
            case 0xe4:              //从RFID中读取一个Block数据
            {
                re_code.MESSAGE.act_code = inbox[0];
                if(3==inbox[1]||4==inbox[1])
               {      
                       re_code.MESSAGE.err_code = ReadRFIDBLOCK(inbox[1],inbox[2],re_code.MESSAGE.info);
                      if(re_code.MESSAGE.err_code == com_ok)
                       {
                            re_code.MESSAGE.result = 's';
                           normal_start = 1;
                        }
                     else
                      {
                           re_code.MESSAGE.result = 'e';
                          normal_start = 2;
                       }
                }
                 else
                    {
                      re_code.MESSAGE.result = 'e';
                      re_code.MESSAGE.err_code =invalid_parameter;
                      normal_start = 1;
                    }
                re_code.MESSAGE.len = 19;
                cmd_reseive(&re_code);
                //inbox[0] = 0;
                break;
            }
            case 0xe5:              //向 RFID 写一个 Sector 数据
            {
                re_code.MESSAGE.act_code = inbox[0];

                   if(3==inbox[1]||4==inbox[1])
                   {      
                        re_code.MESSAGE.err_code = WriteRFIDSECTOR(inbox[1],inbox[2],inbox[3],&inbox[4]);
                        if(re_code.MESSAGE.err_code == com_ok)
                       {
                            re_code.MESSAGE.result = 's';
                            normal_start = 1;
                        }
                        else
                       {
                          re_code.MESSAGE.result = 'e';
                          normal_start = 2;
                       }
                   }
                  else
                    {
                      re_code.MESSAGE.result = 'e';
                      re_code.MESSAGE.err_code =invalid_parameter;
                      normal_start = 1;
                    }
                re_code.MESSAGE.len = 3;
                cmd_reseive(&re_code);
                //inbox[0] = 0;
                break;
            }
            case 0xe6:              //从RFID中读取一个Sector数据
            {
                re_code.MESSAGE.act_code = inbox[0];
                if(3==inbox[1]||4==inbox[1])
                {
                    re_code.MESSAGE.err_code = ReadRFIDSECTOR(inbox[1],inbox[2],re_code.MESSAGE.info);
                    if(re_code.MESSAGE.err_code == com_ok)
                    {
                         re_code.MESSAGE.result = 's';
                         normal_start = 1;
                      }
                    else
                     {
                           re_code.MESSAGE.result = 'e';
                          normal_start = 2;
                     }
                  }
                 else
                    {
                      re_code.MESSAGE.result = 'e';
                      re_code.MESSAGE.err_code =invalid_parameter;
                      normal_start = 1;
                    }
                re_code.MESSAGE.len = 51;
                cmd_reseive(&re_code);
                //inbox[0] = 0;
                break;
            }
            case 0xe7:              //读token卡序列号
            {
                re_code.MESSAGE.act_code = inbox[0];
		 if(3==inbox[1]||4==inbox[1])
                 {
                    re_code.MESSAGE.err_code = ReadRFID_Serial_Number(inbox[1],re_code.MESSAGE.info);
                
       
                   if(re_code.MESSAGE.err_code == com_ok)
                     {
                       re_code.MESSAGE.result = 's';
                       normal_start = 1;
                      }
                    else
                       {
                          re_code.MESSAGE.result = 'e';
                          normal_start = 2;
                        }
                    }
                else
                    {
                      re_code.MESSAGE.result = 'e';
                      re_code.MESSAGE.err_code =invalid_parameter;
                      normal_start = 1;
                    }
                re_code.MESSAGE.len = 9;
                cmd_reseive(&re_code);
                //inbox[0] = 0;
                break;
            }
         case 0xe8:  //生产测试通道传感器、电磁铁打开关断到位
        {
                re_code.MESSAGE.act_code = inbox[0];
                test_sensorstatus(&re_code);
                re_code.MESSAGE.result = 's';
                re_code.MESSAGE.err_code = com_ok;
                re_code.MESSAGE.len = 4;
                cmd_reseive(&re_code);
                break;
        }
            default:
                break;
        }
        for(i=0;i<60;i++)
            inbox[i] = 0;
        receive_ok = 0;
    }
    if(hop1_re.re_data[5] == SDP_ACK_CMD_UNTIME && hop1_re.re_data[6] == SDP_CMD_CLR)
    {
        tic_num1[0] = hop1_re.re_data[7];
        tic_num1[1] = hop1_re.re_data[8];
        tic_flag1 = 1;
    }
    if(hop2_re.re_data[5] == SDP_ACK_CMD_UNTIME && hop2_re.re_data[6] == SDP_CMD_CLR)
    {
        tic_num2[0] = hop2_re.re_data[7];
        tic_num2[1] = hop2_re.re_data[8];
        tic_flag2 = 1;
    }
}


/*****************************************************************************/
/* Function Description:                                                                                                                      */
/*****************************************************************************/
//模块初始化
//参数*re_comm 回复的数据指针
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
void module_init(RETURN_CODE *re_comm)
{
    uint8 i;
    read_sensorstatus();
    SOLE2_ON();
    drop_tic_time = DROP_T2;
    while(drop_tic_time)
    {
        read_sensorstatus();
    }
    SOLE2_OFF();
    antenna = 0;    //清空天线区标志
    WriteHopper(hopper1,SDP_CMD_HD_SELF);//自检命令
    WriteHopper(hopper2,SDP_CMD_HD_SELF);
    delay(500);
    read_sensorstatus();
    delay(500);
    read_sensorstatus();
    delay(500);
    read_sensorstatus();
    delay(500);
    read_sensorstatus();
    WriteHopper(hopper1,SDP_CMD_STOP_HD_SELF);
    WriteHopper(hopper2,SDP_CMD_STOP_HD_SELF);    
    init_over_time = INTI_OVER_TIME;
    while(init_over_time)
    {
        read_sensorstatus();
        if(hop1_re.re_data[5] == SDP_ACK_CMD_INTIME && hop1_re.re_data[6] == SDP_CMD_HD_SELF
            && hop2_re.re_data[5] == SDP_ACK_CMD_INTIME && hop2_re.re_data[6] == SDP_CMD_HD_SELF)
            break;
    }
    
    SOLE1_ON();
    SOLE2_ON();
    delay(100);
    read_sensorstatus();
    if(sens.SENSORS_STATUS.checkticks4 == sens_last.SENSORS_STATUS.checkticks4)
        re_comm->MESSAGE.err_code = sole1_err;
    if(sens.SENSORS_STATUS.checkticks5 == sens_last.SENSORS_STATUS.checkticks5)
        re_comm->MESSAGE.err_code = sole2_err;
    SOLE1_OFF();
    SOLE2_OFF();
    SensorP_OFF;
    delay(100);
    read_sensorstatus();
    SensorP_ON;
    if(sens.SENSORS_STATUS.checkticks1 == sens_last.SENSORS_STATUS.checkticks1    
        || sens.SENSORS_STATUS.checkticks2 == sens_last.SENSORS_STATUS.checkticks2
        || sens.SENSORS_STATUS.checkticks3 == sens_last.SENSORS_STATUS.checkticks3)  /**接收传感器一直供电，修改此处判断逻辑**/
        re_comm->MESSAGE.err_code = checkticks_err;
    for(i=0;i<20;i++)
    {
        hop1_re.re_data[i] = 0;
        hop2_re.re_data[i] = 0;
    }
    hop1_re.re_flag = 0;
    hop2_re.re_flag = 0;
    read_sensorstatus();
    antenna = 0;
}

/*****************************************************************************/
/* Function Description:                                                                                                                      */
/*****************************************************************************/
//电磁铁交替驱动
/*****************************************************************************/
/* Parameters:                                                                                                                                  */
/*****************************************************************************/
/*                                                                                                                                                     */
/*                                                                                                                                                     */
/*                                                                                                                                                     */
/*****************************************************************************/
/* Return Values:          NULL                                                                                */
/*****************************************************************************/
/*                                                                                                                                                      */
/*   NULL                                                                                                                                           */
/*                                                                                                                                                      */
/*****************************************************************************/
  void SOLE1_ON(void)
    {
    static  uint8 SOLE_DCT1=0;
     SOLE_DCT1++;
      if(SOLE_DCT1<2)
        {
          SOLE1_ON_1;
          SOLE1_OFF_2;
        }
      else
        {
          SOLE1_OFF_1;
          SOLE1_ON_2;
        }
       if(SOLE_DCT1>=2)
        SOLE_DCT1=0;
    }
 void SOLE2_ON(void)
    {
     static  uint8 SOLE_DCT2=0;
      SOLE_DCT2++;
      if(SOLE_DCT2<2)
        {
          SOLE2_ON_1;
          SOLE2_OFF_2;
        }
      else
        {
          SOLE2_OFF_1;
          SOLE2_ON_2;
        }
       if(SOLE_DCT2>=2)
          SOLE_DCT2=0;
    }

    void SOLE1_OFF(void)
    {
        SOLE1_OFF_1;
        SOLE1_OFF_2;
    }
 void SOLE2_OFF(void)
    {
        SOLE2_OFF_1;
        SOLE2_OFF_2;
    }

/*****************************************************************************/
/* Function Description:                                                                                                                      */
/*****************************************************************************/
//主函数
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
void main(void)
{
    static RETURN_CODE re_code;
    init_devices();   
    SensorP_ON; //给传感器上电
    SOLE1_OFF();
    SOLE2_OFF(); 
    Timer2_Start;
    //insert your functional code here...
    // ledc2_SET;
    //E2_tickets_read();
    rfid_init();//RFID初始化
    module_init(&re_code);
    normal_start = 1;
    //WriteHopper(hopper2,SDP_CMD_VERSION_QUERY);
    
    //WriteHopper(hopper2,SDP_CMD_VERSION_QUERY);
    while(1)
    {
        read_sensorstatus();
        check_command();
    }
}

