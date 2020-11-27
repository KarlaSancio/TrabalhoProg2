#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define maxLinhas 10
#define maxLinhas 202363
#define maxColunas 12
#define qtdMunicipiosES 78

// "lista" ods municípios do ES
typedef struct Municipio
{
    int Casos;
    char Nome[30];
}tMun;
tMun CasosPorMunicipio[qtdMunicipiosES];

//"tabela" que guarda as informacoes
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
tDCD DCD[maxLinhas]; 

typedef struct Data
{
    int dia;
    int mes;
    int ano;
}tData;

void LeArquivo();
void TransformaDatas();
void ListaCasosPorMunicipio();
void QtdCasosEntreDatas();
tData FiltroDeDatas(char data[]);
int NumberOfDays(int N) ;

int main(){
   
    LeArquivo();
    // ListaCasosPorMunicipio();
    TransformaDatas();
    QtdCasosEntreDatas();
    
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

        //  printf("%s %s %s %s %s %s %s %s %s %s %s %s\n", 
        //      DCD[nLinha].DataCadastro,
        //      DCD[nLinha].DataObito,
        //      DCD[nLinha].Classificacao,
        //      DCD[nLinha].Municipio,
        //      DCD[nLinha].IdadeNaDataNotificacao,
        //      DCD[nLinha].ComorbidadePulmao,
        //      DCD[nLinha].ComorbidadeCardio,
        //      DCD[nLinha].ComorbidadeRenal,
        //      DCD[nLinha].ComorbidadeDiabetes,
        //      DCD[nLinha].ComorbidadeTabagismo,
        //      DCD[nLinha].ComorbidadeObesidade,
        //      DCD[nLinha].FicouInternado
        //      );
        //   printf("\n");
        nLinha++;
    }
    fclose(arquivo);
}

// Filtro de datas
void TransformaDatas(){ 
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

    nLinha = 1;
    while (nLinha <= maxLinhas)
    {
        sscanf(DCD[nLinha].DataObito, "%d-%d-%d", 
        &DCD[nLinha].DataObitoAno, 
        &DCD[nLinha].DataObitoMes, 
        &DCD[nLinha].DataObitoDia
        );
        
        nLinha++;
    }

    // nLinha = 1;
    // while (nLinha <= maxLinhas)
    // {
    //     printf("%d,%d,%d - - - %d,%d,%d\n", DCD[nLinha].DataCadastroAno, DCD[nLinha].DataCadastroMes, DCD[nLinha].DataCadastroDia, 
    //     DCD[nLinha].DataObitoAno, DCD[nLinha].DataObitoMes, DCD[nLinha].DataObitoDia);
    //     nLinha++;
    // }
}

void ListaCasosPorMunicipio(){

    int i=0;

    // preenche lista vazia
    for (int k = 0; k < qtdMunicipiosES; k++)
    {
        strcpy(CasosPorMunicipio[k].Nome, "\0");
        CasosPorMunicipio[k].Casos = 0;
    }
    
    // acha cidades
    int jaexisteomuninicipio;
    for (int i = 1; i <= maxLinhas; i++){
        jaexisteomuninicipio = 0;
        for (int j = 0; j < qtdMunicipiosES; j++){
            char var1[30];
            char var2[30];
            strcpy(var1, DCD[i].Municipio);
            strcpy(var2, CasosPorMunicipio[j].Nome);
            if (strcmp(var1, var2)==0){
                jaexisteomuninicipio = 1;
                j = qtdMunicipiosES;
            }
        }
        if (jaexisteomuninicipio == 0)
        {
            for (int w = 0; w < qtdMunicipiosES; w++)
            {
                if (strcmp(CasosPorMunicipio[w].Nome, "\0")<0)
                {
                    strcpy(CasosPorMunicipio[w].Nome, DCD[i].Municipio);
                    w = qtdMunicipiosES;
                }
            }
        }
    }

    // inicio metodo bolha
    // tMun municipioTemporario;
    // for (int k = 0; k < qtdMunicipiosES-1; k++){
    //     for (int j = k + 1; j < qtdMunicipiosES; j++){ 
    //         if(strcmp(CasosPorMunicipio[j].Nome, CasosPorMunicipio[k].Nome) > 0){
    //             strcpy(municipioTemporario.Nome, CasosPorMunicipio[j].Nome);
    //             strcpy(CasosPorMunicipio[k].Nome, CasosPorMunicipio[j].Nome);
    //             strcpy(CasosPorMunicipio[j].Nome, municipioTemporario.Nome);
    //         }
    //     }
    // }
    // fim metodo bolha

    // marca casos por cidade
    for (i = 1; i <= maxLinhas; i++){
        if(strcmp("Confirmados",DCD[i].Classificacao)==0){     
            for (int j = 0; j < qtdMunicipiosES; j++){
                if (strcmp(DCD[i].Municipio, CasosPorMunicipio[j].Nome)==0){
                    CasosPorMunicipio[j].Casos++;
                }
            }
        }
    }

    for ( i = 0; i <= maxLinhas; i++){
        printf("%s-%d",CasosPorMunicipio[i].Nome,CasosPorMunicipio[i].Casos);
    }
}

void QtdCasosEntreDatas(){
    char d1[11], d2[11];
    tData dataInicio;
    tData dataFinal;
    int contaCasos = 0;

    scanf("%s %s", d1, d2);

    dataInicio = FiltroDeDatas(d1);
    dataFinal = FiltroDeDatas(d2);

    // printf("Ano Inicio: %d, Mes Inicio: %d, Dia Inicio: %d, Ano Final: %d, Mes Final: %d, Dia Final: %d\n", 
    // dataInicio.ano, dataInicio.mes, dataInicio.dia, dataFinal.ano, dataFinal.mes, dataFinal.dia);

    for(int nLinha = 1; nLinha <= maxLinhas; nLinha++){
        int dia = dataInicio.dia;
        for(int mes = dataInicio.mes; mes <= dataFinal.mes; mes++){
            int maxDia = NumberOfDays(mes);
            if(mes == dataFinal.mes){
                maxDia = dataFinal.dia;
            }
            while (dia <= maxDia)
            {
                if(DCD[nLinha].DataCadastroMes == mes &&
                DCD[nLinha].DataCadastroDia == dia &&
                DCD[nLinha].Classificacao[0] == 'C'){
                    contaCasos++;
                }
                dia++;
            }
            dia = 1;            
        }
    }
    printf("%d\n", contaCasos);
}

tData FiltroDeDatas(char data[]){ 
    tData resData;
    sscanf(data, "%d-%d-%d", &resData.ano, &resData.mes, &resData.dia);
    return resData;
}

int NumberOfDays(int N){ 
    if (N == 1 || N == 3 || N == 5 
        || N == 7 || N == 8 || N == 10 
        || N == 12) { 
        return 31;
    } 
  
    else if (N == 4 || N == 6 
             || N == 9 || N == 11) { 
        return 30;
    } 
  
    else if (N == 2) { 
        return 28;
    }
}