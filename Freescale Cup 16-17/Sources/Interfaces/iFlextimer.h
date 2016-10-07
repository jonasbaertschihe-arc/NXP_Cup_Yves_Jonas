/*
------------------------------------------------------------
Copyright 2003-201x Haute �cole ARC Ing�ni�rie, Switzerland. 
All rights reserved.
------------------------------------------------------------
File name : 	iFlextimer.h	
Author and date :	Monnerat Serge 29 ao�t 2015

Goal : 

-----------------------------------------------------------------------------
History:
-----------------------------------------------------------------------------

$History: $


-----------------------------------------------------------------------------
*/
#ifndef __iFlextimer__
#define __iFlextimer__

#include "def.h"

//------------------------------------------------------------
// Flextimer setup
//------------------------------------------------------------
void iFlextimer_Config(void);
//-----------------------------------------------------------------------------
// Lecture de la vitesse de rotation des moteurs
// Moteur A = moteur gauche --> valeur n�gative = en arri�re, valeur pos=en avant
// Moteur B = moteur droite
//-----------------------------------------------------------------------------
void iFlextimer_GetSpeed(float *aSpeedMotLeft, float *aSpeedMotRight);

//---------------------------------------------------------------------------
// Modifie la position du servo
//---------------------------------------------------------------------------
void iFlextimer_SetServoDuty(UInt8 aServoNumber, float aPosition);

//---------------------------------------------------------------------------
// Modifie le duty du PWM
// Moteur A = moteur gauche
// Moteur B = moteur droite
//---------------------------------------------------------------------------
void iFlextimer_SetMotorDuty(float aMotorLeft , float aMotorRight);

#endif
