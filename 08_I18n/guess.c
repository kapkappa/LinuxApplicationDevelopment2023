#include <stdio.h>

int main(int argc, char** argv) {
    printf("Please, guess a number from 1 to 100.\n");

    int lower = 1, upper = 100;

    while (upper != lower) {
        int half = (upper + lower) / 2;
        printf("Does the number more than %d?\n", half);

        int y;
        scanf("%d", &y);

        if (y) {
            lower = half;
        } else {
            upper = half;
        }
    }

    printf("Your number is %d!\n", lower);

    return 0;
}
