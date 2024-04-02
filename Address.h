#pragma once
#include <stdio.h>
#include "General.h"

#define MAX_STREET_LENGTH 50
#define MAX_CITY_LENGTH 50
#define MAX_COUNTRY_LENGTH 50

typedef struct {
    char street[MAX_STREET_LENGTH];
    char city[MAX_CITY_LENGTH];
    char country[MAX_COUNTRY_LENGTH];

} Address;

int initAddress(Address* address, char* str);