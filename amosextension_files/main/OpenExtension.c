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
*
*   INPUTS
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

struct extension * _amosextension_OpenExtension(struct AmosExtensionIFace *Self,
       char * name)
{
	struct _Library *libBase = (struct _Library *) Self -> Data.LibBase;
	struct extension *ext;
	BPTR file;
	unsigned int filesize;

	ext = (struct extension *) libBase->IExec->AllocVecTags( sizeof(struct extension) , AVT_Type, MEMF_SHARED, AVT_ClearWithValue, 0 , TAG_END );

	if (ext)
	{
		file = libBase -> IDOS -> FOpen( name , MODE_OLDFILE, 0 );
		if (file)
		{
			filesize = libBase -> IDOS -> GetFileSize( file );
			ext -> file = (char *)  libBase -> IExec -> AllocVecTags( filesize , AVT_Type, MEMF_SHARED, AVT_ClearWithValue, 0 , TAG_END );
			ext -> header = (struct fileHeader *)	( (char *) ( ext -> file + 0x20) );

			ext -> sizeTable = (unsigned short *) ((char *) ext -> file + 0x20 + sizeof(struct extension) + 0x2 );

			if (ext -> file)
			{
				libBase -> IDOS -> FRead( file, ext -> file, filesize, 1 );
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

