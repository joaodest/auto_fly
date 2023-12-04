#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "helpers.h"

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

void seedRandom()
{
    srand(time(NULL));
}

int generateRandomId()
{
    return rand() % 90 + 1000;
}

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
    printf("5- Deletar uma passagem\n");
    printf("0- Sair do programa\n");
    printf("--------------------------------------------------------------------\n");
    scanf("%d", &option);

    if (option < 0 || option > 5)
    {
        return -1;
    }
    else
        return option;
}
Passagem *createPassage()
{
    seedRandom();

    Passagem *passagem;
    passagem = (Passagem *)malloc(sizeof(Passagem));

    passagem->id = generateRandomId();

    printf("Entre com o codigo do aeroporto de origem: \n");
    scanf(" %[^\n]", passagem->codigoOrigem);

    char formattedAirportOrigin[AIRPORT_CODE_LENGTH];
    if (!validateAirportCode(passagem->codigoOrigem, formattedAirportOrigin))
    {
        free(passagem);
        return NULL;
    }

    strcpy(passagem->codigoOrigem, formattedAirportOrigin);

    printf("Entre com o codigo do aeroporto de destino: \n");
    scanf(" %[^\n]", passagem->codigoDestino);

    char formattedAirportDest[AIRPORT_CODE_LENGTH];
    if (!validateAirportCode(passagem->codigoDestino, formattedAirportDest))
    {
        free(passagem);
        return NULL;
    }

    strcpy(passagem->codigoDestino, formattedAirportDest);

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

        printf("--------------------------------------------------------------------\n");
        printf("[Passagem] \nID: %d \n Codigo do aeroporto (origem/destino): %s / %s \n Cidade (origem/destino): %s / %s \n Data: %s \n Hora (chegada/partida): %s / %s \n Valor pago: R$ %.2f\n",
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
    printf("--------------------------------------------------------------------\n");

    fclose(file);
}

void printPassagem(Passagem *passage)
{
    printf("[Passagem] \nID: %d \n Codigo do aeroporto (origem/destino): %s / %s \n Cidade (origem/destino): %s / %s \n Data: %s \n Hora (chegada/partida): %s / %s \n Valor pago: %.2f\n",
           passage->id,
           passage->codigoOrigem,
           passage->codigoDestino,
           passage->cidadeOrigem,
           passage->cidadeDestino,
           passage->data,
           passage->horaChegada,
           passage->horaPartida,
           passage->valor);
    printf("--------------------------------------------------------------------\n");
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

void findByCode(const char *code)
{
    FILE *file = fopen("passagens.txt", "r");
    if(file == NULL)
    {
        printf("Erro ao abrir arquivo \n");
        return NULL;
    }

    int found = 0;

    char *upperCode = malloc(AIRPORT_CODE_LENGTH * sizeof(char));

    for(int i = 0; i < 4; i++)
    {
        upperCode[i] = toupper(code[i]);
    }

    Passagem passagem;

    while(fscanf(file, "%d;%3s;%3s;%49[^;];%49[^;];%10[^;];%5[^;];%5[^;];%f\n",
                 &passagem.id,
                 passagem.codigoOrigem,
                 passagem.codigoDestino,
                 passagem.cidadeOrigem,
                 passagem.cidadeDestino,
                 passagem.data,
                 passagem.horaChegada,
                 passagem.horaPartida,
                 &passagem.valor) == 9)
    {
        if (strcmp(passagem.codigoOrigem, upperCode) == 0 || strcmp(passagem.codigoDestino, upperCode) == 0)
        {
            printPassagem(&passagem);
            found = 1;
        }
    }
    if(!found)
    {
        printf("Nenhuma passagem com o codigo de aeroporto fornecido \n");
    }
    fclose(file);
}
void findByCity(const char *city)
{
    FILE *file = fopen("passagens.txt", "r");
    if(file == NULL)
    {
        printf("Erro ao abrir arquivo \n");
        return NULL;
    }

    int found = 0;

    char upperCity[MAX_CITY_LENGTH + 1];

    for(int i = 0; i < strlen(city); i++)
    {
        upperCity[i] = toupper(city[i]);
    }

    upperCity[strlen(city)] = '\0';

    Passagem passagem;


    while(fscanf(file, "%d;%3s;%3s;%49[^;];%49[^;];%10[^;];%5[^;];%5[^;];%f\n",
                 &passagem.id,
                 passagem.codigoOrigem,
                 passagem.codigoDestino,
                 passagem.cidadeOrigem,
                 passagem.cidadeDestino,
                 passagem.data,
                 passagem.horaChegada,
                 passagem.horaPartida,
                 &passagem.valor) == 9)
    {
        if (strcasecmp(passagem.cidadeOrigem, upperCity) == 0 || strcasecmp(passagem.cidadeDestino, upperCity) == 0)
        {
            printPassagem(&passagem);
            found = 1;
        }
    }

    fclose(file);

    if(!found)
    {
        printf("Nenhuma passagem encontrada com o nome da cidade fornecida. \n");
    }
}
Passagem* editPassage(int id)
{
    FILE *file  = fopen("passagens.txt", "r+");

    if (file == NULL)
    {
        printf("Erro ao abrir arquivo\n");
        return;
    }
    Passagem passagem;

    int found = 0;

    while(fscanf(file, "%d;%3s;%3s;%49[^;];%49[^;];%10[^;];%5[^;];%5[^;];%f\n",
                 &passagem.id,
                 passagem.codigoOrigem,
                 passagem.codigoDestino,
                 passagem.cidadeOrigem,
                 passagem.cidadeDestino,
                 passagem.data,
                 passagem.horaChegada,
                 passagem.horaPartida,
                 &passagem.valor) == 9)
    {
        if(passagem.id == id)
        {
            found = 1;
            createPassage();
            fseek(file, -ftell(file), SEEK_CUR);


            printf("--------------------------------------------------------------------\n");
            printf("Passagem editada com sucesso! \n");
            printf("--------------------------------------------------------------------\n");
            printf("Informacoes atualizadas da passagem: \n");
            printPassagem(&passagem);
            break;
        }
    }
    if(!found)
    {
        printf("--------------------------------------------------------------------\n");
        printf("Nenhuma passagem encontrada com o ID fornecido. \n");
        printf("--------------------------------------------------------------------\n");
    }

    fclose(file);
}
void deletePassage(int id)
{
    FILE *inputFile = fopen("passagens.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");

    if (inputFile == NULL || tempFile == NULL)
    {
        printf("Erro ao abrir arquivo\n");
        return;
    }

    Passagem passagem;
    int found = 0;

    while (fscanf(inputFile, "%d;%3s;%3s;%49[^;];%49[^;];%10[^;];%5[^;];%5[^;];%f\n",
                  &passagem.id,
                  passagem.codigoOrigem,
                  passagem.codigoDestino,
                  passagem.cidadeOrigem,
                  passagem.cidadeDestino,
                  passagem.data,
                  passagem.horaChegada,
                  passagem.horaPartida,
                  &passagem.valor) == 9)
    {
        if (passagem.id == id)
        {
            found = 1;
        }
        else
        {
            fprintf(tempFile, "%d;%s;%s;%s;%s;%s;%s;%s;%.2f\n",
                    passagem.id,
                    passagem.codigoOrigem,
                    passagem.codigoDestino,
                    passagem.cidadeOrigem,
                    passagem.cidadeDestino,
                    passagem.data,
                    passagem.horaChegada,
                    passagem.horaPartida,
                    passagem.valor);
        }
    }

    fclose(inputFile);
    fclose(tempFile);

    remove("passagens.txt");
    rename("temp.txt", "passagens.txt");

    if (found)
    {
        printf("Passagem removida com sucesso! \n");
    }
    else
    {
        printf("Nenhuma passagem encontrada com o ID fornecido.\n");
    }
}


void submenuOperations(int id)
{
    switch (id)
    {
        int idPassagem;
        char airportCode[AIRPORT_CODE_LENGTH];
        char cityname[MAX_CITY_LENGTH];

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
        printf("Digite o codigo do aeroporto de origem para buscar por passagens:\n> ");
        scanf("%3s", airportCode);

        findByCode(airportCode);

        break;
    case 3:
        printf("Digite o codigo do aeroporto de destino para buscar por passagens:\n> ");
        scanf("%3s", airportCode);

        findByCode(airportCode);

        break;
    case 4:
        printf("Digite o nome da cidade de destino para buscar por passagens:\n> ");
        scanf(" %49s", cityname);

        findByCity(cityname);
        break;
    case 5:
        printf("Digite o nome da cidade de origem para buscar por passagens:\n> ");
        scanf(" %49s", cityname);

        findByCity(cityname);
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
    int id;
    int option;
    option = menu();

    while (option != 0)
    {
        if (option == -1)
            printf("Opcao Invalida! Tente novamente. \n");

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
        if(option == 4)
        {
            printf("Digite o identificador da passagem que deseja editar: \n> ");
            scanf("%d", &id);

            editPassage(id);

        }
        if(option == 5)
        {
            printf("Digite o identificador da passagem que deseja deletar: \n> ");
            scanf("%d", &id);

            deletePassage(id);
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
    printf("Obrigado(a) por escolher a Auto-Fly, ate logo! :)");

    return 0;
}
