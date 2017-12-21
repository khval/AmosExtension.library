/* :ts=4
 *  $VER: CloseExtension.c $Revision$ (15-Dec-2017)
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
#include <stdlib.h>

#include "../libbase.h"

/****** amosextension/main/CloseExtension ******************************************
*
*   NAME
*      CloseExtension -- Description
*
*   SYNOPSIS
*      void CloseExtension(struct extension * extension);
*
*   FUNCTION
*		Close AMOS Extension file
*
*   INPUTS
*       extension - Pointer to AMOS extension to close
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

void _amosextension_CloseExtension(struct AmosExtensionIFace *Self,   struct extension * ext)
{
	struct _Library *libBase = (struct _Library *) Self -> Data.LibBase;

	if (ext)
	{
		if (ext->file)			libBase->IExec->FreeVec( ext -> file );
		if (ext->commands)	libBase->IExec->FreeVec( ext -> commands );

		libBase -> IExec -> FreeVec( ext );
	}
}

