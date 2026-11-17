@echo off
cd /d "%~dp0"

nasm -f bin boot.asm -o boot.bin
if errorlevel 1 (echo [ERROR] fallo boot.asm & pause & exit /b 1)

nasm -f bin Fase2.asm -o Fase2.bin
if errorlevel 1 (echo [ERROR] fallo Fase2.asm & pause & exit /b 1)

for %%A in (boot.bin) do set T1=%%~zA
if not "%T1%"=="512" (echo [ERROR] boot.bin mide %T1%, debe medir 512 & pause & exit /b 1)

copy /b boot.bin+Fase2.bin os.img >nul

rem Agrandar la imagen a 1 MB (se rellena con ceros)
powershell -NoProfile -Command "$f=[IO.File]::Open('os.img','Open','Write'); $f.SetLength(1048576); $f.Close()"
if errorlevel 1 (echo [ERROR] no se pudo agrandar os.img & pause & exit /b 1)

for %%A in (os.img) do echo os.img = %%~zA bytes

qemu-system-i386 -drive format=raw,file=os.img
pause