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
  size_t tamanho_arq;
  int opcao = 1;
  fp = fopen("data.txt","a+");
  // if(fp != NULL){
  //   tamanho_arq = ftell(fp);
  //   if(tamanho_arq == 0){
  //   fseek(fp, 0, SEEK_END);
  //   tamanho_arq = ftell(fp);
  //   }
  // }
  // if(tamanho_arq == 0){
  //     fprintf(fp, "CPF           ");
  //     fprintf(fp, "CHASSI                 ");
  //     fprintf(fp, "\n");
  //   }
  printf("Insira o CPF: ");
  scanf(" %[^\n]",p->cpf);
  if(strlen(p->cpf) < 11)
  do {
    printf("Insira um CPF valido: ");
    scanf(" %[^\n]",p->cpf);
  } while(strlen(p->cpf) < 11);
  // fprintf(fp, p->cpf);
  // fprintf(fp, "   ");
  fwrite(p->cpf, 11, 1, fp);
  printf("Insira o Chassi do Carro: ");
  scanf(" %[^\n]",p->veiculo.chassi);
  // fprintf(fp, p->veiculo.chassi);
  fwrite(p->veiculo.chassi, 17, 1, fp);
  fprintf(fp, "\\");
  fclose(fp);
}

void leProprietarioCPF(char cpf[11]){
  FILE *fp;
  int contador = 0;
  char comparaCPF[11];

  strcpy(comparaCPF, "");
  printf("%d\n",strlen(comparaCPF));
  fp = fopen("data.txt", "r");
  fread(comparaCPF, 10, 1, fp);
  // if(strcmp(comparaCPF,cpf) == 0){
  //   printf("Iguais\n");
  // }
  fclose(fp);
  printf("%s\n",comparaCPF);
  printf("%d\n",strlen(comparaCPF));
}

int main(){
  proprietario p;
  int opcao = 1;
  while(opcao != 0){
    // system("cls");
    printf("MENU\n");
    printf("0 - SAIR\n");
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
        leProprietarioCPF("04590615185");
        break;
      default:
        printf("Insira uma opcao valida\n");
        break;
    }
  }

  return 0;
}
