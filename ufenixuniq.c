#include "prototipos.h"
#include <assert.h>
#include <error.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_UNIQ 100

void ufenix_uniq(FILE *fp) 
{
  char **palavras = malloc(TAM_UNIQ * sizeof(char *)); // matriz de palavras
  int p = 0, tam = TAM_UNIQ, *quant = malloc(TAM_UNIQ * sizeof(int));
  char *l; // linha

  while ((l = ler_linha(fp)) != NULL) 
  {
    int i = 0;
    while (i < p)
    {
      if (!strcmp(l, palavras[i])) // iguais
      {
        quant[i] += 1;
        i = tam++;
        free(l); l = NULL;
      }
      i++;
    }

    if (l != NULL) 
    {
      if (p == tam) 
      {
        quant = realloc(quant, 2 * tam);
        palavras = realloc(palavras, 2 * tam);
        
      }
      quant[p] = 1;
      palavras[p] = l;  p++;
    
    }
  }

  printf("\n\t Linhas unicas: \n");
  int k = 0;
  while (k < p) 
  {
    printf("%7d - %s\n", quant[k], palavras[k]);
    free(palavras[k]);
    k++;
  }
  free(quant);
  free(palavras);
}

int main(int argc, char *argv[]) {
  FILE *fp;

  if (argc == 1) {
    fp = stdin;
  } else {
    fp = fopen(argv[1], "r");
    if (fp == NULL)
      error(1, 0, "%s: Arquivo nao encontrado", argv[1]);
  }
  ufenix_uniq(fp);
  fclose(fp);
  return 0;
}
