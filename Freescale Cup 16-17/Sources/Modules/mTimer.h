/*
------------------------------------------------------------
Copyright 2003-201x Haute �cole ARC Ing�ni�rie, Switzerland. 
All rights reserved.
------------------------------------------------------------
File name : 	mTimer.h	
Author and date :	Monnerat Serge 29 ao�t 201x

Goal : 

-----------------------------------------------------------------------------
History:
-----------------------------------------------------------------------------

$History: $


-----------------------------------------------------------------------------
*/
#ifndef __MTIMER__
#define __MTIMER__

#include "def.h"

//-----------------------------------------------------------------------------
// Speed Mes module setup
//-----------------------------------------------------------------------------
void mTimer_Setup(void);

//-----------------------------------------------------------------------------
// Speed Mes module start
//-----------------------------------------------------------------------------
void mTimer_Open(void);

//-----------------------------------------------------------------------------
// Speed Mes module stop
//-----------------------------------------------------------------------------
void mTimer_Close(void);

//-----------------------------------------------------------------------------
// Lecture de la vitesse de rotation des moteurs
// Moteur A = moteur gauche --> valeur n�gative = en arri�re, valeur pos=en avant
// Moteur B = moteur droite
//-----------------------------------------------------------------------------
void mTimer_GetSpeed(float *aSpeedMotLeft,float *aSpeedMotRight);

//---------------------------------------------------------------------------
// Modifie la position du servo
// Position entre -1.0 to 1.0
//---------------------------------------------------------------------------
void mTimer_SetServoDuty(UInt8 aServoNumber, float aPosition);

//---------------------------------------------------------------------------
// Modifie le duty du PWM
// Moteur A = moteur gauche
// Moteur B = moteur droite
//---------------------------------------------------------------------------
void mTimer_SetMotorDuty(float aMotorLeft , float aMotorRight);

//---------------------------------------------------------------------------
// Enable des ponts en H des moteurs DC
//---------------------------------------------------------------------------
void mTimer_EnableHBridge(void);

//---------------------------------------------------------------------------
// Disable des ponts en H des moteurs DC
//---------------------------------------------------------------------------
void mTimer_DisableHBridge(void);

//---------------------------------------------------------------------------
// Lecture du statut du pont en H gauche
//---------------------------------------------------------------------------
bool mTimer_GetFaultMoteurLeft(void);

//---------------------------------------------------------------------------
// Lecture du statut du pont en H droit
//---------------------------------------------------------------------------
bool mTimer_GetFaultMoteurRight(void);

#endif
