#pragma	once

#include "RentalCompany.h"
#include <stdio.h>
#include "General.h"
#include "Branch.h"
#include <stdlib.h>


BOOL initCompany(RentalCompany* company) {
	/*if (company == NULL)
		return False;

	printf("\nEnter company name : ");
	myGets(company->companyName, MAX_NAME_STR, stdin);
	L_init(&company->branch_list); 
	company->num_customers = 0;
	company->num_rentals = 0;
	company->num_vehicles = 0;
	company->num_vehicles_available = 0;
	company->num_branches = 0;*/
	company->companyName = getStrExactName("Enter company name\n");
	if (!L_init(&company->branch_list))
		return 0;
	company->customerArr = NULL;
	company->vehicleArr = NULL;
	company->rentalArr = NULL;
	company->numRentals = 0;
	company->numCustomers = 0;
	company->numVehicles = 0;
	company->sortBy = 0;
	return 1;
}

int addBranch(RentalCompany* company) {
	Branch newBranch;
	if (!initBranch(&newBranch) || !company)
		return 0;

	NODE* lastNode = &company->branch_list.head;
	while (lastNode->next != NULL)
	{
		lastNode = lastNode->next;
	}

	L_insert(lastNode, &newBranch);
	return 1;
}



	/*for (int i = 0; i < company->num_branches; i++)
	{
		int rowSize = sizeof(company->vehicleArr[i]) / sizeof(Vehicle);
		for (int j = 0; j < rowSize; j++)
		{
			company->vehicleArr[i][j].print(&company->vehicleArr[i][j]);
		}
	}*/


	

int chooseBranch(RentalCompany *company) {
	int choice, i;
	NODE* node = &company->branch_list.head.next;
	if (!node) {
		printf("\nThere are no Branches to your company. Try adding a branch first");
		return -1;
	}
	do {
		printf("\nChoose branch : ");
		for (i = 0; (node != NULL); i++, node = node->next)
		{
			printf("\n[%d]", i);
			printBranch(node->key);
		}

	} while (!scanf("%d", &choice) || choice >= i || choice < 0);

	return choice;
}

int addCustomer(RentalCompany* company) {
	Customer newCust;
	initCustomer(&newCust);
	if (company->customerArr == NULL)
			company->customerArr = (Customer*)malloc(sizeof(Customer));
		
	else 
		company->customerArr = (Customer*)realloc(company->customerArr, (company->numCustomers +1)*sizeof(Customer));
	
	if (!company->customerArr)
		return 0;
	
	company->customerArr[company->numCustomers] = newCust;
	company->numCustomers++;
	return 1;
}

int addRental(RentalCompany* company, Customer* cust, Vehicle* vehicle) {
	Rental newRental;
	printf("\nSelect Pick-up location : ");
	int branchID = chooseBranch(company);
	initRental(&newRental, cust, vehicle,branchID);
	if (!company->rentalArr)
		company->rentalArr = (Rental*)malloc(sizeof(Rental));
	else
		company->rentalArr = (Rental*)realloc(company->rentalArr, (company->numRentals + 1) * sizeof(Rental));
	if (!company->rentalArr)
		return 0;
	company->rentalArr[company->numRentals] = newRental;
	company->numRentals++;
	return 1;
}


BOOL addVehicle(RentalCompany* company) {
	int choice = 0;

	Vehicle* pVehicle = (Vehicle*)calloc(1, sizeof(Vehicle));
	if (!pVehicle) return 0;

	do {
		printf("Please choose vehicle category to add\n");
		for (int i = 0; i < eNofCats; i++)
			printf("\n[%d] for %s", i,Categories[i]);
		scanf("%d", &choice);
	} while (choice<0 || choice>eNofCats);

	switch (choice) {
	case 0:
		initPremium(company->vehicleArr, pVehicle, company->numVehicles);
		break;
	case 1:
		initStandard(company->vehicleArr, pVehicle, company->numVehicles);
		break;
	case 2:
		initCompact(company->vehicleArr, pVehicle, company->numVehicles);
		break;
	default:
		break;
	}

	company->vehicleArr = (Vehicle**)realloc(company->vehicleArr, ((company->numVehicles + 1) * sizeof(Vehicle*)));
	if (!company->vehicleArr)
	{
		free(pVehicle);
		return 0;
	}
	company->vehicleArr[company->numVehicles] = pVehicle;
	company->numVehicles++;
	return 1;
}

