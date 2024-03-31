#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "Customer.h"
#define PHONE_TAV '-'

int initCustomer(Customer* customer)
{
    customer->ID = getCustomerID();
    getCustomerFullName(customer);
    getCorrectDate(&customer->birthDate);
    getPhoneNumber(customer);
    customer->age = calculateAge(&customer->birthDate);
}

int getCustomerID()
{
    int num;
    printf("Enter your ID (numbers only)\n");
    scanf("%d", &num);
    return num;
}

int getPhoneNumber(Customer* customer)
{
    char phone[MAX_STR_LEN];
    int ok = 1;

    do {
        printf("Enter Phone ***%c*******\t", PHONE_TAV);
        myGets(phone, MAX_STR_LEN, stdin);
        if (strlen(phone) != PHONE_LEN)
        {
            printf("Phone should be %d numbers\n", PHONE_LEN);
            ok = 0;
        }
    } while (!ok);

    strcpy(customer->phone, phone);
}

int getCustomerFullName(Customer* customer)
{
    customer->firstName = getStrExactName("Enter your first name\n");
    customer->lastName = getStrExactName("Enter your last name\n");
    return 1;
}

int calculateAge(Date* birthDate)
{
    time_t currentTime;
    struct tm* localTime;

    // Get current time
    time(&currentTime);
    localTime = localtime(&currentTime);

    int currentYear = localTime->tm_year + 1900;
    int age = currentYear - birthDate->year;

    return age;
}