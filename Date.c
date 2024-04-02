#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Date.h"
#include "General.h"
const int DayMonths[MAX_MONTHS] = { 31,28,31,30,31,30,31 ,31,30,31,30,31 };
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
    return 1;
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
    if (month < MIN_MONTHS || month > MAX_MONTHS || year < MIN_YEAR || day < 0 || day > DayMonths[month - 1])
        return 0;

    pDate->day = day;
    pDate->month = month;
    pDate->year = year;

    return 1;
}

int calculateDaysOfRental(Date start, Date end)
{
    int totalDays = 0;
    totalDays += (DAYS_IN_YEAR * (end.year - start.year));
    if (end.month < start.month)
    {
        for (int i = start.month - 1; i < MAX_MONTHS; i++)
            totalDays += (DayMonths[i]);
        for (int i = 0; i < end.month - 1; i++)
            totalDays += (DayMonths[i]);
    }
    else
    {
        for (int i = start.month - 1; i < end.month - 1; i++)
            totalDays += (DayMonths[i]);
    }
    totalDays = totalDays - start.day + end.day;
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
