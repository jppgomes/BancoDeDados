#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 50
#define MAX_CPF 13

typedef struct {
	char nomeVeiculo[25];
	int indentificador;
	char placa[9];
} veiculo;

typedef struct {
	char nomePessoa[50];
	char cpf[MAX_CPF];
	int numeroCarros;
    int* IDcarrosAdiquiridos;
} pessoa;

int menu();
void CadastraNovaPessoa();
int salvarVeiculo(veiculo Veiculo);
void salvarPessoa(pessoa Pessoa);
void PesquisaPessoa();
void stringCut(char linhaDados[], char cpfEncontrado[]);
void buscaVeiculos(int* id, int numCarros);
void mostrarRegistros();

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

            case 3:
                mostrarRegistros();
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
	printf("3 - Mostrar registros\n");
	printf("0 - SAIR\n");
	scanf(" %d", &opcao);
	return opcao;
}

int validaCPF(char* cpf, int deveSerUnico){
    FILE* arq_pessoas;
    pessoa pessoaAtual;
    cpf[strlen(cpf)-1] = '\0';
    if(strlen(cpf) != 11){
        return 0;
    }
    arq_pessoas = fopen("pessoas.txt", "r");
    if(arq_pessoas == NULL){
        return 1; //ainda não há arquivo de dados, portanto é único.
    }
    if(deveSerUnico){
        while(fread(&pessoaAtual, sizeof(pessoa), 1, arq_pessoas)){
            if(!strcmp(pessoaAtual.cpf, cpf)){
                return 0;
            }
        }
    }
    return 1;
}

void CadastraNovaPessoa() {
	pessoa Pessoa;
	veiculo Veiculo;
	char opcao;

    getchar();
    fflush(stdin);
    Pessoa.IDcarrosAdiquiridos = NULL;
    Pessoa.numeroCarros = 0;
	printf("Digite o nome da pessoa a ser cadastrada: \n");
    fgets(Pessoa.nomePessoa, 50, stdin);
    Pessoa.nomePessoa[strlen(Pessoa.nomePessoa)-1] = '\0';
	printf("Digite o CPF de %s: (Somente números - 11 digitos)\n", Pessoa.nomePessoa);
	fgets(Pessoa.cpf, MAX_CPF, stdin);
	while(!validaCPF(Pessoa.cpf, 1)){
	    printf("Cpf inválido, insira novamente: ");
        fgets(Pessoa.cpf, MAX_CPF, stdin);
	}
    do{
		printf("Cadastrar novo veículo para %s? (s/n)\n", Pessoa.nomePessoa);
		opcao = getchar();
		fflush(stdin);
		if(opcao=='s') {
            Pessoa.numeroCarros++;
            if(Pessoa.numeroCarros == 1){
                Pessoa.IDcarrosAdiquiridos = malloc(sizeof(int));
            }
            else{
                Pessoa.IDcarrosAdiquiridos = realloc(Pessoa.IDcarrosAdiquiridos, Pessoa.numeroCarros*sizeof(int));
            }

			printf("Digite o nome do veículo: \n");
            fgets (Veiculo.nomeVeiculo, 25, stdin);
            Veiculo.nomeVeiculo[strlen(Veiculo.nomeVeiculo)-1] = '\0';

			printf("Digite a placa do(a) %s (Sem caracteres especiais): ", Veiculo.nomeVeiculo);
			fgets(Veiculo.placa, 9, stdin);
            Veiculo.placa[strlen(Veiculo.placa)-1] = '\0';
			Pessoa.IDcarrosAdiquiridos[Pessoa.numeroCarros-1] = salvarVeiculo(Veiculo);
		}
	}while(opcao == 's');
	printf("Salvando pessoa\n");
    salvarPessoa(Pessoa);
	return;
}

 void ordenaVeiculos(veiculo* veiculos, int numVeiculos){
    veiculo temp;
    int aux1, aux2;
    for(aux1 = 1; aux1<numVeiculos; aux1++){
        aux2 = aux1;
        while((aux2 != 0) && (veiculos[aux2].indentificador < veiculos[aux2-1].indentificador)){
            temp = veiculos[aux2];
            veiculos[aux2] = veiculos[aux2-1];
            veiculos[aux2-1] = temp;
            aux2--;
        }
    }
 }


