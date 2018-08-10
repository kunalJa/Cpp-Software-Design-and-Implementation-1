//
// Created by kunal on 8/6/18.
//

#ifndef PROJECT8_EXPRESSION_H
#define PROJECT8_EXPRESSION_H

#include <string>
#include <map>
#include <vector>

class exprNode {
public:
    bool isOperand;
    int operand;
    bool isSymbol;
    std::string var;
    std::string operatorType;
    exprNode* left;
    exprNode* right;

    void destroy(exprNode*);

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
        left = nullptr;
        right = nullptr;
        this->isOperand = 0;
        this->operand = 0;
        this->operatorType = "\0";
        this->var = "\0";
        this->isSymbol = 0;
    }

    ~exprNode() {
        delete left;
        delete right;
    }

    exprNode(const exprNode& other) {
        this->isOperand = other.isOperand;
        this->operand = other.operand;
        this->operatorType = other.operatorType;
        this->var = other.var;
        this->isSymbol = other.isSymbol;
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

    exprNode& operator=(const exprNode& other) {
        if (this != &other) {
            destroy(this);
            this->isOperand = other.isOperand;
            this->operand = other.operand;
            this->operatorType = other.operatorType;
            this->var = other.var;
            this->isSymbol = other.isSymbol;
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

        return *this;
    }
};

class expression {
private:
    int parse(exprNode*, std::vector<std::map<std::string, int>>&);
    void destroy(exprNode*);
    exprNode* add(exprNode*, std::vector<exprNode*>&);
    bool isBinary(const std::string&);
    int operateOn(const std::string&, const int&, const int&);
    void copy(const expression&);
public:
    exprNode* root;
    expression();
    expression(std::vector<exprNode*>&);
    expression& operator=(const expression&);
    expression(const expression&);
    ~expression();
    int parse(std::vector<std::map<std::string, int>>&);
};


#endif //PROJECT8_EXPRESSION_H
