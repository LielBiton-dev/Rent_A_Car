#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Vehicle.h"

void updateOdometer(Vehicle* vehicle, int totalDays, int kmPerDay)
{
	vehicle->odometer += (totalDays * kmPerDay);
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
	return e1->odometer - e2->odometer;
}

int compareByCost(const void* v1, const void* v2)
{
	Vehicle* e1 = (Vehicle*)v1;
	Vehicle* e2 = (Vehicle*)v2;
	return e1->costPerDay, e2->costPerDay;
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

	//add is electric
}
void printStandard(const Vehicle* standard)
{
	printVehicle(standard);
	printf("Standard vehicle brand: %s\n", StandardBrand[standard->category.standard.brand]);
	printf("With %e cargo capacity\n", standard->category.standard.cargoCapacity);

	//add baby chair
}
void printCompact(const Vehicle* compact) 
{
	printVehicle(compact);
	printf("Compact vehicle brand: %s\n", CompactBrand[compact->category.compact.brand]);
	printf("With %e fuel Efficiency\n", compact->category.compact.fuelEfficiency);
}