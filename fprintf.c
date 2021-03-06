/*
 * pANS stdio -- fprintf
 */
#include "iolib.h"
#pragma textflag 7
int fprintf(FILE *f, const char *fmt, ...){
	int n;
	va_list args;
	va_start(args, fmt);
	n=vfprintf(f, fmt, args);
	va_end(args);
	return n;
}
