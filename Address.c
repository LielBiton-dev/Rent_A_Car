#include <stdio.h>

#include "Address.h"

//BOOL initAddress(Address* address, char* str) { //string to address
//
//	int numStrings;
//	myGets(str, MAX_CITY_LENGTH + MAX_COUNTRY_LENGTH + MAX_STREET_LENGTH, stdin);
//	if (!address)
//		return False;
//	char* sepStr = splitCharsToWords(str, &numStrings);
//	for (int i = 0; i < numStrings; i++)
//	{
//		switch (i)
//		{
//		case 0:
//			strcpy(&address->country, sepStr[i]);
//			break;
//		case 1:
//			strcpy(&address->city, sepStr[i]);
//			break;
//		case 2:
//			strcpy(&address->street, sepStr[i]);
//			break;
//
//		default: return False;
//		}
//
//	}
//}