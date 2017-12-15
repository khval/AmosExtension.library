#ifndef AMOSEXTENSION_INTERFACE_DEF_H
#define AMOSEXTENSION_INTERFACE_DEF_H
/*
** This file is machine generated from idltool
** Do not edit
*/ 

#include <exec/types.i>
#include <exec/exec.i>
#include <exec/interfaces.i>

STRUCTURE amosextensionIFace, InterfaceData_SIZE
	    FPTR Iamosextension_Obtain
	    FPTR Iamosextension_Release
	    FPTR Iamosextension_Expunge
	    FPTR Iamosextension_Clone
	    FPTR Iamosextension_OpenExtension
	    FPTR Iamosextension_CloseExtension
	    FPTR Iamosextension_GetCommandByName
	    FPTR Iamosextension_GetCommandByToken
	LABEL amosextensionIFace_SIZE

#endif
