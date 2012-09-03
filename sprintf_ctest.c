
#define gostdc_stdio_h
#define gostdc_string_h
#include "ctest.h"

void
TestSprintf(void) {
    char buf[256] = {0};

    if (sprintf(buf, "a%sa", "bbb"), strcmp(buf, "abbba")!=0)
        runtime·panicstring(buf);
    if (sprintf(buf, "a%%a"), strcmp(buf, "a%a")!=0)
        runtime·panicstring(buf);
    if (sprintf(buf, "a%sa%sa", "b", "c"), strcmp(buf, "abaca")!=0)
        runtime·panicstring(buf);

    if (sprintf(buf, "a%.14ga", 1.01l), strcmp(buf, "a1.01a")!=0)
        runtime·panicstring(buf);
}
