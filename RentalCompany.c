#include <stdio.h>
#include <stdlib.h>

#include "RentalCompany.h"
const int Daily_Rate = 100;
const double Economy_multiplier = 1.0;
const double Luxury_multiplier = 2.0;
const double Motorcycle_multiplier = 0.7;

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
	return 1;
}
int addBranch(RentalCompany* company) {

	//Branch newBranch;
	//initBranch(&newBranch);
	//if (company == NULL || &company->branch_list == NULL)
	//	return NULL;
	//NODE* lastNode = &company->branch_list.head;
	//while (lastNode->next != NULL)
	//{
	//	lastNode = lastNode->next;
	//}

	//L_insert(lastNode, &newBranch);
	//return lastNode;

	Branch* pBranch = (Branch*)calloc(1, sizeof(Branch));
	if (!pBranch) return 0;

	if (!initBranch(pBranch)) {
		//freeBranch(pBranch);
		free(pBranch);
		return 0;
	}
	//NODE* pNode = findNodeByAddress(&company->branch_list.head, pBranch->address); 
	// - need to write this function (add branch to list by ABC state address)
	//L_insert(pNode, pBranch);
	return 1;
}

int addVehicle(RentalCompany* company) {
	int choice = 0;

	Vehicle* pVehicle = (Vehicle*)calloc(1, sizeof(Vehicle));
	if (!pVehicle) return 0;

	do {
		printf("Please choose vehicle category to add\n");
		for (int i = 0; i < eNofCats; i++)
			printf("\n[i] for %s", Categories[i]);
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

//Vehicle* addNewVehicle_toBranch(RentalCompany* company) {
//	int choice, i;
//	NODE* node = &company->branch_list.head.next;
//	if (!node) {
//		printf("\nThere are no Branches to your company. Try adding a branch first");
//		return NULL;
//	}
//	do {
//		printf("\nChoose branch : ");
//		for (i = 0; (node != NULL); i++, node = node->next)
//			printf("\n[i]-%s", printBranch(node->key));
//
//	} while (!scanf("%d", &choice) || choice >= i || choice < 0);
//
//	Branch* branch = (Branch*)L_find(&company->branch_list.head, i, compareByID);
//
//	Vehicle* newVehicle = addNewVehicle(branch);
//	if (!newVehicle) {
//		if (branch->num_vehicles > MAX_VEHICLES) {
//			printf("\nBranch has reached maximum vehicle capacity.");
//			free(branch);
//			return NULL;
//		}
//		if (!branch->vehicleArr) {
//			printf("\nError allocating memory in branch.");
//			free(branch);
//			return NULL;
//		}
//	}
//
//	if (++company->num_vehicles > COMPANY_MAX_VEHICLES) {
//		printf("\nReached maximum vehicle capacity.");
//		company->num_vehicles--;
//		return NULL;
//	}
//
//	company->vehicleArr[i] = (Vehicle*)realloc(company->vehicleArr[i], sizeof(Vehicle) * branch->num_vehicles);
//	if (!company->vehicleArr[i]) {
//		printf("\nError allocating memory.");
//		free(branch);
//		free(newVehicle);
//		return NULL;
//	}
//
//}