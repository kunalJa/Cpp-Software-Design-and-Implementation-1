//
// Created by kunal on 8/9/18.
//

#ifndef PROJECT8_COMMAND_H
#define PROJECT8_COMMAND_H
#include <string>
#include <vector>
#include "expression.h"

struct command {
    std::string currentCommand;
    std::string text; // also variable names
    expression output;
};

struct functionMetadata {
    unsigned long index;
    std::vector<std::string> params;
};


#endif //PROJECT8_COMMAND_H
