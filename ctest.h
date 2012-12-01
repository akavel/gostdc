
#include "gostdc.h"

void runtime·panicstring(char *);

typedef void (*ctestf)(void);
void ·go_ctest(uintptr t, ctestf f);

void TestFrexp(void);
void TestLdexp(void);
void TestPtrdiff_t(void);
void TestSprintf(void);
void TestStrcmp(void);
void TestStrlen(void);
void TestStrtod(void);
void TestStrtoul(void);
void TestVarargs(void);
