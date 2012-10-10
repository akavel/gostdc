
#define gostdc_stdio_h
#define gostdc_time_h
#define gostdc_locale_h
#define gostdc_stdarg_h

#include "gostdc.h"


FILE* stderr;
FILE* stdin;
FILE* stdout;

void
·initlibs(void) {
    stdin = (FILE*)3;   // better not 0, because 0 means NULL means sometimes error
    stdout = (FILE*)1;
    stderr = (FILE*)2;
}

////////////////////

void runtime·panicstring(int8*);

static char* nyi_string = "0 not yet implemented";
void
nyi(char char_id) {
    nyi_string[0] = char_id;
    runtime·panicstring(nyi_string);
    //runtime·panicstring("not yet implemented");
}

void
exit(int code) {
    void ·go_exit(uintptr);
    ·go_exit(code);
}

void*
realloc(void* ptr, size_t size) {
    void ·go_realloc(uintptr, uintptr, uintptr);
    void* ret = 0;
    ·go_realloc((uintptr)ptr, (uintptr)size, (uintptr)&ret);
    return ret;
}

void
free(void* ptr) {
    void ·go_free(uintptr);
    ·go_free((uintptr)ptr);
}

double
pow(double x, double y) {
    void ·go_pow(uintptr, uintptr);
    ·go_pow((uintptr)&x, (uintptr)&y);
    return x;
}

double
fmod(double x, double y) {
    void ·go_fmod(uintptr, uintptr);
    ·go_fmod((uintptr)&x, (uintptr)&y);
    return x;
}

double
modf(double x, double *iptr) {
    void ·go_modf(uintptr, uintptr);
    ·go_modf((uintptr)&x, (uintptr)iptr);
    return x;
}

double
atan2(double y, double x) {
    void ·go_atan2(uintptr, uintptr);
    ·go_atan2((uintptr)&y, (uintptr)&x);
    return y;
}

//FIXME
#pragma textflag 7
int
sprintf(char* str, const char* format, ...) {
    void ·go_sprintf(uintptr, uintptr, uintptr, uintptr);
    va_list argp;
    va_start(argp, format);
    ·go_sprintf((uintptr)str, (uintptr)format, (uintptr)argp, (uintptr)_BIGWORD);
    va_end(argp);
    //nyi('6');
    return 0; //FIXME
}

//FIXME
#pragma textflag 7
int
fprintf(FILE* stream, const char* format, ...) {
    void ·go_fprintf(uintptr, uintptr, uintptr, uintptr);
    va_list argp;
    va_start(argp, format);
    ·go_fprintf((uintptr)stream, (uintptr)format, (uintptr)argp, (uintptr)_BIGWORD);
    va_end(argp);
    //nyi('7');
    return 0; //FIXME
}

//FIXME
int
fclose(FILE* stream) {
    nyi('8');
    return 0;
}

//FIXME
int
ferror(FILE* stream) {
    nyi('9');
    return 0;
}

//FIXME
FILE*
freopen(const char* filename, const char* mode, FILE* stream) {
    nyi('a');
    return stderr;
}

//FIXME
FILE*
fopen(const char* filename, const char* mode) {
    nyi('b');
    return stderr;
}

//FIXME
int
getc(FILE* stream) {
    nyi('c');
    return -1;
}

//FIXME
int
ungetc(int ch, FILE* stream) {
    nyi('d');
    return -1;
}

//FIXME
size_t
fread(void* ptr, size_t size, size_t count, FILE* stream) {
    nyi('e');
    return 0;
}

//FIXME
int
feof(FILE* stream) {
    nyi('f');
    return -1;
}

void ·goputc(uintptr, uintptr);

//FIXME
int
fputs(const char* s, FILE* stream) {
    while (*s) {
        ·goputc((uintptr)*s, (uintptr)stream);
        s++;
    }
    return 1; //FIXME
}

//FIXME
char*
strerror(int) {
    nyi('g');
    return "STRERROR";
}

//FIXME
double
strtod(const char* nptr, char** endptr) {
    void ·go_strtod(uintptr, uintptr, uintptr presult);
    double result=0;
    ·go_strtod((uintptr)nptr, (uintptr)endptr, (uintptr)&result);
    return result;
}

int errno;

//FIXME
int isxdigit(int c) {
    return (c>='0' && c<='9') ||
        (c>='a' && c<='f') ||
        (c>='A' && c<='F');
}

//FIXME
int isupper(int c) {
    return (c>='A' && c<='Z');
}

//FIXME
int islower(int c) {
    return (c>='a' && c<='z');
}

//FIXME
int isdigit(int c) {
    return (c>='0' && c<='9');
}

//FIXME
int isalpha(int c) {
    return isupper(c) || islower(c);
}

//FIXME
int isalnum(int c) {
    return isalpha(c) || isdigit(c);
}

//FIXME
int iscntrl(int c) {
    return (c>=0 && c<=0x1f) || c==0x7f;
}

//FIXME
int
isspace(int c) {
    return (c == ' ') ||
        (c == '\n') ||
        (c == '\r') ||
        (c == '\t');
}

//FIXME
int ispunct(int c) {
    return c=='!' ||
        c=='\"' ||
        c=='#' ||
        c=='$' ||
        c=='%' ||
        c=='&' ||
        c=='\'' ||
        c=='(' ||
        c==')' ||
        c=='*' ||
        c=='+' ||
        c==',' ||
        c=='-' ||
        c=='.' ||
        c=='/' ||
        c==':' ||
        c==';' ||
        c=='<' ||
        c=='=' ||
        c=='>' ||
        c=='?' ||
        c=='@' ||
        c=='[' ||
        c=='\\' ||
        c==']' ||
        c=='^' ||
        c=='_' ||
        c=='`' ||
        c=='{' ||
        c=='|' ||
        c=='}' ||
        c=='~';
}

int toupper(int c) {
    if (c>='a' && c<='z') {
        return c - 'a' + 'A';
    }
    return c;
}

int tolower(int c) {
    if (c>='A' && c<='Z') {
        return c - 'A' + 'a';
    }
    return c;
}

//FIXME
int abs(int x) {
    if (x<0)
        return -x;
    return x;
}

//FIXME
double
frexp(double num, int* exp) {
    *exp=0;
    return 0;
/*
    void ·go_frexp(uintptr, uintptr);
    ·go_frexp((uintptr)&num, (uintptr)exp); //FIXME: is int* safe here, with regards to its width?
    return num;
*/
}

//FIXME
double
ldexp(double x, int exp) {
    return 0;
/*
    void ·go_ldexp(uintptr, uintptr);
    ·go_ldexp((uintptr)&x, (uintptr)&exp); //FIXME: is int* safe here, with regards to its width?
    return x;
*/
}

int
rand(void) {
    void ·go_rand(uintptr);
    int32 ret = 0;
    ·go_rand((uintptr)&ret);
    return ret;
}

void
srand(unsigned seed) {
    void ·go_srand(uintptr);
    ·go_srand((uintptr)seed);
}

