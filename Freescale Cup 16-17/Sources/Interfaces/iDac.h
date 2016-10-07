/*
------------------------------------------------------------
Copyright 2003-201x Haute �cole ARC Ing�ni�rie, Switzerland.
All rights reserved.
------------------------------------------------------------
File name : 	iDac.h	
Author and date :	Monnerat Serge 28 f�vr. 201x

Goal : 

-----------------------------------------------------------------------------
History:
-----------------------------------------------------------------------------

$History: $


-----------------------------------------------------------------------------
*/
#ifndef __iDac__
#define __iDac__

#include "def.h"

// Dac enum
typedef enum
{
	kDac0,
	kDac1
}DacEnum;

// Dac mode enum
typedef enum
{
	kNonBuffVRefIn,
	kBuffVRefIn
}DacModeEnum;

//------------------------------------------------------------
// DAC 0 & 1 setup
//------------------------------------------------------------
void iDac_Config(DacEnum aDac,DacModeEnum aMode);

//------------------------------------------------------------
// Dac enable
// aDac: which dac (0 or 1)
//------------------------------------------------------------
void iDac_Enable (DacEnum aDac);

//------------------------------------------------------------
// Dac disable
// aDac: which dac (0 or 1)
//------------------------------------------------------------
void iDac_Disable (DacEnum aDac);

//------------------------------------------------------------
// Set DAC buffer value
// aDac: which dac (0 or 1)
// aBuffIndex: which buffer position to configure
// aBuffVal: which value to set
//------------------------------------------------------------
void iDac_SETDACBUFFER(DacEnum aDac, UInt8 aBuffIndex, float aBuffVal);

#endif
