#include "prototipos.h"
#include <error.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


void ufenix_tail(FILE *fp, int n)
{

}

int argumento_inteiro(const char *str)
{
    char *end;
    long n = strtol(str, &end, 10);
    if (*end != '\0') 
        error(1, 0, "Numero invalido '%s'", str);
    if (n < 1 || n > INT_MAX) 
        error(1, 0, "%s Fora do intervalo [%d, %d]", str, 1, INT_MAX);
    return n;
}

int main(int argc, char *argv[])
{
    int num = 10;

    if (argc > 1 && argv[1][0] == '-') {
        num = argumento_inteiro(argv[1] + 1);
        argv++;
        argc--;
    }

    FILE *fp;
    if (argc == 1) {
        fp = stdin;
    } else {
        fp = fopen(argv[1], "r");
        if (fp == NULL) error(1, 0, "%s: Arquivo nao encontrado", argv[1]);
    }
    ufenix_tail(fp, num);
    fclose(fp);
    return 0;
}
