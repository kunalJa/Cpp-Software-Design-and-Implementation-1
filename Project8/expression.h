//
// Created by kunal on 8/6/18.
//

#ifndef PROJECT8_EXPRESSION_H
#define PROJECT8_EXPRESSION_H

#include <string>
#include <map>
#include <vector>

class exprNode {
private:
    void copy(const exprNode& other) {
        this->isOperand = other.isOperand;
        this->operand = other.operand;
        this->isSymbol = other.isSymbol;
        this->var = other.var;
        this->operatorType = other.operatorType;
        if (other.left != nullptr) {
            this->left = new exprNode(*other.left);
        } else {
            this->left = nullptr;
        }

        if (other.right != nullptr) {
            this->right = new exprNode(*other.right);
        } else {
            this->right = nullptr;
        }
    }

public:
    bool isOperand;
    int operand;
    bool isSymbol;
    std::string var;
    std::string operatorType;
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

    exprNode() {
        this->operand = 0;
        this->left = this->right = nullptr;
        this->isOperand = this->isSymbol = false;
        this->operatorType = this->var = "";
    }

    ~exprNode() {
        delete left;
        delete right;
    }

    exprNode(const exprNode& other) {
        copy(other);
    }

    exprNode& operator=(const exprNode& other) {
        if (this != &other) {
            delete this->left;
            delete this->right;
            copy(other);
        }

        return *this;
    }
};

class expression {
private:
    exprNode* root;

    static bool isBinary(const std::string&);
    static int operateOn(const std::string&, const int&, const int&);
    exprNode* add(exprNode*, std::vector<exprNode*>&);
    int parse(exprNode*, std::vector<std::map<std::string, int>>&) const;

public:
    expression(); // default constructor
    explicit expression(std::vector<exprNode*>&); // vector of exprNode constructor
    expression(const expression&); // copy constructor
    ~expression(); // destructor
    expression& operator=(const expression&);

    int parse(std::vector<std::map<std::string, int>>&);
};


#endif //PROJECT8_EXPRESSION_H
