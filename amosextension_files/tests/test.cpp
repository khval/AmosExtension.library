
#include <stdio.h>
#include <stdlib.h>
#include <proto/exec.h>
#include <proto/AmosExtension.h>
#include <string.h>

struct Library 				 *AmosExtensionBase = NULL;
struct AmosExtensionIFace	 *IAmosExtension = NULL;

struct tokenDefine 
{
	short token;
	char command[256];
	char arg[256];
};


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

#define sread( dest, usize, n )		\
	{							\
		memcpy( dest, ext -> file + _file_offset_, usize *n );	\
		_file_offset_ += (usize * n);								\
	}

void token_reader( struct extension *ext, struct fileHeader &FH )
{
	struct tokenDefine cmd;
	bool is_command;
	short NumberOfInstruction;
	short NumberOfFunction;
	int a_count;
	int c_count;
	signed char c;
	char comment[1000];
	const char *ret;
	char *ptr;
	char *aptr;
	bool rv;

	int _file_offset_ = FH.C_off_size + sizeof(struct fileHeader) + 0x20;

	memset( cmd.command, 0, 256 );
	memset( cmd.arg, 0 , 256 );

		cmd.token = (_file_offset_ - 0x20) - FH.C_off_size - 0x16;

		sread(&NumberOfInstruction, sizeof(NumberOfInstruction), 1);

		while ((NumberOfInstruction != 0))
		{

			sread(&NumberOfFunction, sizeof(NumberOfFunction), 1);
			sread( &c,1,1);

			c_count = 0;
			a_count = 0;

			is_command = TRUE;	// we expect command.
			while ((c != -1) && (c != -2))
			{
				if ( (c & 127) > 0)
				{
					if (is_command)
					{
						if (c_count<255) cmd.command[ c_count++ ] = c & 127;
					}
					else
					{
						if (a_count<255) cmd.arg[ a_count++ ] = c & 127;
					}
				}

				if (c & 128)
				{
					 is_command = FALSE;
				}

				sread( &c,1,1);
			}

			// terminate string only if we have new command.
			if (c_count>0) 
			{
				int n = strlen( cmd.command );
				cmd.command[ c_count ] = 0;	// terminate string.

				while ((n>0) && (cmd.command[n-1]==' '))
				{
					cmd.command[n-1]=0;
					n--;
				}
			}
			cmd.arg[ a_count ] = 0;

			printf("%3d: { 0x%04X,%c%s%c }\n",_file_offset_, cmd.token, 34, cmd.command[0]=='!' ? cmd.command+1 : cmd.command, 34);

			if ( _file_offset_ & 1 )  sread( &c,1,1);
			cmd.token = (_file_offset_ - 0x20) - FH.C_off_size - 0x16;

			sread(&NumberOfInstruction, sizeof(NumberOfInstruction), 1);
		}
}

int main()
{
	struct extension *ext = NULL;
	TokenInfo *info;
	char *name;

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

			token_reader( ext, *ext -> header );

			info = GetCommandByToken( ext, 0x0002 );
			if (info)
			{
				printf("command %s\nargs %s\n", info -> command, info -> args);
				FreeTokenInfo(info);
			}

			info = GetCommandByToken( ext, 0x0012 );
			if (info)
			{
				printf("command %s\nargs %s\n", info -> command, info -> args);
				FreeTokenInfo(info);
			}

			info = GetCommandByToken( ext, 0x0024 );
			if (info)
			{
				printf("command %s\nargs %s\n", info -> command, info -> args);
				FreeTokenInfo(info);
			}

			name = GetExtensionName( ext );
			if (name)
			{
				printf("\nname: %s\n\n", name );
				FreeVec( name );
			}

			CloseExtension(ext);
		}
	}

	closedown( );

	return 0;
}

