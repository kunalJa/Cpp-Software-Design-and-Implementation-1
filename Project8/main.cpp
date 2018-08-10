#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Parse.h"
#include "expression.h"
#include "command.h"
using namespace std;

void run() {
    map<string, int> global;
    vector<map<string, int>> symbols; // vector for scope
    symbols.push_back(global);
    vector<command*> commands;
    int currentScope = 0;
    int commandCounter = 0;
//    vector<int> loopCounters;
    read_next_token();
    while(next_token_type != END) {
        if (next_token_type == NAME) {
            command* command1 = new command;
            commands.push_back(command1);
            commands[commandCounter]->currentCommand = string(next_token());
            if (commands[commandCounter]->currentCommand == "text") {
                read_next_token();
                commands[commandCounter]->text = string(next_token());
            } else if (commands[commandCounter]->currentCommand == "output") {
                peek_next_token();
                vector<exprNode*> expr;
                while(string(next_token()) != "text" && string(next_token()) != "output" && string(next_token()) != "var" && string(next_token()) != "set") {
                    read_next_token();
                    if (string(next_token()) == "//") {
                        break;
                    }

                    if (next_token_type == NUMBER) {
                        expr.push_back(new exprNode(true, token_number_value, false, "", ""));
                    } else if (next_token_type == SYMBOL) {
                        expr.push_back(new exprNode(false, 0, false, "", string(next_token())));
                    } else if (next_token_type == NAME) {
                        expr.push_back(new exprNode(true, 0, true, string(next_token()), ""));
                    }
                    peek_next_token();
                }

                if(string(next_token()) != "//") {
                    commands[commandCounter]->output = expression(expr);
                }
            } else if (commands[commandCounter]->currentCommand == "var") {

            } else if (commands[commandCounter]->currentCommand == "set") {

            }

            commandCounter++;
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
//    map<string, int> global;
//    vector<map<string, int>> symbols; // vector for scope
//    symbols.push_back(global);
//    vector<command*> commands;
//    int currentScope = 0;
//    int commandCounter = 0;
//    string a(" + + 2 3 ~ 4");
//    const int size = 5;
//    exprNode* nodes [size];
//    symbols[0]["x"] = 10;
//    nodes[0] = new exprNode(false, 0, false, "", "+");
//    nodes[1] = new exprNode(false, 0, false, "", "&&");
//    nodes[2] = new exprNode(true, 6, false, "", "");
//    nodes[3] = new exprNode(true, 12, false, "", "");
//    nodes[4] = new exprNode(true, 100, true, "x", "");
////    nodes[5] = new exprNode(true, 4, false, "", '\0');
////    nodes[6] = new exprNode(true, 5, false, "", '\0');
//    vector<exprNode*> expr;
//    for (int i = 0; i < size; i++) { // add Nodes to expression expr
//        expr.push_back(nodes[i]);
//    }
//    cout << endl;
//
//    expression myTree(expr);
//    cout << a << " = " << myTree.parse(symbols) << endl;
}