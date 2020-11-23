#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxLinhas 10
#define maxColunas 12

typedef struct DadosCidadeData
{
    char DataCadastro[10];
    char DataObito[10];
    char Classificacao[11];
    char Municipio[30];
    char IdadeNaDataNotificacao[30];
    //vetores com 3 para sim, nao ou -;
    char ComorbidadePulmao[3];
    char ComorbidadeCardio[3];
    char ComorbidadeRenal[3];
    char ComorbidadeDiabetes[3];
    char ComorbidadeTabagismo[3];
    char ComorbidadeObesidade[3];
    char FicouInternado[13];
}tDCD;

void LeArquivo(tDCD *DCD[]);
void PegaInformacoes(tDCD *DCD[], char *linha[], int cont);

int main(){
    tDCD DCD[maxLinhas];

    LeArquivo(DCD);

    return 0;
}

void LeArquivo(tDCD *DCD[]){
    FILE *arquivo = fopen("covid19ES.csv", "r");
    int nLinha = 0, i;

    if(arquivo==NULL){
        printf("Error\n");
        exit (1);
    }

    do //Lê o conteúdo do arquivo enquanto há algo para ser lido(até o fim do arquivo)
    {
        char bufferLinha[202363];//qtd de linhas do arquivo
        fgets(bufferLinha, 202363, (FILE*)arquivo);// pegando as strings de cada linha do arquivo
        
        if(nLinha != 0){
            PegaInformacoes(DCD, bufferLinha, nLinha);
        }
        nLinha++;

    //} while ((getc(arquivo)) != EOF);
    } while ( nLinha != 10);
    
    fclose(arquivo);
}

void PegaInformacoes(tDCD *DCD[], char *linha[], int nLinha){
    //Separa os itens da string que estão separados por vírgula
    char *item = strtok(linha, ",");

    for(int col = 1; col <= maxColunas; col++)
    {
        if(col == 1)
            strcpy(DCD[col]->DataCadastro, item);
        if(col == 2)
            // DCD[col].DataObito = item;
        // etc até o 12º item
        item = strtok(NULL, ","); //pesquisar o que e
    } 
}
