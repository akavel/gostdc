

/***************************/ 
/* goctypes.h */ 

#ifndef __goctypes_h
#define __goctypes_h

// Copyright 2009 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found at the end of this file.

/*
 * basic types
 */
typedef	signed char		int8;
typedef	unsigned char		uint8;
typedef	signed short		int16;
typedef	unsigned short		uint16;
typedef	signed int		int32;
typedef	unsigned int		uint32;
typedef	signed long long int	int64;
typedef	unsigned long long int	uint64;
typedef	float			float32;
typedef	double			float64;

#ifdef _64BIT
typedef	uint64		uintptr;
typedef	int64		intptr;
#else
typedef	uint32		uintptr;
typedef int32		intptr;
#endif

#define	USED(x)	if(x){}else{}
#define	FLUSH(x)	USED(x)

#define	ROUND(x, n)	(((x)+(n)-1)&~((n)-1)) /* all-caps to mark as macro: it evaluates n twice */

/*
 * get rid of C types
 * the / / / forces a syntax error immediately,
 * which will show "last name: XXunsigned".
 */
/*
#define	unsigned		XXunsigned / / /
#define	signed			XXsigned / / /
#define	char			XXchar / / /
#define	short			XXshort / / /
#define	int			XXint / / /
#define	long			XXlong / / /
#define	float			XXfloat / / /
#define	double			XXdouble / / /
*/

// Copyright (c) 2009 The Go Authors. All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
// 
//    * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//    * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//    * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#endif


/***************************/ 
/* assert.h */ 
#ifdef gostdc_assert_h 

#ifndef __ASSERT_H
#define __ASSERT_H

void runtime·panicstring(int8*);
#define assert(x) ((void)((x) || (runtime·panicstring("ASSERT FAIL in C code"), 1)))

#endif
#endif /* gostdc_assert_h */ 

/***************************/ 
/* ctype.h */ 
#ifdef gostdc_ctype_h 

#ifndef __CTYPE_H
#define __CTYPE_H

int isalnum(int);
int isalpha(int);
int iscntrl(int);
int isdigit(int);
int islower(int);
int ispunct(int);
int isspace(int);
int isupper(int);
int isxdigit(int);
int tolower(int);
int toupper(int);

#endif
#endif /* gostdc_ctype_h */ 

/***************************/ 
/* errno.h */ 
#ifdef gostdc_errno_h 

#ifndef __ERRNO_H
#define __ERRNO_H

extern int errno;

#endif
#endif /* gostdc_errno_h */ 

/***************************/ 
/* limits.h */ 
#ifdef gostdc_limits_h 

#ifndef __LIMITS_H
#define __LIMITS_H

//TODO: verify this
#define INT_MAX 2147483647
// (32b -- 0x7fffffff)

//TODO: verify this
#define SHRT_MAX 32767
// (16b -- 0x7fff)

#define UCHAR_MAX 255

#endif
#endif /* gostdc_limits_h */ 

/***************************/ 
/* locale.h */ 
#ifdef gostdc_locale_h 

#ifndef __LOCALE_H
#define __LOCALE_H

//TODO:
#define LC_ALL          0
#define LC_NUMERIC      1
#define LC_MONETARY     2
#define LC_COLLATE      3
#define LC_CTYPE        4
#define LC_TIME         5

struct lconv {
    char* decimal_point;
};

struct lconv* localeconv(void);
char* setlocale(int, const char*);

#endif
#endif /* gostdc_locale_h */ 

/***************************/ 
/* math.h */ 
#ifdef gostdc_math_h 

#ifndef __MATH_H
#define __MATH_H

//TODO: stolen from GCC (?), change to custom (non GPL) implementation
typedef union { unsigned char __c[8]; double __d; } __huge_val_t;
// # if __BYTE_ORDER == __BIG_ENDIAN
// #  define __HUGE_VAL_bytes      { 0x7f, 0xf0, 0, 0, 0, 0, 0, 0 }
// # endif
// # if __BYTE_ORDER == __LITTLE_ENDIAN
#define __HUGE_VAL_bytes      { 0, 0, 0, 0, 0, 0, 0xf0, 0x7f }
// # endif
static __huge_val_t __huge_val = { __HUGE_VAL_bytes };
#define HUGE_VAL       (__huge_val.__d)

double asin(double);
double acos(double);
double atan(double);
double atan2(double, double);
double ceil(double);
double cos(double);
double cosh(double);
double exp(double);
double fabs(double);
double floor(double);
double fmod(double, double);
double frexp(double, int*);
double ldexp(double, int);
double log(double);
double log10(double);
double modf(double, double*);
double pow(double, double);
double sqrt(double);
double sin(double);
double sinh(double);
double tan(double);
double tanh(double);

#endif
#endif /* gostdc_math_h */ 

/***************************/ 
/* setjmp.h */ 
#ifdef gostdc_setjmp_h 

#ifndef __SETJMP_H
#define __SETJMP_H

//TODO
typedef int jmp_buf;
void longjmp(jmp_buf, int);
int setjmp(jmp_buf);

#endif
#endif /* gostdc_setjmp_h */ 

/***************************/ 
/* stddef.h */ 

#ifndef __STDDEF_H
#define __STDDEF_H

#define NULL ((void*)0)

//typedef void* ptrdiff_t;
//typedef unsigned long long int ptrdiff_t;   // 64b expected
//typedef unsigned int ptrdiff_t; // 32b; will it be ok on 64b PCs?
typedef uintptr ptrdiff_t;

