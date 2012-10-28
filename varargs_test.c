
#define gostdc_string_h
#define gostdc_stdarg_h
#include "ctest.h"

static char buf0[256] = {0};
static char buf1[256] = {0};
static char buf2[256] = {0};
static char buf3[256] = {0};

#define PREPARE(type,x0,x1,x2,x3) \
    x0=*(type*)buf0; \
    x1=*(type*)buf1; \
    x2=*(type*)buf2; \
    x3=*(type*)buf3

#define HEXD(x) ((x)<10 ? '0'+(x) : 'a'-10+(x))
static void dbghdr(void* a0, int n) {
	char tmp[256]=0;
	char *p=(char*)a0;
	int i;
	for (i=0; i<n; i++) {
		tmp[2*i]=HEXD(p[i]>>4);
		tmp[2*i+1]=HEXD(p[i]&0x0f);
	}
	runtime·panicstring(tmp);
}

#pragma textflag 7
static void
testint(int a0, ...) {
    int v0, v1, v2, v3;
    PREPARE(int, v0, v1, v2, v3);
    va_list args;
    va_start(args, a0);
    int a1 = va_arg(args, int);
    int a2 = va_arg(args, int);
    int a3 = va_arg(args, int);
    va_end(args);
//dbghdr(&a0, 32);
    if (a0!=v0) runtime·panicstring("i0");
    if (a1!=v1) runtime·panicstring("i1");
    if (a2!=v2) runtime·panicstring("i2");
    if (a3!=v3) runtime·panicstring("i3");
}

#pragma textflag 7
static void
testdouble(double a0, ...) {
    double v0, v1, v2, v3;
    PREPARE(double, v0, v1, v2, v3);
    va_list args;
    va_start(args, a0);
    double a1 = va_arg(args, double);
    double a2 = va_arg(args, double);
    double a3 = va_arg(args, double);
    va_end(args);
//dbghdr(&a0, 32);
    if (a0!=v0) runtime·panicstring("d0");
    if (a1!=v1) runtime·panicstring("d1");
    if (a2!=v2) runtime·panicstring("d2");
    if (a3!=v3) runtime·panicstring("d3");
}

#pragma textflag 7
static void
testchar(char a0, ...) {
    char v0, v1, v2, v3;
    PREPARE(char, v0, v1, v2, v3);
    va_list args;
    va_start(args, a0);
    char a1 = va_arg(args, char);
    char a2 = va_arg(args, char);
    char a3 = va_arg(args, char);
    va_end(args);
//dbghdr(&a0, 16);
    if (a0!=v0) runtime·panicstring("c0");
    if (a1!=v1) runtime·panicstring("c1");
    if (a2!=v2) runtime·panicstring("c2");
    if (a3!=v3) runtime·panicstring("c3");
}

void
TestVarargs(void) {
    int i;
    for (i=0; i<sizeof(buf1)/sizeof(buf1[0]); i++) {
        buf1[i]=1;
        buf2[i]=2;
        buf3[i]=3;
    }
/*
char tmp[256]={0};
tmp[0]='0'+sizeof(char);
tmp[1]='0'+sizeof(int);
tmp[2]='0'+sizeof(double);
tmp[3]='0'+sizeof(char*);
tmp[4]='0'+sizeof(int*);
tmp[5]='0'+sizeof(double*);
runtime·panicstring(tmp);
*/
    int i0, i1, i2, i3;
    PREPARE(int, i0, i1, i2, i3);
    testint(i0, i1, i2, i3);

    double d0, d1, d2, d3;
    PREPARE(double, d0, d1, d2, d3);
    testdouble(d0, d1, d2, d3);

    char c0, c1, c2, c3;
    PREPARE(char, c0, c1, c2, c3);
    testchar(c0, c1, c2, c3);
}
