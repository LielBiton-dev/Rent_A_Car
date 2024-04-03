#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "RentalCompany.h"
const int Daily_Rate = 100;

int initCompany(RentalCompany* company) {
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

	if (!company) return 0;
	Branch* pBranch = (Branch*)calloc(1, sizeof(Branch));
	if (!pBranch) return 0;

	if (!initBranch(pBranch)) {
		//freeBranch(pBranch);
		free(pBranch);
		return 0;
	}
	NODE* lastNode = &company->branch_list.head;
	while (lastNode->next != NULL)
	{
		lastNode = lastNode->next;
	}

	L_insert(lastNode, pBranch);
	return 1;
}

int addVehicle(RentalCompany* company) {
	int choice = 0;

	Vehicle* pVehicle = (Vehicle*)malloc(sizeof(Vehicle));
	if (!pVehicle) return 0;

	do {
		printf("Please choose vehicle category to add\n");
		for (int i = 0; i < eNofCats; i++)
			printf("\n[%d] for %s\n", i + 1, Categories[i]);
		scanf("%d", &choice);
	} while (choice<=0 || choice>eNofCats);

	switch (choice) {
	case 1:
		initPremium(company->vehicleArr, pVehicle, company->numVehicles);
		break;
	case 2:
		initStandard(company->vehicleArr, pVehicle, company->numVehicles);
		break;
	case 3:
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

int addCustomer(RentalCompany* company)
{
	company->customerArr = (Customer*)realloc(company->customerArr, (company->numCustomers + 1) * sizeof(Customer));
	if (!company->customerArr)
		return 0;
	initCustomer(&company->customerArr[company->numCustomers]);
	company->numCustomers++;
	return 1;
}

Vehicle* findVehicleBySN(Vehicle** vehicleArr, int numVehicles, int SN)
{
	for (int i = 0; i < numVehicles; i++)
		if (vehicleArr[i]->vehicleSN == SN)
			return vehicleArr[i];
	return NULL;
}

Customer* findCustomerByID(Customer* customerArr, int numCustomers, char* ID)
{
	for (int i = 0; i < numCustomers; i++)
		if (strcmp(customerArr[i].ID,ID))
			return &customerArr[i];
	return NULL;
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

void printAllVehicles(const RentalCompany* company)
{
	for (int i = 0; i < company->numVehicles; i++)
	{
		company->vehicleArr[i]->print(company->vehicleArr[i]);
	}
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

void sortVehicles(RentalCompany* company)
{
	if (!company) return;
	company->sortBy = getSortType();
	qsort(company->vehicleArr, company->numVehicles, sizeof(Vehicle*), compareFunctions[company->sortBy]);
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

void printCompany(const RentalCompany* company)
{
	//ADD
}

void printAllCustomers(const RentalCompany* company)
{
	//ADD
}

void printAllRentals(const RentalCompany* company)
{
	for (int i = 0; i < company->numRentals; i++)
		printRental(&company->rentalArr[i]);
}

void printAllBranches(const RentalCompany* company)
{
	//ADD
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