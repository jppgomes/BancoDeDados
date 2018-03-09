#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct carro{
  char chassi[18];
  char placa[9];
}carro;

typedef struct proprietario{
  char cpf[12];
  struct carro veiculo;
  int n_Carros;
}proprietario;

FILE *fp;

void cadastraProprietario(proprietario *p){
  size_t tamanho_arq;
  int contador = 1;
  fp = fopen("data.txt","a+");
  printf("Insira o CPF: ");
  scanf(" %[^\n]",p->cpf);
  if(strlen(p->cpf) < 11 || strlen(p->cpf) > 11)
  do {
    printf("Insira um CPF valido: ");
    scanf(" %[^\n]",p->cpf);
  } while(strlen(p->cpf) < 11 || strlen(p->cpf) > 11);
  fwrite(p->cpf, 12, 1, fp);
  printf("Insira a quantidade de carros que o proprietario possui: ");
  scanf("%d",&p->n_Carros);
  // fwrite(n_Carro, 1, 1, fp);
  // fprintf(fp, "%d ", p->n_Carros);
  do {
    printf("Insira o Chassi do Carro(%d): ",contador);
    scanf(" %[^\n]",p->veiculo.chassi);
    if(strlen(p->veiculo.chassi) < 17 || strlen(p->veiculo.chassi) > 17){
      do {
        printf("Insira um Chassi valido: ");
        scanf(" %[^\n]",p->veiculo.chassi);
      } while(strlen(p->veiculo.chassi) < 17 || strlen(p->veiculo.chassi) > 17);
    }
    fwrite(p->veiculo.chassi, 18, 1, fp);
    contador++;
  } while(contador <= p->n_Carros);
  fclose(fp);
}

void achaCarros(char* cpf){
  FILE *fp;
  int contador = 0;
  int quantidade;
  int divisorLinha = 0;
  char* quantidade_char = malloc(1);
  char* comparaCPF = malloc(11);
  char* chassi = malloc(17);
  fp = fopen("data.txt", "rb");
  while(fread(comparaCPF, 12, 1, fp)){
      // fread(quantidade_char, 2, 1, fp);
      fread(chassi, 18, 1, fp);
      if(strcmp(comparaCPF,cpf) == 0){
        // while(divisorLinha < 31){
        //   printf("_");
        //   divisorLinha++;
        // }
        system("cls");
        printf("\nCPF: %s \n",comparaCPF);
        printf("CHASSI: %s\n", chassi);
        // printf("%c\n", quantidade_char);
        // divisorLinha = 0;
      }
    while(divisorLinha < 31){
      printf("_");
      divisorLinha++;
    }
    printf("\n");
  }
  fclose(fp);
}

int main(){
  proprietario p;
  int opcao = 1;
  char cpf[11];
  while(opcao != 0){
    printf("\t\tMENU\n");
    printf("0 - Sair\n");
    printf("1 - Cadastrar Propietario\n");
    printf("2 - Mostrar Dados\n");
    printf("Opcao: ");
    scanf("%d",&opcao);
    switch (opcao) {
      case 0:
        system("cls");
        break;
      case 1:
        system("cls");
        cadastraProprietario(&p);
        break;
      case 2:
        system("cls");
        printf("CPF: ");
        scanf("%s",cpf);
        fflush(stdin);
        achaCarros(cpf);
        opcao = 3;
        break;
      default:
        printf("Insira uma opcao valida\n");
        break;
    }
  }

  return 0;
}
