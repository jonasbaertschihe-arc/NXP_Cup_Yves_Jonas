/*
------------------------------------------------------------
Copyright 2003-201x Haute école ARC Ingéniérie, Switzerland. 
All rights reserved.
------------------------------------------------------------
Nom du fichier : 	def.h	
Auteur et Date :	Monnerat Serge 29 août 2013

But : Some general settings

-----------------------------------------------------------------------------
Historique:
-----------------------------------------------------------------------------

$History: $

-----------------------------------------------------------------------------
*/

#ifndef DEF_H_
#define DEF_H_

//------------------------------------------------------------
// Constants
//------------------------------------------------------------
// Core clock
#define kClockCpu 		100.0 			// 100MHz
#define kClockCpukHz 	100000.0 		// 100MHz
#define kClockPeriphkHz 50000.0 		// 50MHz
#define CORE_CLOCK		(100000000)	
#define PERIPHERAL_BUS_CLOCK 	(CORE_CLOCK/2)

// Caméra digitale ou analogique
#define kDigCamera 1
// PIT1 period --> 1 ms
#define kPit1Period 1 
// Avec ou sans accéléromètre, magnéto
#define kWithAccel 1

//------------------------------------------------------------
// Interrupt priority (O highest, 15 lowest)
//------------------------------------------------------------
#define kPIT_IntPriority 		15
#define kUART3_IntPriority 	0
#define kFTM1_IntPriority		1
#define kPORB_IntPriority		2

//------------------------------------------------------------
// bool and standard type
//------------------------------------------------------------
typedef int bool;
typedef bool BOOL;
#define TRUE 1
#define true 1
#define FALSE 0
#define false 0

typedef unsigned char				UInt8;  /*  8 bits */
typedef unsigned short int	UInt16; /* 16 bits */
typedef unsigned long int		UInt32; /* 32 bits */
typedef unsigned long long	UInt64; /* 32 bits */

typedef char			    			Int8;   /*  8 bits */
typedef short int	        	Int16;  /* 16 bits */
typedef int		            	Int32;  /* 32 bits */

typedef volatile Int8				VInt8;  /*  8 bits */
typedef volatile Int16			VInt16; /* 16 bits */
typedef volatile Int32			VInt32; /* 32 bits */
typedef long long		        Int64;  /* 32 bits */

typedef volatile UInt8			VUInt8;  /*  8 bits */
typedef volatile UInt16			VUInt16; /* 16 bits */
typedef volatile UInt32			VUInt32; /* 32 bits */

typedef volatile UInt8			VUInt8;  /*  8 bits */
typedef volatile UInt16			VUInt16; /* 16 bits */
typedef volatile UInt32			VUInt32; /* 32 bits */
typedef volatile UInt32    	UINT32;
typedef volatile UInt8      UINT8;
typedef volatile Int8       INT8;
typedef volatile UInt16     UINT16;
typedef volatile UInt64     UINT64;
typedef volatile Int64      INT64;
typedef volatile Int16      INT16;
typedef volatile Int32      INT32;
typedef volatile Int8       CHAR;

// Macros min & max
#define min(a, b)       ((a) < (b) ? (a) : (b))
#define max(a, b)       ((a) < (b) ? (b) : (a))

//------------------------------------------------------------
// Type
//------------------------------------------------------------
// PIT enum
typedef enum
{
	kPit0=0,
	kPit1=1,
	kPit2=2,
	kPit3=3
}PitEnum;

// Structure contenant une frame reçue par wifi
typedef struct
{
	UInt8 	Type;
	UInt16 	Size;
	UInt8 	Payload[300];
	UInt16 	Index;
}ReadFramestruct;

#endif
