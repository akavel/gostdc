/*
 * pANS stdio -- remove
 */
#include "iolib.h"
int remove(const char *f){
	runtime·panicstring("C function \'remove\' not yet implemented");
	USED(&f);
	return -1;
#ifdef __AKAVEL_FALSE
	return unlink((char *)f);
#endif
}
