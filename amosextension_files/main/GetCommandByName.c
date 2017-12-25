/* :ts=4
 *  $VER: GetCommandByName.c $Revision$ (15-Dec-2017)
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
#include <proto/dos.h>
#include <exec/types.h>
#include <libraries/amosextension.h>
#include <proto/amosextension.h>
#include <stdarg.h>
#include <string.h>

#include "../libBase.h"

/****** amosextension/main/GetCommandByName ******************************************
*
*   NAME
*      GetCommandByName -- Description
*
*   SYNOPSIS
*      struct TokenInfo *GetCommandByName( struct extension *ext, char * name );
*
*   FUNCTION
*
*   INPUTS
*       ext -
*       name - 
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

struct tokenDefine 
{
	short token;
	char command[256];
	char arg[256];
};

#define _ext_ ext

struct TokenInfo *_amosextension_GetCommandByName(struct AmosExtensionIFace *Self,
	struct extension *ext, char * cmdName)
{
	struct _Library *libBase = (struct _Library *) Self -> Data.LibBase;
	struct tokenDefine cmd;
	BOOL is_command;
	short NumberOfInstruction;
	short NumberOfFunction;
	int a_count;
	int c_count;
	signed char c;
	struct TokenInfo *info = NULL;
	int _file_offset_ = ext -> header -> C_off_size + sizeof(struct fileHeader) + 0x20;

	memset( cmd.command, 0, 256 );
	memset( cmd.arg, 0 , 256 );

	cmd.token = (_file_offset_ - 0x20) -  ext -> header -> C_off_size - 0x16;

	libBase -> IDOS -> Printf("%s:%ld\n",__FUNCTION__,__LINE__);

	sread(&NumberOfInstruction, sizeof(NumberOfInstruction), 1);

	while ((NumberOfInstruction != 0))
	{

		sread(&NumberOfFunction, sizeof(NumberOfFunction), 1);
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
					if (c_count<255) cmd.command[ c_count++ ] = c & 127;
				}
				else
				{
					if (a_count<255) cmd.arg[ a_count++ ] = c & 127;
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
			int n = strlen( cmd.command );
			cmd.command[ c_count ] = 0;	// terminate string.

			while ((n>0) && (cmd.command[n-1]==' '))
			{
				cmd.command[n-1]=0;
				n--;
			}
		}
		cmd.arg[ a_count ] = 0;

		if (strcmp(cmdName, cmd.command) == 0)
		{
			info = (struct TokenInfo *) libBase -> IExec -> AllocVecTags( sizeof(struct TokenInfo) , AVT_Type, MEMF_SHARED, AVT_ClearWithValue, 0 , TAG_END );
			if (info)
			{
				info -> token = cmd.token;
				info -> NumberOfInstruction = NumberOfInstruction;
				info -> NumberOfFunction = NumberOfFunction;
				info -> command = c_count ? strdup( cmd.command ) : NULL;
				info -> args = a_count ? strdup( cmd.arg ) : NULL;
			}

			 break;
		}

		if ( _file_offset_ & 1 )  sread( &c,1,1);
		cmd.token = (_file_offset_ - 0x20) -  ext -> header -> C_off_size - 0x16;
		sread(&NumberOfInstruction, sizeof(NumberOfInstruction), 1);
	}

	return info;
}

