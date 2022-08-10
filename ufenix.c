/*
TP-3-UFENIX
Prog 2 - Vinicius Mota
Larissa Fernandes da Silva - 2021100360
Khristyan Vilela Oliveira - 2021101467
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototipos.h"

int Ufenix();

  int main(int argc, char *argv[])
{
  int continua = 0;
  
  do 
  {
    continua = Ufenix();
    system("clear");
  } while (continua);

  return 0;
}
  

int Ufenix(int argc, char *argv[])
{

  char caminho[60] = "./ufenix", comando[50] = "\0";

  printf("\n\tUFENIX\t\n");
  printf("\nDigite exit caso queira sair!\n");
  printf("\nComando:");
  
  fgets(comando, 20, stdin);

  char *argumento;

    if (strcmp(comando, "sair") == 0)
    {
      return 0;
    }

  if (strcmp(comando, "ls") == 0)
  {
    int n = main(argc,argv); // main_ls
    return 1;
  }

  //continua ...

  return 0;
}
