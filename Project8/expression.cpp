//
// Created by kunal on 8/6/18.
//

#include "expression.h"

void expression::destroy(exprNode* rootptr) {
    if (rootptr) {
        destroy(rootptr->left);
        destroy(rootptr->right);
        delete rootptr;
    }
}

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
            root->right = new exprNode(true, 0, '\0');
        }
    }

    return root;
}

int expression::parse(exprNode* root) {
    if(root->isOperand) {
        return root->operand;
    }

    int arg1 = parse(root->left);
    int arg2 = parse(root->right); // For unary operators arg2 is a dummy variable
    return operateOn(root->operatorType, arg1, arg2);
}

expression::expression() {
    this->root = nullptr;
}

expression::~expression() {
    destroy(this->root);
}

expression::expression(std::vector<exprNode*>& exp) {
    root = add(this->root, exp);
}

int expression::parse() {
    return parse(root);
}