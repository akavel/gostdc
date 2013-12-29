#ifndef __GOSTDC_STDARG_H
#define __GOSTDC_STDARG_H

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
	(((list).off=0), ((list).base = (uintptr)(void*)((&(arg0))+1)))
#define va_end(list) \
	USED((list).base)
#define va_arg(list,type) \
	((sizeof(type)==4) ? \
		(((list).off = ROUND((list).off, 4)+4), (type*)((list).base+(list).off))[-1] : \
	(sizeof(type)==8) ? \
		(((list).off = ROUND((list).off, sizeof(uintptr))+8), (type*)((list).base+(list).off))[-1] : \
		(runtime·panicstring("va_arg variant unsupported"), (type*)(list).base)[0])

#endif /* __GOSTDC_STDARG_H */
