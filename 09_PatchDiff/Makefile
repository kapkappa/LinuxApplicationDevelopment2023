all: clean gen_lab gen_lab_v1 gen_lab_v2 gen_lab_v3

gen_lab:
	gcc gen_lab.c -o gen_lab_v0

gen_lab_v1: gen_lab
	patch gen_lab.c patch1.patch
	gcc gen_lab.c -o gen_lab_v1

gen_lab_v2: gen_lab
	patch gen_lab.c patch2.patch
	gcc gen_lab.c -o gen_lab_v2

gen_lab_v3: gen_lab
	patch gen_lab.c patch3.patch
	gcc gen_lab.c -o gen_lab_v3


run: all
	./gen_lab_v0
	./gen_lab_v1 10
	./gen_lab_v2 " @" 10
	./gen_lab_v3 10 " %" 15

clean:
	rm -f gen_lab_v* *.o

