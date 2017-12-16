
#include <stdio.h>
#include <stdlib.h>
#include <proto/exec.h>
#include <proto/AmosExtension.h>

struct Library 				 *AmosExtensionBase = NULL;
struct AmosExtensionIFace	 *IAmosExtension = NULL;

BOOL open_lib( const char *name, int ver , const char *iname, int iver, struct Library **base, struct Interface **interface)
{
	*interface = NULL;
	*base = OpenLibrary( name , ver);
	if (*base)
	{
		 *interface = GetInterface( *base,  iname , iver, TAG_END );
		if (!*interface) printf("Unable to getInterface %s for %s %ld!\n",iname,name,ver);
	}
	else
	{
	   	printf("Unable to open the %s %ld!\n",name,ver);
	}
	return (*interface) ? TRUE : FALSE;
}


bool init()
{
	if ( ! open_lib( "amosextension.library", 1L , "main", 1, &AmosExtensionBase, (struct Interface **) &IAmosExtension  ) ) return FALSE;

	return TRUE;
}

void closedown()
{
	if (IAmosExtension) DropInterface((struct Interface*) IAmosExtension); IAmosExtension = 0;
	if (AmosExtensionBase) CloseLibrary(AmosExtensionBase); AmosExtensionBase = 0;
}

int main()
{
	struct extension *ext;

	if (init())
	{
		printf("** lib opened **\n");

		ext = OpenExtension( (char *) "amospro:APSystem/AMOSPro_Ldos.lib");

		if (ext)
		{
			printf(" ** extention open ** \n");

			CloseExtension(ext);
		}
	}

	closedown( );

	return 0;
}

