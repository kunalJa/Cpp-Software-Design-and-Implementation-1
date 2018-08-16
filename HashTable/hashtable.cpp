#include <iostream>
#include "String.h"

using namespace std;

/* 
 * This is a hash table holding int values.
 * The hash table has an array of Nodes called buckets.  
 * 
 */

template <class T>
struct Node { // Linked list to hold entries at each position.
    T el; // value to be entered in the hash table
    Node* next;
};

template <class T>
class HashTable {
private:
    Node<T>** buckets; // An array of Node pointers.
    int size; // size of the table, not the number of entries

    int hash(int el) { // Hash function is a modulo function
        return el % size; 
    }

public:
    HashTable(int size) {
        this->size = size;
        buckets = new Node<T>*[size]; // create an array of Node pointers
        for (int i = 0; i < size; i++) {
            buckets[i] = NULL; // initialize each Node pointer in array
        }
    }

    void insert(T el) {
        Node<T>* n = new Node<T>(); // create a new Node object
        n->el = el; // initialize new Node's variables
        n->next = NULL;

        int ix = hash(el.hash());  // calculate the place where the new value will be placed

        int j = 0;
        Node<T>* head = buckets[ix]; // the head of the linked-list at location ix
        while (head != NULL) { // search through the linked-list at that location
            if (head->el == el) { // if found, return true
                cout << "DUPLICATE" << endl;
            }
            head = head->next;
            j++;
        }

        if (j >= size - 7) {
            this->printMe();

            this->size = 2*size; // getNextPrime() function
            Node<T>** bigger = new Node<T>*[size]; // create an array of Node pointers
            for (int i = 0; i < size; i++) {
                buckets[i] = NULL; // initialize each Node pointer in array
            }

            for (int i = 0; i < size/2; i++) {
                Node<T>* head = buckets[i]; // the head of the linked-list at location ix
                while (head != NULL) { // search through the linked-list at that location
                    Node<T>* n = new Node<T>(); // create a new Node object
                    n->el = buckets[i]->el; // initialize new Node's variables
                    n->next = NULL;

                    int ix = hash(el.hash());  // calculate the place where the new value will be placed
                    if (bigger[ix] != NULL) { // insert into front of the linked list at that place ix
                        n->next = bigger[ix];
                    }

                    bigger[ix] = n;
                    head = head->next;
                    delete buckets[ix];
                }
            }

            buckets = bigger;
        }

        if (buckets[ix] != NULL) { // insert into front of the linked list at that place ix
            n->next = buckets[ix];
        }

        buckets[ix] = n;
    }

    bool find(T el) { // find the value el in the list
        int ix = hash(el.hash());  // find the index of the hash table where the element might be
        Node<T>* head = buckets[ix]; // the head of the linked-list at location ix
        while (head != NULL) { // search through the linked-list at that location
            if (head->el == el) { // if found, return true
                return true;
            }
            head = head->next;
        }
        return false;
    }

    void printMe() {
        for (int i = 0; i < this->size; i++) {
            cout << i << " ";
            Node<T>* head = buckets[i];
            while (head != NULL) {
                cout << head->el << " ";
                head = head->next;
            }
            cout << endl;
        }
    }
};

int main(void) {
    HashTable<String> h1(11);
    String word1("test1");
    String word2("test2");
    String word3("test3");
    String notThere("BAD");
    h1.insert(word1);
    h1.insert(word2);
    h1.insert(word3);
    if (h1.find(notThere)) {
        cout << "BAD" << endl;
    }

    if (h1.find(word1)) {
        cout << "TESTING FIND AND INSERT SINGLE\n" << endl;
        h1.printMe();
        cout << "\n\n" << endl;
    }

    h1.insert(word1); // duplicates go in
    h1.insert(word1); // duplicates go in
    h1.insert(word1); // duplicates go in
    h1.insert(word1); // duplicates go in, should rehash
    h1.printMe();
    return 0;
}
