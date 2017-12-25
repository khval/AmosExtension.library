
struct _Library
{
	struct Library libNode;
	BPTR segList;

	/* If you need more data fields, add them here */

	struct ExecIFace	*IExec;

	struct Library		*DOSBase;
	struct DOSIFace	*IDOS;

	struct Library		*NewLibBase;
	struct Interface	*INewlib;

};

#define sread( dest, usize, n )		\
	{							\
		memcpy( (char *) (dest), _ext_ -> file + _file_offset_, usize *n );	\
		_file_offset_ += (usize * n);								\
	}

