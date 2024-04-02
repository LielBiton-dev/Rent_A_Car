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

BOOL Company_printVehicles_All(const RentalCompany* company);

BOOL Company_printVehicles_byBranch(const RentalCompany* company, const int branchID);

BOOL Company_printVehicles_byType(const RentalCompany* company, const int typeInt);

BOOL Company_printVehicles_byBrand(const RentalCompany* company, const int brandInt);
BOOL Company_printVehicles_Available(const RentalCompany* company);
int addVehicle(RentalCompany* company);
void findVehicle(const RentalCompany* company);
float Company_calculateRevenue(const RentalCompany* company);
int addBranch(RentalCompany* company);
BOOL rentACar();