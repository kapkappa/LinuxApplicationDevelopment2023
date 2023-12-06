CFLAGS = -g -Wall -Wextra

bin_PROGRAMS=rhasher

rhasher_SOURCES=rhasher.c

TESTS=test.sh

test.sh:
	echo 'md5 rhasher.c' | ./rhasher | cut -d ' ' -f2,4 > log
	cat log | md5sum -c
	echo 'sha1 rhasher.c' | ./rhasher | cut -d ' ' -f2,4 > log
	cat log | sha1sum -c

gitclean:
	git clean -df
