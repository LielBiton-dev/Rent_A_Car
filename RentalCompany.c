#pragma	once

#include "RentalCompany.h"
#include <stdio.h>
#include "General.h"
#include "Branch.h"
#include <stdlib.h>


BOOL initCompany(RentalCompany* company) {
	if (company == NULL)
		return False;

	printf("\nEnter company name : ");
	myGets(company->companyName, MAX_NAME_STR, stdin);
	L_init(&company->branch_list); 
	company->num_customers = 0;
	company->num_rentals = 0;
	company->num_vehicles = 0;
	company->num_vehicles_available = 0;
	company->num_branches = 0;

}
Branch* addBranch(RentalCompany* company) {
	Branch newBranch;
	initBranch(&newBranch);

	if (company == NULL || &company->branch_list == NULL)
		return NULL;
	NODE* lastNode = &company->branch_list.head;
	while (lastNode->next != NULL)
	{
		lastNode = lastNode->next;
	}

	L_insert(lastNode, &newBranch);
	return lastNode;
}



Vehicle* addNewVehicle_toBranch(RentalCompany* company) {

	Branch* branch = chooseAndFind_Branch(company);
	int numBranches = countBranches(company) - 1;
	
	Vehicle* newVehicle = addNewVehicle(branch);
	if (!newVehicle) {
		if (branch->num_vehicles > MAX_VEHICLES){
			printf("\nBranch has reached maximum vehicle capacity.");
			free(branch);
			return NULL;
		}
		if (!branch->vehicleArr) {
			printf("\nError allocating memory in branch.");
			free(branch);
			return NULL;
		}
	}

	if (++company->num_vehicles > COMPANY_MAX_VEHICLES) {
		printf("\nReached maximum vehicle capacity.");
		company->num_vehicles--;
		return NULL;
	}
	if (!company->vehicleArr[numBranches])
		company->vehicleArr[numBranches] = (Vehicle*)malloc(sizeof(Vehicle)*branch->num_vehicles); //should be 1 slot in Arr[numBranches]

	company->vehicleArr[numBranches] = (Vehicle*)realloc(company->vehicleArr[numBranches], sizeof(Vehicle) * branch->num_vehicles);
	if (!company->vehicleArr[numBranches]) {
		printf("\nError allocating memory.");
		free(branch);
		free(newVehicle);
		return NULL;
	}
}
int countBranches(RentalCompany* company) {
	NODE* node = &company->branch_list.head;
	int count = 0;

	while (node!=NULL)
	{
		node = node->next;
		count++;
	}
	return count;
}


BOOL Company_printVehicles_All(const RentalCompany* company) {
	int numBranches = countBranches(company);
	for (int i = 0; i < numBranches; i++)
	{
		int rowSize = sizeof(company->vehicleArr[i]) / sizeof(Vehicle);
		for (int j = 0; j < rowSize; j++)
		{
			company->vehicleArr[i][j].print(&company->vehicleArr[i][j]);
		}
	}
}

BOOL Company_printVehicles_byBranch(const RentalCompany* company) {
	
	Branch* branch = chooseAndFind_Branch(company);
	if (!branch) return False;
	return Branch_printVehicleArr_All(branch); //t or f 
		
	
}

Branch* chooseAndFind_Branch(RentalCompany *company) {
	int choice, i;
	NODE* node = &company->branch_list.head.next;
	if (!node) {
		printf("\nThere are no Branches to your company. Try adding a branch first");
		return NULL;
	}
	do {
		printf("\nChoose branch : ");
		for (i = 0; (node != NULL); i++, node = node->next)
			printf("\n[i]-%s", printBranch_basic(node->key));

	} while (!scanf("%d", &choice) || choice >= i || choice < 0);

	return (Branch*)L_find(&company->branch_list.head, i, compareByID);
}

Customer* addCustomer(RentalCompany* company) {
	Customer newCust;
	initCustomer(&newCust);
	if (company->customerArr == NULL)
			company->customerArr = (Customer*)malloc(sizeof(Customer));
		
	else 
		company->customerArr = (Customer*)realloc(company->customerArr, (company->num_customers+1)*sizeof(Customer));	
	
	if (!company->customerArr)
		return NULL;
	
	company->customerArr[company->num_customers] = newCust;
	company->num_customers++;
	return &newCust;
}

Rental* addRental(RentalCompany* company, Customer* cust, Vehicle* vehicle) {
	Rental newRental;
	initRental(&newRental, cust, vehicle);
	if (!company->rentalArr)
		company->rentalArr = (Rental*)malloc(sizeof(Rental));
	else
		company->rentalArr = (Rental*)realloc(company->rentalArr, (company->num_rentals + 1) * sizeof(Rental));
	if (!company->rentalArr)
		return NULL;
	company->rentalArr[company->num_rentals] = newRental;
	company->num_rentals++;
	return &newRental;
}






