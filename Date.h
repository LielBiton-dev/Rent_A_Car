#pragma once

#define MAX_MONTHS 12
#define MIN_MONTHS 1
#define MIN_YEAR 1999
#define MAX_DATE_LEN 12
#define DAYS_IN_YEAR 365

typedef struct {
    int day;
    int month;
    int year;
}Date;

int getCorrectDate(Date* date);
int	 checkDate(char* date, Date* pDate);
int calculateDaysOfRental(Date start, Date end);
void printDate(const Date* date);
int writeDateToBFile(FILE* fp, Date* pDate);

//nothing to free