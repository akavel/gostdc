#include "gostdc.h"

void runtime·prints(int8 *s);
#define HEXD(x) ((x)<10 ? '0'+(x) : 'a'-10+(x))
static void
hexdump(void* a0, int n) {
	char tmp[256];
	char *p = (char*)a0;
	int i;
	for (i=0; i<n; i++) {
		tmp[2*i]=HEXD(p[i]>>4);
		tmp[2*i+1]=HEXD(p[i]&0x0f);
	}
	tmp[n] = '\0';
	runtime·prints(tmp);
	runtime·prints("\n");
}


char bufx[16];
char buferr[] = "0th argument not correct";

#pragma textflag 7
void
testvarargs(const char *fmt, ...) {
	int i;
	for (i=0; i<sizeof(bufx)/sizeof(bufx[0]); i++) {
		bufx[i] = 0;
	}

	char *xC;
	double xd;
	int xi;
	void *xV;
		
	va_list args;
	va_start(args, fmt);
	for (i=0; fmt[i]; i++) {
		int ok = 0;
		bufx[0] = i+1;

		switch (fmt[i]) {
		case 'C':
			xC = va_arg(args, char*);
			ok = (xC == *((char**)(void*)bufx));
			break;
		case 'd':
			xd = va_arg(args, double);
			ok = (xd == *((double*)(void*)bufx));
			break;
		case 'i':
			xi = va_arg(args, int);
			ok = (xi == *((int*)(void*)bufx));
			break;
		case 'V':
			xV = va_arg(args, void*);
			ok = (xV == *((void**)(void*)bufx));
			break;
		default:
			runtime·panicstring("unknown format in testvarargs");
		}
		if (ok) {
			continue;
		}
		hexdump(&fmt, 32);
		buferr[0] = '0' + i;
		runtime·panicstring(buferr);
	}
	va_end(args);
}

static char samples[4][256];
static char buf0[256] = {0};
static char buf1[256] = {0};
static char buf2[256] = {0};
static char buf3[256] = {0};

#define PREPARE(type,x0,x1,x2,x3) \
    x0=*(type*)samples[0]; \
    x1=*(type*)samples[1]; \
    x2=*(type*)samples[2]; \
    x3=*(type*)samples[3]

void
TestVarargs(void) {
	int i, j;
	for (i=0; i<sizeof(samples)/sizeof(samples[0]); i++) {
		samples[i][0] = i+1;
		for (j=1; j<sizeof(samples[0])/sizeof(samples[0][0]); j++) {
			samples[i][j] = 0;
		}
	}

	int i0, i1, i2, i3;
	PREPARE(int, i0, i1, i2, i3);

	double d0, d1, d2, d3;
	PREPARE(double, d0, d1, d2, d3);

	char *c0, *c1, *c2, *c3;
	PREPARE(char*, c0, c1, c2, c3);

	void *v0, *v1, *v2, *v3;
	PREPARE(void*, v0, v1, v2, v3);

	testvarargs("CdiV", c0, d1, i2, v3);
}
