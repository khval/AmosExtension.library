/* :ts=4
 *  $VER: NextExtension.c $Revision$ (20-Dec-2017)
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

/****** amosextension/main/NextExtension ******************************************
*
*   NAME
*      NextExtension -- Description
*
*   SYNOPSIS
*      struct ExtensionDescriptor * NextExtension(
*          struct ExtensionDescriptor * extension_descriptor);
*
*   FUNCTION
*
*   INPUTS
*       extension_descriptor - 
*
*   RESULT
*       The result ...
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

struct ExtensionDescriptor * _amosextension_NextExtension(struct AmosExtensionIFace *Self,
       struct ExtensionDescriptor * extension_descriptor)
{
	return NULL;
}

