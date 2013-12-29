package gostdc

import (
	"testing"
	"unsafe"
)

func c_ctests(t uintptr)

func TestC(t *testing.T) {
	c_ctests(uintptr(unsafe.Pointer(t)))
}
