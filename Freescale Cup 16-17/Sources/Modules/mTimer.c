/*
------------------------------------------------------------
Copyright 2003-201x Haute école ARC Ingéniérie, Switzerland. 
All rights reserved.
------------------------------------------------------------
File name :	mTimer.c
Author and date :	Monnerat Serge 29 août 201x

Description in the header (.h)

-----------------------------------------------------------------------------
History:
-----------------------------------------------------------------------------

$History: $

-----------------------------------------------------------------------------
*/
#include "mTimer.h"
#include "iFlextimer.h"
#include "iDio.h"

//-----------------------------------------------------------------------------
// Speed Mes module setup
//-----------------------------------------------------------------------------
void mTimer_Setup(void)
{
	
	// Flextimer setup
	iFlextimer_Config();
	
	// Pin direction et enable du pont en H en sortie
	iDio_SetPortDirection(kPortA,kMaskIo15+kMaskIo16+kMaskIo17,kIoOutput);
	iDio_SetPortDirection(kPortB,kMaskIo9,kIoOutput);
	iDio_SetPortDirection(kPortB,kMaskIo16+kMaskIo17,kIoInput);
}

//-----------------------------------------------------------------------------
// Speed Mes module start
//-----------------------------------------------------------------------------
void mTimer_Open(void)
{
	mTimer_SetServoDuty(0, 0);
	mTimer_SetServoDuty(1, 0);
	mTimer_SetMotorDuty(0 ,0);
	// Enable des ponts en H
	iDio_SetPort(kPortA,kMaskIo17,kIoOn);
	iDio_SetPort(kPortA,kMaskIo15,kIoOff);
	iDio_SetPort(kPortA,kMaskIo16,kIoOff);
}

//-----------------------------------------------------------------------------
// Speed Mes module stop
//-----------------------------------------------------------------------------
void mTimer_Close(void)
{
	
}

//-----------------------------------------------------------------------------
// Lecture de la vitesse de rotation des moteurs
// Moteur A = moteur gauche --> valeur négative = en arrière, valeur pos=en avant
// Moteur B = moteur droite
//-----------------------------------------------------------------------------
void mTimer_GetSpeed(float *aSpeedMotLeft,float *aSpeedMotRight)
{
	iFlextimer_GetSpeed(aSpeedMotLeft, aSpeedMotRight);
}

//---------------------------------------------------------------------------
// Modifie la position du servo
// Position entre -1.0 to 1.0
//---------------------------------------------------------------------------
void mTimer_SetServoDuty(UInt8 aServoNumber, float aPosition)
{
	iFlextimer_SetServoDuty(aServoNumber,aPosition);
}

//---------------------------------------------------------------------------
// Modifie le duty du PWM
// Moteur A = moteur gauche (-1 à +1)
// Moteur B = moteur droite (-1 à +1)
//---------------------------------------------------------------------------
void mTimer_SetMotorDuty(float aMotorLeft , float aMotorRight)
{
	iFlextimer_SetMotorDuty(aMotorLeft,aMotorRight);	
}

//---------------------------------------------------------------------------
// Enable des ponts en H des moteurs DC
//---------------------------------------------------------------------------
void mTimer_EnableHBridge(void)
{
	// Enable des ponts en H
	iDio_SetPort(kPortA,kMaskIo17,kIoOn);
	iDio_SetPort(kPortA,kMaskIo15,kIoOff);
	iDio_SetPort(kPortA,kMaskIo16,kIoOff);
}

//---------------------------------------------------------------------------
// Disable des ponts en H des moteurs DC
//---------------------------------------------------------------------------
void mTimer_DisableHBridge(void)
{
	// Disable des ponts en H
	iDio_SetPort(kPortA,kMaskIo15,kIoOn);
	iDio_SetPort(kPortA,kMaskIo16,kIoOn);
}

//---------------------------------------------------------------------------
// Lecture du statut du pont en H gauche
//---------------------------------------------------------------------------
bool mTimer_GetFaultMoteurLeft(void)
{
	// Lecture du statut
	return iDio_GetPort(kPortB,kMaskIo16);
}

//---------------------------------------------------------------------------
// Lecture du statut du pont en H droit
//---------------------------------------------------------------------------
bool mTimer_GetFaultMoteurRight(void)
{
	// Lecture du statut
	return iDio_GetPort(kPortB,kMaskIo17);
}