//typedef unsigned long long int size_t;      // 64b expected
//typedef unsigned int size_t; // 32b, to match size described in Lua header for chunks compiled by lua.exe
typedef uintptr size_t; // NOTE: on 64b machines/OSs, compiled chunks will be incompatible with 32b

#endif

/***************************/ 
/* stdarg.h */ 
#ifdef gostdc_stdarg_h 

#ifndef __STDARG_H
#define __STDARG_H

// FIXME: tested only on amd64
// FIXME: tested and supported only for usecases present in Lua source code
// varargs macros based on:
// - vprintf() in $GOROOT/src/pkg/runtime/print.c
// - http://plan9.bell-labs.com/sources/plan9/amd64/include/u.h
// see also:
// - https://bitbucket.org/floren/inferno/src/0513433e212b/Plan9/386/include/u.h?at=default
// - gargs() in $GOROOT/src/cmd/6c/txt.c
// - functions using '...' in $GOROOT/.../*.c
typedef struct {
	uintptr base;
	uintptr off;
} va_list;
#define va_start(list,arg0) \
	((list.off=0), (list.base = (uintptr)(void*)((&(arg0))+1)))
#define va_end(list) \
	USED(list.base)
#define va_arg(list,type) \
	((sizeof(type)==4) ? \
		((list.off = ROUND(list.off, 4)+4), (type*)(list.base+list.off))[-1] : \
	(sizeof(type)==8) ? \
		((list.off = ROUND(list.off, sizeof(uintptr))+8), (type*)(list.base+list.off))[-1] : \
		(runtime·panicstring("va_arg variant unsupported"), (type*)list.base)[0])

#endif
#endif /* gostdc_stdarg_h */ 

/***************************/ 
/* stdio.h */ 
#ifdef gostdc_stdio_h 

#ifndef __STDIO_H
#define __STDIO_H

#define BUFSIZ 1024
#define EOF ((int)-1)
//TODO
#define L_tmpnam 10

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

#define _IOFBF 0
#define _IOLBF 1
#define _IONBF 2

//TODO
typedef int FILE;

extern FILE* stderr;
extern FILE* stdin;
extern FILE* stdout;

void clearerr(FILE*);
int fclose(FILE*);
int feof(FILE*);
int ferror(FILE*);
int fflush(FILE*);
char* fgets(char* s, int n, FILE*);
FILE* fopen(const char*, const char*);
int fprintf(FILE*, const char*, ...);
int fputs(const char*, FILE*);
size_t fread(void*, size_t, size_t, FILE*);
FILE* freopen(const char*, const char*, FILE*);
int fscanf(FILE*, const char*, ...);
int fseek(FILE*, long, int);
long ftell(FILE*);
size_t fwrite(void*, size_t, size_t, FILE*);
int getc(FILE*);
char* getenv(const char*);
int remove(const char*);
int rename(const char*, const char*);
int setvbuf(FILE*, char*, int, size_t);
int sprintf(char*, const char*, ...);
FILE* tmpfile(void);
char* tmpnam(char[L_tmpnam]);
int ungetc(int, FILE*);

#endif
#endif /* gostdc_stdio_h */ 

/***************************/ 
/* stdlib.h */ 
#ifdef gostdc_stdlib_h 

#ifndef __STDLIB_H
#define __STDLIB_H

#define EXIT_FAILURE 255
#define EXIT_SUCCESS 0
#define RAND_MAX INT_MAX

int abs(int);
void exit(int);
void free(void*);
int rand(void);
void* realloc(void*, size_t);
void srand(unsigned int);
double strtod(const char*, char**);
unsigned long strtoul(const char*, char**, int);
int system(const char*);

#endif
#endif /* gostdc_stdlib_h */ 

/***************************/ 
/* string.h */ 
#ifdef gostdc_string_h 

#ifndef __STRING_H
#define __STRING_H

void* memchr(const void*, int, size_t);
int memcmp(const void*, const void*, size_t);
void* memcpy(void*, const void*, size_t);

char* strchr(const char*, int);
char* strcat(char*, const char*);
int strcmp(const char*, const char*);
int strcoll(const char*, const char*);
char* strcpy(char*, const char*);
size_t strcspn(const char*, const char*);
char* strerror(int);
size_t strlen(const char*);
char* strncat(char*, const char*, size_t);
char* strncpy(char*, const char*, size_t);
char* strpbrk(const char*, const char*);
char* strrchr(const char*, int);
char* strstr(const char*, const char*);

#endif
#endif /* gostdc_string_h */ 

/***************************/ 
/* time.h */ 
#ifdef gostdc_time_h 

#ifndef __TIME_H
#define __TIME_H

//TODO:
#define CLOCKS_PER_SEC 1000

//TODO:
typedef unsigned long long int clock_t;
typedef unsigned long long int time_t;

struct tm {
    int tm_sec;
    int tm_min;
    int tm_hour;
    int tm_mday;
    int tm_mon;
    int tm_year;
    int tm_wday;
    int tm_yday;
    int tm_isdst;
};

clock_t clock(void);
double difftime(time_t, time_t);
struct tm* gmtime(const time_t*);
struct tm* localtime(const time_t*);
time_t mktime(struct tm*);
size_t strftime(char*, size_t, const char*, const struct tm*);
time_t time(time_t*);

#endif
#endif /* gostdc_time_h */ 
