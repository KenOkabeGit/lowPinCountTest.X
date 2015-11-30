/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using MPLAB® Code Configurator

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB® Code Configurator - v2.25.2
        Device            :  PIC16LF1509
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 v1.34
        MPLAB             :  MPLAB X v2.35 or v3.00
 */

/*
Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 */

#include "mcc_generated_files/mcc.h"
#include <stdio.h>
#include <string.h>

void sendUart(void);
void EUSART_str_Write(char *txData);
void wiflyInitState(void);

volatile char Heart_beat_flag = 0;
volatile char Transmit_flag = 0;

/*
                         Main application
 */
void main(void) {

    // initialize the device
    SYSTEM_Initialize();

    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    RC0=1;
    RC1=0;
    RC2=0;
    RC3=0;
    EUSART_str_Write((uint8_t *)"Start!\r\n");

    while (1) {
        // Add your application code
        if(Heart_beat_flag){
            Heart_beat_flag = 0;
            RC0 ^= 1;
        }


        wiflyInitState();



    }
}
typedef enum{
  StateCmdDDD,
  StateWaitCMD,
  StateCmdMode,
} StateWiflyInit;

void wiflyInitState(void)
{
  static StateWiflyInit state = StateCmdDDD;
  static const char* strCmdMode = "CMD";
  static unsigned char cmdChkBuf[4];
  static char locate = 0;

  switch(state){
    case StateCmdDDD:
      EUSART_str_Write((uint8_t *)"$$$");
      state = StateWaitCMD;
      break;

    case StateWaitCMD:
      cmdChkBuf[0]=(unsigned char)EUSART_Read();
      cmdChkBuf[1]=(unsigned char)EUSART_Read();
      cmdChkBuf[2]=(unsigned char)EUSART_Read();
      cmdChkBuf[3]='\0';
      if(strncmp(cmdChkBuf,"CMD",3)!=0){
        RC2=1;
        while(1);
      }
      state = StateCmdMode;
      EUSART_str_Write((uint8_t *)"To the Cmd\r\n");
      break;

    case StateCmdMode:
    break;

    default:
      RC3=1;
      while (1) {
        /* code */
      }
  }
}

void sendUart(void)
{

    if(Transmit_flag){
      EUSART_str_Write((uint8_t *)"testw ");
      Transmit_flag = 0;
    }


}

/**
 End of File
 */
