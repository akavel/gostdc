package gostdc

import (
	"fmt"
	"math"
	"math/rand"
	"os"
	"runtime"
	"strconv"
	"testing"
	"time"
	"unsafe"
)

func peek(addr uintptr) *byte {
	return (*byte)(unsafe.Pointer(addr))
}

type alloc struct {
	p unsafe.Pointer
	s []byte
}

var allocs = make(map[uintptr]alloc)

func go_exit(code int) {
	os.Exit(code)
}

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

func go_free(ptr uintptr) {
	go_realloc(ptr, 0, uintptr(unsafe.Pointer(&ptr)))
}

func go_pow(x, y uintptr) {
	px := (*float64)(unsafe.Pointer(x))
	py := (*float64)(unsafe.Pointer(y))
	*px = math.Pow(*px, *py)
}

func go_fmod(x, y uintptr) {
	px := (*float64)(unsafe.Pointer(x))
	py := (*float64)(unsafe.Pointer(y))
	*px = math.Mod(*px, *py)
}

func go_modf(f, iptr uintptr) {
	pf := (*float64)(unsafe.Pointer(f))
	pint := (*float64)(unsafe.Pointer(iptr))
	*pint, *pf = math.Modf(*pf)
}

func go_atan2(y, x uintptr) {
	px := (*float64)(unsafe.Pointer(x))
	py := (*float64)(unsafe.Pointer(y))
	*py = math.Atan2(*py, *px)
}

func go_frexp(numptr, expptr uintptr) {
	pnum := (*float64)(unsafe.Pointer(numptr))
	pexp := (*int)(unsafe.Pointer(expptr)) //FIXME: is int OK here?
	*pnum, *pexp = math.Frexp(*pnum)
}

func go_ldexp(xptr uintptr, exp int) {
	px := (*float64)(unsafe.Pointer(xptr))
	*px = math.Ldexp(*px, exp)
}

func go_rand(retptr uintptr) {
	pret := (*int32)(unsafe.Pointer(retptr))
	*pret = rand.Int31()
}

func go_srand(seed uintptr) {
	rand.Seed(int64(seed))
}

func go_time(t uintptr) {
	pt := (*int64)(unsafe.Pointer(t))
	*pt = time.Now().Unix()
}

func golua_call(L, f, uv uintptr)

func poke(addr uintptr, value byte) {
	*(*byte)(unsafe.Pointer(addr)) = value
}

func pokestringplus0(dst uintptr, src []byte) {
	for i := 0; i < len(src); i++ {
		poke(dst+uintptr(i), src[i])
	}
	poke(dst+uintptr(len(src)), 0)
}

func golua_ctestrun(f uintptr)

func go_ctest(t_, f_ uintptr) {
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
	golua_ctestrun(f_)
}

type stod_state int

const (
	stod_mantissa stod_state = iota
	stod_afterdecimal
	stod_aftere
	stod_afteresign
)

func go_strtod(str, endptr_, hugeval_, mhugeval_, presult_ uintptr) {
	str0 := str
	for *peek(str) == ' ' { //FIXME: isWhitespace(...)
		str++
	}
	buf := make([]byte, 0)
	b := *peek(str)
	if b == '+' || b == '-' {
		buf = append(buf, b)
		str++
		b = *peek(str)
	}
	/*
	   point := false
	   e := false
	   esign := false
	*/
	state := stod_mantissa
	for {
		if '0' <= b && b <= '9' {
			if state == stod_aftere {
				state = stod_afteresign
			}
		} else if state == stod_mantissa && b == '.' {
			state = stod_afterdecimal
		} else if state <= stod_afterdecimal && (b == 'e' || b == 'E') {
			state = stod_aftere
		} else if state == stod_aftere && (b == '+' || b == '-') {
			state = stod_afteresign
		} else {
			break
		}
		/*
		   if '0'<=b && b<='9' {
		       if e && !esign {
		           esign=true
		       }
		   } else if !point && b=='.' {
		       point=true
		   } else if !e && (b=='e' || b=='E') {
		       e = true
		       point = true // decimal point not accepted in exponential part
		   } else if e && !esign && (b=='+' || b=='-') {
		       esign = true
		   } else {
		       break
		   }
		*/
		buf = append(buf, b)
		str++
		b = *peek(str)
	}

	result, err := strconv.ParseFloat(string(buf), 64)
	if err != nil {
		nerr, _ := err.(*strconv.NumError)
		isrange := nerr != nil && nerr.Err == strconv.ErrRange
		switch {
		case isrange && math.IsInf(result, 1):
			result = *(*float64)(unsafe.Pointer(hugeval_))
		case isrange && math.IsInf(result, -1):
			result = *(*float64)(unsafe.Pointer(mhugeval_))
		default:
			// TODO: for library testing, log the error somewhere
			result = 0
			str = str0
		}
	}
	*(*float64)(unsafe.Pointer(presult_)) = result

	if endptr_ != 0 {
		*(*uintptr)(unsafe.Pointer(endptr_)) = str
	}
}

type stdiostream int

var stdiostreams = make(map[stdiostream]*os.File)

//var stdiostreams map[stdiostream]*os.File
func init() {
	// see: golua_cstdlib.c, ·initlibs()
	stdiostreams[3] = os.Stdin
	stdiostreams[1] = os.Stdout
	stdiostreams[2] = os.Stderr
}

func (s stdiostream) putc(c byte) {
	// FIXME: check and return any errors from Write
	stdiostreams[s].Write([]byte{c})
}

func (s stdiostream) gets(n int) []byte {
	// FIXME: check and return any errors from Read
	buf := make([]byte, n)
	n, err := stdiostreams[s].Read(buf)
	if err != nil {
		panic(err.Error())
	} // FIXME: make sure errors are handled somehow sensibly
	return buf[:n]
}

func goputc(c_, stream_ uintptr) {
	stream := stdiostream(stream_)
	c := byte(c_)
	stream.putc(c)
}

func gofgets(s_ uintptr, n int, stream_ uintptr) {
	stream := stdiostream(stream_)
	buf := stream.gets(n - 1)
	pokestringplus0(s_, buf)
}
