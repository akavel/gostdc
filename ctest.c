
#include "ctest.h"

void
·golua_ctestrun(ctestf f) {
    (*f)();
}

void
·golua_ctests(uintptr t) {
    // order is important in the first block
    ·go_ctest(t, TestStrlen);
    ·go_ctest(t, TestStrcmp);
    ·go_ctest(t, TestVarargs);
    ·go_ctest(t, TestSprintf);

    ·go_ctest(t, TestStrtod);
    ·go_ctest(t, TestStrtoul);
    ·go_ctest(t, TestLdexp);
    ·go_ctest(t, TestFrexp);
}
