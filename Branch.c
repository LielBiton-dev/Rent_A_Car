#include <stdio.h>
#include <stdlib.h>

#include "Branch.h"

int initBranch(Branch* branch) {

	/*if (!initAddress(&branch->address, "\nEnter branch address (format: \"country, city, street and number\" : "))
		return 0;*/
	branch->branchID++;
	return 1;
}

int compareByID(const void* b1, const void* b2) {
	Branch* br1 = (Branch*)b1;
	Branch* br2 = (Branch*)b2;

	return br1->branchID - br2->branchID;
}