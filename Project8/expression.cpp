//
// Created by kunal on 8/6/18.
//

#include <string>
#include <vector>
#include <map>
#include "expression.h"

bool expression::isBinary(const std::string& Operator) {
    if (Operator == "!") {
        return false;
    } else if (Operator == "~") {
        return false;
    }

    return true;
}

int expression::operateOn(const std::string& Operator, const int& arg1, const int& arg2) {
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

exprNode* expression::add(exprNode* root, std::vector<exprNode*> & expr) {
    exprNode* first = expr[0];
    expr.erase(expr.begin());
    root = first;
    if (!(first->isOperand)) {
        root->left = add(root->left, expr);
        if(isBinary(first->operatorType)) {
            root->right = add(root->right, expr);
        } else {
            root->right = new exprNode(true, 0, false, "", "");
        }
    }

    return root;
}

int expression::parse(exprNode* root, std::vector<std::map<std::string, int>>& symb) const {
    if(root->isOperand) {
        if (root->isSymbol) {
            return symb[0][root->var];
        }

        return root->operand;
    }

    int arg1 = parse(root->left, symb);
    int arg2 = parse(root->right, symb); // For unary operators arg2 is a dummy variable
    return operateOn(root->operatorType, arg1, arg2);
}

expression::expression() {
    this->root = nullptr;
}

expression::expression(std::vector<exprNode*>& exp) {
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

int expression::parse(std::vector<std::map<std::string, int>>& symb) {
    return parse(this->root, symb);
}