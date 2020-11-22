#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
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

typedef struct Dados dados;

void LeArquivo();
void PegaInformacoes(char *buffer);

void LeArquivo(){
    FILE *arquivo = fopen("covid19ES.csv", "r");
    int cont = 0;

    do //Lê o conteúdo do arquivo enquanto há algo para ser lido(até o fim do arquivo)
    {
        char buffer[202364];//qtd de linhas do arquivo
        fgets(buffer, 202364, (FILE*)arquivo);// pegando as strings de cada linha do arquivo
        cont++;

        if(cont != 1){
            printf("%s", buffer);
            PegaInformacoes(buffer);
        }

    } while ((getc(arquivo)) != EOF);
    
}

void PegaInformacoes(char buffer[]){
    int cont = 0;
    //Separa os itens da string que estão separados por vírgula
    char *item = strtok(buffer, ",");

    while(item !=  NULL){
        cont++;
        printf( " %s\n",item);
        item = strtok(NULL, ",");
    }
}


int main(){


    LeArquivo();




    return 0;
}