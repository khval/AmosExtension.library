/* :ts=4
 *  $VER: FirstExtension.c $Revision$ (20-Dec-2017)
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
#include <proto/dos.h>
#include <dos/dos.h>
#include <exec/types.h>
#include <libraries/amosextension.h>
#include <proto/amosextension.h>
#include <stdarg.h>
#include <string.h>
#include "../libbase.h"

/****** amosextension/main/FirstExtension ******************************************
*
*   NAME
*      FirstExtension -- Description
*
*   SYNOPSIS
*      struct ExtensionDescriptor * FirstExtensionItem(struct extension * ext);
*
*   FUNCTION
*		Find first AMOS command in Extension.
*
*   INPUTS
*       ext - extension struct, obtained by OpenExtension()
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

struct tokenDefine 
{
	short token;
	char command[256];
	char arg[256];
};

#define _file_offset_ ret->fileOffset
#define _ext_			ret->ext

struct ExtensionDescriptor * _amosextension_FirstExtensionItem(struct AmosExtensionIFace *Self,
       struct extension * ext)
{
	struct _Library *libBase = (struct _Library *) Self -> Data.LibBase;
	struct ExtensionDescriptor *ret = NULL;	
	char command[256];
	char arg[256];
	int a_count;
	int c_count;
	signed char c;
	BOOL is_command;

	memset( command, 0, 256 );
	memset( arg, 0 , 256 );

	ret = (struct ExtensionDescriptor *) libBase -> IExec -> AllocVecTags( sizeof(struct ExtensionDescriptor) , AVT_Type, MEMF_SHARED, AVT_ClearWithValue, 0 , TAG_END );

	ret -> ext = ext;
	ret -> blockStart = ext -> header -> C_off_size + sizeof(struct fileHeader) + 0x20;
	ret -> fileOffset = ret -> blockStart;
	ret -> tokenInfo.token = (_file_offset_ - 0x20) -  ext -> header -> C_off_size - 0x16;

//	libBase -> IDOS -> Printf("\n\nfile pos %08lx\n\n", ret -> fileOffset );

	sread(&ret -> tokenInfo.NumberOfInstruction, sizeof(short), 1);
	sread(&ret -> tokenInfo.NumberOfFunction, sizeof(short), 1);
	sread( &c,1,1);

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
		int n = strlen( command );
		command[ c_count ] = 0;	// terminate string.

		while ((n>0) && (command[n-1]==' '))
		{
			command[n-1]=0;
			n--;
		}
	}
	arg[ a_count ] = 0;

	if ((c_count>0)&&(a_count>0))
	{
		ret -> tokenInfo.command = strdup(command);
		ret -> tokenInfo.args = strdup(arg);
	}
	else
	{
		ret -> tokenInfo.command = NULL;
		ret -> tokenInfo.args = NULL;
	}

	return ret;
}

