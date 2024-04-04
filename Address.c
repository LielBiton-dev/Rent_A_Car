#include <stdio.h>
#include "string.h"
#include "General.h"
#include "Address.h"

void initAddress(Address* address) { //string to address
	int choice;
	do {
		printf("\nSelect country:");
		for (int i = 0; i < eNumCountries; i++)
			printf("\n[%d]-%s", i, Countries[i]);

	} while (!scanf("%d", &choice) || choice >= eNumCountries || choice < 0);
	address->country = choice;

	printf("\nEnter city name:");
	myGets(address->city, MAX_STR_LEN, stdin);

	printf("\nEnter street name:");
	myGets(address->street, MAX_STR_LEN, stdin);

	do {
		printf("\nEnter number:");
	} while (!scanf("%d", &address->number));
		
}

void printAddress(Address* address) {
	char* adStr = address->street;
	strcat(adStr, address->number);
	strcat(adStr, ' ');
	strcat(adStr, ",");
	strcat(adStr, address->city);
	strcat(adStr, ",");
	strcat(adStr, Countries[address->country]);

	printf("%s", adStr);
	free(adStr);
}