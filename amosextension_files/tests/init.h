
extern struct Library 			*AmosExtensionBase ;
extern struct AmosExtensionIFace	*IAmosExtension ;
extern BOOL open_lib( const char *name, int ver , const char *iname, int iver, struct Library **base, struct Interface **interface);
extern BOOL init();
extern void closedown();

