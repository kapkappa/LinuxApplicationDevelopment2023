all: clean test

range:
	gcc -O0 -g -Wall -Wextra range.c -o range

test: range
	@echo "First script"
	@gdb --batch --quiet --command=gdb1 --args ./range | grep '@@@'
	@echo "Second script"
	@gdb --batch --quiet --command=gdb2 --args ./range | grep '@@@'

clean::
	rm -rf range
