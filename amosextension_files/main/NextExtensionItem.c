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
#include <proto/dos.h>
#include <libraries/amosextension.h>
#include <proto/amosextension.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "../libbase.h"

/****** amosextension/main/NextExtension ******************************************
*
*   NAME
*      NextExtension -- Description
*
*   SYNOPSIS
*      struct ExtensionDescriptor * NextExtensionItem(
*          struct ExtensionDescriptor * extension_descriptor);
*
*   FUNCTION
*		Find next AMOS command
*
*   INPUTS
*       extension_descriptor - Kind a like file descriptor, 
*				but is used keep track of where in extension we are.
*
*   RESULT
*       The result ...
*	
*		struct ExtensionDescriptor
*		{
*			unsigned int fileOffset;			// Offset in file, in memory
*			struct extension	*ext;			// We keep pointer to extension
*			struct TokenInfo	tokenInfo;		// Where store info about the AMOS command
*		};
*	
*   EXAMPLE
*
*		for ( ed = FirstExtensionItem( ext ); ed ; ed = NextExtensionItem( ed ))
*		{
*		}
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

#define _file_offset_	ret->fileOffset
#define ext			ret->ext

#define debug 0

#if (debug)
#define DPrintf 			libBase -> IDOS -> Printf
#else
#define DPrintf( fmt , ... ) 
#endif

struct ExtensionDescriptor * _amosextension_NextExtensionItem(struct AmosExtensionIFace *Self,
       struct ExtensionDescriptor * extension_descriptor)
{
	struct _Library *libBase = (struct _Library *) Self -> Data.LibBase;
	struct ExtensionDescriptor *ret = NULL;
	char command[256];
	char arg[256];
	int a_count;
	int c_count;
	signed char c;
	BOOL is_command;

	if (extension_descriptor == NULL) return NULL;	

	ret = extension_descriptor;

	// free old
	if (ret -> tokenInfo.command)
	{
		char *s,*d = command;
		for (s=ret -> tokenInfo.command;*s;s++) *d++=*s;
		*d=0;

		 free(ret -> tokenInfo.command);
	}
	if (ret -> tokenInfo.args) free(ret -> tokenInfo.args);

	// clear

	ret -> tokenInfo.command  = NULL;
	ret -> tokenInfo.args  = NULL;

	// last value is dc.b

	// align to 16 bit.
	if (ret->fileOffset & 1) sread( &c,1,1);

	DPrintf("%s::filepos: %08lx\n",__FUNCTION__,ret->fileOffset);

	ret -> tokenInfo.token = (unsigned short) ((_file_offset_ - 0x20) -  ext -> header -> C_off_size - 0x16);

	sread(&ret -> tokenInfo.NumberOfInstruction, sizeof(short), 1);

	if (ret -> tokenInfo.NumberOfInstruction == 0)
	{
		libBase -> IExec-> FreeVec( ret );
		return NULL;
	}

	DPrintf("%s::NumberOfInstruction: %08lx\n",__FUNCTION__,ret -> tokenInfo.NumberOfInstruction);

	sread(&ret -> tokenInfo.NumberOfFunction, sizeof(short), 1);
	sread( &c,1,1);

	DPrintf("%s::NumberOfFunction: %08lx\n",__FUNCTION__,ret -> tokenInfo.NumberOfFunction);

	c_count = 0;
	a_count = 0;

	is_command = TRUE;	// we expect command.
	while ((c != -1) && (c != -2))
	{
		if ( (c & 127) > 0)
		{
			if (is_command)
			{
				if (c_count<255) command[ c_count++ ] = c & 127;
			}
			else
			{
				if (a_count<255) arg[ a_count++ ] = c & 127;
			}
		}

		if (c & 128)
		{
			 is_command = FALSE;
		}

		sread( &c,1,1);
	}

	// terminate string only if we have new command.
	if (c_count>0) 
	{
		int n = c_count;
		command[ c_count ] = 0;	// terminate string.

		while ((n>0) && (command[n-1]==' '))	// remove spaces at end line.
		{
			command[n-1]=0;
			n--;
		}
	}
	arg[ a_count ] = 0;

	if ((c_count>0)||(a_count>0))
	{
		ret -> tokenInfo.command = strdup(command);
		ret -> tokenInfo.args = strdup(arg);
	}
	else
	{
		DPrintf("%s::Exit no args or commands exit\n",__FUNCTION__);

		libBase -> IExec-> FreeVec( ret );
		ret = NULL;
	}

	return ret;
}

