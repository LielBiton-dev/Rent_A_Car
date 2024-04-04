#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Rental.h"

int initRental(Rental* rental, Customer* customer, Vehicle* vehicle, int branchID)
{
	rental->rentalSN = generateRentalSN();
	getCorrectDate(&rental->startDate);
	int ok = 0;
	do {
		getCorrectDate(&rental->endDate);
		ok = checkRentDates(rental->startDate, rental->endDate);
	} while (!ok);

	rental->customer = *customer;
	rental->vehicle = vehicle;
	rental->branchID = branchID;
	rental->insurance = *(createInsurance());
	rental->totalCost = calculateTotalCost(rental);
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

int generateRentalSN()
{
	static int currentSerialNumber = START_SN_RENT; // Initial serial number
	return currentSerialNumber++;
}

float calculateTotalCost(Rental* rental)
{
	float num = 0;
	int days = calculateDaysOfRental(rental->startDate, rental->endDate);
	num += (days * (rental->insurance.costPerDay + rental->vehicle->costPerDay));
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
	printf("Rental serial number: %d\n", rental->rentalSN);
	printCustomer(&rental->customer);
	printf("Rent vehicle: ");
	rental->vehicle->print;
	printf("From ");
	printDate(&rental->startDate);
	printf("to ");
	printDate(&rental->endDate);
	printInsurance(&rental->insurance);
	printInvoice(&rental->invoice);
}

void freeRental(Rental* rental)
{
	//freeVehicle
	free(rental->vehicle);
	freeCustomer(&rental->customer);
}