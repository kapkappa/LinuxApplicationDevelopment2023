#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int main(int argc, char**argv) {
    if (argc != 3) {
        fprintf(stderr, "Wrond number of arguments\n");
        return 1;
    }

    FILE* fin = fopen(argv[1], "r");
    if (fin == NULL) {
        perror("Can't open infile");
        return 2;
    }
    FILE *fout = fopen(argv[2], "w+");
    if (fout == NULL) {
        perror("Can't open outfile");
        return 3;
    }

    char c;
    while ((c = getc(fin)) != EOF) {
        putc(c, fout);
    }

    if (fclose(fin)) {
        perror("Can't close infile");
        remove(argv[2]);
        return 6;
    }

    if (fclose(fout)) {
        perror("Can't close outfile");
        remove(argv[2]);
        return 6;
    }

    remove(argv[1]);

    return 0;
}
