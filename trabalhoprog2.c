#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxLinhas 10
#define maxColunas 12
#define qtdMunicipiosES 78

typedef struct Municipio
{
    int Casos;
    char Nome[30];
}tMun;
tMun CasosPorMunicipio[qtdMunicipiosES];

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
    char Municipio[30];
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
void ListaCasosPorMunicipio();

int main(){
   
    LeArquivo();
    printf("%s\n", DCD[maxLinhas].Municipio);
    ListaCasosPorMunicipio();
    
    
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

        // printf("%s %s %s %s %s %s %s %s %s %s %s %s\n", 
        //     DCD[nLinha].DataCadastro,
        //     DCD[nLinha].DataObito,
        //     DCD[nLinha].Classificacao,
        //     DCD[nLinha].Municipio,
        //     DCD[nLinha].IdadeNaDataNotificacao,
        //     DCD[nLinha].ComorbidadePulmao,
        //     DCD[nLinha].ComorbidadeCardio,
        //     DCD[nLinha].ComorbidadeRenal,
        //     DCD[nLinha].ComorbidadeDiabetes,
        //     DCD[nLinha].ComorbidadeTabagismo,
        //     DCD[nLinha].ComorbidadeObesidade,
        //     DCD[nLinha].FicouInternado
        //     );
        //  printf("\n");
        nLinha++;
    }
    
    fclose(arquivo);
}

/*
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
*/

void ListaCasosPorMunicipio(){

    // preenche lista vazia
    // for (int k = 0; k < qtdMunicipiosES; k++)
    // {
    //     strcpy(CasosPorMunicipio[k].Nome, "NULL");
    //     CasosPorMunicipio[k].Casos = 0;
    // }
    
    // acha cidades
    int jaexisteomuninicipio;
    for (int i = 1; i <= maxLinhas; i++)
    {
        jaexisteomuninicipio = 0;
        for (int j = 0; j < qtdMunicipiosES; j++)
        {
            char var1[30];
            char var2[30];
            strcpy(var1, DCD[i].Municipio);
            strcpy(var2, CasosPorMunicipio[j].Nome);
            if (strcmp(var1, var2)==0)
            {
                printf("%s %s\n", var1, var2);
                jaexisteomuninicipio = 1;
                j = qtdMunicipiosES;
            }
        }
        if (jaexisteomuninicipio == 0)
        {
            printf("%s\n", DCD[i].Municipio);
            //for (int w = 0; w < qtdMunicipiosES; w++)
            //{
                //if (strcmp(CasosPorMunicipio[w].Nome, "ZZZZZZZZZZZZZZZZZZZZZZZZ")<0)
                //{
                    //strcpy(CasosPorMunicipio[w].Nome, DCD[i].Municipio);
                    //w = qtdMunicipiosES;
                //}
            //}
        }
    }

    // // inicio metodo bolha
    // tMun municipioTemporario;
    // for (int k = 0; k < (sizeof(CasosPorMunicipio) - 1); k++){
    //     for (int j = k + 1; j < sizeof(CasosPorMunicipio); j++){ 
    //         if(strcmp(CasosPorMunicipio[k].Nome, CasosPorMunicipio[j].Nome)>0){
    //             strcpy(municipioTemporario.Nome, CasosPorMunicipio[k].Nome);
    //             strcpy(CasosPorMunicipio[k].Nome, CasosPorMunicipio[j].Nome);
    //             strcpy(CasosPorMunicipio[j].Nome, municipioTemporario.Nome);
    //         }
    //     }
    // }
    // // fim metodo bolha

    // // marca casos por cidade
    // for (i = 1; i <= maxLinhas; i++){
    //     if(strcmp("Confirmados",DCD[i].Classificacao)==0){     
    //         for (int j = 0; j < sizeof(CasosPorMunicipio); j++)
    //         {
    //             if (strcmp(DCD[i].Municipio, CasosPorMunicipio[j].Nome)==0)
    //             {
    //                 CasosPorMunicipio[j].Casos++;
    //             }
    //         }
    //     }
    // }

    // print de teste da lista
    // for (int k = 0; k < qtdMunicipiosES; k++)
    // {
    //     printf("%s %d\n", CasosPorMunicipio[k].Nome, CasosPorMunicipio[k].Casos);
    // }
}

// pesquisar strcmp NULL