@echo off

SET files=source/*.c
SET out=lemonic
SET cflags = -g -Wall
SET iflags=-Isource
SET lflags=-luser32
clang %files% %cflags% -o build/%out%.exe %iflags% %lflags% -DLEM_PLATFORM_WIN32
