#include "datetime_utils.h"
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


