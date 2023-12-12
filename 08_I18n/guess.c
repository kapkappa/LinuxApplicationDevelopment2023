#include <stdio.h>
#include <libintl.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>

#define _(STRING) gettext(STRING)

int main(int argc, char** argv) {

    setlocale(LC_ALL, "");
    bindtextdomain("guess", ".");
    textdomain("guess");

    printf(_("Please, guess a number from 1 to 100.\n"));

    int lower = 1, upper = 100;

    while (upper != lower) {
        int half = (upper + lower) / 2;
        printf(_("Does the number more than %d?\n"), half);

        char c[8];
        int correct_input = 0;
        while (correct_input != 1) {
            correct_input = scanf("%7s", c);
            for (int i = 0; c[i] != 0; i++)
                c[i]= tolower(c[i]);

            if (!strcmp(c, _("yes")) || !strcmp(c, _("y")))
                lower = half + 1;
            else if (!strcmp(c, _("no")) || !strcmp(c, _("n")))
                upper = half;
            else {
                printf(_("Bad input! Enter yes or no.\n"));
                correct_input = 0;
            }
        }
    }

    printf(_("Your number is %d!\n"), lower);

    return 0;
}
