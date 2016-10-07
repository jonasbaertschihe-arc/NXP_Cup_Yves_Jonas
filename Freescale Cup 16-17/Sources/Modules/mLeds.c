/*
------------------------------------------------------------
Copyright 2003-201x Haute �cole ARC Ing�ni�rie, Switzerland. 
All rights reserved.
------------------------------------------------------------
File name :	mLeds.c
Author and date :	Monnerat Serge 28 f�vr. 201x

Description in the header (.h)

-----------------------------------------------------------------------------
History:
-----------------------------------------------------------------------------

$History: $

-----------------------------------------------------------------------------
*/

#include "mLeds.h"
#include "iDio.h"


//-----------------------------------------------------------------------------
// Configuration des ports IO utilis�s par les LEDS
//-----------------------------------------------------------------------------
void mLeds_Setup(void)
{
	// Configuration des Ports en entr�e ou en sortie
	iDio_SetPortDirection(kPortB,kMaskIo20+kMaskIo21+kMaskIo22+kMaskIo23,kIoOutput);
}

//-----------------------------------------------------------------------------
// Start du module
//-----------------------------------------------------------------------------
void mLeds_Open(void)
{}

//-----------------------------------------------------------------------------
// On Off des LED
// aMask:   choix des LED sur lesquelles on veut agir (si bit � 1)
// aState:  choix de l'�tat des LED d�sir�s
//-----------------------------------------------------------------------------
void mLeds_Write(LedMaskEnum aMask,LedStateEnum aState)
{  
  UInt32 aTmp;
 
  if(kLedOn==aState)
    {
  		aTmp=(0|((aMask&0x1)<<20)|((aMask&0x2)<<(20))|((aMask&0x04)<<(20))|((aMask&0x08)<<(20)));
  		
			iDio_SetPort(kPortB,(IoMaskEnum)(aTmp),kIoOn);
    }
  else if(kLedOff==aState)
    {
  		aTmp=(0|((aMask&0x1)<<20)|((aMask&0x2)<<(20))|((aMask&0x04)<<(20))|((aMask&0x08)<<(20)));
  		iDio_SetPort(kPortB,(IoMaskEnum)(aTmp),kIoOff);
    }
}

//-----------------------------------------------------------------------------
// On Off des LED
// aMask:   choix des LED sur lesquelles on veut agir (si bit � 1)
//-----------------------------------------------------------------------------
void mLeds_Toggle(LedMaskEnum aMask)
{
	UInt32 aTmp;
	static LedStateEnum pState=kLedOff;
	
	if(kLedOn==pState)
		{
			pState=kLedOff;
			
			aTmp=(0|((aMask&0x1)<<20)|((aMask&0x2)<<(20))|((aMask&0x04)<<(20))|((aMask&0x08)<<(20)));
			
			iDio_SetPort(kPortB,(IoMaskEnum)(aTmp),kIoOn);
		}
	else if(kLedOff==pState)
		{
			pState=kLedOn;
			aTmp=(0|((aMask&0x1)<<20)|((aMask&0x2)<<(20))|((aMask&0x04)<<(20))|((aMask&0x08)<<(20)));
			iDio_SetPort(kPortB,(IoMaskEnum)(aTmp),kIoOff);
		}	
}
