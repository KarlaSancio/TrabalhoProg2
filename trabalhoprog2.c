#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxLinhas 10
#define maxColunas 12

typedef struct DadosCidadeData
{
    char DataCadastro[30];
    char DataObito[30];
    char Classificacao[30];
    char Municipio[30];
    char IdadeNaDataNotificacao[30];
    char IdadeAno[30];
    char IdadeMes[30];
    char IdadeDia[30];
    //vetores com 3 para sim, nao ou -;
    char ComorbidadePulmao[30];
    char ComorbidadeCardio[30];
    char ComorbidadeRenal[30];
    char ComorbidadeDiabetes[30];
    char ComorbidadeTabagismo[30];
    char ComorbidadeObesidade[30];
    char FicouInternado[30];
}tDCD;
tDCD DCD[maxLinhas];
void LeArquivo();
void PegaInformacoesDaLinha(char linha[], int cont);

int main(){
   
    LeArquivo();
    
    return 0;
}

void LeArquivo(){

    FILE *arquivo = fopen("covid19ES.csv", "r");
    int nLinha = 0;

    if(arquivo==NULL){
        printf("Error\n");
        exit (1);
    }
    
    fscanf(arquivo, "%[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^\n]",
        DCD[nLinha].DataCadastro,
        DCD[nLinha].DataObito,
        DCD[nLinha].Classificacao,
        DCD[nLinha].Municipio,
        DCD[nLinha].IdadeNaDataNotificacao,
        DCD[nLinha].ComorbidadePulmao,
        DCD[nLinha].ComorbidadeCardio,
        DCD[nLinha].ComorbidadeRenal,
        DCD[nLinha].ComorbidadeDiabetes,
        DCD[nLinha].ComorbidadeTabagismo,
        DCD[nLinha].ComorbidadeObesidade,
        DCD[nLinha].FicouInternado);

    nLinha++;

    while (nLinha <= maxLinhas)
    {
        fscanf(arquivo, "%[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^\n]",
            DCD[nLinha].DataCadastro,
            DCD[nLinha].DataObito,
            DCD[nLinha].Classificacao,
            DCD[nLinha].Municipio,
            DCD[nLinha].IdadeAno,
            DCD[nLinha].IdadeMes,
            DCD[nLinha].IdadeDia,
            DCD[nLinha].ComorbidadePulmao,
            DCD[nLinha].ComorbidadeCardio,
            DCD[nLinha].ComorbidadeRenal,
            DCD[nLinha].ComorbidadeDiabetes,
            DCD[nLinha].ComorbidadeTabagismo,
            DCD[nLinha].ComorbidadeObesidade,
            DCD[nLinha].FicouInternado
        );
        strcat(DCD[nLinha].IdadeNaDataNotificacao,DCD[nLinha].IdadeAno);
        strcat(DCD[nLinha].IdadeNaDataNotificacao,", ");
        strcat(DCD[nLinha].IdadeNaDataNotificacao,DCD[nLinha].IdadeMes);
        strcat(DCD[nLinha].IdadeNaDataNotificacao,", ");
        strcat(DCD[nLinha].IdadeNaDataNotificacao,DCD[nLinha].IdadeDia);
        printf("%s %s %s %s %s %s %s %s %s %s %s %s\n", 
            DCD[nLinha].DataCadastro,
            DCD[nLinha].DataObito,
            DCD[nLinha].Classificacao,
            DCD[nLinha].Municipio,
            DCD[nLinha].IdadeNaDataNotificacao,
            DCD[nLinha].ComorbidadePulmao,
            DCD[nLinha].ComorbidadeCardio,
            DCD[nLinha].ComorbidadeRenal,
            DCD[nLinha].ComorbidadeDiabetes,
            DCD[nLinha].ComorbidadeTabagismo,
            DCD[nLinha].ComorbidadeObesidade,
            DCD[nLinha].FicouInternado
            );
        printf("\n");
        nLinha++;
    }
    
    fclose(arquivo);
}