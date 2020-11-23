#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max 12


typedef struct Dados
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

};

typedef struct Dados dados;

struct Data
{
	int dia;
	int mes;
	int ano;
};

typedef struct Data dt;

//Declaração das funções
//Declaração das funções
void LeArquivo(dados *dados[], int tam);
void PegaInformacoes(char *buffer, dados *dados[], int tam, FILE * arquivo);
intFiltroDatas(dados data[10]);
int QtdCasos(dados data);
void ListaCidadesTopCasos(dados data, dados municipio);

void LeArquivo(dados *dados[], int tam){
    FILE *arquivo = fopen("covid19ES.csv", "r");
    int cont = 0, i;


    if(arquivo==NULL){
        printf("Error\n");
        exit (1);
    }

    do //Lê o conteúdo do arquivo enquanto há algo para ser lido(até o fim do arquivo)
    {
        char buffer[202363];//qtd de linhas do arquivo
        fgets(buffer, 202363, (FILE*)arquivo);// pegando as strings de cada linha do arquivo
        cont++;

        if(cont != 1){
            //printf("%s", buffer);
            PegaInformacoes(buffer, dados, tam, arquivo);
            
        }

    } while ((getc(arquivo)) != EOF);

    
    
    fclose(arquivo);
}

void PegaInformacoes(char buffer[], dados *dados[], int tam, FILE * arquivo){
    int cont = 0, i;
    //Separa os itens da string que estão separados por vírgula
    char *item = strtok(buffer, ",");

    while(item !=  NULL){
        cont++;
        //fprintf(arquivo2, " %s\n",item);
        // Armazena as informações do arquivo dentro dos vetores das structs
        for(i = 0; i <tam; i++){
            fscanf(arquivo,"%s%s%s%s%s%s%s%s%s%s%s%s\n", &dados[i]->DataCadastro[10], &dados[i]->DataObito[10],
                    &dados[i]->Classificacao[11], &dados[i]->Municipio[30], &dados[i]->IdadeNaDataNotificacao[30], &dados[i]->ComorbidadePulmao[3],
                    &dados[i]->ComorbidadeCardio[3], &dados[i]->ComorbidadeRenal[3], &dados[i]->ComorbidadeDiabetes[3], &dados[i]->ComorbidadeTabagismo[3],
                    &dados[i]->ComorbidadeObesidade[3], &dados[i]->FicouInternado[13]);
        }
        item = strtok(NULL, ",");
    }
    for(i = 0; i < tam; i++){
        printf("data: %s", dados[i]->DataCadastro);
    }
}

int FiltroDatas(dados DataCadastro[10]){
    
    int i,j;
    dt filtro[10];

    for (j=0, i = 0; i < 4; i++, j++){
        filtro[j].ano = DataCadastro[i];
    }
        
    for (j=6, i = 6; i <= 7; i++,j++){
        filtro[j].mes = DataCadastro[i];
    }
        
    for (j=9, i = 9; i <= 10 ; i++,j++){
        filtro[j].dia = DataCadastro[i];
    }
    
    
    
    
}


int main(){
    dados *dates[max];
    int max_size = max;
    char data[10];

    scanf("%s", &data[10]);

    LeArquivo(dates, max_size);
    FiltroDatas(data);


    return 0;
}