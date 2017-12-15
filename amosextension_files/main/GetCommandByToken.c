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

/****** amosextension/main/GetCommandByToken ******************************************
*
*   NAME
*      GetCommandByToken -- Description
*
*   SYNOPSIS
*      unsigned int GetCommandByToken(unsigned short token);
*
*   FUNCTION
*
*   INPUTS
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

unsigned int _amosextension_GetCommandByToken(struct amosextensionIFace *Self,
       unsigned short token)
{
  return 0;
}

