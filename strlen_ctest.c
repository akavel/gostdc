
#define gostdc_string_h
#include "ctest.h"

void
TestStrlen(void) {
    if (strlen("abc")!=3)
        runtime·panicstring("strlen failed");
    if (strlen("")!=0)
        runtime·panicstring("strlen failed");
    if (strlen("1\0")!=1)
        runtime·panicstring("strlen failed");
}

