#include <stdio.h>
#include <libintl.h>
#include <locale.h>

#define _(STRING) gettext(STRING)

int main(int argc, char** argv) {

    bindtextdomain("guess", "po");
    setlocale(LC_ALL, "");
    textdomain("guess");

    printf(_("Please, guess a number from 1 to 100.\n"));

    int lower = 1, upper = 100;

    while (upper != lower) {
        int half = (upper + lower) / 2;
        printf(_("Does the number more than %d?\n"), half);

        int y;
        scanf("%d", &y);

        if (y) {
            lower = half;
        } else {
            upper = half;
        }
    }

    printf(_("Your number is %d!\n"), lower);

    return 0;
}
