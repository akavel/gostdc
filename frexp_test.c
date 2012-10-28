
#define gostdc_stdio_h
#define gostdc_math_h
#include "ctest.h"

void
TestFrexp(void) {
	char buf[256] = {0};
	double d = 0.0l;
	int exp = 0;

	if (d=frexp(15.2l, &exp), ((d!=0.95l) || (exp!=4)))
		sprintf(buf, "[%.14g] [%d]", d, exp), runtime·panicstring(buf);
	sprintf(buf, "[%.14g] [%d]", d, exp), runtime·panicstring(buf);
}
