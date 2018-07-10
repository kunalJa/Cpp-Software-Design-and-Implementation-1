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
int bottlesPurchased = 0;
int rattlesPurchased = 0;
int diapersPurchased = 0;
Customer customers[MAX_CUSTOMERS];
Customer inventory = {0, 0, 0, 0};
String bottles = StringCreate("Bottles");
String rattles = StringCreate("Rattles");
String diapers = StringCreate("Diapers");

// Initializes customer parameters to zero
void customerZero(Customer* c) {
    c->bottles = 0;
    c->rattles = 0;
    c->diapers = 0;
}

// Makes sure the item requested is both in the inventory and in the volume requested
int inStock(String* Name, String* itemName, int itemAmount) {
    int which;
    int outOfStock;

    if (itemAmount < 0) {
        return 0;
    }

    if (StringIsEqualTo(&bottles, itemName)) {
        outOfStock = inventory.bottles < itemAmount ? 1 : 0;
        which = 0;
    } else if (StringIsEqualTo(&diapers, itemName)) {
        outOfStock = inventory.diapers < itemAmount ? 1 : 0;
        which = 1;
    } else if (StringIsEqualTo(&rattles, itemName)) {
        outOfStock = inventory.rattles < itemAmount ? 1 : 0;
        which = 2;
    } else {
        return 0;
    }

    if (outOfStock) {
        printf("Sorry ");
        StringPrint(Name);
        if (which == 0) {
            printf(", we only have %d ", inventory.bottles);
        } else if (which == 1) {
            printf(", we only have %d ", inventory.diapers);
        } else {
            printf(", we only have %d ", inventory.rattles);
        }
        StringPrint(itemName);
        printf("\n");
        return 0;
    }

    return 1;
}

// Clear the inventory and reset the customer database to empty
void reset() {
    customerZero(&inventory);

    for (int i = 0; i < num_customers; i++) {
        StringDestroy(&customers[i].name);
    }

    bottlesPurchased = 0;
    rattlesPurchased = 0;
    diapersPurchased = 0;
    num_customers = 0;
}

// Process a Summarize instruction
// Prints a summary of current customers and inventory
void processSummarize() {
    printf("There are %d Bottles, %d Diapers and %d Rattles in inventory \n", inventory.bottles,
           inventory.diapers, inventory.rattles);
    printf("we have had a total of %d different customers", num_customers);

    if (bottlesPurchased) {
        int maxBottles = 0;
        for (int i = 1; i < num_customers; i++) {
            if (customers[i].bottles > customers[maxBottles].bottles) {
                maxBottles = i;
            }
        }
        StringPrint(&customers[maxBottles].name);
        printf(" has purchased the most Bottles (%d)", customers[maxBottles].bottles);
    } else {
        printf("no one has purchased any Bottles");
    }

    if (diapersPurchased) {
        int maxDiapers = 0;
        for (int i = 1; i < num_customers; i++) {
            if (customers[i].diapers > customers[maxDiapers].diapers) {
                maxDiapers = i;
            }
        }
        StringPrint(&customers[maxDiapers].name);
        printf(" has purchased the most Diapers (%d)", customers[maxDiapers].diapers);
    } else {
        printf("no one has purchased any Diapers");
    }

    if (rattlesPurchased) {
        int maxRattles = 0;
        for (int i = 1; i < num_customers; i++) {
            if (customers[i].rattles > customers[maxRattles].rattles) {
                maxRattles = i;
            }
        }
        StringPrint(&customers[maxRattles].name);
        printf(" has purchased the most Rattles (%d)", customers[maxRattles].rattles);
    } else {
        printf("no one has purchased any Rattles");
    }
}

// Process a Purchase instruction
// Adds the item requested to the customers profile
void processPurchase() {
    int customerIndex = num_customers;

    String* Name;
    String* itemName;
    int itemAmount;
    readString(Name);
    readString(itemName);
    readNum(&itemAmount);

    if (inStock(Name, itemName, itemAmount)) {
        for (int i = 0; i < num_customers; i++) {
            if (StringIsEqualTo(Name, &customers[i].name)) {
                customerIndex = i;
                break;
            }
        }

        if (customerIndex == num_customers) {
            StringReAssign(&customers[customerIndex].name, Name);
            customerZero(&customers[customerIndex]);
            num_customers++;
        }

        if (StringIsEqualTo(&bottles, itemName)) {
            customers[customerIndex].bottles += itemAmount;
            inventory.bottles -= itemAmount;
            bottlesPurchased = 1;
        } else if (StringIsEqualTo(&diapers, itemName)) {
            customers[customerIndex].diapers += itemAmount;
            inventory.diapers -= itemAmount;
            diapersPurchased = 1;
        } else if (StringIsEqualTo(&rattles, itemName)) {
            customers[customerIndex].rattles += itemAmount;
            inventory.rattles -= itemAmount;
            rattlesPurchased = 1;
        }
    }

    StringDestroy(Name);
    StringDestroy(itemName);
}

// Process an Inventory instruction
// Add an item to the inventory
void processInventory() {
    String* itemName;
    int itemAmount;
    readString(itemName);
    readNum(&itemAmount);

    if (StringIsEqualTo(&bottles, itemName)) {
        inventory.bottles += itemAmount;
    } else if (StringIsEqualTo(&diapers, itemName)) {
        inventory.diapers += itemAmount;
    } else if (StringIsEqualTo(&rattles, itemName)) {
        inventory.rattles += itemAmount;
    }

    StringDestroy(itemName);
}
