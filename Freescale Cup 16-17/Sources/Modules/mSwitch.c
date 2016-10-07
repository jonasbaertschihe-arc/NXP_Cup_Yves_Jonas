/*
------------------------------------------------------------
Copyright 2003-201x Haute �cole ARC Ing�ni�rie, Switzerland. 
All rights reserved.
------------------------------------------------------------
File name :	mSwitch.c
Author and date :	Monnerat Serge 29 ao�t 201x

Description in the header (.h)

-----------------------------------------------------------------------------
History:
-----------------------------------------------------------------------------

$History: $

-----------------------------------------------------------------------------
*/

#include "mSwitch.h"
#include "iDio.h"

//-----------------------------------------------------------------------------
// Configuration des ports IO utilis�s par les interrupteurs et les poussoirs
//-----------------------------------------------------------------------------
void mSwitch_Setup(void)
{
	// Configuration des Ports en entr�e ou en sortie
	iDio_SetPortDirection(kPortC,kMaskIo9+kMaskIo10+kMaskIo11+kMaskIo12+kMaskIo16+kMaskIo17,kIoInput);
}

//-----------------------------------------------------------------------------
// Start du module
//-----------------------------------------------------------------------------
void mSwitch_Open(void)
{
}

//-------------------------------------------------------------------------
// Lecture des interrupteurs
// aSwitchNb: quel interrupteur veut-on lire
// Retour: �tat du switch
//-------------------------------------------------------------------------
bool mSwitch_ReadSwitch(SwitchEnum aSwitch)
{
	bool aState=false;
		
	switch(aSwitch)
		{
			case kSw1:
				aState=iDio_GetPort(kPortC,kMaskIo9);
			break;
			case kSw2:
				aState=iDio_GetPort(kPortC,kMaskIo10);
			break;
			case kSw3:
				aState=iDio_GetPort(kPortC,kMaskIo11);
			break;
			case kSw4:
				aState=iDio_GetPort(kPortC,kMaskIo12);
			break;
		}
		
	return aState;
}

//-------------------------------------------------------------------------
// Lecture des boutons poussoir
// aPushButNb: quel boutons poussoir veut-on lire
// Retour: �tat du bouton poussoir
//-------------------------------------------------------------------------
bool mSwitch_ReadPushBut(PushButEnum aPushButNb)
{
	bool aState=false;
	
	switch(aPushButNb)
		{
			case kPushButSW1:
				aState=iDio_GetPort(kPortC,kMaskIo16);
			break;
			case kPushButSW2:
				aState=iDio_GetPort(kPortC,kMaskIo17);
			break;
		}

	return aState;
}

