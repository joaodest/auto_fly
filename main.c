#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "datetime_utils.h"

#define MAX_DATE_LENGTH 11

typedef struct Passagem
{
    int id;
    char codigoOrigem[4];
    char cidadeOrigem[50];
    char codigoDestino[4];
    char cidadeDestino[50];
    char data[11];
    char horaPartida[6];
    char horaChegada[6];
    float valor;
} Passagem;

void label()
{
    printf(" *   ###    ##   ##   # #####  #####             ####### ####     ###  ### * ");
    printf("\n");
    printf(" *  ## ##   ##   ##  ## ## ## ### ###             ##   #  ##       ##  ## * ");
    printf("\n");
    printf(" * ##   ##  ##   ##     ##    ##   ##             ##      ##        #### * ");
    printf("\n");
    printf(" * ##   ##  ##   ##     ##    ##   ##             ####    ##         ## * ");
    printf("\n");
    printf(" * #######  ##   ##     ##    ##   ##             ##      ##         ## * ");
    printf("\n");
    printf(" * ##   ##  ##   ##     ##    ### ###             ##      ##  ##     ## * ");
    printf("\n");
    printf(" * ##   ##   #####     ####    #####             ####    #######    #### * ");
    printf("\n");
}
int menu()
{
    int option;
    label();
    printf("\n");
    printf("Seja bem-vindo(a) a auto-fly\n");
    printf("--------------------------------------------------------------------\n");
    printf("Por favor selecione uma operacao:\n");
    printf("1- Listar todas as passagens\n");
    printf("2- Pesquisar passagens\n");
    printf("3- Cadastrar uma passagem\n");
    printf("4- Editar uma passagem\n");
    printf("0- Sair do programa\n");
    printf("--------------------------------------------------------------------\n");
    scanf("%d", &option);

    if (option < 0 || option > 4)
    {
        printf("Opcao invalida. Por favor, tente novamente.\n");
        return -1;
    }
    else
        return option;
}
Passagem *createPassage()
{
    Passagem *passagem;
    passagem = (Passagem *)malloc(sizeof(Passagem));

    printf("Entre com o ID da passagem: \n");
    scanf("%d", &passagem->id);

    printf("Entre com o codigo do aeroporto de origem: \n");
    scanf(" %[^\n]", passagem->codigoOrigem);

    printf("Entre com o codigo do aeroporto de destino: \n");
    scanf(" %[^\n]", passagem->codigoDestino);

    printf("Entre com a cidade de origem: \n");
    scanf(" %[^\n]", passagem->cidadeOrigem);

    printf("Entre com a cidade de destino: \n");
    scanf(" %[^\n]", passagem->cidadeDestino);
    printf("Entre com a data de partida (no formato dd/MM/yyyy): \n");
    scanf(" %[^\n]", passagem->data);

    char formattedDate[MAX_DATE_LENGTH + 1];
    formatDate(formattedDate, passagem->data);

    if(formattedDate[0] == '\0')
    {
        printf("Data invalida! \n");
        free(passagem);
        return NULL;
    }

    printf("Entre com a hora de partida: \n");
    scanf(" %[^\n]", passagem->horaPartida);

    char formattedTime[MAX_TIME_LENGTH + 1];


    formatTime(formattedTime, passagem->horaPartida);



    printf("Entre com a hora de chegada: \n");
    scanf(" %[^\n]", passagem->horaChegada);


    formatTime(formattedTime, passagem->horaChegada);


    printf("Entre com o valor da passagem: \n");
    scanf("%f", &passagem->valor);



    return passagem;
}

void savePassage(Passagem *passagem)
{
    FILE *file;
    file = fopen("passagens.txt", "a");
    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
        return;
    }

    fprintf(file, "%d;%s;%s;%s;%s;%s;%s;%s;%.2f\n", passagem->id,
            passagem->codigoOrigem,
            passagem->codigoDestino,
            passagem->cidadeOrigem,
            passagem->cidadeDestino,
            passagem->data,
            passagem->horaPartida,
            passagem->horaChegada,
            passagem->valor);

    fclose(file);

    printf("Passagem cadastrada com sucesso!\n");
}

