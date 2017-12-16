
/* This file was generated by idltool 53.6. Do not edit */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef EXEC_EXEC_H
#include <exec/exec.h>
#endif
#ifndef EXEC_INTERFACES_H
#include <exec/interfaces.h>
#endif

#ifndef LIBRARIES_AMOSEXTENSION_H
#include <libraries/amosextension.h>
#endif

extern ULONG                VARARGS68K _amosextension_Obtain(struct AmosExtensionIFace *);
extern ULONG                VARARGS68K _amosextension_Release(struct AmosExtensionIFace *);
extern struct AmosExtension * VARARGS68K _amosextension_OpenExtension(struct AmosExtensionIFace *, char * name);
extern void                 VARARGS68K _amosextension_CloseExtension(struct AmosExtensionIFace *, struct extension * extension);
extern unsigned int         VARARGS68K _amosextension_GetCommandByName(struct AmosExtensionIFace *, char * name);
extern unsigned int         VARARGS68K _amosextension_GetCommandByToken(struct AmosExtensionIFace *, unsigned short token);
