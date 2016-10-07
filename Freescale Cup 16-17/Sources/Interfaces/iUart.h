/*
------------------------------------------------------------
Copyright 2003-201x Haute école ARC Ingéniérie, Switzerland.
All rights reserved.
------------------------------------------------------------
File name : 	iUart.h	
Author and date :	Monnerat Serge 5 mars 201x

Goal : interface série pour le module wifi

-----------------------------------------------------------------------------
History:
-----------------------------------------------------------------------------

$History: $


-----------------------------------------------------------------------------
*/
#ifndef __iUart__
#define __iUart__

#include "def.h"

//------------------------------------------------------------
// UART status flag
//------------------------------------------------------------
typedef enum
{
	kSciTransmitDataRegEmpty=0x80,
	kSciTransmitComplete=0x40,
	kSciReceiveDataRegFull=0x20,
	kSciIdleLineDetect=0x10,
	kSciOverrunErr=0x08,
	kSciNoiseErr=0x04,
	kSciFramingErr=0x02,
	kSciParityErr=0x01
}UartStatusEnum;

//------------------------------------------------------------
// UART fifo status flag
//------------------------------------------------------------
typedef enum
{
	kTxFifoEmpty=0x80,
	kRxFifoEmpty=0x40,
	kTxFifoOverflow=0x02,
	kRxFifoUnderflow=0x01
}UartFifoStatusEnum;

//-----------------------------------------------------------------------
// UART 3 module configuration
//-----------------------------------------------------------------------
void iUart_Config(void);

//------------------------------------------------------------
// Get Uart3 flags state
// aStatus: which flag to read
// retour	: flag state
//------------------------------------------------------------
bool iUart_GetStatus(UartStatusEnum aStatus);

//------------------------------------------------------------
// Get Uart3 fifo flags state
// aStatus: which flag to read
// retour	: flag state
//------------------------------------------------------------
bool iUart_GetFifoStatus(UartFifoStatusEnum aStatus);

//------------------------------------------------------------
// Uart3 Data register write
// aData: datas to transmit
//------------------------------------------------------------
void iUart_SetData(UInt8 aData);

//------------------------------------------------------------
// Check if the buffer is empty
// Return : true --> buffer empty, false --> buffer not empty
//------------------------------------------------------------
bool iUart_IsBufferEmpty(void);

//------------------------------------------------------------
// Byte read in the RX buffer
// Return : oldest byte in the buffer
//------------------------------------------------------------
Int8 iUart_GetCharFromBuffer(void);

//-----------------------------------------------------------------------
// Reset RX buffer
//-----------------------------------------------------------------------
void iUart_ResetBuffer(void);

//------------------------------------------------------------
// RX buffer command read
// Return : pointer on the frame
//------------------------------------------------------------
ReadFramestruct *iUart_GetReadWifiFrame(void);

//------------------------------------------------------------
// Uart4 Data register write
// aData: datas to transmit
//------------------------------------------------------------
void iUart_Uart4SetData(UInt8 aData);

//------------------------------------------------------------
// Get Uart4 flags state
// aStatus: which flag to read
// retour	: flag state
//------------------------------------------------------------
bool iUart_Uart4GetStatus(UartStatusEnum aStatus);

#endif
