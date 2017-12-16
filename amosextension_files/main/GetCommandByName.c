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
#include <exec/types.h>
#include <libraries/amosextension.h>
#include <proto/amosextension.h>
#include <stdarg.h>

/****** amosextension/main/GetCommandByName ******************************************
*
*   NAME
*      GetCommandByName -- Description
*
*   SYNOPSIS
*      unsigned int GetCommandByName(char * name);
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

unsigned int _amosextension_GetCommandByName(struct AmosExtensionIFace *Self,
       char * name)
{
  return 0;
}

