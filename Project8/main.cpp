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
//    int currentScope = 0;
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
                        expr.push_back(new exprNode(true, token_number_value, false, "\0", "\0"));
                    } else if (next_token_type == SYMBOL) {
                        expr.push_back(new exprNode(false, 0, false, "\0", string(next_token())));
                    } else if (next_token_type == NAME) {
                        expr.push_back(new exprNode(true, 0, true, string(next_token()), "\0"));
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

    for (int i = 0; i < commands.size(); i++) {
        string currentCommand = commands[i]->currentCommand;
        if (currentCommand == "text") {
            cout << commands[i]->text;
        } else if (currentCommand == "output") {
            cout << commands[i]->output.parse(symbols);
        } else if (currentCommand == "var") {
            if (symbols[0].count(commands[i]->text) != 0) {
                cout << "variable " << commands[i]->text << " incorrectly re-initialized" << endl;
            }
            symbols[0][commands[i]->text] = commands[i]->output.parse(symbols);

        } else if (currentCommand == "set") {
            if (symbols[0].count(commands[i]->text) == 0) {
                cout << "variable " << commands[i]->text << " not declared" << endl;
            }

            symbols[0][commands[i]->text] = commands[i]->output.parse(symbols);
        }
    }

}

int main() {
    set_input("test_grader.blip");
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
}