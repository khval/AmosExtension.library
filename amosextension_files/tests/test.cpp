
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

void dump_list(unsigned short *ptr , int cnt)
{
	int n = 0;
	unsigned int off = 0;

	for(n=0;n<cnt;n++)
	{
		printf("%3d\t%08x\t%04X (%d)\n",n, off, *ptr,(int) (*ptr *2) );

		off += (*ptr *2);
		ptr++;
	}

	printf("\nSize %d\n\n",off);
}

void dump_command_list(struct command *ptr , int cnt)
{
	int n = 0;
	unsigned int off = 0;

	for(n=0;n<cnt;n++)
	{
		printf("%3d\t%08x\t%04X (%d)\n",n, off, ptr->func,(int) ptr->size );

		off += ptr->size;
		ptr++;
	}

	printf("\nSize %d\n\n",off);
}

int main()
{
	struct extension *ext = NULL;
	unsigned int name_off;

	if (init())
	{
		printf("** lib opened **\n");

		ext = OpenExtension( (char *) "amospro:APSystem/AMOSPro_Request.lib");
//		ext = OpenExtension( (char *) "amospro:APSystem/AMOSPro_Music.lib");
//		ext = OpenExtension( (char *) "amospro:APSystem/AMOSPro_Ldos.lib");

		if (ext)
		{
			printf(" ** extention open ** \n");

			printf("%6d  (%04x)\n", ext -> header-> C_off_size, ext -> header-> C_off_size );
			printf("%6d  (%04x)\n", ext -> header-> C_tk_size, ext -> header-> C_tk_size );
			printf("%6d  (%04x)\n", ext -> header-> C_lib_size, ext -> header-> C_lib_size );
			printf("%6d  (%04x)\n", ext -> header-> C_title_size, ext -> header-> C_title_size );

			printf("end %d\n", ext -> header -> end );

//			ext -> sizeTable = (unsigned short *) ((char *) ext -> file + 0x20 + sizeof(struct fileHeader) + 0x2 );

			dump_command_list( ext -> commands, ext -> header->C_off_size / 2 );

//			dump_list( ext -> sizeTable, ext -> header->C_off_size / 2 );

			printf("off size %08X - %d ---- %08x\n", 
					ext -> header->C_off_size,
					ext -> header->C_off_size,
					((char *) ext -> header - (char *) ext -> file));

			name_off = 0x20;
			name_off += sizeof(struct fileHeader);
			name_off += ext -> header-> C_off_size;
			name_off += ext -> header-> C_tk_size;
			name_off += ext -> header-> C_lib_size;

			printf("\nname off %08X\n\n", name_off );

			printf("name: %s\n", ext -> file + name_off );

			CloseExtension(ext);
		}
	}

	closedown( );

	return 0;
}

