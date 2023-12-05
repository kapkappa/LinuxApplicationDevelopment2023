CFLAGS = -g -Wall -Wextra

bin_PROGRAMS=rhasher

rhasher_SOURCES=rhasher.c

TESTS=test.sh

test.sh:
	echo 'md5 rhasher.c' | ./rhasher | cut -d ' ' -f2 | md5sum -c


