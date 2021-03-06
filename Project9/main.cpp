#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <list>
#include <unordered_map>
#include "Parse.h"
#include "expression.h"
#include "command.h"


using namespace std;


bool isNotCommand(const string& token) {
    return token != "text" && token != "output" && token != "var" &&
           token != "set" && token != "if" && token != "else" && token != "fi" &&
           token != "do" && token != "od" && token != "call" && token != "defun" &&
           token != "nufed" && token != "return" && token != "params" && token != "smarap" &&
           token != "args" && token != "sgra" && token != ":"; // args separated by : ?
}

void buildExpression(vector<command*>& commands, unsigned long& commandCounter) {
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
            expr.push_back(new exprNode(false, 0, false, "", token));
        } else if (next_token_type == NAME) {
            if (token == "call") {
                read_next_token();
                expr.push_back(new exprNode(true, 0, true, token, next_token())); // put call into var and name of func into operator
            } else {
                expr.push_back(new exprNode(true, 0, true, token, ""));
            }
        }
        peek_next_token();
    }

    commands[commandCounter]->output = expression(expr);
}

void run() {
    unordered_map<string, int> global;
    vector<unordered_map<string, int>> symbols; // vector for scope
    symbols.push_back(global);
    vector<command*> commands;
    unordered_map<string, functionMetadata> functions; // function map
    unsigned long commandCounter = 0;

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
            } else if (commands[commandCounter]->currentCommand == "var" ||
                       commands[commandCounter]->currentCommand == "set") {
                read_next_token();
                commands[commandCounter]->text = next_token();
                buildExpression(commands, commandCounter);
            } else if (commands[commandCounter]->currentCommand == "if") { // do nothing on else or fi
                buildExpression(commands, commandCounter);
            } else if (commands[commandCounter]->currentCommand == "do") { // do nothing on od
                buildExpression(commands, commandCounter);
            } else if (commands[commandCounter]->currentCommand == "defun") {
                read_next_token();
                commands[commandCounter]->text = next_token(); // function name is in text
                functions[commands[commandCounter]->text].index = commandCounter; // put the function:index in the map
                read_next_token();
                if (string(next_token()) != "params") { // investigate why string needs to be there
                    // ERROR
                } else {
                    read_next_token();
                    while (string(next_token()) != "smarap") {
                        functions[commands[commandCounter]->text].params.emplace_back(next_token()); // emplace_ vs push_?
                        read_next_token();
                    }
                }
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
    stack<unsigned  long> index;
    stack<bool> depth;
    unsigned long numCommands = commands.size();
    for (unsigned long i = 0; i < numCommands; i++) {
        string currentCommand = commands[i]->currentCommand;
        if (executable && currentCommand == "text") {
            cout << commands[i]->text;
        } else if (executable && currentCommand == "output") {
            cout << commands[i]->output.parse(symbols);
        } else if (executable && currentCommand == "var") {
            if (symbols[0].find(commands[i]->text) != symbols[0].end()) {
                cout << "variable " << commands[i]->text << " incorrectly re-initialized" << endl;
            }
            symbols[0][commands[i]->text] = commands[i]->output.parse(symbols);
        } else if (executable && currentCommand == "set") {
            if (symbols[0].find(commands[i]->text) == symbols[0].end()) {
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
        } else if (currentCommand == "do") {
            depth.push(executable);
            if (executable) {
                if (!commands[i]->output.parse(symbols)) {
                    executable = false;
                } else {
                    index.push(i);
                }
            }
        } else if (currentCommand == "od") {
            if (executable) {
                i = index.top() - 1; // for loop immediately increments i
                        // cant have od as first line!! this breaks becuase i is unsigned long
                index.pop();
            }
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
    cout << endl;
    set_input("test3.blip");
    run();
//    cout << endl;
//    set_input("test4.blip");
//    run();
//    cout << endl;
//    set_input("test5.blip");
//    run();
//    cout << endl;
    set_input("test6.blip");
    run();
    cout << endl;
    set_input("test7.blip");
    run();
//    cout << endl;
//    set_input("test8.blip");
//    run();
//    cout << endl;
//    set_input("test9.blip");
//    run();
//    cout << endl;
    set_input("test10.blip");
    run();
}
