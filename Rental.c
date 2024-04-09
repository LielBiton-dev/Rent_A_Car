#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Rental.h"
static int rentalSN_generator = START_SN_RENT;

int initRental(Rental* rental, Customer* customer, Vehicle* vehicle, int branchID)
{
	rental->rentalSN = rentalSN_generator++;
	printf("Enter Start Date: ");
	getCorrectDate(&rental->startDate);
	int ok = 0;
	do {
		printf("Enter End Date: ");
		getCorrectDate(&rental->endDate);
		ok = checkRentDates(rental->startDate, rental->endDate);
	} while (!ok);

	rental->customer = *customer;
	rental->vehicle = vehicle;
	rental->branchID = branchID;
	rental->insurance = *(createInsurance());
	rental->totalCost = 0;
	rental->invoice = *(createInvoice(rental->totalCost, rental->rentalSN));
	return 1;
}

int checkRentDates(Date start, Date end)
{
	if (end.year < start.year)
		return 0;
	if (end.year == start.year && end.month < start.month)
		return 0;
	if (end.year == start.year && end.month == start.month && end.day < start.day)
		return 0;
	return 1;
}

int compareRentalByVehicleSN(const void* v1, const void* v2)
{
	Rental* e1 = (Rental*)v1;
	Rental* e2 = (Rental*)v2;
	return e1->vehicle->vehicleSN - e1->vehicle->vehicleSN;
}

int updateRentalGenerator(int num)
{
	rentalSN_generator = num;
	return ++rentalSN_generator;
}

int getCurrentRentalGenerator()
{
	return rentalSN_generator;
}

float calculateTotalCost(Rental* rental)
{
	float num = 0.0;
	int days = calculateDaysOfRental(rental->startDate, rental->endDate);
	num = num + (days * (rental->insurance.costPerDay + rental->vehicle->costPerDay));
	return num;
}

int endRental(Rental* rental)
{
	rental->vehicle->isTaken = 0;
	updateOdometer(rental->vehicle, calculateDaysOfRental(rental->startDate, rental->endDate), AVG_KM);
	printInvoice(&rental->invoice);
	return 1;
}

void printRental(const Rental* rental)
{
	printf("\033[1;32mRental serial number: %d\033[0m\n", rental->rentalSN);
	printCustomer(&rental->customer);
	printf("Rent From ");
	printDate(&rental->startDate);
	printf("Until ");
	printDate(&rental->endDate);
	printf("\nPick up vehicle number %d from branch number %d\n", rental->vehicle->vehicleSN, rental->branchID);
	//rental->vehicle->print(rental->vehicle);
	printInsurance(&rental->insurance);
	printInvoice(&rental->invoice);
}

void freeRental(Rental* rental)
{
	free(rental->vehicle);
	freeCustomer(&rental->customer);
}