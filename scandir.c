#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>

int musl_scandir(const char *path, struct dirent ***res,
   int (*sel)(const struct dirent *),
   int (*cmp)(const struct dirent **, const struct dirent **)) {
    
    DIR *d = opendir(path);
    struct dirent *de;
    struct dirent **names = NULL;
    struct dirent **tmp;
    size_t cnt = 0;
    size_t len = 0;

    if (!d) {
        return -1;
    }

    while ((de = readdir(d))) {
        if (sel && !sel(de)) {
            continue;
        }
        if (cnt >= len) {
            len = 2 * len + 1;
            if (len > SIZE_MAX / sizeof(*names)) {
                break;
            }
            tmp = realloc(names, len * sizeof(*names));
            if (!tmp) {
                break;
            }
            names = tmp;
        }
        names[cnt] = malloc(de->d_reclen);
        if (!names[cnt]) {
            break;
        }
        memcpy(names[cnt++], de, de->d_reclen);
    }

    closedir(d);

    if (errno) {
        if (names) {
            while (cnt-- > 0) {
                free(names[cnt]);
            }
        }
        free(names);
        return -1;
    }
    if (cmp) {
        qsort(names, cnt, sizeof *names, 
            (int (*)(const void *, const void *))cmp);
    }
    *res = names;
    return cnt;
}