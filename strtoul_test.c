#include "gostdc.h"

void
TestStrtoul(void) {
	char *s, *end;
	if (s="123", strtoul(s, 0, 0)!=123ul)
		runtime·panicstring("strtoul failed 1");
	if (s="-1", strtoul(s, 0, 0)!=(unsigned long)(-1))
		runtime·panicstring("strtoul failed 2");
	if (s="0xff", strtoul(s, 0, 0)!=255ul)
		runtime·panicstring("strtoul failed 3");

	if (s="9999999999999999999999999999999999999", strtoul(s, 0, 0)!=ULONG_MAX)
		runtime·panicstring("strtoul failed 4");
	if (errno!=ERANGE)
		runtime·panicstring("strtoul failed 5");

	if (s="  asdf", strtoul(s, &end, 0)!=0)
		runtime·panicstring("strtoul failed 6");
	if (end!=s)
		runtime·panicstring("strtoul failed 7");

	if (s="  123asdf", strtoul(s, &end, 0)!=123)
		runtime·panicstring("strtoul failed 8");
	if (end!=&s[5])
		runtime·panicstring("strtoul failed 9");

/*
    if (s="123", strtod(s, 0)!=123)
        runtime·panicstring("strtod failed 1");
    if (s="123.45", strtod(s, 0)!=123.45)
        runtime·panicstring("strtod failed 2");

    if (s="", strtod(s, &end)!=0)
        runtime·panicstring("strtod failed 3");
    if (end!=s)
        runtime·panicstring("strtod failed 4");

    if (s="  asdf", strtod(s, &end)!=0)
        runtime·panicstring("strtod failed 5");
    if (end!=s)
        runtime·panicstring("strtod failed 6");

    if (s="   ", strtod(s, &end)!=0)
        runtime·panicstring("strtod failed 7");
    if (end!=s)
        runtime·panicstring("strtod failed 8");
*/
}

