
#include "gostdc.h"

void runtime·panicstring(char *);

typedef void (*ctestf)(void);
void ·go_ctest(uintptr t, ctestf f);

void TestSprintf(void);
void TestStrcmp(void);
void TestStrlen(void);
