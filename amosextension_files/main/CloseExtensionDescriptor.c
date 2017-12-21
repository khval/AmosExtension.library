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
#include <stdlib.h>
#include "../libbase.h"

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
*		This command should be used if extension_descriptor
*		is not NULL, for example if you exit the loop early.
*
*   INPUTS
*       extension_descriptor - Kind a like file descriptor, 
*				but is used keep track of where in extension we are.
*
*   RESULT
*       This function does not return a result
*
*   EXAMPLE
*
*		for ( ed = FirstExtensionItem( ext ); ed ; ed = NextExtensionItem( ed ))
*		{
*			if (strcmp( ed -> tokenInfo.command, "find command")==0)
*			{
*				CloseExtensionDescriptor(ed);	// clean up before exit loop
*				ed = NULL;
*				break;
*			}
*		}
*
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
	struct _Library *libBase = (struct _Library *) Self -> Data.LibBase;

	if (extension_descriptor == NULL)  return;		// can be freed by NextExtension

	if (extension_descriptor -> tokenInfo.command) free( extension_descriptor -> tokenInfo.command );
	if (extension_descriptor -> tokenInfo.args) free( extension_descriptor -> tokenInfo.args );
	libBase -> IExec -> FreeVec(extension_descriptor);
}

