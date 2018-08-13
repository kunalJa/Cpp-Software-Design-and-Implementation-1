// Blip <Project9.cpp>
// EE 312 Project 8 submission by
// Kunal Jain
// ksj572
// Slip days used: 0
// Summer 2018

#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <list>
#include <map>
#include "Parse.h"
#include "expression.h"
#include "command.h"


using namespace std;


bool isNotCommand(const string& token) {
    return token != "text" && token != "output" && token != "var" && token != "set" && token != "if" && token != "else" && token != "fi";
}

void buildExpression(vector<command*>& commands, int& commandCounter) {
    string token;
    peek_next_token();
    list<exprNode*> expr;
    while(isNotCommand(next_token()) && next_token_type != END) {
        read_next_token();
        token = next_token();
        if (token == "//") {
            break;
        }

        if (next_token_type == NUMBER) {
            expr.push_back(new exprNode(true, token_number_value, false, "", ""));
        } else if (next_token_type == SYMBOL) {
            expr.push_back(new exprNode(false, 0, false, "", next_token()));
        } else if (next_token_type == NAME) {
            expr.push_back(new exprNode(true, 0, true, next_token(), ""));
        }
        peek_next_token();
    }

    commands[commandCounter]->output = expression(expr);
}

void run() {
    map<string, int> global;
    vector<map<string, int>> symbols; // vector for scope
    symbols.push_back(global);
    vector<command*> commands;
    int commandCounter = 0;

    read_next_token();
    while(next_token_type != END) {
        if (next_token_type == NAME) {
            commands.push_back(new command());
            commands[commandCounter]->currentCommand = next_token();
            if (commands[commandCounter]->currentCommand == "text") {
                read_next_token();
                commands[commandCounter]->text = next_token();
            } else if (commands[commandCounter]->currentCommand == "output") {
                buildExpression(commands, commandCounter);
            } else if (commands[commandCounter]->currentCommand == "var" || commands[commandCounter]->currentCommand == "set") {
                read_next_token();
                commands[commandCounter]->text = next_token();
                buildExpression(commands, commandCounter);
            } else if (commands[commandCounter]->currentCommand == "if") { // do nothing on else or fi
                buildExpression(commands, commandCounter);
            }
            commandCounter++;
        } else {
            skip_line();
        }

        if (string(next_token()) == "//") {
            skip_line();
        }
        read_next_token();
    }

    bool executable = true;
    stack<bool> depth;
    unsigned long numCommands = commands.size();
    for (unsigned long i = 0; i < numCommands; i++) {
        string currentCommand = commands[i]->currentCommand;
        if (currentCommand == "text" && executable) {
            cout << commands[i]->text;
        } else if (currentCommand == "output" && executable) {
            cout << commands[i]->output.parse(symbols);
        } else if (currentCommand == "var" && executable) {
            if (symbols[0].count(commands[i]->text) != 0) {
                cout << "variable " << commands[i]->text << " incorrectly re-initialized" << endl;
            }
            symbols[0][commands[i]->text] = commands[i]->output.parse(symbols);
        } else if (currentCommand == "set" && executable) {
            if (symbols[0].count(commands[i]->text) == 0) {
                cout << "variable " << commands[i]->text << " not declared" << endl;
            }
            symbols[0][commands[i]->text] = commands[i]->output.parse(symbols);
        } else if (currentCommand == "if") {
            depth.push(executable);
            if (executable && !commands[i]->output.parse(symbols)) {
                executable = false;
            }
        } else if (currentCommand == "else") { // assumes correct format for input fix this
            if (depth.top()) {
                executable ^= true; // toggle
            }
        } else if (currentCommand == "fi") {
            executable = depth.top();
            depth.pop();
        }
    }

    for (unsigned long i = 0; i < numCommands; i++) {
        delete commands[i];
    }
}


int main(void) {
    set_input("test1.blip");
    run();
    cout << endl;
    set_input("test2.blip");
    run();
//    cout << endl;
//    set_input("test3.blip");
//    run();
//    cout << endl;
//    set_input("test4.blip");
//    run();
//    cout << endl;
//    set_input("test5.blip");
//    run();
//    cout << endl;
//    set_input("test6.blip");
//    run();
//    cout << endl;
//    set_input("test7.blip");
//    run();
//    cout << endl;
//    set_input("test8.blip");
//    run();
//    cout << endl;
//    set_input("test9.blip");
//    run();
    cout << endl;
    set_input("test10.blip");
    run();
}
