/* Implementing Linked List Functions
 * The signture of the functions has already been 
 * defined for you, all you need to do is write these
 * functions and turn it in before DDL
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node* next;
}node;

int length(node* head)
{
    int len = 1;
    node* current = head->next; // the first item in the list
    if (head->next == 0) {
        return 0;
    }

    while (current->next != 0) {
        current = current->next;
        len++;
    }

    return len;
}

// Do nothing if index is out of range
node* ll_insert(node* head, int index, int data)
{
    int count = 0;
    node* prev = 0;
    node* current = head->next;
    if (head->next == 0) {
        node* newNode = (node*) malloc(sizeof(node));
        newNode->data = data;
        newNode->next = 0;
        head->next = newNode;
        return head;
    }

    while(current != 0) {
        if (count == index) {
            node* newNode = (node*) malloc(sizeof(node));
            newNode->data = data;
            if (count == 0) {
                newNode->next = head->next;
                head->next = newNode;
            } else {
                newNode->next = current;
                prev->next = newNode;
            }
            return head;
        } else {
                prev = current;
                current = current->next;
                count++;
        }
    }

    if (count == index) {
        node* newNode = (node*) malloc(sizeof(node));
        newNode->data = data;
        newNode->next = 0;
        prev->next = newNode;
    }

    return head;
}

// Do nothing if index is out of range
node* ll_remove(node* head, int index)
{
    int count = 0;
    node* prev = 0;
    node* current = head->next;
    if (head->next == 0) { // if empty remove nothing
        return head;
    }

    while(current != 0) {
        if (count == index) {
            if (prev != 0) {
                prev->next = current->next;
            } else {
                head->next = current->next;
            }
            free(current);
            break;
        } else {
            prev = current;
            current = current->next;
            count++;
        }
    }

    return head;
}

node* ll_append(node* head, int data)
{
    node* current = head;
    while(current->next != 0) {
        current = current->next;
    }

    node* newNode = (node*) malloc(sizeof(node));
    newNode->data = data;
    newNode->next = 0;
    current->next = newNode;
    return head;
}

// Deep copy
node* copyList(node* head)
{
    node* newList = (node*) malloc(sizeof(node));
    newList->data = 0;
    node* current = head->next;
    if(head->next == 0) {
        return newList;
    }
    node* newNext = (node*) malloc(sizeof(node));
    newList->next = newNext;
    node* currentNew = newList->next;
    while(current != 0) {
        currentNew->data = current->data;
        if (current->next != 0) {
            node* newNext = (node*) malloc(sizeof(node));
            currentNew->next = newNext;
        } else {
            currentNew->next = 0;
        }
        currentNew = currentNew->next;
        current = current->next;
    }

    return newList;
}

void printList(node* head) {
    if (head->next == 0) {
        printf("{}\n");
        return;
    }

    node* current = head->next; // The first item in the list
    printf("{ ");
    while (current != 0) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("}\n");
}

int main() {
    node test = {0, 0};
    node* ptr = &test;
    printf("len %d: ", length(ptr)); // Test 0 length head
    printList(ptr);

    ptr = ll_append(ptr, -1);
    printf("len %d: ", length(ptr)); // Test append on empty
    printList(ptr);

    ptr = ll_insert(ptr, 0, 10);
    printf("len %d: ", length(ptr)); // Test insert length change
    printList(ptr);

    ptr = ll_insert(ptr, 0, 15);
    printf("len %d: ", length(ptr)); // Test insert to front
    printList(ptr);

    ptr = ll_insert(ptr, 0, 20);
    printf("len %d: ", length(ptr)); // Test insert to front
    printList(ptr);

    ptr = ll_insert(ptr, 3, 5);
    printf("len %d: ", length(ptr)); // Test insert to end
    printList(ptr);

    ptr = ll_insert(ptr, 10, 5);
    printf("len %d: ", length(ptr)); // Test insert to out of range
    printList(ptr);

    ptr = ll_append(ptr, -2);
    printf("len %d: ", length(ptr)); // Test append
    printList(ptr);

    ptr = ll_remove(ptr, 2);
    printf("len %d: ", length(ptr)); // Test remove 10
    printList(ptr);

    printf("\n");
    node test2 = {0, 0};
    node* ptr2 = &test2;

    ptr2 = copyList(ptr);
    printf("len %d: ", length(ptr2)); // Test remove 10
    printList(ptr2);
}
