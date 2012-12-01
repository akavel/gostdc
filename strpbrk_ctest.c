
#define gostdc_string_h
#include "ctest.h"

void
TestStrpbrk(void) {
	char *s;

	if (s="abc", strpbrk(s, "a")!=s)
		runtime·panicstring("strpbrk failed 1");
	if (s="abc", strpbrk(s, "b")!=&s[1])
		runtime·panicstring("strpbrk failed 2");
	if (s="abc", strpbrk(s, "x")!=0)
		runtime·panicstring("strpbrk failed 3");

	if (s="abc", strpbrk(s, "xa")!=s)
		runtime·panicstring("strpbrk failed 4");
	if (s="abc", strpbrk(s, "xb")!=&s[1])
		runtime·panicstring("strpbrk failed 5");
	if (s="abc", strpbrk(s, "xca")!=s)
		runtime·panicstring("strpbrk failed 6");
	if (s="abc", strpbrk(s, "")!=0)
		runtime·panicstring("strpbrk failed 7");
	if (s="abc", strpbrk(s, "xy")!=0)
		runtime·panicstring("strpbrk failed 8");

	if (s="", strpbrk(s, "")!=0)
		runtime·panicstring("strpbrk failed b1");
	if (s="", strpbrk(s, "abc")!=0)
		runtime·panicstring("strpbrk failed b2");
}
