#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>

// define maximo de linhas e quantidade de muncipios
#define maxLinhas 202363
#define qtdMunicipiosES 78

typedef struct Municipio// "lista" dos municípios do ES
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

// declaracao das funcoes
void LeArquivo();
void TransformaDatas();
void ListaCasosPorMunicipio(char diretorio[]);
void QtdCasosEntreDatas(char diretorio[]);
tData FiltroDeDatas(char data[]);
int NumeroDeDias(int N);
void ListaTopN(char diretorio[]);
void Porcentagens(char diretorio[]);
void MediaIdade(char diretorio[]);

int main()
{
    char  diretorio[40];
    scanf("%s", diretorio);

    mkdir(diretorio, 0777);// Cria a pasta de teste, onde serao impressas as saidas dos itens de 3 a 7

    // chamada das funcoes
    LeArquivo();
    TransformaDatas();
    ListaCasosPorMunicipio(diretorio);
    QtdCasosEntreDatas(diretorio);
    ListaTopN(diretorio);
    Porcentagens(diretorio);
    MediaIdade(diretorio);
    
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

void TransformaDatas()// Filtro de datas da struct principal
{ 
    int nLinha = 1;
    while (nLinha <= maxLinhas)// armazenamento da data de cadastro (transforma em uma informacao comparavel)
    {
        sscanf(DCD[nLinha].DataCadastro, "%d-%d-%d",&DCD[nLinha].DataCadastroAno,&DCD[nLinha].DataCadastroMes,&DCD[nLinha].DataCadastroDia); 
        nLinha++;
    }

    nLinha = 1;
    while (nLinha <= maxLinhas)// armazenamento da data de obito (transforma em uma informacao comparavel)
    {
        sscanf(DCD[nLinha].DataObito, "%d-%d-%d", &DCD[nLinha].DataObitoAno, &DCD[nLinha].DataObitoMes, &DCD[nLinha].DataObitoDia); 
        nLinha++;
    }

}

void ListaCasosPorMunicipio(char diretorio[])// Lista em ordem alfabetica cidades com mais de N casos
{
    char diret[40];
    strcpy(diret, diretorio);

    int i=0, j=0, N;
    char temporario[30];
    int casosTemporario;

    scanf("%d",&N);// leitura do minimo de casos pra entrar na lista 

    for (i = 0; i < qtdMunicipiosES; i++)// preenche lista vazia
    {
        strcpy(CasosPorMunicipio[i].Nome, "\0");
        CasosPorMunicipio[i].Casos = 0;
        CasosPorMunicipio[i].vetorNulo = 0;
    }
    
    for (i = 1; i <= maxLinhas; i++)//preenche lista com tds municipios
    {
        int jaExiste = 0;
        for (j = 0; j < qtdMunicipiosES; j++)// preenche os 78 municipios 
        {
            if(strcmp(CasosPorMunicipio[j].Nome, DCD[i].Municipio) == 0) // verifica se a cidade ja esta na lista
            {
                jaExiste = 1;
            }
            if(CasosPorMunicipio[j].vetorNulo == 0 && jaExiste == 0) // se a cidade nao existe na lista, ela eh adicionada na lista
            {
               strcpy(CasosPorMunicipio[j].Nome, DCD[i].Municipio); 
               CasosPorMunicipio[j].vetorNulo++; 
               break;
            }
        }
    }
    for (i = 1; i <= maxLinhas; i++)// conta casos das cidades
    {
        if(strcmp(DCD[i].Classificacao,"Confirmados") == 0) // verfica apenas os casos confirmados de covid
        {     
            for (j = 0; j < qtdMunicipiosES; j++) // contar os casos no municipio correspondente
            {
                if (strcmp(DCD[i].Municipio, CasosPorMunicipio[j].Nome) == 0)
                {
                    CasosPorMunicipio[j].Casos++;
                }
            }
        }
    }
    for (i = 0; i < qtdMunicipiosES-1; i++)//Bubble Sort
    {
        for (j = i+1; j < qtdMunicipiosES; j++)
        {
            if (strcmp(CasosPorMunicipio[i].Nome,CasosPorMunicipio[j].Nome) > 0)
            {
                //copia os nomes dos municipios 
                strcpy(temporario,CasosPorMunicipio[i].Nome);
                strcpy(CasosPorMunicipio[i].Nome,CasosPorMunicipio[j].Nome);
                strcpy(CasosPorMunicipio[j].Nome,temporario);
                //copia os valores de casos
                casosTemporario = CasosPorMunicipio[i].Casos;
                CasosPorMunicipio[i].Casos = CasosPorMunicipio[j].Casos;
                CasosPorMunicipio[j].Casos = casosTemporario;
            }
            
        }
        
    }

    // cria o arquivo com as saidas correspondentes ao item 3
    strcat(diret, "item3.txt");
    FILE *dir =  fopen(diret, "w");
    
    for (i = 0; i < qtdMunicipiosES; i++)// imprime cidades acima de N
    {
        if(CasosPorMunicipio[i].Casos > N)
        fprintf(dir,"- %s: %d casos\n",CasosPorMunicipio[i].Nome,CasosPorMunicipio[i].Casos);
    }


    fclose(dir);
}

void QtdCasosEntreDatas(char diretorio[])// informa a qtd de casos confirmados entre duas datas, d1 e d2
{
    char diret[40];
    strcpy(diret, diretorio);

    char d1[11], d2[11];
    tData dataInicio;
    tData dataFinal;
    int contaCasos = 0;

    scanf("%s %s", d1, d2); // leitura das datas

    // transforma as datas em uma informacao comparavel
    dataInicio = FiltroDeDatas(d1);
    dataFinal = FiltroDeDatas(d2);

    for(int nLinha = 1; nLinha <= maxLinhas; nLinha++)// varredura das linhas
    {
        int dia = dataInicio.dia; // setando o comeco do dia
        for(int mes = dataInicio.mes; mes <= dataFinal.mes; mes++) // varredura entra as datas a partir do mes inicial ate o final
        {
            int maxDia = NumeroDeDias(mes);// verifica o ultimo dia do mes (30 ou 31)
            if(mes == dataFinal.mes) // se o mes das duas entradas eh o mesmo, o valor maximo de dias eh o dia final do mes
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

    // cria o arquivo com as saidas correspondentes ao item 4
    strcat(diret, "item4.txt");
    FILE *dir =  fopen(diret, "w");

    fprintf(dir,"- Total de pessoas: %d", contaCasos); // print com o total de pessoas que tiveram covid nesse periodo

    fclose(dir);

}

tData FiltroDeDatas(char data[])// transforma datas(do input) em informacao comparavel
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

void ListaTopN(char diretorio[]){// lista top de N casos entre as datas informadas

    char diret[40];
    strcpy(diret, diretorio);

    int N, i, j, casosTemporario = 0;
    char d1[11], d2[11], temporario[30];
    tData dataInicio, dataFinal;


    scanf("%d",&N);
    scanf("%s %s", d1, d2);

    dataInicio = FiltroDeDatas(d1);
    dataFinal = FiltroDeDatas(d2);
 
    for (i = 0; i < qtdMunicipiosES; i++)// preenche lista vazia
    {
        strcpy(CasosPorMunicipio[i].Nome, "\0");
        CasosPorMunicipio[i].Casos = 0;
        CasosPorMunicipio[i].vetorNulo = 0;
    }

    for (i = 1; i <= maxLinhas; i++)//preenche lista com todos os municipios
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

    for(int nLinha = 1; nLinha <= maxLinhas; nLinha++)//contador de casos com base nas datas
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
                    for ( i = 0; i < qtdMunicipiosES; i++)
                    {
                        if (strcmp(DCD[nLinha].Municipio,CasosPorMunicipio[i].Nome) == 0)
                        {
                            CasosPorMunicipio[i].Casos++;
                        }
                    }
                }
                dia++;
            }
            dia = 1;            
        }
    }

    for (i = 0; i < qtdMunicipiosES-1; i++)// bubble sort para por em ordem decrescente
    {
        for (j = 0; j < qtdMunicipiosES; j++)
        {
            if( CasosPorMunicipio[i].Casos > CasosPorMunicipio[j].Casos)
            {
                casosTemporario = CasosPorMunicipio[i].Casos;
                CasosPorMunicipio[i].Casos = CasosPorMunicipio[j].Casos;
                CasosPorMunicipio[j].Casos = casosTemporario;

                strcpy(temporario,CasosPorMunicipio[i].Nome);
                strcpy(CasosPorMunicipio[i].Nome,CasosPorMunicipio[j].Nome);
                strcpy(CasosPorMunicipio[j].Nome,temporario);
            }
        }
        
    }
    
    // cria o arquivo com as saidas correspondentes ao item 5
    strcat(diret, "item5.txt");
    FILE *dir =  fopen(diret, "w");

    for ( i = 0; i < N; i++)//printa os casos em ordem ate o N
    {
        fprintf(dir,"- %s: %d casos\n",CasosPorMunicipio[i].Nome ,CasosPorMunicipio[i].Casos);
    }
    
    fclose(dir);
}

