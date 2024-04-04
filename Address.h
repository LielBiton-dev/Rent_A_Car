#pragma once
#include <stdio.h>


typedef enum {eIsrael, eThailand, eUSA, eNumCountries} eCountry;
static const char* Countries[eNumCountries] = { "Israel" , "Thailand" , "USA" };

typedef struct {
	eCountry country;
	char* city;
	char* street;
	int number;
} Address;

void initAddress(Address* address);
