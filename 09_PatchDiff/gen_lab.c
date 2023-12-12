#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum direction {left, right, up, down};

int main(int argc, char** argv) {

    srand(time(NULL));

    int size = 6;

    // alloc
    char** maze = calloc(2*size+1, sizeof(char*));
    for (int i = 0; i < 2*size+1; i++)
        maze[i] = calloc(2*size+2, sizeof(char));

    // fill
    for (int i = 0; i < 2*size+1; i++)
        for (int j = 0; j < 2*size+1; j++)
            maze[i][j] = '#';

    // generate
    int row = rand() % size;
    int col = rand() % size;
    maze[2*row+1][2*col+1] = '.';
    int visited = 1;

    while (visited < size * size) {
        int passages = 0;
        int neighbors[4] = {0};
        if (col > 0 && maze[2*row+1][2*col-1] == '#') {         // left
            neighbors[passages] = left;
            passages++;
        }
        if (col < size-1 && maze[2*row+1][2*col+3] == '#') {    // right
            neighbors[passages] = right;
            passages++;
        }
        if (row > 0 && maze[2*row-1][2*col+1] == '#') {         // up
            neighbors[passages] = up;
            passages++;
        }
        if (row < size-1 && maze[2*row+3][2*col+1] == '#') {    // down
            neighbors[passages] = down;
            passages++;
        }
        if (!passages) {
            do {
                row = rand() % size;
                col = rand() % size;
            } while (maze[2*row+1][2*col+1] != '.');
            continue;
        }

        int next = rand() % passages;
        switch (neighbors[next]) {
            case left:
                maze[2*row+1][2*col] = '.';
                maze[2*row+1][2*col-1] = '.';
                col--;
                visited++;
                break;
            case right:
                maze[2*row+1][2*col+2] = '.';
                maze[2*row+1][2*col+3] = '.';
                col++;
                visited++;
                break;
            case up:
                maze[2*row][2*col+1] = '.';
                maze[2*row-1][2*col+1] = '.';
                row--;
                visited++;
                break;
            case down:
                maze[2*row+2][2*col+1] = '.';
                maze[2*row+3][2*col+1] = '.';
                row++;
                visited++;
                break;
        }
    }

    for (int i = 0; i < 2*size+1; i++)
        printf("%s\n", maze[i]);

    for (int i = 0; i < 2*size+1; i++)
        free(maze[i]);
    free(maze);

    return 0;
}
