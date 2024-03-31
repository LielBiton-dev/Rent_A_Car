#include "Branch.h"
#include <stdio.h>
#include <stdlib.h>
#include "string.h"

BOOL initBranch(Branch* branch) {

	char* addressStr;
	if (!branch)
		return False;
	printf("\nEnter branch address (format: \"country, city, street and number\" : ");
	myGets(addressStr, MAX_CITY_LENGTH + MAX_COUNTRY_LENGTH + MAX_STREET_LENGTH, stdin);
	while (!initAddress(&branch->address, addressStr))
		printf("\nenter a valid format for the address : ");
	branch->branchID++;
	branch-> num_vehicles= 0;
	branch->revenue = 0;

	return True;

}

Vehicle* addNewVehicle(Branch* branch) {
	Vehicle newVehicle;
	int choice1,choice2,choice3, k;
	char** temp;

	if (++branch->num_vehicles > MAX_VEHICLES)
		return NULL;
	if (branch->vehicleArr = NULL)
		branch->vehicleArr = (Vehicle*)malloc(sizeof(Vehicle));
	do {
		printf("\nWhat type of vehicle?");
		for (int i = 0; i < eNumTypes; i++)
			printf("\n[i]- %s", temp[i]);
	} while (!scanf("%d", &choice1) || choice1 > 3 || choice1 < 1);
	newVehicle.type = (eType)choice1;
	
	do {
		printf("\nWhich brand?");
		switch (choice1) {

		case 1: k = eNumCompactBrands;
			strcpy(temp, CompactBrand);
			break;
		case 2: k = eNumStandardBrands;
			strcpy(temp, StandardBrand);
			break;
		case 3: k = eNumPremiumBrands;
			strcpy(temp, PremiumBrand);
			break;
		}
		for (int i = 0; i < k; i++)
			printf("\n[i]- %s", temp[i]);
	} while (!scanf("%d", &choice2) || choice2 >= k || choice2 < 0);

	switch (newVehicle.type) {

	case eCompact:
		strcpy(newVehicle.brand, CompactBrand[choice2]);
		break;
	case eStandard:
		strcpy(newVehicle.brand, StandardBrand[choice2]);
		break;
	case ePremium:
		strcpy(newVehicle.brand, PremiumBrand[choice2]);
		break;
	}
	
	strcpy(temp, Features);
	do {
		printf("\nAdditional features?");//need to add Features in vehicle struct
		for (int i = 0; i < eNofOpt; i++)
			printf("\n[i]- %s", temp[i]);
	} while (!scanf("%d", choice3) || choice3 >= eNofOpt || choice3 < 0); 

	
	branch->vehicleArr = (Vehicle*)realloc(branch->vehicleArr, sizeof(Vehicle) * branch->num_vehicles);
	if (!branch->vehicleArr)
		return NULL;
	
	branch->vehicleArr[branch->num_vehicles] = newVehicle;
	return &newVehicle;
}

int compareByID( const void* b1, const void* b2) {
	Branch* br1 = (Branch*)b1;
	Branch* br2 = (Branch*)b2;

	return br1->branchID - br2->branchID;
}



