#pragma once
#define START_SN_INVOICE 1000
#include "Date.h"

typedef struct {
    int invoiceSN;
    int rentalSN;
    float totalAmount;
    Date issueDate;
}Invoice;

int generateInvoiceSN();
Invoice createInvoice(float amount, int rentalSerial);
void printInvoice(const Invoice* invoice);

//nothing to free