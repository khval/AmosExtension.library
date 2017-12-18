/* :ts=4
 *  $VER: GetExtensionName.c $Revision$ (18-Dec-2017)
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

#include "../libbase.h"

/****** amosextension/main/GetExtensionName ******************************************
*
*   NAME
*      GetExtensionName -- Description
*
*   SYNOPSIS
*      char * GetExtensionName(struct TokenInfo * ext);
*
*   FUNCTION
*
*   INPUTS
*       ext - 
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

extern char *local_strdup( struct ExecIFace *IExec, char *str ) ;

char * _amosextension_GetExtensionName(struct AmosExtensionIFace *Self,
       struct extension * ext)
{
	struct _Library *libBase = (struct _Library *) Self -> Data.LibBase;
	unsigned int name_off;
	char *ret;

	name_off = 0x20;
	name_off += sizeof(struct fileHeader);
	name_off += ext -> header-> C_off_size;
	name_off += ext -> header-> C_tk_size;
	name_off += ext -> header-> C_lib_size;

	ret = local_strdup( libBase -> IExec, ext -> file + name_off );
	return ret;
}

