CFLAGS = -std=c99 -Wall -Wextra -O3 -g3

bin_PROGRAMS = buf
buf_SOURCES = buf.c libbuf.c

libbuf.c: buf.h

check: buf
	@./buf --test

gcov:
	gcov -o .libs libbuf -t -k -b | egrep -v '[[:digit:]]:[ /][*]'
