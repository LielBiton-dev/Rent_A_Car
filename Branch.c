#include <stdio.h>
#include <stdlib.h>

#include "Branch.h"

int initBranch(Branch* branch) {

	/*if (!initAddress(&branch->address, "\nEnter branch address (format: \"country, city, street and number\" : "))
		return 0;*/
	branch->branchID++;
	//branch->num_vehicles = 0;
	branch->revenue = 0;
	//branch->vehicleArr = NULL;
	return 1;
}

//int addVehicle(Branch* branch) {
//	Vehicle newVehicle = { 0 };
//	int choice;
//
//	if (branch->num_vehicles > MAX_VEHICLES)
//		return 0;
//
//	do {
//		printf("Please choose vehicle category to add\n");
//		for (int i = 0; i < eNofCats; i++)
//			printf("\n[i] for %s", Categories[i]);
//		scanf("%d", &choice);
//	} while (choice<0 || choice>eNofCats);
//
//	switch (choice) {
//	case 0:
//		initPremium(&branch->vehicleArr, &newVehicle, branch->num_vehicles);
//		break;
//	case 1:
//		initStandard(&branch->vehicleArr, &newVehicle, branch->num_vehicles);
//		break;
//	case 2:
//		initCompact(&branch->vehicleArr, &newVehicle, branch->num_vehicles);
//		break;
//	default:
//		break;
//	}
//
//	branch->vehicleArr = (Vehicle*)realloc(branch->vehicleArr, ((branch->num_vehicles + 1) * sizeof(Vehicle)));
//	if (!branch->vehicleArr)
//		return 0;
//	branch->vehicleArr[branch->num_vehicles] = newVehicle;
//	branch->num_vehicles++;
//	return 1;
//}

int compareByID(const void* b1, const void* b2) {
	Branch* br1 = (Branch*)b1;
	Branch* br2 = (Branch*)b2;

	return br1->branchID - br2->branchID;
}