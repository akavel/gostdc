#include "gostdc.h"

#define CHARP(p) ((char*)(p))

void
TestRealloc(void) {
	void *p=0;

	// see: http://pubs.opengroup.org/onlinepubs/7999959899/functions/realloc.html

	free(0); // defined: no action shall occur.
	free(0);
	free(0);
	if (p=realloc(0, 0), p!=0) // NOTE: result need not be 0, but 0 would be good practice.
		runtime·panicstring("realloc failed 1");

	if (p=realloc(0, 10), p==0)
		runtime·panicstring("realloc failed 2");
	CHARP(p)[9] = 9; // trying to check here that no segfault occurs
	CHARP(p)[8] = 8;

	if (p=realloc(p, 9), CHARP(p)[8]!=8)
		runtime·panicstring("realloc failed 3");

	if (p=realloc(p, 10), p==0)
		runtime·panicstring("realloc failed 4");
	if (CHARP(p)[8]!=8)
		runtime·panicstring("realloc failed 5");

	if (p=realloc(p, 0), p!=0) // NOTE: result need not be 0, but 0 would be good practice.
		runtime·panicstring("realloc failed 6");
}
