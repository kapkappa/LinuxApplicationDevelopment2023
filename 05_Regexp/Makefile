all: clean test

esub:
	gcc -O0 -g -Wall -Wextra esub.c -o prog

test: esub
	@echo "\nGold value: "
	@echo "Wed 25 Oct 25:23:12 MSK 2023" | sed -E "s/([0-9][0-9]*)([0-9])/ABC  dd<\1>dd<\2>/"
	@echo "\nProgram :"
	@./prog "([0-9][0-9]*)([0-9])" "ABC  dd<\1>dd<\2>" "Wed 25 Oct 25:23:12 MSK 2023"

clean::
	rm -rf prog
