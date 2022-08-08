#include "prototipos.h"
#include <error.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
void ufenix_uniq(FILE *fp){
 
}


int main(int argc, char *argv[])
{
    FILE *fp;

    if (argc == 1) {
        fp = stdin;
    } else {
        fp = fopen(argv[1], "r");
        if (fp == NULL) error(1, 0, "%s: Arquivo nao encontrado", argv[1]);
    }
    ufenix_uniq(fp);
    fclose(fp);
    return 0;
}
