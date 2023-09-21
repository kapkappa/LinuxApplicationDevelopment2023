// Very long string: @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#include "curses.h"

#include "string.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define DX 3
#define LINE_SIZE 256
#define LINES_NUM 128
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

    int i = 0, lines_num = LINES_NUM, line_size = LINE_SIZE, offset = 0, n_strings = 0;
    size_t max_line_len = 0;

    char **all_lines = (char**)malloc(lines_num * sizeof(char*));
    int *lines_lens = (int*)malloc(lines_num * sizeof(int));

    if (all_lines == NULL || lines_lens == NULL) {
        perror("Error");
        return 1;
    }
    for (i = 0; i < lines_num; i++) {
        all_lines[i] = (char*)calloc(line_size, sizeof(char));
        if (all_lines[i] == NULL) {
            perror("Error");
            return 1;
        }
    }

    i = 0;
    while (fgets(&all_lines[i][offset], line_size, fp)) {
        if (all_lines[i][line_size-1] != 0) {
            offset = line_size;
            line_size *= 2;
            all_lines[i] = realloc(all_lines[i], line_size * sizeof(char));
        } else {
            lines_lens[i] = line_size;
            max_line_len = max_line_len > strlen(all_lines[i]) ? max_line_len : strlen(all_lines[i]);
            i++;
            line_size = LINE_SIZE;
            if (i == lines_num) {
                lines_num *= 2;
                all_lines = realloc(all_lines, lines_num * sizeof(char*));
                lines_lens = realloc(lines_lens, lines_num * sizeof(int));
                int j;
                for (j = i; j < lines_num; j++) {
                    all_lines[j] = (char*)calloc(line_size, sizeof(char));
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
    wmove(win, 0, 0);

    offset = 0;
    int c = 0, x = 0;

    do {
        werase(win);
        switch(c) {
            case 32:
            case KEY_NPAGE:
                if (offset + WIN_LINES < n_strings)
                    offset += WIN_LINES;
                break;
            case KEY_PPAGE:
                offset = offset > WIN_LINES ? offset - WIN_LINES : 0;
                break;
            case KEY_DOWN:
                if (offset < n_strings)
                    offset += 1;
                break;
            case KEY_UP:
                if (offset > 0)
                    offset -= 1;
                break;
            case KEY_LEFT:
                if (x > 0)
                    x -= 1;
                break;
            case KEY_RIGHT:
                if (x < (int)max_line_len)
                    x += 1;
                break;
            case KEY_HOME:
                x = 0;
                break;
        }

        for (i = offset; i < n_strings && i < offset + WIN_LINES; i++) {
            mvwprintw(win, i-offset+2, 0, " %4d: ", i);
            x = x < lines_lens[i] ? x : lines_lens[i]-1;
            mvwprintw(win, i-offset+2, 7, "%s", all_lines[i]+x);
        }

        box(win, 0, 0);
    } while ((c = wgetch(win)) != 27);

    endwin();


    for (i = 0; i < lines_num; i++)
        free(all_lines[i]);
    free(all_lines);
    free(lines_lens);

    fclose(fp);
    return 0;
}
