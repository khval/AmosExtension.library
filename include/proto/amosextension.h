#ifndef PROTO_AMOSEXTENSION_H
#define PROTO_AMOSEXTENSION_H

/*
**	$Id$
**
**	Prototype/inline/pragma header file combo
**
**	Copyright (c) 2010 LiveForIt Software.
**	MIT License.
*/

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef LIBRARIES_AMOSEXTENSION_H
#include <libraries/amosextension.h>
#endif

/****************************************************************************/

#ifndef __NOLIBBASE__
 #ifndef __USE_BASETYPE__
  extern struct Library * amosExtensionBase;
 #else
  extern struct Library * amosExtensionBase;
 #endif /* __USE_BASETYPE__ */
#endif /* __NOLIBBASE__ */

/****************************************************************************/

#ifdef __amigaos4__
 #include <interfaces/amosextension.h>
 #ifdef __USE_INLINE__
  #include <inline4/amosextension.h>
 #endif /* __USE_INLINE__ */
 #ifndef CLIB_AMOSEXTENSION_PROTOS_H
  #define CLIB_AMOSEXTENSION_PROTOS_H 1
 #endif /* CLIB_AMOSEXTENSION_PROTOS_H */
 #ifndef __NOGLOBALIFACE__
  extern struct amosextensionIFace *Iamosextension;
 #endif /* __NOGLOBALIFACE__ */
#else /* __amigaos4__ */
 #ifndef CLIB_AMOSEXTENSION_PROTOS_H
  #include <clib/amosextension_protos.h>
 #endif /* CLIB_AMOSEXTENSION_PROTOS_H */
 #if defined(__GNUC__)
  #ifndef __PPC__
   #include <inline/amosextension.h>
  #else /* __PPC__ */
   #include <ppcinline/amosextension.h>
  #endif /* __PPC__ */
 #elif defined(__VBCC__)
  #ifndef __PPC__
   #include <inline/amosextension_protos.h>
  #endif /* __PPC__ */
 #else /* __GNUC__ */
  #include <pragmas/amosextension_pragmas.h>
 #endif /* __GNUC__ */
#endif /* __amigaos4__ */

/****************************************************************************/

#endif /* PROTO_AMOSEXTENSION_H */
