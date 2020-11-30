#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// #define maxLinhas 20
#define maxLinhas 202363
#define maxColunas 12
#define qtdMunicipiosES 78

typedef struct Municipio// "lista" ods municípios do ES
{
    int Casos;
    char Nome[30];
    int vetorNulo;

}tMun;

typedef struct DadosCidadeData//"tabela" que guarda as informacoes
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

typedef struct Data// struct para o filtro de data
{
    int dia;
    int mes;
    int ano;
}tData;

tDCD DCD[maxLinhas];
tMun CasosPorMunicipio[qtdMunicipiosES];

void LeArquivo();
void TransformaDatas();
void ListaCasosPorMunicipio();
void QtdCasosEntreDatas();
tData FiltroDeDatas(char data[]);
int NumeroDeDias(int N);
void Porcentagens();

int main()
{

    LeArquivo();
    // ListaCasosPorMunicipio();
    TransformaDatas();
    //QtdCasosEntreDatas();
    Porcentagens();
    
    return 0;
}

void LeArquivo()// abre, le o arquivo em uma struct, e fecha o arquivo
{
    FILE *arquivo = fopen("covid19ES.csv", "r");
    int nLinha = 0;

    if(arquivo==NULL)
    {
        printf("Error\n");
        exit (1);
    } 
    
    // fscnf para ler o cabeçalho
    fscanf(arquivo, "%[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^\n]\n",DCD[nLinha].DataCadastro,DCD[nLinha].DataObito,DCD[nLinha].Classificacao,DCD[nLinha].Municipio,DCD[nLinha].IdadeNaDataNotificacao,DCD[nLinha].ComorbidadePulmao,DCD[nLinha].ComorbidadeCardio,DCD[nLinha].ComorbidadeRenal,DCD[nLinha].ComorbidadeDiabetes,DCD[nLinha].ComorbidadeTabagismo,DCD[nLinha].ComorbidadeObesidade,DCD[nLinha].FicouInternado);
    nLinha++;

    while (fscanf(arquivo, "%[^,], %[^,], %[^,], %[^,], \"%[^\"]\", %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^\n]\n",DCD[nLinha].DataCadastro,DCD[nLinha].DataObito,DCD[nLinha].Classificacao,DCD[nLinha].Municipio,DCD[nLinha].IdadeNaDataNotificacao,DCD[nLinha].ComorbidadePulmao,DCD[nLinha].ComorbidadeCardio,DCD[nLinha].ComorbidadeRenal,DCD[nLinha].ComorbidadeDiabetes,DCD[nLinha].ComorbidadeTabagismo,DCD[nLinha].ComorbidadeObesidade,DCD[nLinha].FicouInternado) != EOF)
    {
        nLinha++;
    }
    fclose(arquivo);
}

void TransformaDatas()// Filtro de datas
{ 
    int nLinha = 1;
    while (nLinha <= maxLinhas)
    {
        sscanf(DCD[nLinha].DataCadastro, "%d-%d-%d",&DCD[nLinha].DataCadastroAno,&DCD[nLinha].DataCadastroMes,&DCD[nLinha].DataCadastroDia); 
        nLinha++;
    }

    nLinha = 1;
    while (nLinha <= maxLinhas)
    {
        sscanf(DCD[nLinha].DataObito, "%d-%d-%d", &DCD[nLinha].DataObitoAno, &DCD[nLinha].DataObitoMes, &DCD[nLinha].DataObitoDia); 
        nLinha++;
    }

}

void ListaCasosPorMunicipio()// Lista em ordem alfabetica cidades com mais de N casos
{

    int i=0,j=0,k=0;

    // preenche lista vazia
    for (i = 0; i < qtdMunicipiosES; i++)
    {
        strcpy(CasosPorMunicipio[i].Nome, "\0");
        CasosPorMunicipio[i].Casos = 0;
        CasosPorMunicipio[i].vetorNulo = 0;
    }

    //preenche lista com tds municipios
   for (i = 1; i <= maxLinhas; i++)
   {
        int jaExiste = 0;
        for (j = 0; j < qtdMunicipiosES; j++)
        {
            if(strcmp(CasosPorMunicipio[j].Nome, DCD[i].Municipio) == 0)
            {
                jaExiste = 1;
            }
            if(CasosPorMunicipio[j].vetorNulo == 0 && jaExiste == 0)
            {
               strcpy(CasosPorMunicipio[j].Nome, DCD[i].Municipio); 
               CasosPorMunicipio[j].vetorNulo++; 
               break;
            }
        }
    }
    // conta casos das cidades
    for (i = 1; i <= maxLinhas; i++)
    {
        if(DCD[i].Classificacao[0]=='C')
        {     
            for (j = 0; j < qtdMunicipiosES; j++)
            {
                if (strcmp(DCD[i].Municipio, CasosPorMunicipio[j].Nome)==0)
                {
                    CasosPorMunicipio[j].Casos++;
                    break;
                }
            }
        }
    }

    for ( i = 0; i < qtdMunicipiosES; i++)
    {
        printf("%s-%d\n",CasosPorMunicipio[i].Nome,CasosPorMunicipio[i].Casos);
    }
}

