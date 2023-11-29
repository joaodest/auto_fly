#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



void formatDate(char *formattedDate, const char *date)
{
    int day, month, year;
    char separator;

    if (sscanf(date, "%2d%c%2d%c%4d", &day, &separator, &month, &separator, &year) != 5)
    {
        printf("Data inválida! \n");
        formattedDate[0] = '\0';
        return;
    }

    if (day < 1 || day > 31 || month < 1 || month > 12 || (separator != '/' && separator != '-'))
    {
        printf("Data inválida! \n");
        formattedDate[0] = '\0';
        return;
    }

    snprintf(formattedDate, MAX_DATE_LENGTH + 1, "%02d/%02d/%04d", day, month, year);
}

void formatTime(char *formattedTime, const char *time)
{
    int hour, minutes;
    char separator;

    if (sscanf(time, "%2d%c%2d", &hour, &separator, &minutes) != 3)
    {
        if (sscanf(time, "%2d%c%2d", &hour, &separator, &minutes) != 3)
        {
            printf("Formato de hora invalido! Use o formato 24h (por exemplo, 23:30) ou 'h' (por exemplo, 23h30)\n");
            formattedTime[0] = '\0';
            return;
        }
    }

    if (!(hour >= 0 && hour <= 23) || !(minutes >= 0 && minutes <= 59))
    {
        printf("Hora invalida! Use valores dentro das faixas aceitáveis\n");
        formattedTime[0] = '\0';
        return;
    }

    snprintf(formattedTime, MAX_TIME_LENGTH + 1, "%02d:%02d", hour, minutes);
}

int validateAirportCode(const char *code, char *formattedCode)
{
    if(strlen(code) != 3)
    {
        printf("Por favor, insira um codigo de aeroporto valido!\nO codigo de aeroporto segue este modelo: XXX\n");
        return 0;
    }

    for(int i = 0; i < 3; i++)
    {
        if(!isalpha((unsigned char)code[i]))
        {
            printf("Codigo de aeroporto inválido! Deve conter apenas letras.\n");
            return 0;
        }
        formattedCode[i] = toupper((unsigned char)code[i]);
    }

    formattedCode[3] = '\0';

    return 1;
}

int validateCityName(const char *city, char *formattedCity)
{

    if(strlen(city) > MAX_CITY_LENGTH)
    {
        printf("Por favor, insira um nome valido \n");
        return 0;
    }

    for(int i = 0; i < strlen(city); i++)
    {
        if(!isalpha((unsigned char)city[i]))
        {
            printf("Nome invalido! Deve conter apenas letras.\n");
            return 0;
        }
    }

    int capitalizeNext = 1;

    for(int i = 0; i < strlen(city); i++)
    {
        if(isalpha((unsigned char)city[i]))
        {
            if(capitalizeNext)
            {
                formattedCity[i] = toupper((unsigned char)city[i]);
                capitalizeNext = 0;
            }
            else
            {
                formattedCity[i] = tolower((unsigned char)city[i]);
            }
        }
        else if (city[i] == ' ')
        {
            capitalizeNext = 1;
            formattedCity[i] = ' ';
        }

        formattedCity[MAX_CITY_LENGTH - 1] = '\0';

        return 1;
    }
}


