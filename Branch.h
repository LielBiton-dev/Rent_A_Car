#pragma once
#include <stdio.h>
#include "Address.h"

#define MAX_VEHICLES 25
#define START_ID_BRANCH 0

typedef struct{

	Address address;
	int branchID;
}Branch;

int initBranch(Branch* branch);
int compareByID(const void* b1, const void* b2);
int updateBranchGenerator(int num);
int getCurrentBranchGenerator();
void printBranch(const void* branch);
void freeBranch(Branch* branch);