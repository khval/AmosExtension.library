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
#include <dos/dos.h>
#include <exec/types.h>
#include <libraries/amosextension.h>
#include <proto/amosextension.h>
#include <stdarg.h>

/****** amosextension/main/FirstExtension ******************************************
*
*   NAME
*      FirstExtension -- Description
*
*   SYNOPSIS
*      struct ExtensionDescriptor * FirstExtension(struct extension * ext);
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

struct ExtensionDescriptor * _amosextension_FirstExtension(struct AmosExtensionIFace *Self,
       struct extension * ext)
{
	struct ExtensionDescriptor *ret = NULL;
	return ret;
}

