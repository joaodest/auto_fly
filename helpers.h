#ifndef HELPERS_H
#define HELPERS_H

#define MAX_DATE_LENGTH 10
#define MAX_TIME_LENGTH
#define AIRPORT_CODE_LENGTH 4
#define MAX_CITY_LENGTH 50

void formatDate(char *formattedDate, const char *date);

int validateAirportCode(const char *code, char *formattedCode);

int validateCityName(const char *city, char *formattedCity);
#endif
