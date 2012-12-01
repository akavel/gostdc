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

var printf_matcher = regexp.MustCompile(
	`%(` + // percent sign
		`[-+ #0]{0,5}` + // optional flags
		`\d{0,2}` + // optional width
		`(\.\d{0,2})?` + // optional precision
		`l?` + // optional long
		`[cdiouxXeEfgGsp]` + // format specifier
		`|%)`) // or two percents

func vround(x, n uintptr) uintptr {
	return (x + n - 1) &^ (n - 1)
}

//FIXME
func go_vprintf(format_, argsbase, argsoff, bigword uintptr) []byte {
	format := cstr2bytes(format_)
	format = printf_matcher.ReplaceAllFunc(format, func(pat []byte) []byte {
		if pat[len(pat)-2] == 'l' {
			// FIXME: HACK
			pat = append(pat[:len(pat)-2], pat[len(pat)-1])
		}
		switch pat[len(pat)-1] {
		case 'e', 'E', 'f', 'g', 'G':
			argsoff = vround(argsoff, 8) + 8
			return []byte(fmt.Sprintf(string(pat), *(*float64)(unsafe.Pointer(argsbase + argsoff - 8))))
		case 's':
			argsoff = vround(argsoff, bigword) + bigword
			arg := cstr2bytes(*(*uintptr)(unsafe.Pointer(argsbase + argsoff - bigword)))
			return arg
		case 'p':
			argsoff = vround(argsoff, bigword) + bigword
			arg := (uintptr)(unsafe.Pointer(argsbase + argsoff - bigword))
			return []byte(fmt.Sprintf("%x", arg))
		case 'd', 'i':
			pat[len(pat)-1] = 'd'
			argsoff = vround(argsoff, 4) + 4 // FIXME: ok or not?
			arg := *((*int)(unsafe.Pointer(argsbase + argsoff - 4)))
			return []byte(fmt.Sprintf(string(pat), arg))
		case 'u', 'o', 'x', 'X':
			if pat[len(pat)-1] == 'u' {
				pat[len(pat)-1] = 'd'
			}
			argsoff = vround(argsoff, 4) + 4 // FIXME: ok or not?
			arg := *((*uint)(unsafe.Pointer(argsbase + argsoff - 4)))
			return []byte(fmt.Sprintf(string(pat), arg))
		case 'c':
			argsoff = vround(argsoff, 1) + 1 // FIXME: ok or not?
			arg := *((*byte)(unsafe.Pointer(argsbase + argsoff - 1)))
			return []byte{arg}
		case '%':
			return pat[1:]
		default:
			panic("not implemented printf format " + string(pat) + " in \"" + string(format) + "\"")
		}
		return pat
	})
	return format
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
