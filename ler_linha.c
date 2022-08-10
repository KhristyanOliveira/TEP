/**
 * @file ler_linha.c
 * @author Vinicius Mota
 * @brief a função ler_linha lê um tamanho minimo e caso não tenha espaço
 *  dobra de tamanho, isto é começa em 32, vai para 64, então 128, then 256, etc. as needed to accommodate the entire linha

 * @version 0.1
 * @date 2022-07-05
 * 
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define TAM_LINHA 32

char * ler_linha (FILE *fp)
{
  size_t tamanho_atual = TAM_LINHA;

  char*linha = NULL;

  while(1)
  {
    linha = realloc (linha, tamanho_atual);
    
    assert(linha != NULL);
    
    if(ungetc(getc(fp), fp)==EOF)
    {
      free(linha);
      return NULL;
    }
    
    fgets(linha,tamanho_atual, fp);

    char*fim_linha = strstr(linha, "\n");
    
    if(fim_linha)
    {
      *fim_linha = '\0';
      return linha;
    }
    else
    {
      if(ungetc(getc(fp), fp)==EOF)
      {
        return linha;
      }
      else
      {
        assert(fseek(fp, 1-tamanho_atual, SEEK_CUR)==0);
        tamanho_atual *= 2;       
      }
    }      
  }
}


