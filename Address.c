#include <stdio.h>
#include "string.h"
#include "General.h"
#include "Address.h"

BOOL initAddress(Address* address, char* str) { //string to address

	int numStrings;
	if (!address)
		return False;
	char* sepStr = splitCharsToWords(str, &numStrings);
	for (int i = 0; i < numStrings; i++)
	{
		switch (i)
		{
		case 0:
			strcpy(&address->country, sepStr[i]);
			break;
		case 1:
			strcpy(&address->city, sepStr[i]);
			break;
		case 2:
			strcpy(&address->street, sepStr[i]);
			break;

		default: return False;
		}
		
	}
}

void printAddress(Address* address) {
	char* adStr = address->street;
	strcat(adStr, ",");
	strcat(adStr, address->city);
	strcat(adStr, ",");
	strcat(adStr, address->country);
	printf("%s", adStr);
	free(adStr);
}