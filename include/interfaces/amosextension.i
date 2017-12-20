#ifndef AMOSEXTENSION_INTERFACE_DEF_H
#define AMOSEXTENSION_INTERFACE_DEF_H
/*
** This file is machine generated from idltool
** Do not edit
*/ 

#include <exec/types.i>
#include <exec/exec.i>
#include <exec/interfaces.i>

STRUCTURE AmosExtensionIFace, InterfaceData_SIZE
	    FPTR IAmosExtension_Obtain
	    FPTR IAmosExtension_Release
	    FPTR IAmosExtension_Expunge
	    FPTR IAmosExtension_Clone
	    FPTR IAmosExtension_OpenExtension
	    FPTR IAmosExtension_CloseExtension
	    FPTR IAmosExtension_GetCommandByName
	    FPTR IAmosExtension_GetCommandByToken
	    FPTR IAmosExtension_FreeTokenInfo
	    FPTR IAmosExtension_GetExtensionName
	    FPTR IAmosExtension_FirstExtension
	    FPTR IAmosExtension_NextExtension
	    FPTR IAmosExtension_CloseExtensionDescriptor
	LABEL AmosExtensionIFace_SIZE

#endif
