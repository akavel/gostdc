package gostdc

import (
	"fmt"
	"regexp"
	"unsafe"
)

func cstr2bytes(cstr uintptr) []byte {
	buf := make([]byte, 0)
	i := uintptr(0)
	for {
		addr := peek(cstr + i)
		if *addr == 0 {
			break
		}
		buf = append(buf, *addr)
		i++
	}
	return buf
}

var printf_matcher = regexp.MustCompile(`%.`)
var printf_gmatcher = regexp.MustCompile(`%\.14g`) // HACK: standard Lua float format

func vround(x, n uintptr) uintptr {
	return (x + n - 1) &^ (n - 1)
}

//FIXME
func go_vprintf(format, argsbase, argsoff, bigword uintptr) []byte {
	format1 := cstr2bytes(format)
	//HACK:
	format1 = printf_gmatcher.ReplaceAllFunc(format1, func(pat []byte) []byte {
		argsoff = vround(argsoff, 8) + 8
		return []byte(fmt.Sprintf("%.14g", *(*float64)(unsafe.Pointer(argsbase + argsoff - 8))))
	})
	format1 = printf_matcher.ReplaceAllFunc(format1, func(pat []byte) []byte {
		switch pat[1] {
		case 's':
			argsoff = vround(argsoff, bigword) + bigword
			arg := cstr2bytes(*(*uintptr)(unsafe.Pointer(argsbase + argsoff - bigword)))
			return arg
		case 'd':
			argsoff = vround(argsoff, 4) + 4 // FIXME: ok or not?
			arg := *((*int)(unsafe.Pointer(argsbase + argsoff - 4)))
			return []byte(fmt.Sprintf("%d", arg))
		case '%':
			return pat[1:]
		default:
			panic("not implemented printf format %" + string(pat[1]) + " in \"" + string(format1) + "\"")
		}
		return pat
	})
	return format1
}

//FIXME
func go_fprintf(stream, format, argsbase, argsoff, bigword uintptr) {
	format1 := go_vprintf(format, argsbase, argsoff, bigword)
	print(string(format1))
}

//FIXME
func go_sprintf(str, format, argsbase, argsoff, bigword uintptr) {
	format1 := go_vprintf(format, argsbase, argsoff, bigword)
	pokestringplus0(str, format1)
}
