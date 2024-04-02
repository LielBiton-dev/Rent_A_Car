#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Vehicle.h"
#include "General.h"

void initPremium(Vehicle** vehicleArr, Vehicle* premium, int vehicleCount)
{
	initVehicle(vehicleArr, premium, vehicleCount);
	premium->print = printPremium;
	premium->category.premium.isElectric = getYesNoAnswer("Enter 1 for electric vehicle.\nEnter 0 if other.\n");
	premium->category.premium.feature = getPremiumFeature();
	premium->category.premium.brand = getVehicleBrand(PremiumBrand, eNumPremiumBrands);
}

void initStandard(Vehicle** vehicleArr, Vehicle* standard, int vehicleCount)
{
	initVehicle(vehicleArr, standard, vehicleCount);
	standard->print = printStandard;
	standard->category.standard.cargoCapacity = getDoubleNum("Enter cargo capacity: ");
	standard->category.standard.brand = getVehicleBrand(StandardBrand, eNumStandardBrands);
}

void initCompact(Vehicle** vehicleArr, Vehicle* compact, int vehicleCount)
{
	initVehicle(vehicleArr, compact, vehicleCount);
	compact->print = printCompact;
	compact->category.compact.fuelEfficiency = getDoubleNum("Enter the fuel efficiency: ");
	compact->category.compact.brand = getVehicleBrand(CompactBrand, eNumCompactBrands);
}

void initVehicle(Vehicle** vehicleArr, Vehicle* vehicle, int vehicleCount)
{
	vehicle->vehicleSN = getVehicleSN(vehicleArr, vehicleCount);
	vehicle->year = getvehicleYear(MIN_MAN_YEAR);
	vehicle->numSeats = getNumSeats();
	vehicle->gearBox = getYesNoAnswer("Enter 1 for automatic transmission.\nEnter 0 for manual transmission.\n");
	vehicle->isTaken = 0;
	vehicle->odometer = 0;
	getLicensePlate(vehicle);
}

eFeatures getPremiumFeature()
{
	int option;
	printf("\n\n");
	do {
		printf("Please choose one of the following features\n");
		for (int i = 0; i < eNofOpt; i++)
			printf("%d for %s\n", i, Features[i]);
		scanf("%d", &option);
	} while (option < 0 || option >= eNofOpt);
	getchar();
	return (eFeatures)option;
}

int getVehicleBrand(char** arrName, int numOfOpt)
{
	int option;
	printf("\n\n");
	do {
		printf("Please choose one of the following brands\n");
		for (int i = 0; i < numOfOpt; i++)
			printf("%d for %s\n", i, arrName[i]);
		scanf("%d", &option);
	} while (option < 0 || option >= numOfOpt);
	getchar();
	return option;
}

double getDoubleNum(const char* msg)
{
	double num;
	do {
		printf("%s\t", msg);
		scanf("%lf", &num);
	} while (num <= 0);
	printf("\n");
	return num;
}

void getLicensePlate(Vehicle* vehicle)
{
	char plate[MAX_STR_LEN];
	int ok = 1;

	do {
		printf("Enter License Plate\t");
		myGets(plate, MAX_STR_LEN, stdin);
		if (strlen(plate) > MAX_PLATE)
		{
			printf("License plate should be maximum %d chars\n", MAX_PLATE);
			ok = 0;
		}
	} while (!ok);

	strcpy(vehicle->licensePlate, plate);
}

int getYesNoAnswer(const char* msg)
{
	int num;
	do {
		printf("%s\t", msg);
		scanf("%d", &num);
	} while (num != 0 && num != 1);
	printf("\n");
	return num;
}

int getNumSeats()
{
	int num;
	do {
		for (int i = 0; i < SEATS_OPT; i++)
			printf("Enter %d for %d seats\n", i,Seats[i]);
		scanf("%d", &num);
	} while (num < Seats[0] || num>Seats[SEATS_OPT - 1]);
	return num;
}

int getvehicleYear(int minYear)
{
	int num;
	do {
		printf("Enter vehicle year of manufacture\n");
		scanf("%d", &num);
		if (num < minYear)
			printf("The year is under the minimum. Try again.\n");
	} while (num < minYear);
	return num;
}

int getVehicleSN(Vehicle** vehicleArr, int vehicleCount)
{
	int num;
	int unique = 0;
	do {
		printf("Enter vehicle serial number\n");
		scanf("%d", &num);
		unique = checkUniqueSN(num, vehicleArr, vehicleCount);
	} while (!unique);
	return num;
}

void updateOdometer(Vehicle* vehicle, int totalDays, int kmPerDay)
{
	vehicle->odometer += (totalDays * kmPerDay);
}

int rentVehicle(Vehicle* vehicle)
{
	//add extra check about dates?
	vehicle->isTaken = 1;
	return 1;
}

int checkUniqueSN(int SN, Vehicle** vehicleArr, int vehicleCount)
{
	for (int i = 0; i < vehicleCount; i++)
	{
		if (vehicleArr[i]->vehicleSN == SN)
			return 0;
	}
	return 1;
}

int compareByOdometer(const void* v1, const void* v2)
{
	Vehicle* e1 = (Vehicle*)v1;
	Vehicle* e2 = (Vehicle*)v2;
	return (int)(e1->odometer - e2->odometer);
}

int compareByYear(const void* v1, const void* v2)
{
	Vehicle* e1 = (Vehicle*)v1;
	Vehicle* e2 = (Vehicle*)v2;
	return e1->year - e2->year;
}

int compareBySN(const void* v1, const void* v2)
{
	Vehicle* e1 = (Vehicle*)v1;
	Vehicle* e2 = (Vehicle*)v2;
	return e1->vehicleSN - e2->vehicleSN;
}

void printVehicle(const Vehicle* vehicle)
{
	printf("Serial Number: %d\nNumber of seats: %d\nYear: %d\n", vehicle->vehicleSN, vehicle->numSeats, vehicle->year);
	printf("Odometer: %e\nLicense plate: %s\n", vehicle->odometer, vehicle->licensePlate);

	//add gearbox, cost and is taken.
}
void printPremium(const Vehicle* premium)
{
	printVehicle(premium);
	printf("Premium vehicle brand: %s\n", PremiumBrand[premium->category.premium.brand]);
	printf("Feature: %s\n", Features[premium->category.premium.feature]);
	if (premium->category.premium.isElectric)
		printf("Vehicle is electric.\n");
}
void printStandard(const Vehicle* standard)
{
	printVehicle(standard);
	printf("Standard vehicle brand: %s\n", StandardBrand[standard->category.standard.brand]);
	printf("With %e cargo capacity\n", standard->category.standard.cargoCapacity);

}
void printCompact(const Vehicle* compact) 
{
	printVehicle(compact);
	printf("Compact vehicle brand: %s\n", CompactBrand[compact->category.compact.brand]);
	printf("With %e fuel Efficiency\n", compact->category.compact.fuelEfficiency);
}