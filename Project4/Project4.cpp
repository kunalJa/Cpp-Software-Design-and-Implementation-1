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
Customer myInventory = {{10, "inventory"}, 0, 0, 0};
String bottles = StringCreate("Bottles");
String rattles = StringCreate("Rattles");
String diapers = StringCreate("Diapers");

// Initializes customer parameters to zero
void customerZero(Customer* c) {
    c->bottles = 0;
    c->rattles = 0;
    c->diapers = 0;
}

// Makes sure the item requested is both in the myInventory and in the volume requested
int inStock(String* Name, String* itemName, int itemAmount) {
    int which;
    int outOfStock;

    if (itemAmount <= 0) {
        return 0;
    }

    if (StringIsEqualTo(&bottles, itemName)) {
        outOfStock = myInventory.bottles < itemAmount ? 1 : 0;
        which = 0;
    } else if (StringIsEqualTo(&diapers, itemName)) {
        outOfStock = myInventory.diapers < itemAmount ? 1 : 0;
        which = 1;
    } else if (StringIsEqualTo(&rattles, itemName)) {
        outOfStock = myInventory.rattles < itemAmount ? 1 : 0;
        which = 2;
    } else {
        return 0;
    }

    if (outOfStock) {
        printf("Sorry ");
        StringPrint(Name);
        if (which == 0) {
            printf(", we only have %d ", myInventory.bottles);
        } else if (which == 1) {
            printf(", we only have %d ", myInventory.diapers);
        } else {
            printf(", we only have %d ", myInventory.rattles);
        }
        StringPrint(itemName);
        printf("\n");
        return 0;
    }

    return 1;
}

// Clear the myInventory and reset the customer database to empty
void reset() {
    customerZero(&myInventory);

    for (int i = 0; i < num_customers; i++) {
        StringDestroy(&customers[i].name);
        customerZero(&customers[i]);
    }

    bottlesPurchased = 0;
    rattlesPurchased = 0;
    diapersPurchased = 0;
    num_customers = 0;
}

// Process a Summarize instruction
// Prints a summary of current customers and myInventory
void processSummarize() {
    printf("There are %d Bottles, %d Diapers and %d Rattles in inventory\n", myInventory.bottles, myInventory.diapers, myInventory.rattles);
    printf("we have had a total of %d different customers\n", num_customers);

    if (bottlesPurchased) {
        int maxBottles = 0;
        for (int i = 1; i < num_customers; i++) {
            if (customers[i].bottles > customers[maxBottles].bottles) {
                maxBottles = i;
            }
        }
        StringPrint(&customers[maxBottles].name);
        printf(" has purchased the most Bottles (%d)\n", customers[maxBottles].bottles);
    } else {
        printf("no one has purchased any Bottles\n");
    }

    if (diapersPurchased) {
        int maxDiapers = 0;
        for (int i = 1; i < num_customers; i++) {
            if (customers[i].diapers > customers[maxDiapers].diapers) {
                maxDiapers = i;
            }
        }
        StringPrint(&customers[maxDiapers].name);
        printf(" has purchased the most Diapers (%d)\n", customers[maxDiapers].diapers);
    } else {
        printf("no one has purchased any Diapers\n");
    }

    if (rattlesPurchased) {
        int maxRattles = 0;
        for (int i = 1; i < num_customers; i++) {
            if (customers[i].rattles > customers[maxRattles].rattles) {
                maxRattles = i;
            }
        }
        StringPrint(&customers[maxRattles].name);
        printf(" has purchased the most Rattles (%d)\n", customers[maxRattles].rattles);
    } else {
        printf("no one has purchased any Rattles\n");
    }
}

// Process a Purchase instruction
// Adds the item requested to the customers profile
void processPurchase() {
    int customerIndex = num_customers;

    String Name;
    String itemName;
    int itemAmount;
    readString(&Name);
    readString(&itemName);
    readNum(&itemAmount);

    if (inStock(&Name, &itemName, itemAmount)) {
        for (int i = 0; i < num_customers; i++) {
            if (StringIsEqualTo(&Name, &customers[i].name)) {
                customerIndex = i;
                break;
            }
        }

        if (customerIndex == num_customers) {
            customers[customerIndex].name = StringDup(&Name);
            customerZero(&customers[customerIndex]);
            num_customers++;
        }

        if (StringIsEqualTo(&bottles, &itemName)) {
            customers[customerIndex].bottles += itemAmount;
            myInventory.bottles -= itemAmount;
            bottlesPurchased = 1;
        } else if (StringIsEqualTo(&diapers, &itemName)) {
            customers[customerIndex].diapers += itemAmount;
            myInventory.diapers -= itemAmount;
            diapersPurchased = 1;
        } else if (StringIsEqualTo(&rattles, &itemName)) {
            customers[customerIndex].rattles += itemAmount;
            myInventory.rattles -= itemAmount;
            rattlesPurchased = 1;
        }
    }

    StringDestroy(&Name);
    StringDestroy(&itemName);
}

// Process an Inventory instruction
// Add an item to the myInventory
void processInventory() {
    String itemName;
    int itemAmount;
    readString(&itemName);
    readNum(&itemAmount);

    if (StringIsEqualTo(&bottles, &itemName)) {
        myInventory.bottles += itemAmount;
    } else if (StringIsEqualTo(&diapers, &itemName)) {
        myInventory.diapers += itemAmount;
    } else if (StringIsEqualTo(&rattles, &itemName)) {
        myInventory.rattles += itemAmount;
    }

    StringDestroy(&itemName);
}
