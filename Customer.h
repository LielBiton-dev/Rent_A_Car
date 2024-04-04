#pragma once
#include "Date.h"
#include "General.h"
#define PHONE_LEN 20
typedef struct {
    int ID;
    char* firstName;
    char* lastName;
    char phone[PHONE_LEN];
    Date birthDate;
    int age;
}Customer;

int initCustomer(Customer* customer);
int getCustomerID();
int getPhoneNumber(Customer* customer);
int getCustomerFullName(Customer* customer);
int calculateAge(Date* birthDate);
void printCustomer(const Customer* customer);
void freeCustomer(Customer* customer);