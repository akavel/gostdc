package gostdc

import (
	"os"
	"time"
	"unsafe"
)

func peek(addr uintptr) *byte {
	return (*byte)(unsafe.Pointer(addr))
}

func go_creat(uintptr, uintptr, uintptr)          { panic("nyi") }
func go_open(uintptr, uintptr, uintptr)           { panic("nyi") }
func go_close(uintptr, uintptr)                   { panic("nyi") }
func go_lseek(uintptr, uintptr, uintptr, uintptr) { panic("nyi") }
func go_read(uintptr, uintptr, uintptr, uintptr)  { panic("nyi") }

func go_write(fd, buf_, n_, ret_ uintptr) {
	var f *os.File
	switch fd {
	case 0:
		f = os.Stdin
	case 1:
		f = os.Stdout
	case 2:
		f = os.Stderr
	default:
		panic("file descriptors not yet implemented")
	}

	n := int32(n_)
	if n < 0 || uintptr(n) != n_ {
		panic("too many bytes to write") //FIXME
	}

	buf := make([]byte, int(n))
	for i := 0; i < int(n); i++ {
		buf[i] = *peek(buf_ + uintptr(i))
	}

	written, err := f.Write(buf)
	if err != nil {
		//FIXME do something
	}
	*((*int32)(unsafe.Pointer(ret_))) = int32(written)
}

func go__exit(uintptr) { panic("nyi") }
func go_abort()        { panic("nyi") }

type alloc struct {
	p unsafe.Pointer
	s []byte
}

var allocs = make(map[uintptr]alloc)

func go_realloc(ptr uintptr, size uint32, pnewptr uintptr) {
	var newptr uintptr = 0
	switch {
	case ptr == 0 && size == 0:
		break
	case ptr == 0: // malloc
		//TODO: if (size > int32.MAX) return 0; and set errno?
		if int(size) < 0 {
			break
		}
		buf := alloc{s: make([]byte, int(size))}
		buf.p = unsafe.Pointer(&buf.s[0])
		allocs[uintptr(buf.p)] = buf
		newptr = uintptr(buf.p)
	case size == 0: // free
		delete(allocs, ptr)
		break
	default: // realloc
		tmp := allocs[ptr].s
		go_realloc(ptr, 0, uintptr(unsafe.Pointer(&newptr)))
		go_realloc(0, size, uintptr(unsafe.Pointer(&newptr)))
		copy(allocs[newptr].s, tmp)
	}
	*((*uintptr)(unsafe.Pointer(pnewptr))) = newptr
}

var clock0 = time.Now()

func go_clock(secs_ uintptr) {
	secs := time.Since(clock0) / time.Second
	*((*int32)(unsafe.Pointer(secs_))) = int32(secs)
}
