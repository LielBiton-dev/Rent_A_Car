#pragma once

#define MAX_STR_LEN 255

char* getStrExactName(const char* msg);
char* myGets(char* buffer, int size, FILE* source);
char* getDynStr(char* str);
double getDoubleNum(const char* msg);
int getIntegerNum(const char* msg);
int getYesNoAnswer(const char* msg);