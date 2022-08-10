#include "prototipos.h"
#include <error.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int (*cmp_fn_t)(const void *p, const void *q);

int cmp_pstr(const void *p, const void *q)
{
    // casting
    char * pPtr = (char*) p;
    char * qPtr = (char*) q;

    return  strcmp(pPtr,qPtr);
}

int cmp_pstr_tamanho(const void *p, const void *q)
{
     // casting
   	char * pPtr = (char*) p;
    char * qPtr = (char*) q;
  
	  int n1 = strlen(pPtr);
	  int n2 = strlen(qPtr);
  
	  return (n1>n2) - (n1<n2);
}

int cmp_pstr_numeros(const void *p, const void *q)
{
    int qtd1=0, qtd2=0;

    // casting
   	char * pPtr = (char*) p;
    char * qPtr = (char*) q;

    qtd1 = atoi(pPtr);
    qtd2 = atoi(qPtr);
  
  return (qtd1>qtd2) - (qtd1<qtd2); 
}

void ufenix_sort(FILE *fp, cmp_fn_t cmp, bool uniq, bool reverse)
{
  
}


int main(int argc, char *argv[])
{
    cmp_fn_t cmp = cmp_pstr;
    bool uniq = false, reverse = false;

    int opt;
    while ((opt = getopt(argc, argv, "lnru")) != -1) {
        //Baseado no opt seta a função de comparação
        switch (opt) {

            // a ultima flag tem  prioridade
            case 'l': cmp = cmp_pstr_tamanho; break; // compr de linha
            case 'n': cmp = cmp_pstr_numeros; break; // alfabetico
            case 'r': reverse = true; break; // alfabetico inverso
            case 'u': uniq = true; break; // nao repete palavras
            default: exit(1); 
        }
    }

    FILE *fp = stdin;
    if (optind < argc) {
        fp = fopen(argv[optind], "r");
        if (fp == NULL) error(1, 0, "%s: Arquivo nao encontrado", argv[optind]);
    }
    ufenix_sort(fp, cmp, uniq, reverse);
    fclose(fp);
    return 0;
}
