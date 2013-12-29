#include "gostdc.h"

void
TestLdexp(void) {
	char buf[256] = {0};
	double d = 0.0l;

	if (d=ldexp(0.95l, 4), d!=15.2l)
		sprintf(buf, "[%.14g]", d), runtime·panicstring(buf);
}
