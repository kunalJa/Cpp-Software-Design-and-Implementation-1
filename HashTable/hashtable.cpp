#include <iostream>
#include "String.h"

using namespace std;


template <class T>
struct Node {
    T el;
    struct Node* next = nullptr;
};

template <class T>
class HashTable {
private:
    Node<T>** buckets;
    int size;

    int hash(int el) {
        return el % size; 
    }

    void rehash() {
        int oldSize = this->size;
        Node<T>** bucketsOld = this->buckets;
        this->size += 17;
        this->buckets = new Node<T>*[this->size];
        for (int i = 0; i < this->size; i++) {
            buckets[i] = nullptr;
        }

        for (int j = 0; j < oldSize; j++) {
            Node<T>* head = bucketsOld[j];
            while (head != nullptr) {
                insert(head->el);
                head = head->next;
            }
        }

        for (int k = 0; k < oldSize; k++) {
            destroy(bucketsOld[k]);
        }

        delete [] bucketsOld;
    }

    void destroy(Node<T>*& root) {
        if (root == nullptr) {
            return;
        }

        destroy(root->next);
        delete root;
    }

public:
    explicit HashTable(int size) {
        this->size = size;
        buckets = new Node<T>*[size];
        for (int i = 0; i < this->size; i++) {
            buckets[i] = nullptr;
        }
    }

    ~HashTable() {
        for (int i = 0; i < this->size; i++) {
            destroy(this->buckets[i]);
        }
        delete [] this->buckets;
    }

    void insert(T el) {
        Node<T>* nodeNew = new Node<T>();
        nodeNew->el = el;
        nodeNew->next = nullptr;
        int ix = hash(el.hash());  // Assumes type T has a hash function

        int count = 0;
        Node<T>* prev = nullptr;
        Node<T>* head = buckets[ix];
        while (head != nullptr) { // insert into end of the linked list at that place ix
            if (head->el == el) { // No duplicates
                delete nodeNew;
                return;
            }
            prev = head;
            head = head->next;
            count++;
        }

        if (prev) {
            prev->next = nodeNew;
        } else {
            buckets[ix] = nodeNew;
        }

        if (count >= 5) {
            rehash();
        }
    }

    bool find(T el) { // find the value el in the list
        int ix = hash(el.hash());  // Assumes type T has a hash function
        Node<T>* head = buckets[ix];
        while (head != nullptr) { // search through the linked-list at that location
            if (head->el == el) {
                return true;
            }
            head = head->next;
        }
        return false;
    }

    void printMe() {
        for (int i = 0; i < this->size; i++) {
            cout << i << ": ";
            Node<T>* head = buckets[i];
            while (head != nullptr) {
                cout << head->el << ", ";
                head = head->next;
            }
            cout << endl;
        }
    }
};

int main(void) {
    HashTable<String> h1(3);
    h1.insert("test1");
    h1.insert("test2");
    h1.insert("test3");
    if (h1.find("not there")) {
        cout << "BAD" << endl;
    }

    if (h1.find("test1")) {
        cout << "TESTING FIND AND INSERT SINGLE\n" << endl;
        h1.printMe();
        cout << "\n" << endl;
    }

    cout << "TESTING DUPLICATES\n" << endl;
    h1.insert("test4");
    h1.insert("test5");
    h1.insert("test6");
    h1.insert("test7");
    h1.insert("test1"); // duplicates don't go in
    h1.insert("test4"); // duplicates don't go in
    h1.printMe();

    cout << "\n\nTESTING REHASH\n" << endl;
    h1.insert("a");
    h1.insert("A");
    h1.printMe();
    return 0;
}