void Porcentagens(char diretorio[])// determina % de internados, e mortes decorrentes das internacoes
{
    char diret[40];
    strcpy(diret, diretorio);

    char comando[30];
    int i = 0;

    scanf("%s", comando);

    for(i = 0; i <= strlen(comando); i++) // transforma a string inteira em maiusculo para a entrada poder ser lida sem importar como ela foi passada no input
    {
      if(comando[i] >= 'a' && comando[i] <= 'z')
      {
        comando[i] = comando[i] - 32;
      }
    }

    int nLinha, qtdInternadoComCovid = 0, qtdMorreramComCovid = 0, qtdInternadoMorreu = 0, qtdConfirmados = 0, mortes = 0;
    float porcentagemInternadas = 0.0, porcentagemMorreram = 0.0, porcentagemInternadasMorreram = 0.0;

    if(strcmp(comando, "TODAS") == 0)// verifica se forem todos os municipios
    {
        for(nLinha = 1; nLinha <= maxLinhas; nLinha++)
        { 
            if(strcmp(DCD[nLinha].Classificacao, "Confirmados") == 0) // conta apenas os casos confirmados
            {
                qtdConfirmados++;
                if(strcmp(DCD[nLinha].FicouInternado, "Sim") == 0) // conta apenas se o individuo ficou internado
                {
                    qtdInternadoComCovid++;
                }
                if(strcmp(DCD[nLinha].DataObito, "0000-00-00") != 0)// conta a quantidade de mortos por covid
                {
                    qtdMorreramComCovid++;
                }

                if(strcmp(DCD[nLinha].DataObito, "0000-00-00") != 0)// conta a quantidade de mortos que ficaram internados
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

    else{
        for(nLinha = 1; nLinha <= maxLinhas; nLinha++)// verifica nos casos de municipios especificos
        { 
            if(strcmp(DCD[nLinha].Classificacao, "Confirmados") == 0 && strcmp(DCD[nLinha].Municipio, comando) == 0)// conta apenas os casos confirmados do municipio correspondente
            {
                qtdConfirmados++;
                if(strcmp(DCD[nLinha].FicouInternado, "Sim") == 0)// conta apenas se o individuo ficou internado
                {
                    qtdInternadoComCovid++;
                }
                if(strcmp(DCD[nLinha].DataObito, "0000-00-00") != 0)// conta a quantidade de mortos por covid
                {
                    qtdMorreramComCovid++;
                }

                if(strcmp(DCD[nLinha].DataObito, "0000-00-00") != 0)// conta a quantidade de mortos que ficaram internados
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

    // cria o arquivo com as saidas correspondentes ao item 6
    strcat(diret, "item6.txt");
    FILE *dir =  fopen(diret, "w");


   
    fprintf(dir,"- Resultados para %s:\n",comando);
    
    // impressao das porcentagens
    fprintf(dir,"- A %c de pessoas com Covid-19 que ficaram internadas: %.3f%c\n", '%', porcentagemInternadas, '%');
    fprintf(dir,"- A %c de pessoas com Covid-19 que morreram: %.3f%c\n", '%', porcentagemMorreram, '%');
    fprintf(dir,"- A %c de pessoas que ficaram internadas e morreram: %.3f%c",'%', porcentagemInternadasMorreram, '%');


    fclose(dir);
    
}

void MediaIdade(char diretorio[]){// calcula media de idade dos mortos, desvio padrao, e porcentagem de mortes sem comorbidades
    char diret[40];
    strcpy(diret, diretorio);

    tData Idade[maxLinhas];
    int i, morreram = 0, qtdSemComorbidades = 0;
    char d1[11], d2[11];
    long double soma = 0.0, desvioPadrao = 0.0, media = 0.0, porcentagemMortesSemComorbidades = 0.0, variancia = 0.0;
    tData dataInicio;
    tData dataFinal;

    scanf("%s %s", d1, d2);

    dataInicio = FiltroDeDatas(d1);
    dataFinal = FiltroDeDatas(d2);

    for ( i = 1; i <= maxLinhas; i++)// separa a idade em dia, mes e ano, pra poder comparar
    {
        sscanf(DCD[i].IdadeNaDataNotificacao,"%d anos,%d meses, %d dias",&Idade[i].ano,&Idade[i].mes,&Idade[i].dia);
    }

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
                if(DCD[nLinha].DataCadastroMes == mes && 
                DCD[nLinha].DataCadastroDia == dia && 
                strcmp(DCD[nLinha].Classificacao, "Confirmados") == 0) // verifica se eh confirmado
                {
                    if(strcmp(DCD[nLinha].DataObito, "0000-00-00") != 0 )// verifica se morreu
                    {
                        morreram++;
                        if(strcmp(DCD[nLinha].ComorbidadePulmao, "Sim") != 0 && strcmp(DCD[nLinha].ComorbidadeCardio, "Sim") != 0 &&
                            strcmp(DCD[nLinha].ComorbidadeRenal, "Sim") != 0 && strcmp(DCD[nLinha].ComorbidadeDiabetes, "Sim") != 0 &&
                            strcmp(DCD[nLinha].ComorbidadeTabagismo, "Sim") != 0 && strcmp(DCD[nLinha].ComorbidadeObesidade, "Sim") != 0 )// verifica se nao tem comorbidades
                        {
                            qtdSemComorbidades++;
                        }
                        soma = soma + (long double) Idade[nLinha].ano; // soma das idades das pessoas que morreram de covid
                    }
                }
                dia++;
            }
            dia = 1;            
        }
    }
    
    media = soma/(long double) morreram;// calcula a media de idade das pessoas que morreram de covid
    porcentagemMortesSemComorbidades = ((long double) qtdSemComorbidades / (long double) morreram) * 100.0; // calculo da porcentagem de pessoas que morreram de covid sem ter nenhuma comorbidade

    for(int nLinha = 1; nLinha <= maxLinhas; nLinha++)//contador apenas para o somatorio pro desvio padrao
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
                if(DCD[nLinha].DataCadastroMes == mes && DCD[nLinha].DataCadastroDia == dia && strcmp(DCD[nLinha].Classificacao, "Confirmados") == 0)
                {
                    if(strcmp(DCD[nLinha].DataObito, "0000-00-00") != 0 ) 
                    {
                        desvioPadrao += pow((long double) Idade[nLinha].ano - media, 2); // somatorio para o calculo do desvio padrao
                    }
                }
                dia++;
            }
            dia = 1;            
        }
    }
    
    variancia = desvioPadrao / (long double)(morreram-1); // calculo da variancia

    // cria o arquivo com as saidas correspondentes ao item 7
    strcat(diret, "item7.txt");
    FILE *dir =  fopen(diret, "w");


    fprintf(dir,"A media e desvio padrao da idade: %.3Lf -- %.3lf\n", media, sqrt(variancia)); // print e calculo do desvio padrao e da media de idades
    fprintf(dir,"A %c de pessoas que morreram sem comorbidade: %.3Lf%c",'%', porcentagemMortesSemComorbidades, '%'); // print da porcentagem de pessoas que morreram de covid sem nenhuma comorbidade

    fclose(dir);
}