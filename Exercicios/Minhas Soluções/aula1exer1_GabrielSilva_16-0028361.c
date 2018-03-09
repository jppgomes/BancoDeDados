#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PLACA 10
#define MAX_MODELOECOR 15
#define MAX_NOME 30
#define MAX_CPF 13

typedef struct carro{
    char placa[MAX_PLACA];
    char modelo[MAX_MODELOECOR];
    char cor[MAX_MODELOECOR];
    struct carro* prox;
}carro;

typedef struct pessoa{
    char nome[MAX_NOME];
    char cpf[MAX_CPF];
    int carrosPossuidos;
    struct carro* carros;
    struct pessoa* prox;
}pessoa;

int main(){
    pessoa* cadastrarPessoa(pessoa* novaPessoa, pessoa* pessoas);
    pessoa* lerDadosPessoa();
    void mostrarPessoas(pessoa* pessoas);
    pessoa* lerDadosArquivo();
    void escreverDadosArquivo(pessoa* pessoas);

    pessoa* pessoas, *novaPessoa;

    pessoas = lerDadosArquivo();
    int opcao;
    do{
        printf("0 - Sair\n1 - Cadastrar pessoa\n2 - Mostrar registros\n\nOpcao: ");
        scanf("%d", &opcao);
        switch(opcao){
        case 1:
            novaPessoa = lerDadosPessoa();
            pessoas = cadastrarPessoa(novaPessoa, pessoas);
            escreverDadosArquivo(pessoas);
            break;
        case 2:
            mostrarPessoas(pessoas);
            break;
        }
    }while(opcao != 0);


}

pessoa* cadastrarPessoa(pessoa* novaPessoa, pessoa* pessoas){
    if(pessoas != NULL){
        novaPessoa->prox = pessoas;
    }
    return novaPessoa;
}

pessoa* lerDadosPessoa(){
    carro* cadastrarCarro(carro* carros, int carroAtual);

    pessoa* novaPessoa = malloc(sizeof(pessoa));
    fflush(stdin);
    printf("Nome: ");
    fgets(novaPessoa->nome, MAX_NOME, stdin);
    novaPessoa->nome[strlen(novaPessoa->nome)-1] = '\0';
    printf("CPF: ");
    fgets(novaPessoa->cpf, MAX_CPF, stdin);
    novaPessoa->cpf[strlen(novaPessoa->cpf)-1] = '\0';
    printf("Nro de carros: ");
    novaPessoa->prox = NULL;
    novaPessoa->carros = NULL;
    fflush(stdin);
    scanf("%d", &novaPessoa->carrosPossuidos);
    for(int contador = 0; contador < novaPessoa->carrosPossuidos; contador++){
        novaPessoa->carros = cadastrarCarro(novaPessoa->carros, contador+1);
    }
    return novaPessoa;
}

carro* cadastrarCarro(carro* carros, int carroAtual){
    carro* novoCarro = malloc(sizeof(carro));
    fflush(stdin);
    printf("Modelo do %d carro: ", carroAtual);
    fgets(novoCarro->modelo, MAX_MODELOECOR, stdin);
    novoCarro->modelo[strlen(novoCarro->modelo)-1] = '\0';
    printf("Cor do %d carro: ", carroAtual);
    fgets(novoCarro->cor, MAX_MODELOECOR, stdin);
    novoCarro->cor[strlen(novoCarro->cor)-1] = '\0';
    printf("Placa do %d carro: ", carroAtual);
    fgets(novoCarro->placa, MAX_PLACA, stdin);
    novoCarro->placa[strlen(novoCarro->placa)-1] = '\0';
    novoCarro->prox = NULL;
    if(carros != NULL){
        novoCarro->prox = carros;
    }
    return novoCarro;
}

void mostrarPessoas(pessoa* pessoas){
    pessoa* pessoaAtual = pessoas;
    carro* carroAtual = NULL;
    while(pessoaAtual != NULL){
        for(int contador = 0; contador < 30; contador++){
            printf("_");
        }
        printf("\nNome: %s\tCPF: %s\t Nro de carros: %d\n\n", pessoaAtual->nome, pessoaAtual->cpf, pessoaAtual->carrosPossuidos);
        carroAtual = pessoaAtual->carros;
        while(carroAtual != NULL){
            printf("Placa: %s\tModelo: %s %s\n", carroAtual->placa, carroAtual->modelo, carroAtual->cor);
            carroAtual = carroAtual->prox;
        }
        pessoaAtual = pessoaAtual->prox;
    }
    if(pessoas != NULL){
        for(int contador = 0; contador < 30; contador++){
            printf("_");
        }
        printf("\n");
    }
    else{
        printf("\nNao ha pessoas cadastradas!\n\n");
    }
}

void escreverDadosArquivo(pessoa* pessoas){
    pessoa* pessoaAtual = pessoas;
    carro* carroAtual;

    FILE* arquivo = fopen("dados.bin", "w+");

    while(pessoaAtual != NULL){
        fwrite(pessoaAtual, sizeof(pessoa), 1, arquivo);
        carroAtual = pessoaAtual->carros;
        while(carroAtual != NULL){
            fwrite(carroAtual, sizeof(carro), 1, arquivo);
            carroAtual = carroAtual->prox;
        }
        pessoaAtual = pessoaAtual->prox;
    }
    fclose(arquivo);
}

pessoa* lerDadosArquivo(){
    pessoa* pessoas = NULL, *novaPessoa;

    FILE* arquivo = fopen("dados.bin", "r+");
    novaPessoa = malloc(sizeof(pessoa));

    if(arquivo != NULL){
        while(fread((void*)novaPessoa, sizeof(pessoa), 1, arquivo)){
            novaPessoa->prox = NULL;
            novaPessoa->carros = NULL;
            for(int contador = 0; contador < novaPessoa->carrosPossuidos; contador++){
                carro* novoCarro = malloc(sizeof(carro));
                fread((void*)novoCarro, sizeof(carro), 1, arquivo);
                if(novaPessoa->carros != NULL){
                    novoCarro->prox = novaPessoa->carros;
                }
                else{
                    novoCarro->prox = NULL;
                }
                novaPessoa->carros = novoCarro;
            }
            if(pessoas != NULL){
                novaPessoa->prox = pessoas;
            }
            pessoas = novaPessoa;
            novaPessoa = malloc(sizeof(pessoa));
        }
        fclose(arquivo);
    }
    return pessoas;
}