int salvarVeiculo(veiculo Veiculo) {
    FILE *arq_carros;
    int numCarros = 1;
    int maiorId = 0;
    veiculo* veiculos = malloc(sizeof(veiculo));
    if((arq_carros = fopen("carros.txt", "r"))==NULL) {
        arq_carros = fopen("carros.txt", "w");
        fclose(arq_carros);
    }
    else{
        while(fread(&veiculos[numCarros-1], sizeof(veiculo), 1, arq_carros)){
            numCarros++;
            veiculo* temp = realloc(veiculos, sizeof(veiculo)*numCarros);
            if(temp != NULL){
                veiculos = temp;
            }
            else{
                printf("Erro ao ler carros!\n");
                fclose(arq_carros);
                free(veiculos);
                return -1;
            }
        }
        for(int aux = 0; aux < numCarros; aux++){
            if(veiculos[aux].indentificador > maiorId){
                maiorId=veiculos[aux].indentificador;
            }
        }
    }
    fclose(arq_carros);
    Veiculo.indentificador = maiorId+1;

    *(veiculos + numCarros - 1) = Veiculo;
    ordenaVeiculos(veiculos, numCarros);

    if((arq_carros = fopen("carros.txt", "w"))==NULL) {
        printf("Não foi possível abrir o arquivo carros.txt");
        return -1;
    }
    for(int aux = 0; aux < numCarros; aux++){
        fwrite(&veiculos[aux], sizeof(veiculo), 1, arq_carros);
    }
    free(veiculos);
    fclose(arq_carros);
	return maiorId+1;
}

 void ordenaPessoas(pessoa* pessoas, int numPessoas){
    pessoa temp;
    int aux1, aux2;
    for(aux1 = 1; aux1<numPessoas; aux1++){
        aux2 = aux1;
        while((aux2 != 0) && strcmp(pessoas[aux2].cpf, pessoas[aux2-1].cpf) < 0){
            temp = pessoas[aux2];
            pessoas[aux2] = pessoas[aux2-1];
            pessoas[aux2-1] = temp;
            aux2--;
        }
    }
 }


void salvarPessoa(pessoa Pessoa) {
    FILE *arq_pessoas;
    int numPessoas = 1;
    pessoa* pessoas = malloc(sizeof(pessoa));
    if((arq_pessoas = fopen("pessoas.txt", "r"))==NULL) {
        arq_pessoas = fopen("pessoas.txt", "w");
        fclose(arq_pessoas);
    }
    else{
        while(fread(&pessoas[numPessoas-1], sizeof(pessoa), 1, arq_pessoas)){
           pessoas[numPessoas-1].IDcarrosAdiquiridos = NULL;
            pessoas[numPessoas-1].IDcarrosAdiquiridos = malloc(pessoas[numPessoas-1].numeroCarros*sizeof(int));
            for(int aux = 0; aux < pessoas[numPessoas-1].numeroCarros; aux++){
                getchar();
                fread(&pessoas[numPessoas-1].IDcarrosAdiquiridos[aux], sizeof(int), 1, arq_pessoas);
                printf("id:%d\n", pessoas[numPessoas-1].IDcarrosAdiquiridos[aux]);
            }
            numPessoas++;
            pessoa* temp = realloc(pessoas, sizeof(pessoa)*numPessoas);
            if(temp != NULL){
                pessoas = temp;
            }
            else{
                printf("Erro ao ler pessoas!\n");
                fclose(arq_pessoas);
                free(pessoas);
                return;
            }
        }
        fclose(arq_pessoas);
    }
    *(pessoas + numPessoas - 1) = Pessoa;
    ordenaPessoas(pessoas, numPessoas);

    if((arq_pessoas = fopen("pessoas.txt", "w"))==NULL) {
        printf("Não foi possível abrir o arquivo pessoas.txt");
        return;
    }
    for(int aux = 0; aux < numPessoas; aux++){
        int escrito = fwrite(pessoas + aux, sizeof(pessoa), 1, arq_pessoas);
        for(int aux2 = 0; aux2 < pessoas[aux].numeroCarros; aux2++){
            fwrite(&pessoas[aux].IDcarrosAdiquiridos[aux2], sizeof(int), 1, arq_pessoas);
        }
    }
    free(pessoas);
    fclose(arq_pessoas);
	return;
}

