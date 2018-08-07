//
// Created by kunal on 8/6/18.
//

#ifndef PROJECT8_EXPRESSION_H
#define PROJECT8_EXPRESSION_H

#include <string>
#include <vector>

typedef struct expNode {
    std::string operatorType;
    int operand;
    bool isOperand;
    struct expNode* left;
    struct expNode* right;
} exprNode;

class expression {
private:
    exprNode* root;
    int parse(exprNode*);
    void destroy(exprNode*);
    exprNode* add(exprNode*, std::vector<expNode*>&);
    bool isBinary(const std::string&);
    int operateOn(const std::string&, const int&, const int&);
public:
    expression();
    expression(std::vector<expNode*>&);
    ~expression();
    int parse();
};


#endif //PROJECT8_EXPRESSION_H
