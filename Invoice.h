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
Invoice* createInvoice(float amount, int rentalSerial);
void printInvoice(const Invoice* invoice);
void updateInvoice(Invoice* invoice, float updateCost);

//nothing to free