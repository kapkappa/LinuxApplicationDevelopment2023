#include <stdio.h>
#include <stdlib.h>

int main(int argc, char**argv) {
    int start = 0, stop, step = 1, i;
    switch (argc) {
        case 1:
            printf("HELP: Produces a sequence of integers from start (inclusive) to stop (exclusive) by step.\nTakes from 1 upto 3 parameters: start, stop, step.\n");
            exit(1);
        case 2:
            stop = atoi(argv[1]);
            break;
        case 3:
            start = atoi(argv[1]);
            stop = atoi(argv[2]);
            break;
        case 4:
            start = atoi(argv[1]);
            stop = atoi(argv[2]);
            step = atoi(argv[3]);
            break;
        default:
            printf("Wronf number of parameters\n");
            exit(1);
    }
    for (i = start; i < stop; i += step) {
        printf("%d\n", i);
    }
    return 0;
}
