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

Invoice createInvoice(float amount, int rentalSerial)
{
	Invoice newInvoice = { 0 };
	newInvoice.invoiceSN = generateInvoiceSN();
	newInvoice.totalAmount = amount;
	newInvoice.rentalSN = rentalSerial;
	getCorrectDate(&newInvoice.issueDate);

	return newInvoice;
}

void printInvoice(Invoice* invoice)
{
	printf("Invoice Serial Number: %d\nRental Serial Number: %d\nTotal Amount: %f\nIssue Date: ",
		invoice->invoiceSN, invoice->rentalSN, invoice->totalAmount);
	printDate(&invoice->issueDate);
	printf("\n");
}