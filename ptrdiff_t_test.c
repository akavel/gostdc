#include "gostdc.h"

void
TestPtrdiff_t(void) {
	void *tab[5];
	ptrdiff_t d;

	if (d=(tab-tab), d!=0)
		runtime·panicstring("ptrdiff_t failed 1");

	if (d=(&tab[4]-tab), d!=4)
		runtime·panicstring("ptrdiff_t failed 2");
	if (d<=0)
		runtime·panicstring("ptrdiff_t failed 3");

	if (d=(tab-&tab[4]), d!=-4)
		runtime·panicstring("ptrdiff_t failed 4");
	if (d>=0)
		runtime·panicstring("ptrdiff_t failed 5");
}
