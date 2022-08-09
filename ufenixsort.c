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
    // função que compara se as strings são iguais
    // uma das funções do comando sort é retirar palavras duplicadas com base em um comando de flag
    // com isso podemos comparar se são iguais
    int result;

    result=strcmp(p,q);

    if(result==0){
        return 0;
    }
    else if(result==-1){
        return -1;
    }
    else{
        return 1;
    }
  
}

int cmp_pstr_tamanho(const void *p, const void *q)
{

    // testar a saida com printf, para ver se sai valores !!!
    int tam1, tam2;
    tam1=strlen(p);// função que compara o tamanho da string ...
    tam2=strlen(q);
    if(tam1 > tam2){
        return tam1;
    }
    else 
        return tam2;
  
}

int cmp_pstr_numeros(const void *p, const void *q)
{
    int qtd1, qtd2;

    qtd1=atoi(p);// converte para numero inteiro e compara o maior valor
    
    qtd2=atoi(q);

    if(qtd1>qtd2){
        return qtd1;
    }
    else
        return qtd2;
  
}

void ufenix_sort(FILE *fp, cmp_fn_t cmp, bool uniq, bool reverse)
{
    /* função que será utlizada para chamar os comandos de comparação 
    para assim ser ordenada conforme solicitada em sua flag*/

    // não possui limite de quantos comandos de flag serão chamados !!! OBS:(no máximo 4)

    /*
    if(cmp != arquivo){
        devo comparar se o proximo comando será ou um cmp ou o nome do arquivo !!!!
    }
    */
  
}

int main(int argc, char *argv[])
{
    cmp_fn_t cmp = cmp_pstr;
    bool uniq = false, reverse = false;

    int opt;
    while ((opt = getopt(argc, argv, "lnru")) != -1) {
        //Baseado no opt seta a função de comparação
        switch (opt) {
           
            case 'l': cmp = cmp_pstr_tamanho; break;
            case 'n': cmp = cmp_pstr_numeros; break;
            case 'r': reverse = true; break; // imprime a ordem decrescente
            case 'u': uniq = true; break;// imprime a ordem crescente, sem as palavras repetidas
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
