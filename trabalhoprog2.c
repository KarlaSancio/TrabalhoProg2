#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxLinhas 10
#define maxColunas 12

typedef struct Municipio
{
    int Casos;
    char Nome[30];
}tMun;

typedef struct DadosCidadeData
{
    char DataCadastro[30];
    int DataCadastroAno;
    int DataCadastroMes;
    int DataCadastroDia;
    char DataObito[30];
    int DataObitoAno;
    int DataObitoMes;
    int DataObitoDia;
    char Classificacao[30];
    tMun Municipio;
    char IdadeNaDataNotificacao[30];
    char IdadeAno[30];
    char IdadeMes[30];
    char IdadeDia[30];
    char ComorbidadePulmao[30];
    char ComorbidadeCardio[30];
    char ComorbidadeRenal[30];
    char ComorbidadeDiabetes[30];
    char ComorbidadeTabagismo[30];
    char ComorbidadeObesidade[30];
    char FicouInternado[30];
}tDCD;

tDCD DCD[maxLinhas]; //variavel que guarda as informacoes

void LeArquivo();
void PegaInformacoesDaLinha(char linha[], int cont);
void TransformaDatas();
void ListaCidadesComNCasos();

int main(){
   
    LeArquivo();

    ListaCidadesComNCasos();
    
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
        DCD[nLinha].Municipio.Nome,
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
            DCD[nLinha].Municipio.Nome,
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
            DCD[nLinha].Municipio.Nome,
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

void TransformaDatas(){ // Filtro de datas
    int nLinha = 1;
    while (nLinha <= maxLinhas)
    {
        sscanf(DCD[nLinha].DataCadastro, "%d-%d-%d", 
        &DCD[nLinha].DataCadastroAno, 
        &DCD[nLinha].DataCadastroMes, 
        &DCD[nLinha].DataCadastroDia
        );
        
        nLinha++;
    }

    int nLinha = 1;
    while (nLinha <= maxLinhas)
    {
        sscanf(DCD[nLinha].DataObito, "%d-%d-%d", 
        &DCD[nLinha].DataObitoAno, 
        &DCD[nLinha].DataObitoMes, 
        &DCD[nLinha].DataObitoDia
        );
        
        nLinha++;
    }
}

void ListaCidadesComNCasos(){

    int N, i;
    
    char Comparador[15] = "Confirmados";

    // scanf("%d",&N);

    for (i = 0; i <= maxLinhas; i++){

        if(strcmp(Comparador,DCD[i].Classificacao)==0){       
            DCD[i].Municipio.Casos ++;
            printf("%d_%s\n",DCD[i].Municipio.Casos,DCD[i].Municipio.Nome);
        }

        

    }
    
}