gostdc provides C Standard Library (alias libc) for porting legacy C programs to compile with [the Go compiler suite][goc] [Work In Progress].

  [goc]: http://golang.org/cmd/cc/

QUICK USAGE
-----------

  * `go get github.com/akavel/gostdc`
  * `cd github.com/akavel/gostdc`
  * `cp copy_me/*.h $MY_PROJECT/`
  * edit `$MY_PROJECT/gostdc.h` to make sure it has right number of `../` segments
  * in some Go file `$MY_PROJECT/*.go` add: `import _ "github.com/akavel/gostdc"`


TODO
----

  * slap license on the files + add AUTHORS file.
  * write full pretty readme
  * remove any left 'golua' in file contents
  * fix `strstr()` (it now uses simple naive O(m*n) algorithm) or
    reuse some MIT/BSD implementation for it
  * fix all FIXMEs and/or reuse some MIT/BSD implementations
  * extend the library to cover all of Standard C Library
  * [optionally] replace most C functions with some MIT/BSD
    implementations
  * split the .c and .go files functionally as .h files would suggest


LICENSE
-------

### Where not otherwise specified, MIT-licensed as:


Copyright (c) 2011-2012 Mateusz Czapliński

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
