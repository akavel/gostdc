/*
 * pANS stdio -- tmpnam
 */
#include "iolib.h"
#include <string.h>

char *
tmpnam(char *s)
{
	runtime·panicstring("C function \'tmpnam\' not yet implemented");
	USED(&s);
	return 0;
#ifdef __AKAVEL_FALSE
	static char name[] = "/tmp/tn000000000000";
	char *p;

	do {
		p = name + 7;
		while (*p == '9')
			*p++ = '0';
		if (*p == '\0')
			return NULL;
		++*p;
	} while (access(name, 0) == 0);
	if (s) {
		strcpy(s, name);
		return s;
	}
	return name;
#endif
}


char *
tmpnam_r(char *s)
{
	return s ? tmpnam(s) : NULL;
}
