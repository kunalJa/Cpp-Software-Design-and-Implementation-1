#include <iostream>
#include "Parse.h"
#include <string>
#include "expression.h"
using namespace std;

void run() {
}

void dummy() {
//    map<string, int> vars;
    read_next_token();
    while(next_token_type != END) {
        if (next_token_type == NAME) {
            string command = string(next_token());
            if (command == "text") {
                read_next_token();
                cout << next_token() << endl;
            }
        }
        read_next_token();
    }
}

int main() {
//    set_input("test_grader.blip");
//    run();
    string a(" + + 2 3 ~ 4");
    const int size = 6;
    exprNode* nodes [size];
    nodes[0] = new exprNode(false, 0, '+');
    nodes[1] = new exprNode(false, 0, '+');
    nodes[2] = new exprNode(true, 2, '\0');
    nodes[3] = new exprNode(true, 3, '\0');
    nodes[4] = new exprNode(false, 0, '~');
    nodes[5] = new exprNode(true, 4, '\0');
    //nodes[6] = new exprNode(true, 5, '\0');
    vector<exprNode*> expr;
    for (int i = 0; i < size; i++) { // add Nodes to expression expr
        expr.push_back(nodes[i]);
    }
    cout << endl;

    expression myTree(expr);
    cout << a << " = " << myTree.parse() << endl;
}