@echo off
setlocal

if not exist unifdef.txt (
	echo %0: please put path to 'unifdef.exe' in 'unifdef.txt'
	echo %0: [download from: https://github.com/fanf2/unifdef]
	goto :eof
)
set /p unifdef=<unifdef.txt

if "%1"=="" (
	echo USAGE: %0 FUNC_NAME
	goto :eof
)

if not exist "_libc\%1.c" (
	echo %0: "_libc\%1.c" does not exist
	goto :eof
)

set defs= 
set defs=%defs% -U_KERNEL
set defs=%defs% -U_STANDALONE
%unifdef% %defs% "_libc\%1.c" > "%1.c"

endlocal