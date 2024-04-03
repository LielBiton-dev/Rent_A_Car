#pragma once

#define PHONE_LEN 10
#define ID_LEN 9
#define MIN_AGE 21

typedef struct {
    char ID[ID_LEN];
    char* firstName;
    char* lastName;
    char phone[PHONE_LEN];
    int age;
}Customer;

int initCustomer(Customer* customer);
int getCustomerID(Customer* customer);
int getPhoneNumber(Customer* customer);
int getCustomerFullName(Customer* customer);
int getAge();
int checkID(const char* ID);
void printCustomer(const Customer* customer);
void freeCustomer(Customer* customer);