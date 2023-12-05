all: clean test_all

move:
	gcc -O0 -g -Wall -Wextra move.c -o move

remove.so: remove.c
	gcc remove.c -shared -fPIC -o remove.so

test: move
	cat move.c > file1.txt
	strace -e fault=open:error=ENOENT ./move file1.txt file2.txt > /dev/null 2> err1.log
	cat move.c > file1.txt
	strace -e fault=open:error=EPERM  ./move file1.txt file2.txt > /dev/null 2> err2.log
	cat move.c > file1.txt
	strace -e fault=open:error=EINTR  ./move file1.txt file2.txt > /dev/null 2> err3.log

test_preload: move remove.so
	cat move.c > PROTECTED_file.txt
	LD_PRELOAD=./remove.so ./move PROTECTED_file.txt file2.txt > /dev/null 2> err4.log


test_all: test test_preload

clean::
	rm -rf move *.txt *.log
