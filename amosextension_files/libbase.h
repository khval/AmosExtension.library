
struct _Library
{
	struct Library libNode;
	BPTR segList;

	/* If you need more data fields, add them here */

	struct ExecIFace	*IExec;

	struct Library		*DOSBase;
	struct DOSIFace	*IDOS;
};

