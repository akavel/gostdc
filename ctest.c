
#include "ctest.h"

void
·golua_ctestrun(ctestf f) {
    (*f)();
}

void
·golua_ctests(uintptr t) {
    ·go_ctest(t, TestStrlen);
    ·go_ctest(t, TestStrcmp);
    ·go_ctest(t, TestStrtod);
    ·go_ctest(t, TestSprintf);
}
