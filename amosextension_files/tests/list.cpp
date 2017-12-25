
#include <stdio.h>
#include <stdlib.h>
#include <proto/exec.h>
#include <proto/AmosExtension.h>
#include <string.h>
#include "init.h"

int main()
{
	struct extension *ext = NULL;
	TokenInfo *info;
	char *name;
	struct ExtensionDescriptor *ed;

	if (init())
	{
		ext = OpenExtension( (char *) "amospro:APSystem/AMOSPro_Misc.lib");

		if (ext)
		{
			for ( ed =FirstExtensionItem( ext ); ed ; ed = NextExtensionItem( ed ))
			{
				printf("%04X,%04x,%d,%d\n", 
						ed -> fileOffset,
						ed -> tokenInfo.token,
						ed -> tokenInfo.NumberOfInstruction,
						ed -> tokenInfo.NumberOfFunction);

				printf("%s: %s\n", 
						(ed -> tokenInfo.command) ? ed -> tokenInfo.command : "NULL",
						(ed -> tokenInfo.args) ? ed -> tokenInfo.args : "NULL");
			}

			CloseExtension(ext);
		}
	}

	closedown( );

	return 0;
}

