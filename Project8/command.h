#ifndef PROJECT8_COMMAND_H
#define PROJECT8_COMMAND_H
#include <string>
#include "expression.h"

class command {
public:
    std::string currentCommand;
    std::string text; // also variable names
    expression output;
};


#endif //PROJECT8_COMMAND_H
