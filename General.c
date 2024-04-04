#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "General.h"

char* getStrExactName(const char* msg)
{
	char* str;
	char temp[MAX_STR_LEN];
	printf("%s\t", msg);
	myGets(temp, MAX_STR_LEN, stdin);

	str = getDynStr(temp);
	return str;
}

char* getDynStr(char* str)
{
	char* theStr;
	theStr = (char*)malloc((strlen(str) + 1) * sizeof(char));
	if (!theStr)
		return NULL;

	strcpy(theStr, str);
	return theStr;
}

char* myGets(char* buffer, int size, FILE* source)
{
	char* ok;
	if (buffer != NULL && size > 0)
	{
		do { //skip only '\n' strings
			ok = fgets(buffer, size, source);
		} while (ok && ((strlen(buffer) <= 1) && (isspace(buffer[0]))));
		if (ok)
		{
			char* back = buffer + strlen(buffer);
			//trim end spaces
			while ((buffer < back) && (isspace(*--back)));
			*(back + 1) = '\0';
			return buffer;
		}
		buffer[0] = '\0';
	}
	return NULL;
}
char** splitCharsToWords(char* str, int* pCount, int* pTotalLength)
{
	char temp[255];
	char* delimiters = ",";
	char* word;
	int count = 0;

	strcpy(temp, str);
	char** wordsArray = NULL;
	*pTotalLength = 0;

	word = strtok(temp, delimiters);
	while (word != NULL)
	{
		wordsArray = (char**)realloc(wordsArray, (count + 1) * sizeof(char*));
		if (!wordsArray)
			return 0;
		wordsArray[count] = getDynStr(word);
		count++;
		*pTotalLength += (int)strlen(word);
		word = strtok(NULL, delimiters);
	}
	*pCount = count;
	return wordsArray;
}

void generalArrayFunction(void* arr, int size, size_t typeSize, void(*f)(void*))
{
	for (int i = 0; i < size; i++)
	{
		f((char*)arr + i * typeSize);
	}
}
double getDoubleNum(const char* msg)
{
	double num;
	do {
		printf("%s\t", msg);
		scanf("%lf", &num);
	} while (num <= 0);
	printf("\n");
	return num;
}

int getIntegerNum(const char* msg)
{
	int num;
	do {
		printf("%s\t", msg);
		scanf("%d", &num);
	} while (num <= 0);
	printf("\n");
	return num;
}

int getYesNoAnswer(const char* msg)
{
	int num;
	do {
		printf("%s\t", msg);
		scanf("%d", &num);
	} while (num != 0 && num != 1);
	printf("\n");
	return num;
}