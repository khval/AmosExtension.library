/* :ts=4
 *  $VER: GetExtensionNameByToken.c $Revision$ (30-Dec-2017)
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
#include "../libBase.h"

/****** amosextension/main/GetExtensionNameByToken ******************************************
*
*   NAME
*      GetExtensionNameByToken -- Description
*
*   SYNOPSIS
*      char * GetExtensionNameByToken(struct extension * ext, 
*          unsigned short token);
*
*   FUNCTION
*	This function is guaranteed  to find a name, while normaly token don't always have a name,
*	but instead depend on previous token. this function scans the token list to find previous names.
*
*	So if most find a name use this, if you don't need the name use GetCommandByToken() its quicker.
*
*   INPUTS
*       ext - Extension struct, obtained by OpenExtension()
*       token - Token number
*
*   RESULT
*       If name is found a string is returned if token number is wrong, this function should return NULL.
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

struct ExtensionDescriptor * _amosextension_FirstExtensionItem(struct AmosExtensionIFace *Self, struct extension * ext);
struct ExtensionDescriptor * _amosextension_NextExtensionItem(struct AmosExtensionIFace *Self, struct ExtensionDescriptor * extension_descriptor);

char * _amosextension_GetExtensionNameByToken(struct AmosExtensionIFace *Self,
       struct extension * ext,
       unsigned short token)
{
	char *str = NULL;
	struct ExtensionDescriptor *ed;

	for ( ed = _amosextension_FirstExtensionItem( Self, ext ); ed ; ed = _amosextension_NextExtensionItem( Self, ed ))
	{
		if (ed->tokenInfo.command) str = ed -> tokenInfo.command;

		if ( ed -> tokenInfo.token == token )
		{
			return str ? strdup( (str[0]=='!' ? str+1 : str ) ) : NULL;
		}
	}
	return NULL;
}

