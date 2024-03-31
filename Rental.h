#pragma once
#include "Customer.h"
#include "Invoice.h"
#include "Insurance.h"
#include "Vehicle.h"

#define START_SN_RENT 0
#define AVG_KM 100

typedef struct {
    int rentalSN;
    Vehicle* vehicle;
    Customer customer;
    Date startDate;
    Date endDate;
    float totalCost;
    Insurance insurance;
    Invoice invoice;

    //Branch* branch - from struct "Branches" choose the pointer to the right branch from list
}Rental;

int initRental(Rental* rental, Customer* customer, Vehicle* vehicle);
int checkRentDates(Date start, Date end);
int generateRentalSN();
int updateRental(Rental* rental); //what would you like to update? add menu
float calculateTotalCost(Rental* rental);
int calculateDaysOfRental(Date start, Date end);
int endRental(Rental* rental);
void printRental(const Rental* rental);
void freeRental(Rental* rental);
