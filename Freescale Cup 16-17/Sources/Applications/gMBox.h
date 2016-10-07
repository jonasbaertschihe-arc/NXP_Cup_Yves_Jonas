/*
------------------------------------------------------------
Copyright 2003-20xx Haute �cole ARC Ing�ni�rie, Switzerland. 
All rights reserved.
------------------------------------------------------------
Nom du fichier : 	gMBox.h	
Auteur et Date :	Monnerat Serge 8.5.20xx

But : Bo�te aux lettres

Modifications
Date		Faite	Ctrl		Description
------------------------------------------------------------
*/

#ifndef __GMBOX__
#define __GMBOX__

#include "def.h"

//-----------------------------------------------------------------------------
// Structure du gestionnaire Input
//-----------------------------------------------------------------------------

#define kNbOfSw 8

typedef struct
{
  bool Toto;
}InputStruct;

extern InputStruct gInput;

//-----------------------------------------------------------------------------
// Structure du gestionnaire Compute
//-----------------------------------------------------------------------------

#define kNbOfErr 8
 
typedef struct
{
  bool Titi;
}ComputeStruct;

extern ComputeStruct gCompute;


#endif /* __GMBOX__ */
