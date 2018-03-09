#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 50

typedef struct {
	char nomeVeiculo[25];
	char cpfDono[12];
	char placa[8];
} veiculo;

typedef struct {
	char nomePessoa[50];
	char cpf[12];
	veiculo Veiculo;
} pessoa;

int menu();
void CadastraNovaPessoa();
void salvarVeiculo(veiculo Veiculo);
void salvarPessoa(pessoa Pessoa); 
void PesquisaPessoa();
void stringCut(char linhaDados[], char cpfEncontrado[]);
void buscaVeiculos(char cpf[]);

int main(void) {
    int opcao=1;
	while (opcao) {
        opcao = menu();
		switch(opcao) {
			case 0:
                printf("Obrigado por utilizar este programa!\n");
                break;

            case 1:
				CadastraNovaPessoa();
				break;

			case 2:
				PesquisaPessoa();
				break;

			default:
				printf("Opção inválida");
		}
	}

	return 0;
}

int menu() {
	int opcao;
	printf("1 - Cadastrar nova pessoa\n");
	printf("2 - Pesquisar por carros de pessoa\n");
	printf("0 - SAIR\n");
	scanf(" %d", &opcao);
	return opcao;
}

void CadastraNovaPessoa() {
	pessoa Pessoa;
	char opcao = 's';

    getchar();
	printf("Digite o nome da pessoa a ser cadastrada: \n");
    scanf (" %50[^\n]", Pessoa.nomePessoa);

	printf("Digite o CPF de %s: (Somente números - 11 digitos)\n", Pessoa.nomePessoa);
    scanf (" %12[^\n]", Pessoa.cpf);

	salvarPessoa(Pessoa);
	while(opcao=='s') {
        getchar();
		printf("Cadastrar novo veículo para %s? (s/n)\n", Pessoa.nomePessoa);
		opcao = getchar();
		if(opcao=='s') {
			printf("Digite o nome do veículo: \n");
            scanf (" %25[^\n]", Pessoa.Veiculo.nomeVeiculo);

			printf("Digite a placa do(a) %s: (Sem caracteres especiais)\n", Pessoa.Veiculo.nomeVeiculo);
			scanf (" %8[^\n]", Pessoa.Veiculo.placa);
			strcpy(Pessoa.Veiculo.cpfDono, Pessoa.cpf);
			salvarVeiculo(Pessoa.Veiculo);
		}
	}

	return;
}

void salvarVeiculo(veiculo Veiculo) {
    FILE *arq_carros;
    if((arq_carros = fopen("carros.txt", "a"))==NULL) {
        printf("Não foi possível abrir o arquivo carros.txt");
        return;
    }
    fprintf(arq_carros, "%s %s %s\n", Veiculo.cpfDono, Veiculo.nomeVeiculo, Veiculo.placa);
    fclose(arq_carros);
	return;
}

void salvarPessoa(pessoa Pessoa) {
    FILE *arq_pessoas;

    if((arq_pessoas = fopen("pessoas.txt", "a"))==NULL) {
        printf("Não foi possível abrir o arquivo pessoas.txt");
        return;
    }
    fprintf(arq_pessoas, "%s;%s;\n", Pessoa.cpf, Pessoa.nomePessoa);
    fclose(arq_pessoas);
	return;
}

void PesquisaPessoa() {
    char cpf[12];
    char linhaDados[62];
    char dadosVeiculo[35];
    char cpfEncontrado[12];
    int flagEncontrado = 0;
    int k=1;

    veiculo Veiculo;

    FILE *arq_pessoas;

    printf("Digite o CPF da pessoa: \n");
    scanf (" %12[^\n]", cpf);
    if((arq_pessoas = fopen("pessoas.txt", "r"))==NULL) {
        printf("Não foi possível abrir o arquivo pessoas.txt");
        return;
    }
    while(fgets(linhaDados, 62, arq_pessoas) != NULL && !feof(arq_pessoas)) {
        stringCut(linhaDados, cpfEncontrado);
        if(strcmp(cpfEncontrado,cpf)==0) {
            printf("\n\n\nCarros comprados por este cpf: (CPF = %s)\n", cpf);
            flagEncontrado = 1;
        }
    }
    if(flagEncontrado==0) {
        printf("CPF não existe na base de dados\n");
        fclose(arq_pessoas);
        return;
    }
    fclose(arq_pessoas);

    buscaVeiculos(cpf);

    return;
}

void stringCut(char linhaDados[], char cpfEncontrado[]) {

    int i;

    for(i=0; ; i++) {
        if(linhaDados[i]!=';') {
            cpfEncontrado[i] = linhaDados[i];
        } else {
            break;
        }
    }

    return ;
}

void buscaVeiculos(char cpf[]) {

    veiculo Veiculo;
    FILE *arq_carros;

    if((arq_carros = fopen("carros.txt", "r"))==NULL) {
        printf("Não foi possível abrir o arquivo carros.txt");
        return ;
    }

    rewind(arq_carros);
    printf("Nome | Placa\n");
    while(fscanf(arq_carros, "%s %s %s", Veiculo.cpfDono, Veiculo.nomeVeiculo, Veiculo.placa)!=EOF) {
        if(strcmp(Veiculo.cpfDono, cpf)==0) {
            printf("%s | %s", Veiculo.nomeVeiculo, Veiculo.placa);
        }
    }
    printf("\n\n\n\n");

    fclose(arq_carros);

    return ;
}