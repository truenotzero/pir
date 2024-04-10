@echo off

:: make target dir
echo Ensuring target dir exists...
mkdir target

:: compile assembly stub
echo Compiling Assembly Stub...
ml64 /nologo /c /Zd /Zi /Fo target/stub.obj stub.asm

:: compile C source
echo Compiling C source...
clang -c -g -O0 -o target/main.obj main.c

:: link together
echo Linking executable...
clang -g -O0 -o target/main.exe target/main.obj target/stub.obj
:: -Wl,/subsystem:windows 

echo Done!
