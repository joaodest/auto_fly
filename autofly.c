#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
    printf("Por favor selecione uma operacao ou -1 para sair:\n");
    printf("1- Criar uma nova passagem aerea\n");
    printf("2- Editar os dados de uma passagem ja existente\n");
    printf("3- Pesquisar por passagens\n");
    printf("4- Excluir uma passagem\n");
    printf("--------------------------------------------------------------------\n");
    scanf("%d", &option);

    if (option == -1)
        return -1;
    else if (option < 1 || option > 4)
        printf("\nOpcao invalida. Por favor, tente novamente.\n");
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

    printf("Entre com a data de partida: \n");
    scanf(" %[^\n]", passagem->data);

    printf("Entre com a hora de partida: \n");
    scanf(" %[^\n]", passagem->horaPartida);

    printf("Entre com a hora de chegada: \n");
    scanf(" %[^\n]", passagem->horaChegada);

    printf("Entre com o valor da passagem: \n");
    scanf("%f", &passagem->valor);

    return passagem;
}

void print(Passagem *passagem)
{
    printf("[Passagem] ID: %d | Codigo do aeroporto (origem/destino): %s / %s | Cidade (origem/destino): %s / %s | Data: %s | Hora (chegada/partida): %s / %s | Valor pago: %.2f",
           passagem->id,
           passagem->codigoOrigem,
           passagem->codigoDestino,
           passagem->cidadeOrigem,
           passagem->cidadeDestino,
           passagem->data,
           passagem->horaChegada,
           passagem->horaPartida,
           passagem->valor);
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
}

int main()
{
    int option;
    option = menu();

    if (option == 1)
    {
        Passagem *newPassage;
        newPassage = createPassage();
        savePassage(newPassage);
        free(newPassage);
    }
}