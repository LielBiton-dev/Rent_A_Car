#pragma once

#include "Customer.h"
#include "Insurance.h"
#include "Vehicle.h"
#include "Invoice.h"
#include "Branch.h"

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
    int branchID; //print all branches and choose a proper ID.
   
}Rental;

int initRental(Rental* rental, Customer* customer, Vehicle* vehicle, int branchID);
int checkRentDates(Date start, Date end);
int generateRentalSN();
int updateRental(Rental* rental); //what would you like to update? add menu
float calculateTotalCost(Rental* rental);
int calculateDaysOfRental(Date start, Date end);
int endRental(Rental* rental);
void printRental(const Rental* rental);
void freeRental(Rental* rental);
