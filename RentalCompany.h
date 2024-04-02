#pragma once
#include <stdio.h>
#include "List.h"
#include "Customer.h"
#include "Rental.h"
#include "Branch.h"

#define MAX_NAME_STR 50
#define COMPANY_MAX_VEHICLES 1000
const int Daily_Rate = 100;
const float Economy_multiplier = 1.0;
const float Luxury_multiplier = 2.0;
const float Motorcycle_multiplier = 0.7;

typedef struct {
	char companyName[MAX_NAME_STR];
	LIST branch_list;
	Vehicle** vehicleArr;
	Customer* customerArr;
	Rental* rentalArr;
	int num_vehicles;
	int num_vehicles_available;
	int num_customers;
	int num_rentals;
	int num_branches;
}RentalCompany;



BOOL initCompany(RentalCompany* company);

BOOL Company_printVehicles_All(const RentalCompany* company);

BOOL Company_printVehicles_byBranch(const RentalCompany* company, const int branchID);

BOOL Company_printVehicles_byType(const RentalCompany* company, const int typeInt);

BOOL Company_printVehicles_byBrand(const RentalCompany* company, const int brandInt);

BOOL Company_printVehicles_Available(const RentalCompany* company);

BOOL Company_printCustomers_All(const RentalCompany* company);

Vehicle* findVehicle(const RentalCompany* company);

float Company_calculateRevenue(const RentalCompany* company);

BOOL addVehicle(RentalCompany* company);

Branch* addBranch(RentalCompany* company);

Vehicle* addNewVehicle_toBranch(RentalCompany* company);

int countBranches(RentalCompany* company);

Branch* chooseAndFind_Branch(RentalCompany* company);

Customer* addCustomer(RentalCompany* company);

BOOL removeCustomer(RentalCompany* company);

Rental* addRental(RentalCompany* company);

BOOL closeRental(RentalCompany* company);


