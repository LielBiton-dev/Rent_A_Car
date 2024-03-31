#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Rental.h"

int initRental(Rental* rental, Customer* customer, Vehicle* vehicle)
{
	rental->rentalSN = generateRentalSN();
	getCorrectDate(&rental->startDate);
	int ok = 0;
	do {
		getCorrectDate(&rental->endDate);
		ok = checkDates(rental->startDate, rental->endDate);
	} while (!ok);

	rental->customer = *customer;
	rental->vehicle = vehicle;
	rental->insurance = createInsurance();
	rental->totalCost = calculateTotalCost(rental);
	rental->invoice = createInvoice(rental->totalCost, rental->rentalSN);

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

int generateRentalSN()
{
	static int currentSerialNumber = START_SN_RENT; // Initial serial number
	return currentSerialNumber++;
}

int updateRental(Rental* rental); //what would you like to update? add menu - needs to be in RentalCompany

float calculateTotalCost(Rental* rental)
{
	float num = 0;
	int days = calculateDaysOfRental(rental->startDate, rental->endDate);
	num += (days * (rental->insurance.costPerDay + rental->vehicle->costPerDay));
	return num;
}

int calculateDaysOfRental(Date start, Date end)
{
	int totalDays = 0;
	totalDays += (DAYS_IN_YEAR * (end.year - start.year));
	if (end.month < start.month)
	{
		for (int i = start.month-1; i < MAX_MONTHS; i++)
			totalDays += (DAY_MONTHS[i]);
		for (int i = 0; i < end.month - 1; i++)
			totalDays += (DAY_MONTHS[i]);
	}
	else
	{
		for (int i = start.month - 1; i < end.month - 1; i++)
			totalDays += (DAY_MONTHS[i]);
	}
	totalDays = totalDays - start.day + end.day;
}

int endRental(Rental* rental)
{
	rental->vehicle->isTaken = 0;
	updateOdometer(rental->vehicle, calculateDaysOfRental(rental->startDate, rental->endDate), AVG_KM);
	printInvoice(&rental->invoice);
}