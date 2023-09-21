#include "curses.h"

#include "string.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define DX 3
#define SSIZE 256
#define MAX_STRINGS 128
#define WIN_COLS COLS-2*DX
#define WIN_LINES LINES-2*DX

int main(int argc, char **argv) {

    if (argc != 2) {
        printf("Error: enter filename!");
        return 1;
    }

    FILE *fp;
    if ((fp = fopen(argv[1], "r")) == NULL) {
        perror("Error");
        return 1;
    }

    int i = 0, max_strings = MAX_STRINGS, string_size = SSIZE, offset = 0, n_strings = 0;

    char **all_strings = (char**)malloc(max_strings * sizeof(char*));
    if (all_strings == NULL) {
        perror("Error");
        return 1;
    }
    for (i = 0; i < max_strings; i++) {
        all_strings[i] = (char*)calloc(string_size, sizeof(char));
        if (all_strings[i] == NULL) {
            perror("Error");
            return 1;
        }
    }

    i = 0;
    while (fgets(&all_strings[i][offset], string_size, fp)) {
        if (all_strings[i][string_size-1] != 0) {
            offset = string_size;
            string_size *= 2;
            all_strings[i] = realloc(all_strings[i], string_size * sizeof(char));
        } else {
            i++;
            string_size = SSIZE;
            if (i == max_strings) {
                max_strings *= 2;
                all_strings = realloc(all_strings, max_strings * sizeof(char*));
                int j;
                for (j = i; j < max_strings; j++) {
                    all_strings[j] = (char*)calloc(string_size, sizeof(char));
                }
            }
        }
    }
    n_strings = i;


    WINDOW *win;

    initscr();
    noecho();
    cbreak();
    printw("File: %s; size: %d", argv[1], i);
    refresh();

    win = newwin(WIN_LINES, WIN_COLS, DX, DX);
    keypad(win, TRUE);
    scrollok(win, TRUE);
    box(win, 0, 0);
    wmove(win, 2, 2);

    offset = 0;
    int c = 0, x = 0;
    do {
        werase(win);

        if (c == 32 && offset + WIN_LINES < n_strings) {
            offset += WIN_LINES;
        } else if (!strcmp(keyname(c), "KEY_DOWN")) {
            offset += 1;
        } else if (!strcmp(keyname(c), "KEY_UP") && offset > 0) {
            offset -= 1;
        } else if (!strcmp(keyname(c), "KEY_LEFT") && x > 0) {
            x -= 1;
        } else if (!strcmp(keyname(c), "KEY_RIGHT")) {
            x += 1;
        }

        for (i = offset; i < n_strings && i < offset + WIN_LINES; i++) {
            mvwprintw(win, i-offset+2, x, "   %d: %s", i, all_strings[i]);
        }

        box(win, 0, 0);
    } while ((c = wgetch(win)) != 27);

    endwin();


    for (i = 0; i < max_strings; i++)
        free(all_strings[i]);
    free(all_strings);

    fclose(fp);
    return 0;
}
