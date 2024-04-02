#pragma once
#include <stdio.h>
#include "Address.h"

#define MAX_VEHICLES 25

typedef struct {

	Address address;
	int branchID;
	//int num_vehicles;
	float revenue;
	//Vehicle* vehicleArr;
}Branch;

int initBranch(Branch* branch);
int compareByID(const void* b1, const void* b2);