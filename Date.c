#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "General.h"
#include "Date.h"
#define DATE_TAV '#'

int getCorrectDate(Date* pDate) //extract Date from inputted string
{
    char date[MAX_STR_LEN];
    int ok = 1;

    do {
        printf("Enter Date dd%c%cmm%c%cyyyy\t",
            DATE_TAV, DATE_TAV, DATE_TAV, DATE_TAV);
        myGets(date, MAX_STR_LEN, stdin);
        ok = checkDate(date, pDate);
        if (!ok)
            printf("Error, try again\n");
    } while (!ok);
}

int	 checkDate(char* date, Date* pDate)
{
    int day, month, year;
    if (strlen(date) != MAX_DATE_LEN)
        return 0;

    // read the date components from the input string
    //check date: exact size, number of integers and regural date validation.

    if (sscanf(date, "%d##%d##%d", &day, &month, &year) != 3)
        return 0;
    if (month < MIN_MONTHS || month > MAX_MONTHS || year < MIN_YEAR || day < 0 || day > DAY_MONTHS[month - 1])
        return 0;

    pDate->day = day;
    pDate->month = month;
    pDate->year = year;

    return 1;
}

void printDate(const Date* date) {
    printf(" Date: %d/%d/%d ", date->day, date->month, date->year);
}

int writeDateToBFile(FILE* fp, Date* pDate)
{
    if (fwrite(pDate, sizeof(Date), 1, fp) != 1) return 0;
    return  1;
}