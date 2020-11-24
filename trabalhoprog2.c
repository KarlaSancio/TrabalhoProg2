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
tDCD DCD[maxLinhas];
void LeArquivo();
void PegaInformacoesDaLinha(char linha[], int cont);

int main(){
   
    LeArquivo();
    
    return 0;
}

void LeArquivo(){

    FILE *arquivo = fopen("covid19ES2.csv", "r");
    int nLinha = 0, i;
    char lixo1[20], lixo2[20];

    if(arquivo==NULL){
        printf("Error\n");
        exit (1);
    }
    for (i = 1; i <= maxLinhas; i++){
        fscanf(arquivo, "%[^44], %[^44], %[^44], %[^44], %[^44], %[^44], %[^44], %[^44], %[^44], %[^44], %[^44], %[^44]",
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
    }

    //char caracteresLinha[150];
    //while ((fscanf(arquivo, "%[^\n]%*c", caracteresLinha)) != EOF) 
    //{
        //if(nLinha != 0){
            //PegaInformacoesDaLinha( caracteresLinha, nLinha - 1);
            //printf("%d %s\n", nLinha, caracteresLinha);
        //}
        //nLinha++;
    //}
    
    fclose(arquivo);
}

void PegaInformacoesDaLinha( char linha[], int mLinha){
    // printf("%s %d\n", linha, mLinha);
    int posLetra = 0, comecaPalavra = 0, numItem = 0;
    
    while (linha[posLetra] != '\n')
    {
        if(linha[posLetra] == ',')
        {
            char word[posLetra-comecaPalavra];
            for(int i = comecaPalavra; i < posLetra; i++) 
            {
                word[i - comecaPalavra] = linha[i];
            }
            
            if(numItem == 0)
            {
                strcpy(DCD[mLinha].DataCadastro, word);
                // printf("%s %s \n", word, DCD[mLinha].DataCadastro);
            }
            else if(numItem == 1)
            {
                strcpy(DCD[mLinha].DataObito, word);
                // printf("%s\n", DCD[mLinha].DataObito);
            }
            numItem++;
            comecaPalavra = posLetra + 1;
        }
        posLetra++;
    }
}

