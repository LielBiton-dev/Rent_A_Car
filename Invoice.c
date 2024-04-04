#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Invoice.h"

int generateInvoiceSN()
{
	static int currentSerialNumber = START_SN_INVOICE; // Initial serial number
	return currentSerialNumber++;
}

Invoice* createInvoice(float amount, int rentalSerial)
{
	Invoice* newInvoice = (Invoice*)malloc(sizeof(Invoice));
	if (!newInvoice)
		return NULL;
	newInvoice->invoiceSN = generateInvoiceSN();
	newInvoice->totalAmount = amount;
	newInvoice->rentalSN = rentalSerial;
	getCorrectDate(&newInvoice->issueDate);

	return newInvoice;
}

void updateInvoice(Invoice* invoice, float updateCost)
{
	invoice->totalAmount = updateCost;
}

void printInvoice(const Invoice* invoice)
{
	printf("Invoice Serial Number: %d\nRental Serial Number: %d\nTotal Amount: %f\nIssue Date: ",
		invoice->invoiceSN, invoice->rentalSN, invoice->totalAmount);
	printDate(&invoice->issueDate);
	printf("\n");
}