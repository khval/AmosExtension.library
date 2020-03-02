/* :ts=4
 *  $VER: OpenExtension.c $Revision$ (15-Dec-2017)
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

#include <string.h>
#include <stdarg.h>

#include "../libbase.h"

/****** amosextension/main/OpenExtension ******************************************
*
*   NAME
*      OpenExtension -- Description
*
*   SYNOPSIS
*      struct extension * OpenExtension(char * name);
*
*   FUNCTION
*		Open Amos Extension file
*
*   INPUTS
*       name - Name of AMOS lib with full path, normally 
*				AMOSPRO:APSystem/xxxxxx.lib
*
*   RESULT
*       The result ...
*
*		struct extension
*		{
*			char *file;						# Address of file in memory
*			struct fileHeader *header;		# Extension Header, size of blocks in extension.
*			unsigned short *sizeTable;		# list of Sizes of commands in bytes
*			struct command *commands;		# list of commands with address to 680x0 assembler routine, and size of the code.
*		};
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

void init_command_list( struct extension *ext , int commands )
{
	int n = 0;
	unsigned int off = 0x20 + sizeof(struct fileHeader);

	off += ext -> header -> C_off_size;
	off += ext -> header -> C_tk_size;

	for(n=0;n<commands;n++)
	{
		ext->commands[n].func = (void *) (ext -> file + off);
		ext->commands[n].size = ext -> sizeTable[n] *2;
		off += ext->commands[n].size;
	}
}

struct errorFix
{
	const char *name;
	int token_error_offset;
};

static struct errorFix errortab[] =
{
	{"AMOSPro_TURBO_Plus.Lib",4},
	{"AMOSPro_CRAFT.Lib",4}
};


struct extension * _amosextension_OpenExtension(struct AmosExtensionIFace *Self,
       char * name)
{
	struct _Library *libBase = (struct _Library *) Self -> Data.LibBase;
	struct extension *ext;
	BPTR file;
	unsigned int filesize;
	unsigned int commands;
	char *ptr, *cptr;
	int n;

	ext = (struct extension *) libBase->IExec->AllocVecTags( sizeof(struct extension) , AVT_Type, MEMF_SHARED, AVT_ClearWithValue, 0 , TAG_END );

	if (ext)
	{
		file = libBase -> IDOS -> FOpen( name , MODE_OLDFILE, 0 );
		if (file)
		{
			filesize = libBase -> IDOS -> GetFileSize( file );
			ext -> file = (char *)  libBase -> IExec -> AllocVecTags( filesize , AVT_Type, MEMF_SHARED, AVT_ClearWithValue, 0 , TAG_END );
			ext -> header = (struct fileHeader *)	( (char *) ( ext -> file + 0x20) );
			ext -> sizeTable = (unsigned short *) ((char *) ext -> file + 0x20 + sizeof(struct fileHeader) );

			if (ext -> file)
			{
				libBase -> IDOS -> FRead( file, ext -> file, filesize, 1 );
			}

			commands = ext -> header -> C_off_size / 2;
			ext -> commands = (struct command *)  libBase -> IExec -> AllocVecTags( sizeof(struct command) * commands , AVT_Type, MEMF_SHARED, AVT_ClearWithValue, 0 , TAG_END );
			if (ext -> commands) init_command_list( ext , commands );

			cptr = name;
			for (ptr = name + strlen(name); ptr > name ; ptr-- )
			{
				if ((*ptr=='/')||(*ptr==':'))
				{
					cptr = ptr+1;
					break;
				}
			}
			
			ext -> token_error_offset = 0;
			for (n=0; n < sizeof(errortab)/sizeof(struct errorFix);n++)
			{
				if (strcasecmp(errortab[n].name,cptr)==0)
				{
					ext -> token_error_offset = errortab[n].token_error_offset;
					break;
				}	
			}

			libBase -> IDOS -> FClose( file );
		}	
		else
		{
			libBase -> IExec -> FreeVec(ext);
			ext = NULL;
		}
	}

	return ext;
}

