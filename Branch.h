#pragma once
#include <stdio.h>
#include "Address.h"
#include "General.h"
#include "Def.h"

static int branchID_generator = 0;


typedef struct {

	Address address;
	int branchID;
}Branch;

BOOL initBranch(Branch* branch);

int compareByID(const void* b1, const void* b2);

void printBranch(const void* branch);

void freeBranch(Branch* branch);