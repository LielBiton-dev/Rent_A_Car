#include <stdio.h>
#include <stdlib.h>
#include "RentalCompany.h"

typedef enum
{
	eFromTxt, eFromBin, ePrintCompany, ePrintBranches, ePrintVehicles,
	ePrintCustomers, ePrintRentals, eAddVehicle,eAddCustomer,eAddRental,eAddBranch,eSortVehicles, 
	eFindVehicle, ePrintRentalsInBranch,eUpdateRental, eNofOptionsMenu
} eMenuOptions;

const char* str[eNofOptionsMenu] = { "Upload Data From Text File", "Upload Data From Binary File", "Print Rental Company", "Print All Branches", "Print All Vehicles",
	"Print All Customers", "Print All Rentals", "Add New Vehicle To Company","Add New Customer","Add New Rental","Add New Branch","Sort Vehicles Array",
	"Find Vehicle", "Print All Rentals In specific Branch","Update Existing Rental" };

#define EXIT -1
int menu();

int main()
{
	RentalCompany company;
	initCompany(&company);
	int option;
	int stop = 0;


	do
	{
		option = menu();
		switch (option)
		{
		case eFromTxt:
			//initCompanyFromTxtFile
			break;

		case eFromBin:
			//initCompanyFromBinFile
			break;

		case ePrintCompany:
			printCompany(&company);
			break;

		case ePrintBranches:
			printAllBranches(&company);
			break;

		case ePrintVehicles:
			printAllVehicles(&company);
			break;

		case ePrintCustomers:
			printAllCustomers(&company);
			break;

		case ePrintRentals:
			printAllRentals(&company);
			break;

		case eAddVehicle:
			addVehicle(&company);
			break;

		case eAddCustomer:
			//addCustomer(&company);
			break;

		case eAddRental:
			//addRental(&company);
			break;

		case eAddBranch:
			addBranch(&company);
			break;

		case eSortVehicles:
			sortVehicles(&company);
			break;

		case eFindVehicle:
			findVehicle(&company);
			break;

		case ePrintRentalsInBranch:
			//print rental in branch function.
			break;

		case eUpdateRental:
			updateRental(&company);
			break;

		case EXIT:
			printf("Bye bye\n");
			stop = 1;
			break;

		default:
			printf("Wrong option\n");
			break;
		}
	} while (!stop);

	//saveCompanyToTxtFile(&company, "rental_company.txt");
	//saveCompanyToBinFile(&company, "rental_company.bin");
	//freeCompany(&company);

	return 1;
}

int menu()
{
	int option;
	printf("\n\n");
	printf("Please choose one of the following options\n");
	for (int i = 0; i < eNofOptionsMenu; i++)
		printf("%d - %s\n", i, str[i]);
	printf("%d - Quit\n", EXIT);
	scanf("%d", &option);
	//clean buffer
	char tav;
	scanf("%c", &tav);
	return option;
}