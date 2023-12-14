#include <stdio.h>
#include <libintl.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

/** @file guess.c
* Implementation
*
* Guesses the hidden number
*/


#define _(STRING) gettext(STRING)

static char* roman_numbers[100] = {
    "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X", "XI", "XII", "XIII", "XIV", "XV",
    "XVI", "XVII", "XVIII", "XIX", "XX", "XXI", "XXII", "XXIII", "XXIV", "XXV", "XXVI", "XXVII", "XXVIII",
    "XXIX", "XXX", "XXXI", "XXXII", "XXXIII", "XXXIV", "XXXV", "XXXVI", "XXXVII", "XXXVIII", "XXXIX", "XL",
    "XLI", "XLII", "XLIII", "XLIV", "XLV", "XLVI", "XLVII", "XLVIII", "XLIX", "L", "LI", "LII", "LIII",
    "LIV", "LV", "LVI", "LVII", "LVIII", "LIX", "LX", "LXI", "LXII", "LXIII", "LXIV", "LXV", "LXVI", "LXVII",
    "LXVIII", "LXIX", "LXX", "LXXI", "LXXII", "LXXIII", "LXXIV", "LXXV", "LXXVI", "LXXVII", "LXXVIII",
    "LXXIX", "LXXX", "LXXXI", "LXXXII", "LXXXIII", "LXXXIV", "LXXXV", "LXXXVI", "LXXXVII", "LXXXVIII",
    "LXXXIX", "XC", "XCI", "XCII", "XCIII", "XCIV", "XCV", "XCVI", "XCVII", "XCVIII", "XCIX", "C"
};

char str_number[4] = {0};

/** Convert integer number into string representation.
*
* @param number integer number
* @return string buffer
*/
char* convert_to_str(int number) {
    sprintf(str_number, "%d", number);
    return str_number;
}

/** Convert integen number into ROMAN string representation.
*
* @param number integer number
* @return string buffer
*/
char* convert_to_roman(int number) {
    return roman_numbers[number-1];
}

int main(int argc, char** argv) {

    char*(*convert_ptr)(int) = &convert_to_str;

    setlocale(LC_ALL, "");
    bindtextdomain("guess", ".");
    textdomain("guess");

    if (argc == 2) {
        if (!strcmp(argv[1], _("--help"))) {
            printf(_("This is the help you asked!\n"));
            printf(_("Args usage:\n\t--help shows this message\n\t-r enables Roman numbers\n"));
            printf(_("The program guesses the hidden number!\n"));
            return 0;
        }
        if (!strcmp(argv[1], _("-r"))) {
            printf(_("Roman numbers enabled\n"));
            convert_ptr = &convert_to_roman;
        } else {
            printf(_("WARNING: unknown argument!\n"));
        }
    }

    printf(_("Please, guess a number from %s to %s.\n"), convert_ptr(1), convert_ptr(100));

    int lower = 1, upper = 100;

    while (upper != lower) {
        int half = (upper + lower) / 2;
        printf(_("Does the number more than %s?\n"), convert_ptr(half));

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

    printf(_("Your number is %s!\n"), convert_ptr(lower));

    return 0;
}
