
#define LIBRARIES_AMOSEXTENSION_H

struct command
{
	void *func;
	unsigned int size;
};

struct fileHeader
{
	unsigned int	C_off_size;
	unsigned int	C_tk_size;
	unsigned int	C_lib_size;
	unsigned int	C_title_size;
	unsigned short end;
} __attribute__((packed)) ;

struct extension
{
	char *file;
	struct fileHeader *header;
	unsigned short *sizeTable;
	struct command *commands;
};

struct TokenInfo
{
	unsigned short token;
	short NumberOfInstruction;
	short NumberOfFunction;
	char *command;
	char *args;
};

struct ExtensionDescriptor
{
	unsigned int blockStart;
	unsigned int fileOffset;
	struct extension	*ext;
	struct TokenInfo	tokenInfo;
};

