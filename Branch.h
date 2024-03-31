#pragma once
#include <stdio.h>
#include "Address.h"
#include "General.h"
#include "Vehicle.h"

#define MAX_VEHICLES 25

typedef struct {

	Address address;
	int branchID;
	int available_vehicle_count;
	float revenue;
	Vehicle* vehicleArr;
}Branch;

BOOL initBranch(Branch* branch);

