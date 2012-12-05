
#define gostdc_string_h
#include "ctest.h"

void
TestMemchr(void) {
	char *s;
	unsigned char c;

	if (s="abc", c='a', memchr(s, c, 4)!=s)
		runtime·panicstring("memchr failed 1");
	if (s="abc", c='b', memchr(s, c, 4)!=&s[1])
		runtime·panicstring("memchr failed 2");
	if (s="abc", c='x', memchr(s, c, 4)!=0)
		runtime·panicstring("memchr failed 3");
	if (s="abc", c=0, memchr(s, c, 4)!=&s[3])
		runtime·panicstring("memchr failed 4");

	if (s="abc", c='a', memchr(s, c, 0)!=0)
		runtime·panicstring("memchr failed 5");
	if (s="abc", c='a', memchr(s, c, 1)!=s)
		runtime·panicstring("memchr failed 6");
	if (s="abc", c='x', memchr(s, c, 0)!=0)
		runtime·panicstring("memchr failed 7");
}
