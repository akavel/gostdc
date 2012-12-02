
#define gostdc_stdlib_h
#define gostdc_math_h
#include "ctest.h"

void
TestStrtod(void) {
    char *s, *end;
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

    if (s="10e500", strtod(s, 0)!=HUGE_VAL)
        runtime·panicstring("strtod failed 9");
    if (s="-10e500", strtod(s, 0)!=-HUGE_VAL)
        runtime·panicstring("strtod failed 10");
}

