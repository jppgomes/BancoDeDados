#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
    char placa[9];
    char chassi[18];
    char cpfProprietario[12]; /* Ver se é necessário mudar pra CHAR */
}carro;

typedef struct {
  char nome[99];
  char endereco[100];
  char cpf[12]; /* Ver se é necessário mudar pra CHAR */
  carro veiculo;
}proprietario;

FILE *fp; /* Variável global para apontador de arquivo */

void insereProprietario();
void leDadosProprietario();

int main(){
  int opcao = 1;
  char cpf[12];
  proprietario *p;
  while(opcao != 0){
    // system("cls");
    printf("\tMENU\n");
    printf("0 - Sair\n");
    printf("1 - Inserir Proprietario\n");
    printf("2 - Ler Dados Propietario\n");
    printf("Opcao: ");
    scanf("%d",&opcao);
    switch (opcao) {
      case 0:
        printf("Bye! :)");
        system("cls");
        break;
      case 1:
        insereProprietario(&p);
        break;
      case 2:
        printf("Insira o CPF do proprietario: ");
        scanf("%s",cpf);
        leDadosProprietario(cpf);
        break;
    }
  }
  return 0;
}

void insereProprietario(proprietario *p){
  fp = fopen("data.txt", "a+");
  printf("Insira o CPF do proprietario: ");
  scanf(" %[^\n]",p->cpf);
  if(strlen(p->cpf) < 11 || strlen(p->cpf) > 11){
    do {
      printf("Insira um CPF valido: "); scanf(" %[^\n]",p->cpf);
    } while(strlen(p->cpf) < 11 || strlen(p->cpf) > 11);
  }
  fwrite(p->cpf, 12, 1, fp);
  printf("Insira o Nome do proprietario: ");
  scanf(" %[^\n]",p->nome);
  if(strlen(p->nome) < 10){
    fprintf(fp, "0%d", strlen(p->nome));
  }
  if(strlen(p->nome) >= 10){
    fprintf(fp, "%d ", strlen(p->nome));
  }
  fwrite(p->nome, strlen(p->nome) + 1, 1, fp);
  printf("Insira o Endereco do proprietario: ");
  scanf(" %[^\n]",p->endereco);
  fprintf(fp, "%d ", strlen(p->endereco));
  fwrite(p->endereco, strlen(p->endereco) + 1, 1, fp);
  /* fwrite(variavel que vai escrever, quantos bytes, quantas vezes, qual arquivo) */
  fclose(fp);
}

void leDadosProprietario(char cpf[12]){
  char *compara_cpf = malloc(11);
  char *nome = malloc(99);
  char *endereco = malloc(100);
  char nomeNum[2];
  char enderecoNum[100];
  int tamNome, tamEndereco;
  fp = fopen("data.txt", "rb+");
  while(fread(compara_cpf, 12, 1, fp)){
    fread(nomeNum, 3, 1, fp);
    tamNome = atof(nomeNum);
    fread(nome, tamNome + 1, 1, fp);
    fread(enderecoNum, 3, 1, fp);
    tamEndereco = atof(enderecoNum);
    fread(endereco, tamEndereco + 1, 1, fp);
    if(strcmp(compara_cpf, cpf) == 0){
      printf("_________________________\n");
      printf("NOME: %s\n", nome);
      printf("ENDERECO: %s\n", endereco);
      printf("CPF: %s\n",compara_cpf);
      // printf("TAM NOME: %d\n", tamNome);
      printf("_________________________\n");
    }
  }
  /* fread(onde vai gravar, quantos bytes, quantas vezes, qual arquivo)*/
  fclose(fp);
}
