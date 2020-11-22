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

struct Data
{
	int dia;
	int mes;
	int ano;
};

typedef struct Data dt;

//Declaração das funções
void LeArquivo();
void PegaInformacoes(char *buffer);
void FiltroDatas(char data[10]);
int QtdCasos(dados data);
void ListaCidadesTopCasos(dados data, dados municipio);

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
    FILE* arquivo2 = fopen("foi.txt", "w");
    //Separa os itens da string que estão separados por vírgula
    char *item = strtok(buffer, ",");

    while(item !=  NULL){
        cont++;
        fprintf(arquivo2, " %s\n",item);
        item = strtok(NULL, ",");
    }
    fclose(arquivo2);
}

void FiltroDatas(char data[10]){
    // 0, 1 = dia
	// 2    = -
	// 3, 4 = mes
	// 5    = -
	// 6, 7 = ano
	// 8    = NULO

    int dia, mes , ano;

    char _dia[3] = {
        data[0],
        data[1],
        0
    };

    char _mes[3] = {
        data[3],
        data[4],
        0
    };

    char _ano[3] = {
        data[6],
        data[7],
        0
    };

    dia = atoi(_dia);
    mes = atoi(_mes);
    ano = atoi(_ano);

    printf("dia: %d", dia);
    printf("mes: %d", mes);
    printf("ano: %d", ano);
}


int main(){
    char data[10];

    scanf("%s", &data[10]);

    //LeArquivo();
    FiltroDatas(data);


    return 0;
}