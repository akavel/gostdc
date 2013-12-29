#include "gostdc.h"

int errno;

void
free(void *ptr) {
	realloc(ptr, 0);
}

void *
malloc(size_t size) {
	return realloc(0, size);
}


/*
 * Below this point only stubs/bridges between C and Go should be found.
 */

int
creat(const char *path, uint16 mode) {
	void ·go_creat(uintptr, uintptr, uintptr);
	int32 ret;
	·go_creat((uintptr)path, (uintptr)mode, (uintptr)&ret);
	return ret;
}

int
open(const char *path, int oflag) {
	void ·go_open(uintptr, uintptr, uintptr);
	int32 ret;
	·go_open((uintptr)path, (uintptr)oflag, (uintptr)&ret);
	return ret;
}

int
close(int filedes) {
	void ·go_close(uintptr, uintptr);
	int32 ret;
	·go_close((uintptr)filedes, (uintptr)&ret);
	return ret;
}

int64
lseek(int filedes, int64 offset, int whence) {
	void ·go_lseek(uintptr, uintptr, uintptr, uintptr);
	int64 ret;
	·go_lseek((uintptr)filedes, (uintptr)&offset, (uintptr)whence, (uintptr)&ret);
	return ret;
}

ssize_t
read(int filedes, void *buf, size_t nbyte) {
	void ·go_read(uintptr, uintptr, uintptr, uintptr);
	int32 ret;
	·go_read((uintptr)filedes, (uintptr)buf, (uintptr)nbyte, (uintptr)&ret);
	return ret;
}

ssize_t
write(int filedes, const void *buf, size_t nbyte) {
	void ·go_write(uintptr, uintptr, uintptr, uintptr);
	int32 ret;
	·go_write((uintptr)filedes, (uintptr)buf, (uintptr)nbyte, (uintptr)&ret);
	return ret;
}

void
_exit(int code) {
	void ·go__exit(uintptr);
	·go__exit((uintptr)code);
}

void
abort(void) {
	void ·go_abort(void);
	·go_abort();
}

void*
realloc(void* ptr, size_t size) {
	void ·go_realloc(uintptr, uintptr, uintptr);
	uintptr ret = 0;
	·go_realloc((uintptr)ptr, (uintptr)size, (uintptr)&ret);
	return (void*)ret;
}

clock_t
clock(void)
{
	void ·go_clock(uintptr);
	int32 secs;
	·go_clock((uintptr)&secs);
	return ((long)secs)*((long)CLOCKS_PER_SEC);
}