void PesquisaPessoa() {
    char cpf[12];
    pessoa pessoaAtual;
    char dadosVeiculo[35];
    char cpfEncontrado[MAX_CPF];
    int flagEncontrado = 0;
    int k=1;

    veiculo Veiculo;

    FILE *arq_pessoas;
    fflush(stdin);
    printf("Digite o CPF da pessoa: ");
    fgets(cpf, MAX_CPF, stdin);
	while(!validaCPF(cpf, 0)){
	    printf("Cpf inválido, insira novamente: ");
        fgets(cpf, MAX_CPF, stdin);
	}
    if((arq_pessoas = fopen("pessoas.txt", "r"))==NULL) {
        printf("Não foi possível abrir o arquivo pessoas.txt");
        return;
    }
    int valido = fread(&pessoaAtual, sizeof(pessoa), 1, arq_pessoas);
    while(valido) {
        pessoaAtual.IDcarrosAdiquiridos = NULL;
        for(int aux = 0; aux < pessoaAtual.numeroCarros; aux++){
            if(pessoaAtual.IDcarrosAdiquiridos == NULL){
                pessoaAtual.IDcarrosAdiquiridos = malloc(sizeof(int));
            }
            else{
                pessoaAtual.IDcarrosAdiquiridos = realloc(pessoaAtual.IDcarrosAdiquiridos, (aux+1)*sizeof(int));
            }
            fread(&pessoaAtual.IDcarrosAdiquiridos[aux], sizeof(int), 1, arq_pessoas);
        }
        if(strcmp(pessoaAtual.cpf,cpf)==0) {
            if(!flagEncontrado){
                if(pessoaAtual.numeroCarros > 0){
                    printf("\n\nCarros comprados por este cpf:\n");
                }
                else{
                    printf("\n\nEsse proprietario nao possui carros\n");
                }

            }
            flagEncontrado = 1;
        }
        valido = fread(&pessoaAtual, sizeof(pessoa), 1, arq_pessoas);
    }
    if(flagEncontrado==0) {
        printf("CPF %s não existe na base de dados\n", cpf);
        fclose(arq_pessoas);
        return;
    }
    fclose(arq_pessoas);

    buscaVeiculos(pessoaAtual.IDcarrosAdiquiridos, pessoaAtual.numeroCarros);

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

void buscaVeiculos(int* id, int numCarros) {

    veiculo Veiculo;
    FILE *arq_carros;
    for(int i = 0; i < numCarros; i++){
        printf("%d\t", id[i]);
    }
    printf("\n");
    if((arq_carros = fopen("carros.txt", "r"))==NULL) {
        printf("Não foi possível abrir o arquivo carros.txt");
        return ;
    }

    printf("Nome | Placa\n");
    while(fread(&Veiculo, sizeof(veiculo), 1, arq_carros)) {
        for(int contador = 0; contador < numCarros; contador++){
            if(Veiculo.indentificador == id[contador]) {
                printf("%s | %s", Veiculo.nomeVeiculo, Veiculo.placa);
            }
        }
    }

    printf("\n\n\n\n");

    fclose(arq_carros);

    return ;
}

void mostrarRegistros(){
    FILE *arq_pessoas;
    int contador;
    int numPessoas = 0;
    FILE *arq_carros;
    int numCarros = 0;
    pessoa* pessoas = malloc(sizeof(pessoa));
    veiculo* veiculos = malloc(sizeof(veiculo));
    if((arq_pessoas = fopen("pessoas.txt", "r"))==NULL) {
        arq_pessoas = fopen("pessoas.txt", "w");
        fclose(arq_pessoas);
    }
    else{
        while(fread(&pessoas[numPessoas], sizeof(pessoa), 1, arq_pessoas)){
            pessoas[numPessoas].IDcarrosAdiquiridos = NULL;
            for(int aux = 0; aux < pessoas[numPessoas].numeroCarros; aux++){
                if(pessoas[numPessoas].IDcarrosAdiquiridos == NULL){
                    pessoas[numPessoas].IDcarrosAdiquiridos = malloc(sizeof(int));
                }
                else{
                    pessoas[numPessoas].IDcarrosAdiquiridos = realloc(pessoas[numPessoas].IDcarrosAdiquiridos, (aux+1)*sizeof(int));
                }
                fread(&pessoas[numPessoas].IDcarrosAdiquiridos[aux], sizeof(int), 1, arq_pessoas);
            }
            numPessoas++;
            pessoa* temp = realloc(pessoas, sizeof(pessoa)*(numPessoas+1));
            if(temp != NULL){
                pessoas = temp;
            }
            else{
                printf("Erro ao ler pessoas!\n");
                fclose(arq_pessoas);
                free(pessoas);
                return;
            }
        }
        fclose(arq_pessoas);
    }
        if((arq_carros = fopen("carros.txt", "r"))==NULL) {

    }
    else{
        while(fread(&veiculos[numCarros], sizeof(veiculo), 1, arq_carros)){
            numCarros++;
            veiculo* temp = realloc(veiculos, sizeof(veiculo)*(numCarros+1));
            if(temp != NULL){
                veiculos = temp;
            }
            else{
                printf("Erro ao ler carros!\n");
                fclose(arq_carros);
                free(veiculos);
                return -1;
            }
        }
        fclose(arq_carros);
    }
    printf("\n\nPESSOAS:\n");
    for(contador = 0; contador < numPessoas; contador++){
        printf("Nome: %s\tCpf:%s\tNumCarros:%d\n", pessoas[contador].nomePessoa, pessoas[contador].cpf, pessoas[contador].numeroCarros);
    }
    if(contador == 0){
        printf("Nenhuma cadastrada!\n");
    }
    printf("\n\nCARROS:\n");
    for(contador = 0;contador < numCarros; contador++){
        printf("ID:%d\tNome: %s\tPlaca:%s\n", veiculos[contador].indentificador, veiculos[contador].nomeVeiculo, veiculos[contador].placa);
    }
    if(contador == 0){
        printf("Nenhum cadastrado!\n");
    }
    printf("\n\n");
}
