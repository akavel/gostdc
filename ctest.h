
#include "gostdc.h"

void runtime·panicstring(char *);

typedef void (*ctestf)(void);
void ·go_ctest(uintptr t, ctestf f);

void TestFrexp(void);
void TestLdexp(void);
void TestSprintf(void);
void TestStrcmp(void);
void TestStrlen(void);
void TestStrtod(void);
