// CRM <Project4.cpp>
// EE 312 Project 4 submission by
// Kunal Jain
// ksj572
// Slip days used: 0
// Summer 2018

#include <stdio.h>
#include <assert.h>
#include "MyString.h"
#include "Invent.h"

#define MAX_CUSTOMERS 1000
int num_customers = 0;
Customer customers[MAX_CUSTOMERS];
Customer inventory = {{10, "inventory"}, 0, 0, 0};

/* clear the inventory and reset the customer database to empty */
void reset(void) {
	/* your code here */
    inventory.bottles = 0;
    inventory.diapers = 0;
    inventory.rattles = 0;
}

void processSummarize() {}

void processPurchase() {}

void processInventory() {
    String* itemName;

    char* bottle = "bottles";
    char* diaper = "diapers";
    char* rattle = "rattles";
    int* itemAmmout;

    readString(itemName);
    readNum(itemAmmout);
    String bottles = StringCreate(bottle);
    String rattles = StringCreate(rattle);
    String diapers = StringCreate(diaper);


    if (StringIsEqualTo(&bottles, itemName)) {
        inventory.bottles += *itemAmmout;
    } else if (StringIsEqualTo(&diapers, itemName)) {
        inventory.diapers += *itemAmmout;
    } else if (StringIsEqualTo(&rattles, itemName)) {
        inventory.rattles += *itemAmmout;
    }

    StringDestroy(itemName);
    StringDestroy(&bottles);
    StringDestroy(&diapers);
    StringDestroy(&rattles);
}
