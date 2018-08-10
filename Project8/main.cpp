#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Parse.h"
#include "expression.h"
#include "command.h"
using namespace std;

void run() {
    map<string, int>* global = new map<string, int>;
    vector<map<string, int>*> symbols; // vector for scope
    symbols.push_back(global);
    vector<command*> commands;
    int commandCounter = 0;
//    vector<int> loopCounters;
    read_next_token();
    while(next_token_type != END) {
        if (next_token_type == NAME) {
            command* currentCommand = new command;
            commands.push_back(currentCommand);
            commands[commandCounter]->text = string(next_token());
            if (commands[commandCounter]->text == "text") {
                
            } else if (commands[commandCounter]->text == "output") {

            } else if (commands[commandCounter]->text == "var") {

            } else if (commands[commandCounter]->text == "set") {

            }
        } else {
            skip_line();
        }

        read_next_token();
    }
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
    set_input("test_grader.blip");
    run();
//    string a(" + + 2 3 ~ 4");
//    const int size = 5;
//    exprNode* nodes [size];
//    nodes[0] = new exprNode(false, 0, "+");
//    nodes[1] = new exprNode(false, 0, "&&");
//    nodes[2] = new exprNode(true, 6, "");
//    nodes[3] = new exprNode(true, 12, "");
//    nodes[4] = new exprNode(true, 10, "");
//    nodes[5] = new exprNode(true, 4, '\0');
//    nodes[6] = new exprNode(true, 5, '\0');
//    vector<exprNode*> expr;
//    for (int i = 0; i < size; i++) { // add Nodes to expression expr
//        expr.push_back(nodes[i]);
//    }
//    cout << endl;
//
//    expression myTree(expr);
//    cout << a << " = " << myTree.parse() << endl;
}