/* :ts=4
 *  $VER: GetCommandByToken.c $Revision$ (15-Dec-2017)
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

/****** amosextension/main/GetCommandByToken ******************************************
*
*   NAME
*      GetCommandByToken -- Description
*
*   SYNOPSIS
*      struct TokenInfo * GetCommandByToken(struct extension *ext,unsigned short token);
*
*   FUNCTION
*
*   INPUTS
*       ext - 
*       token - 
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


static void local_memcpy(char *dest, char *src, int size )
{
	int n;
	for (n=0;n<size;n++) { dest[n] = src[n]; }
}

static char *local_strdup( struct ExecIFace *IExec, char *str ) 
{
	char *ret;
	int _len_ = 0;
	char *p;
	char *d;
	for (p=str; *p; p++) _len_++;

	if (_len_>0)
	{
		ret = (char *) IExec->AllocVecTags( _len_ + 1 , AVT_Type, MEMF_SHARED, AVT_ClearWithValue, 0 , TAG_END );
		d = ret;
		for (p=str; *p; p++) *d++= *p;
		*d =0;
	}
	else
	{
		ret = NULL;
	}

	return ret;
}


#define sread( dest, usize, n )		\
	{							\
		local_memcpy( (char *) (dest), ext -> file + _file_offset_, usize *n );	\
		_file_offset_ += (usize * n);								\
	}

struct TokenInfo * _amosextension_GetCommandByToken(struct AmosExtensionIFace *Self,
	struct extension *ext, unsigned short token)
{
	struct _Library *libBase = (struct _Library *) Self -> Data.LibBase;
	struct TokenInfo *info;
	signed char c;
	int a_count = 0;
	int c_count = 0;
	BOOL is_command;
	int _file_offset_ = 0x20;
	char command[256];
	char arg[256];

	info = (struct TokenInfo *) libBase->IExec->AllocVecTags( sizeof(struct TokenInfo) , AVT_Type, MEMF_SHARED, AVT_ClearWithValue, 0 , TAG_END );
	if (!info) return NULL;

	_file_offset_ = token + 0x20 + ext -> header -> C_off_size + 0x16;

	sread(&info -> NumberOfInstruction, sizeof(short), 1);
	sread(&info -> NumberOfFunction, sizeof(short), 1);
	sread(&c,1,1);

	// is it valid?
	if (info -> NumberOfInstruction & 0xF000)
	{
		libBase->IExec->FreeVec( info );
		return NULL;
	}

	is_command = TRUE;	// we expect command.
	while ((c != -1) && (c != -2) && (c_count < 254) && (a_count < 254))
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
	command[ c_count ] = 0;
	arg[ a_count ] = 0;

	info -> command = c_count ? local_strdup( libBase->IExec, command) : NULL;
	info -> args = a_count ? local_strdup( libBase->IExec, arg) : NULL;

	return info;
}