int chooseIndexFromRentalArray(RentalCompany* company)
{
	int index, ok = 1;
	do {
		index = getIntegerNum("Choose the line number of the rental you want to update: "); // The index in rental array that user want to update.
		if (index <= 0 || index > company->numRentals)
		{
			printf("No such line. Try again\n");
			ok = 0;
		}
	} while (!ok);
	return index;
}

updateType getUpdateType()
{
	int option;
	printf("\n");
	do {
		printf("Please choose the option to update\n");
		for (int i = 0; i < eNum; i++)
			printf("\n[%d] for %s", i + 1, updateName[i]);
		scanf("%d", &option);
	} while (option <= 0 || option > eNum);
	getchar();
	return (updateType)option;
}

void updateVehicleInRental(RentalCompany* company, int rentalIndex)
{
	Vehicle* newVehicle;
	printAvailableVehicles(company, &company->rentalArr[rentalIndex]);
	int ok = getIntegerNum("Choose the serial number of the vehicle: ");
	newVehicle = findVehicleBySN(company->vehicleArr, company->numVehicles, ok);
	if (!newVehicle)
		printf("Wrong serial number.\n");
	else
		company->rentalArr[rentalIndex].vehicle = newVehicle;
}


void updateRental(RentalCompany* company)
{
	int index, ok;
	for (int i = 0; i < company->numRentals; i++)
	{
		printf(" - %d - ", i + 1);
		printRental(&company->rentalArr[i]);
	}
	index = chooseIndexFromRentalArray(company) - 1;
	updateType type = getUpdateType();

	switch (type)
	{
	case eStartDate:
		do {
			getCorrectDate(&company->rentalArr[index].startDate);
			ok = checkRentDates(company->rentalArr[index].startDate, company->rentalArr[index].endDate);
		} while (!ok);
		break;
	case eEndDate:
		do {
			getCorrectDate(&company->rentalArr[index].endDate);
			ok = checkRentDates(company->rentalArr[index].startDate, company->rentalArr[index].endDate);
		} while (!ok);
		break;
	case eVehicle:
		updateVehicleInRental(company, index);
		break;
	}

	company->rentalArr[index].totalCost = calculateTotalCost(&company->rentalArr[index]); // Calculate the total cost in case of changes.
	updateInvoice(&company->rentalArr[index].invoice, company->rentalArr[index].totalCost); // Update the invoice as well.
}

sortType getSortType()
{
	int option;
	printf("Base on what field do you want to sort?\n");
	do {
		for (int i = 1; i < eOpt; i++)
			printf("Enter %d for %s\n", i, sortName[i]);
		scanf("%d", &option);
		printf("\n");
	} while (option <= 0 || option >= eOpt);
	getchar();
	return (sortType)option;
}

void askUserSearchParameter(Vehicle* toSearch, const RentalCompany* company)
{
	switch (company->sortBy)
	{
	case eOdometer:
		toSearch->odometer = getDoubleNum("Enter odometer: ");
		break;
	case eSerialNumber:
		toSearch->vehicleSN = getIntegerNum("Enter serial number: ");
		break;
	case eYear:
		toSearch->year = getvehicleYear(MIN_MAN_YEAR);
		break;
	case eLicensePlate:
		getLicensePlate(toSearch);
		break;
	default:
		break;
	}
}

