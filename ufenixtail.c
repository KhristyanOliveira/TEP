#include "prototipos.h"
#include <assert.h>
#include <error.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ufenix_tail(FILE *fp, int n) {

  char **palavras = malloc(n * sizeof(char *)); // matriz de palavras
  char *l;
  int id = 0;

  while ((l = ler_linha(fp)) != NULL) {
    if (id ==
        n) // "retirando" palavra... como se fosse colocando de n em n elementos
           // na fila e reposicionando para ficar sempre os ultimos
    {
      id = 0;
    }
    if (palavras[id] != NULL) {
      free(palavras[id]);
    }
    palavras[id] = l;
    id++;
  }

  // fila circular cheia quanto inicio for igual ao fim

  int i = 0;
  printf("\n\n\tUltimas %d linhas:\n", n);

  while (i < n) {

    if (id == n) {
      id = 0;
    }

    if (palavras[id] == NULL) {
      printf("%6d - invalido\n", i + 1);
    } else {
      printf("%6d - %s\n", i + 1, palavras[id]);
    }
    id++;
    i++;
  }

  for (int y = 0; y < n; y++) {
    if (palavras[y] != NULL) {
      free(palavras[y]);
    }
  }
  free(palavras);
}

int argumento_inteiro(const char *str) {
  char *end;
  long n = strtol(str, &end, 10);
  if (*end != '\0')
    error(1, 0, "Numero invalido '%s'", str);
  if (n < 1 || n > INT_MAX)
    error(1, 0, "%s Fora do intervalo [%d, %d]", str, 1, INT_MAX);
  return n;
}

int main(int argc, char *argv[]) {

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
    if (fp == NULL)
      error(1, 0, "%s: Arquivo nao encontrado", argv[1]);
  }
  ufenix_tail(fp, num);
  fclose(fp);
  return 0;
}
