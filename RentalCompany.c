#pragma	once

#include "RentalCompany.h"
#include <stdio.h>
#include "General.h"
#include "Branch.h"
#include <stdlib.h>


BOOL initCompany(RentalCompany* company) {
	char* addressStr;
	if (company == NULL)
		return False;

	printf("\nEnter company name : ");
	myGets(company->companyName, MAX_NAME_STR, stdin);
	L_init(&company->branch_list);
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
	int choice, i;
	NODE* node = &company->branch_list.head.next;
	if (!node) {
		printf("\nThere are no Branches to your company. Try adding a branch first");
		return NULL;
	}
	do{
		printf("\nChoose branch : ");
		for (i = 0; (node != NULL); i++, node = node->next)
			printf("\n[i]-%s", printBranch(node->key));
	
	} while (!scanf("%d", &choice) || choice >= i || choice < 0);

	Branch* branch = (Branch*) L_find(&company->branch_list.head, i, compareByID);
	
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

	company->vehicleArr[i] = (Vehicle*)realloc(company->vehicleArr[i], sizeof(Vehicle) * branch->num_vehicles);
	if (!company->vehicleArr[i]) {
		printf("\nError allocating memory.");
		free(branch);
		free(newVehicle);
		return NULL;
	}
	

	

		
}





