// CRM <Project4.cpp>
// EE 312 Project 4 submission by
// Kunal Jain
// ksj572
// Slip days used: 0
// Summer 2018

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "MyString.h"
#include "Invent.h"

#define MAX_CUSTOMERS 1000
int num_customers = 0;
Customer customers[MAX_CUSTOMERS];
Customer inventory = {{10, "inventory"}, 0, 0, 0};

char* bottle = "bottles";
char* diaper = "diapers";
char* rattle = "rattles";
String bottles = StringCreate(bottle);
String rattles = StringCreate(rattle);
String diapers = StringCreate(diaper);

int inStock(String* Name, String* itemName, int* itemAmount) {
    int outOfStock = 0;

    if (StringIsEqualTo(&bottles, itemName)) {
        if (inventory.bottles < *itemAmount) {
            outOfStock = 1;
        }
    } else if (StringIsEqualTo(&diapers, itemName)) {
        if (inventory.diapers < *itemAmount) {
            outOfStock = 1;
        }
    } else if (StringIsEqualTo(&rattles, itemName)) {
        if (inventory.rattles < *itemAmount) {
            outOfStock = 1;
        }
    }

    if (outOfStock) {
        printf("Sorry %s, we only have %d %s", Name->ptr, *itemAmount, itemName->ptr);
        return 0;
    }

    return 1;
}

/* clear the inventory and reset the customer database to empty */
void reset(void) {
    inventory.bottles = 0;
    inventory.diapers = 0;
    inventory.rattles = 0;

    for (int i = 0; i < num_customers; i++) {
        StringDestroy(&customers[i].name);
    }
    num_customers = 0;
}

void processSummarize() {}

void processPurchase() {
    int customerIndex = num_customers;

    String* Name;
    String* itemName;
    int* itemAmount;
    readString(Name);
    readString(itemName);
    readNum(itemAmount);

    if (inStock(Name, itemName, itemAmount)) {

    }
    for (int i = 0; i < num_customers; i++) {
        if (StringIsEqualTo(Name, &customers[i].name)) {
            customerIndex = i;
            break;
        }
    }

    if (customerIndex == num_customers) {
        StringReAssign(&customers[customerIndex].name, Name);
        customers[customerIndex].bottles = 0;
        customers[customerIndex].diapers = 0;
        customers[customerIndex].rattles = 0;
    }



    StringDestroy(Name);
    StringDestroy(itemName);
}

void processInventory() {
    String* itemName;
    int* itemAmount;
    readString(itemName);
    readNum(itemAmount);

    if (StringIsEqualTo(&bottles, itemName)) {
        inventory.bottles += *itemAmount;
    } else if (StringIsEqualTo(&diapers, itemName)) {
        inventory.diapers += *itemAmount;
    } else if (StringIsEqualTo(&rattles, itemName)) {
        inventory.rattles += *itemAmount;
    }

    StringDestroy(itemName);
}
