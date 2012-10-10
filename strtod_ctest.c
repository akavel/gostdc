
#define gostdc_stdlib_h
#include "ctest.h"

void
TestStrtod(void) {
    char *s;
    if (s="123", strtod(s, 0)!=123)
        runtime·panicstring("strtod failed 1");
    if (s="123.45", strtod(s, 0)!=123.45)
        runtime·panicstring("strtod failed 2");
}

