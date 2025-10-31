#!/bin/sh

CXXFLAGS= -g -lm -D _DEBUG -ggdb3  -O0 -Wall -Wextra  \
  -Waggressive-loop-optimizations -Wmissing-declarations -Wcast-align -Wcast-qual \
   -Wchar-subscripts -Wconversion -Wempty-body -Wfloat-equal \
    -Wformat-nonliteral -Wformat-security -Wformat-signedness \
    -Wformat=2 -Winline -Wlogical-op -Wopenmp-simd  -Wpacked -Wpointer-arith \
    -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wstrict-overflow=2 \
    -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wswitch-default \
    -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros \
    -Wno-missing-field-initializers -Wno-narrowing -Wno-varargs -Wstack-protector -fcheck-new \
    -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer \
    -Wstack-usage=8192 -pie -fPIE -Werror=vla \
    -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr

all: spu2 asm

run: all
	./run/asm run/funcs.asm run/ByteCode.txt
	./run/spu2 run/ByteCode.txt

asm: asm/Assembler.cpp
	@g++  -o run/asm asm/Assembler.cpp -lm

spu2: SPU.o obj/Stack.o
	@g++ SPU.o obj/Stack.o -o run/spu2 -lm

Stack.o: stack/Stack.cpp stack/Stack.h
	@g++ -c stack/Stack.cpp -o obj/Stack.o -lm

SPU.o: SPU/SPU.cpp lib/Colors.h
	@g++ -c SPU/SPU.cpp -o SPU.o -lm

