#include <stdlib.h>
#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <ctype.h>

#define MAXGR 10
#define BUF_LEN 100

int main(int argc, char**argv) {
    if (argc != 4) {
        printf("Wrong number of parameters!\n");
        exit(1);
    } else {
        printf("regexp: %s\nsubstitution: %s\nstring: %s\n", argv[1], argv[2], argv[3]);
    }

    char* regexp = argv[1];
    char* substr = argv[2];
    char* string = argv[3];

    char buffer[BUF_LEN];
    regex_t reg;
    regmatch_t bags[MAXGR];
    int status, i;
    if ((status = regcomp(&reg, regexp, REG_EXTENDED)) != 0) {
        regerror(status, &reg, buffer, BUF_LEN);
        printf("regcomp() failed with '%s'\n", buffer);
        exit(1);
    }

    if ((status = regexec(&reg, string, MAXGR, bags, 0)) != 0) {
        regerror(status, &reg, buffer, BUF_LEN);
        printf("regexec() failed with '%s'\n", buffer);
        exit(1);
    }

    int n_replaces = 0;
    for (i = 0; i < MAXGR; i++) {
        if (bags[i].rm_so >= 0) {
            printf("[%d] With the whole expression, a matched substring \"%.*s\" is found at position %d to %d.\n", i,
             bags[i].rm_eo - bags[i].rm_so, string + bags[i].rm_so,
             bags[i].rm_so,
             bags[i].rm_eo - 1);
            n_replaces += 1;
        }
    }



//checks bags in substring
    int n_bags = 0, substr_len = strlen(argv[2]);
    for (i = 0; i < substr_len - 1; i++) {
        if (argv[2][i] == '\\'  &&  isdigit(argv[2][i+1])) {
            int bag = argv[2][i+1] - '0';
            if (bag > n_replaces) {
                printf("Wrong number of bags\n");
                exit(1);
            }
            n_bags += 1;
        }
    }

    char *res_string = calloc(strlen(string) + strlen(substr), sizeof(char));

//fill final string
    strncpy(res_string, string, bags[0].rm_so);

    int bag = 0;
    int res_offset = bags[0].rm_so;
    for (i = 0; i < substr_len; i++) {
        if (substr[i] == '\\' && i < substr_len - 1) {
            if (isdigit(substr[i+1])) {
                int len = bags[bag].rm_eo - bags[bag].rm_so;
                strncpy(res_string + res_offset, string + bags[bag].rm_so, len);
                res_offset += len;
                i += 1;
                bag += 1;
            } else if (substr[i+1] == '\\') {
                res_string[res_offset++] = substr[i];
                i += 1;
            }
        } else {
            res_string[res_offset++] = substr[i];
        }
    }

    strncpy(res_string + res_offset, string + bags[n_replaces-1].rm_eo, strlen(string) - bags[n_replaces-1].rm_eo);

    printf("%s\n", res_string);
    free(res_string);
    regfree(&reg);
    return 0;
}
