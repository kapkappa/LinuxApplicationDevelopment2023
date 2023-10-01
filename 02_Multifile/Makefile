CFLAGS=
CC=

%.o:	%.c
	cc $(CFLAGS) $< -c -o $@

all:	prog prog-a prog-so

prog:	const.o fun.o prog.o
	cc $^ -o $@

prog-a:	
	ar -rcs liboutput_static.a const.o fun.o
	cc -L. prog.o -loutput_static -o prog-a

prog-so:	clean_o 
	make CFLAGS=-fPIC prog
	cc -shared fun.o const.o -o liboutput.so
	cc -L. prog.o -loutput -o prog-so

fun.o:	outlib.h

test: test1 test2 test3

test1:
	@echo "\nTest 1\n"
	./prog   > file1-1 2>&1
	./prog-a > file1-2 2>&1
	LD_LIBRARY_PATH=`pwd` ./prog-so > file1-3 2>&1
	-diff -s file1-1 file1-2
	-diff -s file1-2 file1-3

test2:
	@echo "\nTest 2\n"
	./prog second > file2-1
	./prog-a second > file2-2
	LD_LIBRARY_PATH=`pwd` ./prog-so second > file2-3
	-diff -s file2-1 file2-2
	-diff -s file2-2 file2-3

test3:
	@echo "\nTest 3\n"
	./prog third run > file3-1
	./prog-a third run > file3-2
	LD_LIBRARY_PATH=`pwd` ./prog-so third run > file3-3
	-diff -s file3-1 file3-3
	-diff -s file3-2 file3-3

clean_o:
	rm -f *.o

clean:
	rm -f prog prog-a prog-so a.out *.o *.a *.so file*
