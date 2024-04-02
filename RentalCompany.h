#pragma once
#include <stdio.h>
#include "List.h"
#include "Rental.h"
#define COMPANY_MAX_VEHICLES 150

typedef struct {
	char* companyName;
	LIST branch_list;
	Vehicle** vehicleArr;
	Customer* customerArr;
	Rental* rentalArr; //I added
	int numVehicles;
	int numCustomers;
	int numRentals;

}RentalCompany;



BOOL initCompany(RentalCompany* company);

BOOL printVehicles_All(const RentalCompany* company);

BOOL printVehicles_Available(const RentalCompany* company);
int addVehicle(RentalCompany* company);
void findVehicle(const RentalCompany* company);
float Company_calculateRevenue(const RentalCompany* company);
int addBranch(RentalCompany* company);
BOOL rentACar();