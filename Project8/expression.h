//
// Created by kunal on 8/6/18.
//

#ifndef PROJECT8_EXPRESSION_H
#define PROJECT8_EXPRESSION_H

#include <string>
#include <vector>

class exprNode {
public:
    std::string operatorType;
    std::string var;
    int operand;
    bool isOperand;
    bool isSymbol;
    exprNode* left;
    exprNode* right;

    exprNode(bool isOperand, int operand, bool isSymbol, std::string variable, std::string optr) {
        left = nullptr;
        right = nullptr;
        this->isOperand = isOperand;
        this->operand = operand;
        this->operatorType = optr;
        this->var = variable;
        this->isSymbol = isSymbol;
    }
};

class expression {
private:
    exprNode* root;
    int parse(exprNode*);
    void destroy(exprNode*);
    exprNode* add(exprNode*, std::vector<exprNode*>&);
    bool isBinary(const std::string&);
    int operateOn(const std::string&, const int&, const int&);
public:
    expression();
    expression(std::vector<exprNode*>&);
    ~expression();
    int parse();
};


#endif //PROJECT8_EXPRESSION_H
