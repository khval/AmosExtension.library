/* :ts=4
 *  $VER: FreeTokenInfo.c $Revision$ (18-Dec-2017)
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
#include <string.h>

#include "../libbase.h"

/****** amosextension/main/FreeTokenInfo ******************************************
*
*   NAME
*      FreeTokenInfo -- Description
*
*   SYNOPSIS
*      void FreeTokenInfo(struct TokenInfo * info);
*
*   FUNCTION
*
*   INPUTS
*       info - 
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

void _amosextension_FreeTokenInfo(struct AmosExtensionIFace *Self,
       struct TokenInfo * info)
{
	struct _Library *libBase = (struct _Library *) Self -> Data.LibBase;

	if (info -> command) free( info -> command );
	if (info -> args)  free( info -> args );
 	libBase->IExec->FreeVec( info );
}

