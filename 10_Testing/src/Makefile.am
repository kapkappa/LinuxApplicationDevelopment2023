CFLAGS = -std=c99 -Wall -Wextra -O3 -g3

lib_LTLIBRARIES = libbuf.la
bin_PROGRAMS = buf

buf_LDADD = libbuf.la

libbuf.c: buf.h

check: buf
	@./buf --test

gcov:
	gcov -o .libs libbuf -t -k -b | egrep -v '[[:digit:]]:[ /][*]'
