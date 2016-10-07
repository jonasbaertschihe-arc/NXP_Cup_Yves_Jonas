/*
------------------------------------------------------------
Copyright 2003-201x Haute �cole ARC Ing�ni�rie, Switzerland.
All rights reserved.
------------------------------------------------------------
File name :	mCpu.c
Author and date :	Monnerat Serge 7 mars 201x

Description in the header file (.h)

-----------------------------------------------------------------------------
History:
-----------------------------------------------------------------------------

$History: $

-----------------------------------------------------------------------------
*/

#include "mCpu.h"
#include "iCpu.h"

//-----------------------------------------------------------------------
// Low level CPU setup
//-----------------------------------------------------------------------
void mCpu_Setup(void)
{
	// PLL and crossbar configuration
	iCpu_SysInit();
}

