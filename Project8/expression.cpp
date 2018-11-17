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

exprNode* expression::add(exprNode* root, std::vector<exprNode*>& expr) {
    exprNode* first = new exprNode(*expr[0]);
    delete expr[0];
    expr.erase(expr.begin());
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

int expression::parse(exprNode* root, std::vector<std::map<std::string, int>>& symb) const {
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
