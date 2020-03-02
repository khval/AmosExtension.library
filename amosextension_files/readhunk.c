#include <proto/exec.h>
#include <proto/dos.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../libBase.h"

char *read_string(struct AmosExtensionIFace *libBase, BPTR *file)
{
	int numLongs;
	char *txt;

	libBase -> IDOS -> FRead( file, &numLongs, sizeof(int),1 );

	if (numLongs<1) return NULL;

	txt = (char *) malloc( (numLongs*4) + 1 );
	if (txt)
	{
		libBase -> IDOS -> FRead( file, txt, (numLongs*4), 1 );
		return txt;
	}

	return NULL;
}


void readHeader(struct AmosExtensionIFace *libBase, BPTR *file)
{
	char *txt;
	int tableSize;
	int firstHunkSlot;
	int lastHunkSlot;
	int n;
	int i32;
	int numberOfHunks;

	// read strings
	do
	{
		txt = read_string( libBase, file );
		if (txt)
		{
			free(txt);
		}
	} while (txt != NULL);

	libBase -> IDOS -> FRead( file, &tableSize, sizeof(int),1 );
	libBase -> IDOS -> FRead( file, &firstHunkSlot, sizeof(int),1 );
	libBase -> IDOS -> FRead( file, &lastHunkSlot, sizeof(int),1 );

	numberOfHunks =lastHunkSlot - firstHunkSlot + 1;
	
	for (n=0;n<numberOfHunks;n++)
	{
		libBase -> IDOS -> FRead( file, &i32, sizeof(int),1 );
	}
}

char *readCodeBlock(struct AmosExtensionIFace *libBase, BPTR *file)
{
	unsigned int size;
	char *code = NULL;

	fread(&size,sizeof(int),1,fd);

	code = (char *) malloc(size * 4) ;
	if (code)
	{
		fread(code,size*4,1,fd);
		free(code);
	}

	return code;
}

void readReloc32(struct AmosExtensionIFace *libBase, BPTR *file)
{
	unsigned int num_offsets;
	unsigned int hunk_number;
	unsigned int skip;
	int n;

	while (TRUE)
	{
		fread(&num_offsets,sizeof(int),1,fd);
		if (num_offsets == 0) break;
		fread(&hunk_number,sizeof(int),1,fd);

		for (n=0; n<num_offsets;n++)	fread(&skip,sizeof(int),1,fd);
	}

}

#define HUNK_HEADER	0x3F3
#define HUNK_RELOC32 0x3EC
#define HUNK_CODE	0x3E9
#define HUNK_END		0x3F2

void freehunk(struct ExecIFace *IExec, char **code_table)
{
	IExec->FreeVec(code_table);
}

char **readhunk(struct AmosExtensionIFace *libBase, const char *name)
{
	BPTR file;
	unsigned int hunkid;
	int tabSize = 0;
	int code_table_count = 0;
	char *code_table[100];
	char **ret_code_table = NULL;

	BOOL _error = FALSE;
	BOOL _exit = FALSE;

	file = libBase -> IDOS -> FOpen( name , MODE_OLDFILE, 0 );
	if (fd)
	{
		while( !feof(fd) && !_error && !_exit )
		{
			libBase -> IDOS -> FRead( file, &hunkid, sizeof(int),1 );
			switch (hunkid)
			{
				case HUNK_HEADER:
					readHeader( file );
					break;

				case HUNK_CODE:
					code_table[ code_table_count++ ] = readCodeBlock(fd);
					code_table[ code_table_count ] = 0;	// null terminate table...
					break;

				case HUNK_RELOC32:
					readReloc32(fd);
					break;

				case HUNK_END:
					break;

				default:
					_error = TRUE;
					break;
			}
		}

		libBase -> IDOS -> FClose( file );
	}

	if (code_table_count)
	{
		tabSize = (code_table_count + 1) * sizeof(char *);
		ret_code_table = IExec -> AllocVecTags( tabSize , AVT_Type, MEMF_SHARED, AVT_ClearWithValue, 0 , TAG_END );
		memcpy( ret_code_table, code_table, tabSize );
	}

	return ret_code_table;
}

