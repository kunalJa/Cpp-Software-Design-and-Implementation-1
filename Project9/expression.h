//
// Created by kunal on 8/6/18.
//

#ifndef PROJECT8_EXPRESSION_H
#define PROJECT8_EXPRESSION_H

#include <string>
#include <vector>
#include <list>
#include <map>

using namespace std;

class exprNode {
private:
    bool isOperand;
    int operand;
    bool isSymbol;
    string var;
    string operatorType;
    exprNode* left;
    exprNode* right;

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

    bool getIsOperand() {
        return this->isOperand;
    }

    bool getIsSymbol() {
        return this->isSymbol;
    }

    int getOperand() {
        return this->operand;
    }

    string getVar() {
        return this->var;
    }

    string getOperatorType() {
        return this->operatorType;
    }

    exprNode* getLeft() {
        return this->left;
    }

    exprNode* getRight() {
        return this->right;
    }

    void setLeft(exprNode* other) {
        this->left = other;
    }

    void setRight(exprNode* other) {
        this->right = other;
    }
};

class expression {
private:
    exprNode* root;

    static bool isBinary(const string&);
    static int operateOn(const string&, const int&, const int&);
    exprNode* add(exprNode*, list<exprNode*>&);
    int parse(exprNode*, vector<map<string, int>>&) const;

public:
    expression(); // default constructor
    explicit expression(list<exprNode*>&); // list of exprNode constructor
    expression(const expression&); // copy constructor
    ~expression(); // destructor
    expression& operator=(const expression&);

    int parse(vector<map<string, int>>&);
};


#endif //PROJECT8_EXPRESSION_H
