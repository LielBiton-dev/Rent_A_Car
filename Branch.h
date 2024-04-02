#pragma once
#include <stdio.h>
#include "Address.h"
#include "General.h"
#include "Vehicle.h"

#define MAX_VEHICLES 25

typedef struct {

	Address address;
	int branchID;
	int num_vehicles;
	float revenue;
	Vehicle* vehicleArr;
}Branch;

BOOL initBranch(Branch* branch);

Vehicle* addNewVehicle(Branch* branch);

int compareByID(const void* b1, const void* b2);

BOOL Branch_printVehicleArr_All(Branch* branch);

BOOL printBranch_basic(Branch* branch);

void freeBranch(Branch* branch);