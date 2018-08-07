#include <iostream>
#include "Parse.h"

using namespace std;

void run() {
    parse();
    execute();
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
}