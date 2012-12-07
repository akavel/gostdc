
#include "ctest.h"

typedef void (*ctestf)(void);
void ·go_ctest(uintptr t, ctestf f);

void
·golua_ctestrun(ctestf f) {
	(*f)();
}

#define RUN_CTEST(t,func)\
	void func(void);\
	·go_ctest(t, func)

void
·golua_ctests(uintptr t) {
	// order is important in the first block
	RUN_CTEST(t, TestStrlen);
	RUN_CTEST(t, TestStrcmp);
	RUN_CTEST(t, TestVarargs);
	RUN_CTEST(t, TestSprintf);

	RUN_CTEST(t, TestMemchr);
	RUN_CTEST(t, TestStrpbrk);
	RUN_CTEST(t, TestStrtod);
	RUN_CTEST(t, TestStrtoul);
	RUN_CTEST(t, TestLdexp);
	RUN_CTEST(t, TestFrexp);
	RUN_CTEST(t, TestPtrdiff_t);
}
