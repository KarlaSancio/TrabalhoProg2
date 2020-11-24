#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxLinhas 100000
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
void PegaInformacoes(char linha[], int cont);

int main(){
   
    LeArquivo(DCD);
    for (int i = 0; i < maxLinhas; i++)
    {
        // printf("%s\n", DCD[i].DataCadastro);
    }
    return 0;
}

void LeArquivo(){
    FILE *arquivo = fopen("covid19ES.csv", "r");
    int nLinha = 0, i;
    if(arquivo==NULL){
        printf("Error\n");
        exit (1);
    }
    // (getc(arquivo)) != EOF
    while ( nLinha != maxLinhas) //Lê o conteúdo do arquivo enquanto há algo para ser lido(até o fim do arquivo)
    {
        char bufferLinha[202363]; //qtd de linhas do arquivo
        fgets(bufferLinha, 202363, (FILE*)arquivo); // pegando as strings de cada linha do arquivo
        
        if(nLinha != 0){
            PegaInformacoes( bufferLinha, nLinha);
        }
        nLinha++;
    }
    fclose(arquivo);
}

void PegaInformacoes( char linha[], int nLinha){
    //Separa os itens da string que estão separados por vírgula
    // printf("%s", linha);
    int mLinha = nLinha - 1;
    int letra = 0, comecaPalavra = 0;

    while (linha[letra] != '\n')
    {
        // if(linha[letra] == ',')
        if(letra == 10)
        {
            char word[letra-comecaPalavra];
            for(int i = comecaPalavra; i < letra; i++) {
                word[i - comecaPalavra] = linha[i];
            }
            
            strcpy(DCD[mLinha].DataCadastro, word);
            printf("%s\n", DCD[mLinha].DataCadastro);
            comecaPalavra = letra + 1;
        }
        letra++;
    }
}