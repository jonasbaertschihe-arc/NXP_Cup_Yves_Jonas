/*
------------------------------------------------------------
Copyright 2003-201x Haute �cole ARC Ing�ni�rie, Switzerland. 
All rights reserved.
------------------------------------------------------------
Nom du fichier : 	mSwitch.h	
Auteur et Date :	Monnerat Serge 29 ao�t 201x

But : Interface permettant l'utilisation des interrupteurs et poussoirs

-----------------------------------------------------------------------------
Historique:
-----------------------------------------------------------------------------

$History: $


-----------------------------------------------------------------------------
*/

#ifndef MSWITCH_H_
#define MSWITCH_H_

#include"def.h"

// Enum�r� des interrupteurs 
typedef enum
{
	kSw1=0,
	kSw2=1,
	kSw3=2,
	kSw4=3
}SwitchEnum;

// Enum�r� des boutons poussoirs
typedef enum
{
	kPushButSW1=0,
	kPushButSW2=1
}PushButEnum;

//-----------------------------------------------------------------------------
// Configuration des ports IO utilis�s par les interrupteurs et les poussoirs
//-----------------------------------------------------------------------------
void mSwitch_Setup(void);

//-----------------------------------------------------------------------------
// Start du module
//-----------------------------------------------------------------------------
void mSwitch_Open(void);

//-------------------------------------------------------------------------
// Lecture des interrupteurs
// aSwitchNb: quel interrupteur veut-on lire
// Retour: �tat du switch
//-------------------------------------------------------------------------
bool mSwitch_ReadSwitch(SwitchEnum aSwitch);

//-------------------------------------------------------------------------
// Lecture des boutons poussoir
// aPushButNb: quel boutons poussoir veut-on lire
// Retour: �tat du bouton poussoir
//-------------------------------------------------------------------------
bool mSwitch_ReadPushBut(PushButEnum aPushButNb);

#endif
