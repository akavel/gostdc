
#define gostdc_string_h
#define gostdc_ctype_h
#define gostdc_stdlib_h
#include "ctest.h"

void
·golua_ctestrun(ctestf f) {
    (*f)();
}

void
·golua_ctests(uintptr t) {
    ·go_ctest(t, TestFrexp);
    ·go_ctest(t, TestLdexp);
    ·go_ctest(t, TestStrlen);
    ·go_ctest(t, TestStrcmp);
    ·go_ctest(t, TestStrtod);
    ·go_ctest(t, TestSprintf);
}

#define USEF(f) {void*v=(void*)f; if(v){}else{}}

void
usef(void) {
/* string.h */
    USEF(memchr);
    USEF(memcmp);
    USEF(memcpy);
    USEF(strchr);
    USEF(strcat);
    USEF(strcmp);
    USEF(strcoll);
    USEF(strcpy);
    USEF(strcspn);
    USEF(strerror);
    USEF(strlen);
    USEF(strncat);
    USEF(strncpy);
    USEF(strpbrk);
    USEF(strrchr);
    USEF(strstr);

/* ctype.h */ 
    USEF(isalnum);
    USEF(isalpha);
    USEF(iscntrl);
    USEF(isdigit);
    USEF(islower);
    USEF(ispunct);
    USEF(isspace);
    USEF(isupper);
    USEF(isxdigit);
    USEF(tolower);
    USEF(toupper);

/* stdlib.h */
    USEF(abs);
    //USEF(exit);
    //USEF(free);
    //USEF(rand);
    //USEF(realloc);
    //USEF(srand);
    USEF(strtod);
    USEF(strtoul);
    //USEF(system);
}
