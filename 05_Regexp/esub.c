#include <stdlib.h>
#include <stdio.h>
#include <regex.h>

#define MAXGR 10
#define BUF_LEN 100

int main(int argc, char**argv) {
    if (argc != 4) {
        printf("Wrong number of parameters!\n");
        exit(1);
    } else {
        printf("regexp: %s\nsubstitution: %s\nstring: %s\n", argv[1], argv[2], argv[3]);
    }
    char buffer[BUF_LEN];
    regex_t reg;
    regmatch_t bags[MAXGR];
    int status, i;
    if ((status = regcomp(&reg, argv[1], REG_EXTENDED)) != 0) {
        regerror(status, &reg, buffer, BUF_LEN);
        printf("regcomp() failed with '%s'\n", buffer);
        exit(1);
    }

    if ((status = regexec(&reg, argv[3], MAXGR, bags, 0)) != 0) {
        regerror(status, &reg, buffer, BUF_LEN);
        printf("regexec() failed with '%s'\n", buffer);
        exit(1);
    }

    int n_replaces = 0;
    int result_len = strlen(argv[3]);
    for (i = 0; i < MAXGR; i++) {
        if (bags[i].rm_so >= 0) {
            printf("[%d] With the whole expression, a matched substring \"%.*s\" is found at position %d to %d.\n", i,
             bags[i].rm_eo - bags[i].rm_so, &argv[3][bags[i].rm_so],
             bags[i].rm_so,
             bags[i].rm_eo - 1);
        }
        n_replaces += 1;
        result_len -= bags[i].rm_eo - bags[i].rm.so;
        result_len += len(argv[2]);
    }

//checks bags in substring
    for (i = 0; i < strlen(argv[2]) - 1; i++) {
        if (argv[2][i] == '\\'  &&  isdigit(argv[2][i+1])) {
            int bag = argv[2][i+1] - '0';
            if (bag > n_replaces) {
                printf("Wrong number of bags\n");
                exit(1);
            }
        }
    }

    char *result_string = calloc(strlen(argv[3]), sizeof(char));

    return 0;
}
