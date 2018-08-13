// Blip <Project9.cpp>
// EE 312 Project 8 submission by
// Kunal Jain
// ksj572
// Slip days used: 0
// Summer 2018

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include "Parse.h"
#include "expression.h"
#include "command.h"


using namespace std;


bool isNotCommand(const string& token) {
    return token != "text" && token != "output" && token != "var" && token != "set";
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

    for (vector<command*>::iterator it = commands.begin(); it != commands.end(); ++it) {
        command* command = *it;
        string currentCommand = command->currentCommand;

        if (currentCommand == "text") {
            cout << command->text;
        } else if (currentCommand == "output") {
            cout << command->output.parse(symbols);
        } else if (currentCommand == "var") {
            if (symbols[0].count(command->text) != 0) {
                cout << "variable " << command->text << " incorrectly re-initialized" << endl;
            }
            symbols[0][command->text] = command->output.parse(symbols);
        } else if (currentCommand == "set") {
            if (symbols[0].count(command->text) == 0) {
                cout << "variable " << command->text << " not declared" << endl;
            }
            symbols[0][command->text] = command->output.parse(symbols);
        }

        delete command;
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
}
