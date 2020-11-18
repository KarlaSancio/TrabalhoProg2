#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Dados
{
    //datas com 10 vetores para padrao de data;
    char DataCadastro[10];
    char DataObito[10];

    //com no maximo 11 por ser a maior entrada esperada de caracteres;
    char Classificacao[11];

    // sempre em maiusculo;
    char Municipio[20];
        
    char IdadeNaDataNotificacao[20];

    //vetores com 3 para sim, nao ou -;
    char ComorbidadePulmao[3];
    char ComorbidadeCardio[3];
    char ComorbidadeRenal[3];
    char ComorbidadeDiabetes[3];
    char ComorbidadeTabagismo[3];
    char ComorbidadeObesidade[3];
    char FicouInternado[3];

} Dados;



int main(){


    FILE*fl=fopen("covid19ES.csv","r");

        if(fl==NULL){
            printf("ERRO NA LEITURA DE ARQUIVO!");
            exit(1);// aborta o programa;
        }




    return 0;
}