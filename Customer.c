#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "Customer.h"
#include "General.h"
#define PHONE_TAV '-'

int initCustomer(Customer* customer)
{
    if (!getCustomerID(customer)) return 0;
    getCustomerFullName(customer);
    //getCorrectDate(&customer->birthDate);
    if (!getPhoneNumber(customer)) return 0;
    customer->age = getAge();
    return 1;
}

int getCustomerID(Customer* customer)
{
    char id[MAX_STR_LEN];
    int ok = 1;
    do {
        printf("Enter your ID (numbers only)\n");
        myGets(id, MAX_STR_LEN, stdin);
        if (strlen(id) != ID_LEN)
        {
            printf("ID should be 9 numbers. Try again.\n");
            ok = 0;
        }
    } while (!ok);
    strcpy(customer->ID, id);
    return 1;
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
    return 1;
}

int getCustomerFullName(Customer* customer)
{
    customer->firstName = getStrExactName("Enter your first name\n");
    customer->lastName = getStrExactName("Enter your last name\n");
    return 1;
}

int getAge()
{
    int age;
    do {
        printf("Enter your age\n");
        scanf("%d", &age);
        if (age < MIN_AGE)
            printf("Not above minimum age for rental.\n");
    } while (age < MIN_AGE);
    return age;
}

void printCustomer(const Customer* customer)
{
    printf("Customer %s %s:\nID %s\tAge %d\tphone %s\n", 
        customer->firstName, customer->lastName, customer->ID, customer->age, customer->phone);
}

void freeCustomer(Customer* customer)
{
    free(customer->firstName);
    free(customer->lastName);
}