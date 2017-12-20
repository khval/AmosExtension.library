/* :ts=4
 *  $VER: CloseExtensionDescriptor.c $Revision$ (20-Dec-2017)
 *
 *  This file is part of amosextension.
 *
 *  Copyright (c) 2017 LiveForIt Software.
 *  MIT License.
 *
 * $Id$
 *
 * $Log$
 *
 *
 */


#include <exec/exec.h>
#include <proto/exec.h>
#include <dos/dos.h>
#include <exec/types.h>
#include <libraries/amosextension.h>
#include <proto/amosextension.h>
#include <stdarg.h>

/****** amosextension/main/CloseExtensionDescriptor ******************************************
*
*   NAME
*      CloseExtensionDescriptor -- Description
*
*   SYNOPSIS
*      void CloseExtensionDescriptor(
*          struct ExtensionDescriptor * extension_descriptor);
*
*   FUNCTION
*
*   INPUTS
*       extension_descriptor - 
*
*   RESULT
*       This function does not return a result
*
*   EXAMPLE
*
*   NOTES
*
*   BUGS
*
*   SEE ALSO
*
*****************************************************************************
*
*/

void _amosextension_CloseExtensionDescriptor(struct AmosExtensionIFace *Self,
       struct ExtensionDescriptor * extension_descriptor)
{
	if (extension_descriptor == NULL)  return;		// can be freed by NextExtension

}