void QtdCasosEntreDatas()// informa a qtd de casos entre duas datas, d1 e d2
{
    char d1[11], d2[11];
    tData dataInicio;
    tData dataFinal;
    int contaCasos = 0;

    scanf("%s %s", d1, d2);

    dataInicio = FiltroDeDatas(d1);
    dataFinal = FiltroDeDatas(d2);

    for(int nLinha = 1; nLinha <= maxLinhas; nLinha++)
    {
        int dia = dataInicio.dia;
        for(int mes = dataInicio.mes; mes <= dataFinal.mes; mes++)
        {
            int maxDia = NumeroDeDias(mes);
            if(mes == dataFinal.mes)
            {
                maxDia = dataFinal.dia;
            }
            while (dia <= maxDia)
            {
                if(DCD[nLinha].DataCadastroMes == mes && DCD[nLinha].DataCadastroDia == dia && DCD[nLinha].Classificacao[0] == 'C')
                {
                    contaCasos++;
                }
                dia++;
            }
            dia = 1;            
        }
    }
    printf("%d\n", contaCasos);
}

tData FiltroDeDatas(char data[])// transforma datas em informacao comparavel
{ 
    tData resData;
    sscanf(data, "%d-%d-%d", &resData.ano, &resData.mes, &resData.dia);
    return resData;
}

int NumeroDeDias(int N)// padroniza o final dos meses
{ 
    if (N == 1 || N == 3 || N == 5 || N == 7 || N == 8 || N == 10 || N == 12)
    { 
        return 31;
    } 
  
    else if (N == 4 || N == 6 || N == 9 || N == 11)
    { 
        return 30;
    } 
  
    else if (N == 2)
    { 
        return 28;
    }
}

void Porcentagens()// determina % de internados, e mortes decorrentes das internacoes
{
    char comando[30];

    scanf("%s", comando);

    int nLinha, qtdInternadoComCovid = 0, qtdMorreramComCovid = 0, qtdInternadoMorreu = 0, qtdConfirmados = 0, mortes = 0;
    float porcentagemInternadas = 0.0, porcentagemMorreram = 0.0, porcentagemInternadasMorreram = 0.0;

    if(strcmp(comando, "TODAS") == 0)
    {
        for(nLinha = 1; nLinha <= maxLinhas; nLinha++)
        { 
            if(strcmp(DCD[nLinha].Classificacao, "Confirmados") == 0)
            {
                qtdConfirmados++;
                if(strcmp(DCD[nLinha].FicouInternado, "Sim") == 0)
                {
                    qtdInternadoComCovid++;
                }
                if(strcmp(DCD[nLinha].DataObito, "0000-00-00") != 0)
                {
                    qtdMorreramComCovid++;
                }

                if(strcmp(DCD[nLinha].DataObito, "0000-00-00") != 0)
                {
                    mortes++;
                    if(strcmp(DCD[nLinha].FicouInternado, "Sim") == 0)
                    {
                        qtdInternadoMorreu++;
                    }
                }
            }
        }    
    }

    porcentagemInternadas =  ((float) qtdInternadoComCovid/(float) qtdConfirmados) * 100.0;
    porcentagemMorreram =  ((float) qtdMorreramComCovid/(float) qtdConfirmados) * 100.0;
    porcentagemInternadasMorreram =  ((float) qtdInternadoMorreu/(float) mortes) * 100.0;

    printf("%.3f\n", porcentagemInternadas);
    printf("%.3f\n", porcentagemMorreram);
    printf("%.3f\n", porcentagemInternadasMorreram);
    
}