package gostdc

import (
	"fmt"
	"os"
	"runtime"
	"testing"
	"unsafe"
)

func c_ctestrun(f uintptr)

func go_ctest(t_, f_ uintptr) {
	if os.Getenv("GOTRACEBACK") != "2" {
		t := (*testing.T)(unsafe.Pointer(t_))
		defer func() {
			err := recover()
			if err == nil {
				return
			}
			where := "???"
			// skip panic() and panicstring()
			_, file, line, ok := runtime.Caller(3)
			if ok {
				where = fmt.Sprintf("%s:%d", file, line)
			}
			t.Fatalf("%s\nat %s", err, where)
		}()
	}
	c_ctestrun(f_)
}
