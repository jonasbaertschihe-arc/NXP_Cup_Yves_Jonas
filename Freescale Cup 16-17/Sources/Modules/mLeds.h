/*
------------------------------------------------------------
Copyright 2003-201x Haute �cole ARC Ing�ni�rie, Switzerland.
All rights reserved.
------------------------------------------------------------
File name : 	mLeds.h
Author and date :	Monnerat Serge 29 ao�t 201x

Goal : ON/OFF des LEDs

-----------------------------------------------------------------------------
History:
-----------------------------------------------------------------------------

$History: $


-----------------------------------------------------------------------------
*/

#ifndef MLEDS_H_
#define MLEDS_H_

#include"def.h"

// Masque des LED
typedef enum
{
  kMaskLed1=1,
  kMaskLed2=2,
  kMaskLed3=4,
  kMaskLed4=8
}LedMaskEnum;

// Etat des LED
typedef enum
{
  kLedOff,
  kLedOn
}LedStateEnum;

//-----------------------------------------------------------------------------
// Configuration des ports IO utilis�s par les LEDS
//-----------------------------------------------------------------------------
void mLeds_Setup(void);

//-----------------------------------------------------------------------------
// Start du module
//-----------------------------------------------------------------------------
void mLeds_Open(void);

//-----------------------------------------------------------------------------
// On Off des LED
// aMask:   choix des LED sur lesquelles on veut agir (si bit � 1)
// aState:  choix de l'�tat des LED d�sir�s
//-----------------------------------------------------------------------------
void mLeds_Write(LedMaskEnum aMask,LedStateEnum aState);

//-----------------------------------------------------------------------------
// On Off des LED
// aMask:   choix des LED sur lesquelles on veut agir (si bit � 1)
//-----------------------------------------------------------------------------
void mLeds_Toggle(LedMaskEnum aMask);

#endif
