#include "gostdc.h"

void
TestStrcmp(void) {
    if (!(strcmp("abc", "abz")<0))
        runtime·panicstring("strcmp failed");
    if (!(strcmp("ab", "aba")<0))
        runtime·panicstring("strcmp failed");
    if (!(strcmp("", "a")<0))
        runtime·panicstring("strcmp failed");
    if (!(strcmp("aa", "ab")<0))
        runtime·panicstring("strcmp failed");
    if (!(strcmp("aaa", "ab")<0))
        runtime·panicstring("strcmp failed");

    if (!(strcmp("", "")==0))
        runtime·panicstring("strcmp failed");
    if (!(strcmp("abc", "abc")==0))
        runtime·panicstring("strcmp failed");

    if (!(strcmp("abz", "abc")>0))
        runtime·panicstring("strcmp failed");
    if (!(strcmp("aba", "ab")>0))
        runtime·panicstring("strcmp failed");
    if (!(strcmp("a", "")>0))
        runtime·panicstring("strcmp failed");
    if (!(strcmp("ab", "aa")>0))
        runtime·panicstring("strcmp failed");
    if (!(strcmp("ab", "aaa")>0))
        runtime·panicstring("strcmp failed");
}

