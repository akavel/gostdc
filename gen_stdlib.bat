@echo off
setlocal

if not exist unifdef.txt (
	echo %0: please put path to 'unifdef.exe' in 'unifdef.txt'
	echo %0: [download from: https://github.com/fanf2/unifdef]
	goto :eof
)
set /p unifdef=<unifdef.txt

cd _libc
for %%f in (*.c) do call :conv %%f
endlocal
goto :eof

:conv %1
set defs= 
set defs=%defs% -U_KERNEL
set defs=%defs% -U_STANDALONE
set defs=%defs% -UAPIWARN
set defs=%defs% -DMEMCOPY
%unifdef% %defs% "%1" > "..\%1"
goto :eof
