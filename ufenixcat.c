/**
 * @file ufenixcat.c

 * @brief Programa le um arquivo de entrada e vai imprimindo a
   até encontrar o final do arquivo.

   A entrada é passada como um argumento do programa ou a entrada padrão.
   ./ufenixcat cores.txt
 * @version 0.1
 * @date 2022-07-05
 *
 */
#include "prototipos.h"
#include <error.h>
#include <stdio.h>
#include <stdlib.h>

void ufenix_cat(FILE *fp) {
  char *line;
  for (int i = 1; (line = ler_linha(fp)) != NULL; i++) {
    printf("%6d  %s\n", i, line);
    free(line);
  }
}

int main(int argc, char *argv[]) {
  FILE *fp;

  if (argc == 1) {
    fp = stdin;
  } else {
    fp = fopen(argv[1], "r");
    if (fp == NULL)
      error(1, 0, "%s: Arquivo não encontrado", argv[1]);
  }

  ufenix_cat(fp);

  fclose(fp);
  return 0;
}