int isVehicleAvailableInDates(const RentalCompany* company, Vehicle* vehicle, Date* start, Date* end) // Return 1 if vehicle is available
{
	for (int i = 0; i < company->numRentals; i++)
	{
		if (company->rentalArr[i].vehicle->vehicleSN == vehicle->vehicleSN)
		{
			if (!dateRangesDoNotCollide(&company->rentalArr[i].startDate, &company->rentalArr[i].endDate, start, end))
				return 0; // the vehicle is unAvailable in the dates
			else
				return 1;
		}
	}
	return 1;
}


void sortVehicles(RentalCompany* company)
{
	if (!company) return;
	company->sortBy = getSortType();
	qsort(company->vehicleArr, company->numVehicles, sizeof(Vehicle*), compareFunctions[company->sortBy]);
}


Customer* findCustomerByID(Customer* customerArr, int numCustomers, char* ID)
{
	for (int i = 0; i < numCustomers; i++)
		if (strcmp(customerArr[i].ID, ID))
			return &customerArr[i];
	return NULL;
}


Vehicle* findVehicleBySN(Vehicle** vehicleArr, int numVehicles, int SN)
{
	for (int i = 0; i < numVehicles; i++)
		if (vehicleArr[i]->vehicleSN == SN)
			return vehicleArr[i];
	return NULL;
}



void findVehicle(const RentalCompany* company)
{
	if (company->sortBy == 0)
	{
		printf("\nThe search cannot be performed, array not sorted\n");
		return;
	}

	Vehicle* toSearch = (Vehicle*)malloc(sizeof(Vehicle));
	if (!toSearch) return;
	askUserSearchParameter(toSearch, company);

	Vehicle** pRes = (Vehicle**)bsearch(&toSearch, company->vehicleArr, company->numVehicles, sizeof(Vehicle*), compareFunctions[company->sortBy]);
	if (!pRes) printf("Vehicle was not found\n");
	else {
		printf("Vehicle found, ");
		printVehicle(*pRes);
	}
	free(toSearch);
}

void printRentals_byBranch(const RentalCompany* company)
{
	int chosenBranchID = chooseBranch(company);

	for (int i = 0; i < company->numRentals; i++)
	{
		if (company->rentalArr[i].branchID = chosenBranchID)
			printRental(&company->rentalArr[i]);
	}
}

void printAllVehicles(const RentalCompany* company)
{
	for (int i = 0; i < company->numVehicles; i++)
		generalArrayFunction(company->vehicleArr, 1, sizeof(Vehicle), company->vehicleArr[i]->print);
}

void printAvailableVehicles(const RentalCompany* company, Rental* rental) // Print available vehicles considering the NEW rental chosen dates
{
	printf("\n--- Available Vehicles ---\n");
	for (int i = 0; i < company->numVehicles; i++)
	{
		if (company->vehicleArr[i]->isTaken == 1)
		{
			if (isVehicleAvailableInDates(company, company->vehicleArr[i], &rental->startDate, &rental->endDate))
				company->vehicleArr[i]->print(company->vehicleArr[i]);
		}
		else
			company->vehicleArr[i]->print(company->vehicleArr[i]);
	}
}


void printAllCustomers(const RentalCompany* company)
{
	generalArrayFunction(company->customerArr, company->numCustomers, sizeof(Customer), printCustomer);
}

void printAllRentals(const RentalCompany* company)
{
	generalArrayFunction(company->rentalArr, company->numRentals, sizeof(Rental), printRental);
}
void printAllBranches(const RentalCompany* company)
{
	L_print(&company->branch_list, printBranch);
}

void printCompany(const RentalCompany* company)
{
	printf("\n\nCompany Branches:");
	printAllBranches(company);
	printf("\n\nCompany Vehicles:");
	printAllVehicles(company);
	printf("\n\nCompany Customers:");
	printAllCustomers(company);
	printf("\n\nCompany Current Rentals:");
	printAllRentals(company);

}

void freeCompany(RentalCompany* company)
{
	free(company->companyName);
	//L_free(&company->branch_list, freeBranch);
	//freeVehicleArray(company->vehicleArr, company->numVehicles);
	//free(company->vehicleArr);
	free(company->customerArr);
	free(company->rentalArr);
}