#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Insurance.h"

Insurance* createInsurance()
{
	Insurance* insurance = (Insurance*)malloc(sizeof(Insurance));
	insurance->type = getInsuranceType();
	insurance->costPerDay = costs[insurance->type];
	insurance->InsuranceSN = generateInsuranceSN();

	return insurance;
}

int generateInsuranceSN () 
{
	static int currentSerialNumber = START_SN_INSUR; // Initial serial number
	return currentSerialNumber++;
}

eType getInsuranceType() 
{
	int option;
	do {
		printf("Please enter one of the following types\n");
		for (int i = 0; i < eNumTypes; i++)
			printf("%d for %s\n", i, types[i]);
		scanf("%d", &option);
	} while (option < 0 || option >= eNumTypes);
	getchar();
	return (eType)option;
}

const char* GetTypeStr(int type)
{
	if (type < 0 || type >= eNumTypes)
		return NULL;
	return types[type];
}

void printInsurance(const Insurance* insurance)
{
	printf("Insurance %s number %d\n", GetTypeStr((int)insurance->type), insurance->InsuranceSN);
}