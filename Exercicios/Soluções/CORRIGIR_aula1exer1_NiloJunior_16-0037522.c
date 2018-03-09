#include <stdio.h>
#include <string.h>

//Programa aula Sistema de banco de dados
//autor: Nilo Mendonca de Brito Junior
//matricula: 160037522

int main(void)
{
	char url[]="cadastros.txt";
	FILE *arq;

    while(1){
        printf("Selecione uma opcao:\n[1] - Buscar registro\n[2] - Listar todos os registros\n[3] - Incluir registro\n[4] - excluir registro\n[0] - Sair\n");
        int opcao;
        scanf("%d", &opcao);

        if(opcao == 1 || opcao == 2 || opcao == 3 || opcao == 4 || opcao == 0){
            if(opcao == 0)
                break;

            if (opcao == 1){
                int encontrado = -1;
                char chassi[30], cpfUsuarioInput[15], cpfUsuarioTemp[15];
                printf("Digite o CPF do usuario: \n");
                scanf("%s", cpfUsuarioInput);
                arq = fopen(url, "r");
                if(arq == NULL)
                    printf("Erro, nao foi possivel abrir o arquivo ou arquivo vazio\n");

                else{
                    while( (fscanf(arq,"%s %s\n", cpfUsuarioTemp, chassi))!=EOF ){
                        if (strcmp(cpfUsuarioInput, cpfUsuarioTemp) == 0){
                            printf("CPF: %s\nVeiculo: %s", cpfUsuarioTemp, chassi);
                            encontrado = 0;
                            }
                        }

                    if (encontrado != 0)
                        printf("Usuario nao encontrado.");
                }
                fclose(arq);
            }


            if (opcao == 2){
                char chassi[30], cpfUsuarioTemp[15];
                arq = fopen(url, "r");
                if(arq == NULL)
                    printf("Erro, nao foi possivel abrir o arquivo ou arquivo vazio\n");

                else{
                    while( (fscanf(arq,"%s %s\n", cpfUsuarioTemp, chassi))!=EOF ){
                        printf("CPF: %s\nVeiculo: %s\n", cpfUsuarioTemp, chassi);
                    }
                }
                fclose(arq);
            }

            if (opcao == 3){
                char chassi[30], cpfUsuarioTemp[15];
                arq = fopen(url, "a");
                if(arq == NULL)
                    printf("Erro, nao foi possivel abrir o arquivo\n");

                else{
                    printf("\nDigite o CPF do usuario: ");
                    scanf ("%s", cpfUsuarioTemp);
                    printf("\nDigite o CHASSI do veiculo: ");
                    scanf ("%s", chassi);

                    fprintf(arq, "\n%s %s", cpfUsuarioTemp, chassi);
                }
                fclose(arq);
            }


            if (opcao == 4){
                int encontrado = -1;
                char chassiTemp[30], chassiInput[15], cpfUsuario[15];
                printf("Digite o CHASSI do veiculo: \n");
                scanf("%s", chassiInput);
                arq = fopen(url, "r");
                if(arq == NULL)
                    printf("Erro, nao foi possivel abrir o arquivo\n");

                else{
                    char urlTemp[]="cadastrosTemp.txt";
                    FILE *arqTemp;
                    arqTemp = fopen(urlTemp, "w");
                    if(arqTemp == NULL)
                        printf("Erro.\n");
                    else{

                        while( (fscanf(arq,"%s %s\n", cpfUsuario, chassiTemp))!=EOF ){
                            if (strcmp(chassiInput, chassiTemp) != 0){
                                fprintf(arqTemp, "\n%s %s", cpfUsuario, chassiTemp);
                                encontrado = 0;
                                }
                            }

                        fclose(arqTemp);
                        fclose(arq);

                        arq = fopen(url, "w");
                        arqTemp = fopen(urlTemp, "r");

                        if(arqTemp == NULL || arq == NULL)
                            printf("Erro.\n");
                        else{

                            while( (fscanf(arqTemp,"%s %s\n", cpfUsuario, chassiTemp))!=EOF ){
                                fprintf(arq, "\n%s %s", cpfUsuario, chassiTemp);
                            }
                        }
                    }
                    fclose(arqTemp);
                    fclose(arq);
                    if (encontrado != 0)
                        printf("Usuario nao encontrado.");
                    else
                        printf("Registro apagado com sucesso.");
                    }
                }
            }
            else {
                printf("Opcao invalida!!!\n\n\n\n\n\n");
                continue;
            }
            printf("\n\n\n\n\n\n");
        }
	return 0;
}
