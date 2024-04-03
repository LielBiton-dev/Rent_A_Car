#pragma once
#include <stdio.h>
#include "List.h"
#include "Rental.h"
#define COMPANY_MAX_VEHICLES 150
typedef enum { eNoSort, eOdometer, eSerialNumber, eYear, eLicensePlate, eOpt } sortType;
static const char* sortName[eOpt] = { "Unsorted", "Odometer","Serial Number", "Manufacture Year","License Plate" };

typedef enum {eStartDate, eEndDate, eVehicle, eNum} updateType;
static const char* updateName[eNum] = { "Start Date", "End Date","Vehicle"};

typedef int (*CompareFunction)(const void*, const void*);
static const CompareFunction compareFunctions[] = { NULL, compareByOdometer, compareBySN, compareByYear, compareByLicensePlate};

typedef struct {
	char* companyName;
	LIST branch_list;
	Vehicle** vehicleArr;
	Customer* customerArr;
	Rental* rentalArr;
	int numVehicles;
	int numCustomers;
	int numRentals;
	sortType sortBy;

}RentalCompany;



BOOL initCompany(RentalCompany* company);
int addBranch(RentalCompany* company);
int addVehicle(RentalCompany* company);
int addCustomer(RentalCompany* company);
int addRental(RentalCompany* company);

Vehicle* findVehicleBySN(Vehicle** vehicleArr, int numVehicles, int SN);
Customer* findCustomerByID(Customer* customerArr, int numCustomers, char* ID);
void sortVehicles(RentalCompany* company);
void findVehicle(const RentalCompany* company);
sortType getSortType();
void askUserSearchParameter(Vehicle* toSearch, const RentalCompany* company);
int isVehicleAvailableInDates(const RentalCompany* company, Vehicle* vehicle, Date* start, Date* end); // Returns 1 if the vehicle that was sent is available in the dates that were sent (by customer request).
void updateRental(RentalCompany* company); // Can update start date, end date or vehicle.
int chooseIndexFromRentalArray(RentalCompany* company);
updateType getUpdateType();
void updateVehicleInRental(RentalCompany* company, int rentalIndex);

void printAvailableVehicles(const RentalCompany* company, Rental* rental);
void printAllVehicles(const RentalCompany* company);
void printCompany(const RentalCompany* company);
void printAllCustomers(const RentalCompany* company);
void printAllRentals(const RentalCompany* company);
void printAllBranches(const RentalCompany* company);

float Company_calculateRevenue(const RentalCompany* company);
BOOL rentACar();
void freeCompany(RentalCompany* company);