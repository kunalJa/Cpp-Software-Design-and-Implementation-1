//
// Created by kunal on 8/6/18.
//

#include <string>
#include <vector>
#include <list>
#include <map>
#include "expression.h"

using namespace std;

bool expression::isBinary(const string& Operator) {
    if (Operator == "!") {
        return false;
    } else if (Operator == "~") {
        return false;
    }

    return true;
}

int expression::operateOn(const string& Operator, const int& arg1, const int& arg2) {
    if (isBinary(Operator)) {
        if (Operator == "+") {
            return arg1 + arg2;
        } else if (Operator == "-") {
            return arg1 - arg2;
        } else if (Operator == "*") {
            return arg1 * arg2;
        } else if (Operator == "/") {
            return arg1 / arg2;
        } else if (Operator == "%") {
            return arg1 % arg2;
        } else if (Operator == "&&") {
            return arg1 && arg2;
        } else if (Operator == "||") {
            return arg1 || arg2;
        } else if (Operator == "<") {
            return arg1 < arg2;
        } else if (Operator == ">") {
            return arg1 > arg2;
        } else if (Operator == "==") {
            return arg1 == arg2;
        } else if (Operator == "!=") {
            return arg1 != arg2;
        } else if (Operator == "<=") {
            return arg1 <= arg2;
        } else if (Operator == ">=") {
            return arg1 >= arg2;
        }
    } else {
        if (Operator == "!") {
            return !arg1;
        } else if (Operator == "~") {
            return -1 * arg1;
        }
    }
}

exprNode* expression::add(exprNode* root, list<exprNode*>& expr) {
    exprNode* first = new exprNode(*expr.front());
    delete expr.front();
    expr.pop_front();
//    delete expr[0];
//    expr.erase(expr.begin());
    root = first;
    if (!first->getIsOperand()) {
        root->setLeft(add(root->getLeft(), expr));
        if(isBinary(first->getOperatorType())) {
            root->setRight(add(root->getRight(), expr));
        } else {
            root->setRight(new exprNode(true, 0, false, "", ""));
        }
    }
    return root;
}

int expression::parse(exprNode* root, vector<map<string, int>>& symb) const {
    if(root->getIsOperand()) {
        if (root->getIsSymbol()) {
            return symb[0][root->getVar()];
        }

        return root->getOperand();
    }

    int arg1 = parse(root->getLeft(), symb);
    int arg2 = parse(root->getRight(), symb); // For unary operators arg2 is a dummy variable
    return operateOn(root->getOperatorType(), arg1, arg2);
}

expression::expression() {
    this->root = nullptr;
}

expression::expression(list<exprNode*>& exp) {
    this->root = add(this->root, exp);
}

expression::expression(const expression& other) {
    this->root = new exprNode(*other.root);
}

expression::~expression() {
    delete this->root;
}

expression& expression::operator=(const expression& other) {
    if (this != &other) {
        delete this->root;
        this->root = new exprNode(*other.root);
    }

    return *this;
}

int expression::parse(vector<map<string, int>>& symb) {
    return parse(this->root, symb);
}