#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct carro{
  char chassi[17];
}carro;

typedef struct proprietario{
  int cpf;
  char nome[30];
  struct carro veiculo;
  int status;
}proprietario;

void cadastraProprietario(proprietario *p){
  printf("Insira o CPF: ");
  scanf("%d",&p->cpf);
  printf("Insira o Chassi do Carro: ");
  scanf(" %[^\n]",p->veiculo.chassi);
  p->status = 0;
}

int main(){
  proprietario p;
  int opcao = 1;
  while(opcao != 0){
    system("cls");
    printf("MENU\n");
    printf("0 - SAIR\n");
    printf("1 - Cadastrar Propietario\n");
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
      default:
        printf("Insira uma opcao valida\n");
        break;
    }
  }
  // system("cls");
  // printf("%d %s\n",p.cpf, p.veiculo.chassi);
  return 0;
}
