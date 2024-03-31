#pragma once
#include "Date.h"
#define START_SN_INVOICE 1000

typedef struct {
    int invoiceSN;
    int rentalSN;
    float totalAmount;
    Date issueDate;
}Invoice;

int generateInvoiceSN();
Invoice createInvoice(float amount, int rentalSerial);
void printInvoice(Invoice* invoice);

//nothing to free