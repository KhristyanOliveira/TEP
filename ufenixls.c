#include "prototipos.h"
#include <assert.h>
#include <dirent.h>
#include <errno.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ordenaTipo(const struct dirent **dir1, const struct dirent **dir2) {

  // DT_REG -> arquivo
  // DT_DIR -> diretorio

  char t1 = (*dir1)->d_type;
  char t2 = (*dir2)->d_type;

  if (t1 == t2) {
    return alphasort(dir1, dir2);
  }

  return strcmp(&t1, &t2);
}

int filtro(const struct dirent *dir) {
  if (dir->d_name[0] == '.') {
    return 0;
  }
  return 1;
}

void ufenix_ls(const char *dir, bool show_all, bool sort_by_type) {

  int n;
  struct dirent **d;

  DIR *dh = opendir(dir);

  if (!dh) {
    if (errno = ENOENT) {
      printf("Nao eh possivel acessar '%s'!!\n", dir);
      exit(0);
    }
  }

  if (dh != NULL)
    free(dh);

  if (show_all == true) {
    n = scandir(dir, &d, NULL,
                alphasort); // devolve os resultados em "d", um vetor de
                            // apontadores de estruturas do tipo dirent;

    if (n == -1) {
      printf("Erro\n\n");
      exit(0);
    }
    printf("\n");

    for (int k = 0; k < n; k++) {
      printf("\n%s", d[k]->d_name);
      if (d[k]->d_type == DT_DIR) // se for diretorio
      {
        printf("/");
      }
      free(d[k]);
    }
    printf("\n");
  }

  if (sort_by_type == true) {
    n = scandir(dir, &d, filtro,
                ordenaTipo); // devolve os resultados em "d", um vetor de
                             // apontadores de estruturas do tipo dirent;
    if (n == -1) {
      printf("Erro\n\n");
      exit(0);
    }
    printf("\n");

    for (int u = 0; u < n; u++) {
      printf("\n%s", d[u]->d_name);
      if (d[u]->d_type == DT_DIR) {
        printf("/");
      }
      free(d[u]);
    }
    printf("\n");
  }
  free(d);
}

int main(int argc, char *argv[]) {
  bool mostrar_tudo = false;
  bool dirs_primeiro = false;

  int opt;
  // o getopt ajuda a pegar e tratar os argumentos
  while ((opt = getopt(argc, argv, "az")) != -1) {
    switch (opt) {
    case 'a':
      mostrar_tudo = true;
      break;
    case 'z':
      dirs_primeiro = true;
      break;
    default:
      exit(1);
    }
  }
  // optind é um variavel com escopo extern do getopt
  // ver documentação para entender
  if (optind < argc - 1) {
    for (int i = optind; i < argc; i++) {
      printf("%s:\n", argv[i]);
      ufenix_ls(argv[i], mostrar_tudo, dirs_primeiro);
      printf("\n");
    }
  } else {
    ufenix_ls(optind == argc - 1 ? argv[optind] : ".", mostrar_tudo,
              dirs_primeiro);
  }
  return 0;
}