void printAllPassages(int *pcount)
{

    char linha[100];
    FILE *file;
    Passagem passage;
    file = fopen("passagens.txt", "r");
    fseek(file, 0, SEEK_SET);

    printf("Passagens encontradas:\n");

    while (fgets(linha, sizeof(linha), file) != NULL)
    {

        sscanf(linha, "%d;%3s;%3s;%49[^;];%49[^;];%10[^;];%5[^;];%5[^;];%f", &passage.id,
               passage.codigoOrigem,
               passage.codigoDestino,
               passage.cidadeOrigem,
               passage.cidadeDestino,
               passage.data,
               passage.horaChegada,
               passage.horaPartida,
               &passage.valor);
        printf("[Passagem] ID: %d | Codigo do aeroporto (origem/destino): %s / %s | Cidade (origem/destino): %s / %s | Data: %s | Hora (chegada/partida): %s / %s | Valor pago: %.2f\n",
               passage.id,
               passage.codigoOrigem,
               passage.codigoDestino,
               passage.cidadeOrigem,
               passage.cidadeDestino,
               passage.data,
               passage.horaChegada,
               passage.horaPartida,
               passage.valor);
        (*pcount)++;
    }

    fclose(file);
}

void printPassagem(Passagem *passage)
{
    printf("[Passagem] ID: %d | Codigo do aeroporto (origem/destino): %s / %s | Cidade (origem/destino): %s / %s | Data: %s | Hora (chegada/partida): %s / %s | Valor pago: %.2f\n",
           passage->id,
           passage->codigoOrigem,
           passage->codigoDestino,
           passage->cidadeOrigem,
           passage->cidadeDestino,
           passage->data,
           passage->horaChegada,
           passage->horaPartida,
           passage->valor);
}
Passagem *findById(int id)
{
    FILE *file = fopen("passagens.txt", "r");

    if (file == NULL)
    {
        printf("Erro ao abrir arquivo.\n");
        return NULL;
    }

    Passagem *passagem = malloc(sizeof(Passagem));

    if (passagem == NULL)
    {
        printf("Erro ao alocar memória para a passagem.\n");
        fclose(file);
        return NULL;
    }

    while (fscanf(file, "%d;%3s;%3s;%49[^;];%49[^;];%10[^;];%5[^;];%5[^;];%f\n",
                  &passagem->id,
                  passagem->codigoOrigem,
                  passagem->codigoDestino,
                  passagem->cidadeOrigem,
                  passagem->cidadeDestino,
                  passagem->data,
                  passagem->horaChegada,
                  passagem->horaPartida,
                  &passagem->valor) == 9)
    {
        if (passagem->id == id)
        {
            fclose(file);
            return passagem;
        }
    }

    // Se a passagem não foi encontrada, libera a memória
    free(passagem);
    fclose(file);

    return NULL;
}
void submenuOperations(int id)
{
    switch (id)
    {
        int idPassagem;
    case 1:

        printf("\nDigite o ID da passagem que deseja buscar:\n> ");
        scanf("%d", &idPassagem);

        Passagem *passagem = findById(idPassagem);

        if (passagem != NULL)
        {
            printPassagem(passagem);
            free(passagem);
        }
        else
        {
            printf("Nenhuma passagem encontrada com esse ID.\n\n");
        }
        break;
    case 2:
        printf("usecase 2\n");
        break;
    case 3:
        printf("usecase 3\n");
        break;
    case 4:
        printf("usecase 4\n");
        break;
    case 5:
        printf("usecase 5\n");
        break;
    }
}
void submenu()
{
    int submenuOpt;
    printf("Para buscar uma passagem, informe qual metodo gostaria de utilizar:\n");
    printf("--------------------------------------------------------------------\n");
    printf("\t1 - Busca por identificador da passagem.\n");
    printf("\t2 - Busca por Aeroporto de origem.\n");
    printf("\t3 - Busca por Aeroporto de destino.\n");
    printf("\t4 - Busca pela cidade de origem.\n");
    printf("\t5 - Busca pela cidade de destino.\n");
    printf("\t0 - Voltar para o menu principal.\n");
    printf("--------------------------------------------------------------------\n");
    scanf("%d", &submenuOpt);

    submenuOperations(submenuOpt);
}

int main()
{
    // dd/MM/yyyy

    int option;
    option = menu();

    while (option != 0)
    {
        if (option == -1)
            printf("Opcao Invalida! Tente novamente: \n");

        if (option == 1)
        {
            int count = 0;
            printAllPassages(&count);
            printf("--------------------------------------------------------------------\n");
            printf("Passagens atualmente registradas: %d\n", count);
        }
        if (option == 2)
        {
            submenu();
        }

        if (option == 3)
        {
            Passagem *newPassage;
            newPassage = createPassage();

            formatDate(newPassage->data, newPassage->data);

            savePassage(newPassage);


            free(newPassage);
        }

        char continuar;
        printf("Deseja realizar mais alguma tarefa?(s/n) \n");
        scanf(" %c", &continuar);
        if (continuar == 's' || continuar == 'S')
        {
            option = menu();
        }
        else if (continuar == 'n' || continuar == 'N')
        {
            option = 0;
        }
        else
        {
            printf("Opcao invalida!\n");
        }
    }
    printf("Obrigado por escolher a Auto-Fly, ate logo! :)");

    return 0;
}
