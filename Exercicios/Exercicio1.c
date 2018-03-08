#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct carro{
  char chassi[17];
}carro;

typedef struct proprietario{
  char cpf[11];
  struct carro veiculo;
  int status;
}proprietario;

FILE *fp;

void cadastraProprietario(proprietario *p){
  fp = fopen("data.txt", "a+");
  printf("Insira o CPF: ");
  scanf(" %[^\n]",p->cpf);
  // p->status = 0;
  fprintf(fp, p->cpf);
  fprintf(fp, "   ");
  printf("Insira o Chassi do Carro: ");
  scanf(" %[^\n]",p->veiculo.chassi);
  fprintf(fp, p->veiculo.chassi);
  fprintf(fp, "\n");
  fclose(fp);
}

int main(){
  proprietario p;
  fp = fopen("data.txt","a+w");
  if(fp != NULL){
    int tamanho;
    tamanho = ftell(fp);
    if(tamanho == 0){
      fseek(fp, 0, SEEK_END);
      fprintf(fp, "\n");
    } else {
      fprintf(fp, "CPF           ");
      fprintf(fp, "CHASSI                 ");
      fprintf(fp, "\n");
    }
  }
  fclose(fp);
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

  return 0;
}
