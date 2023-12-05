#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>
#include <string.h>

typedef int (*my_remove_f)(const char *filename);

int remove(const char *filename) {
    printf("%s", filename);

    my_remove_f my_remove = (my_remove_f) dlsym(RTLD_NEXT, "remove");
    if (strstr(filename, "PROTECT") == NULL) {
        return my_remove(filename);
    } else {
        return -1;
    }
}
