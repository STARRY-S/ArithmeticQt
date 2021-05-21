/**
 * Calculator: 将中缀表达式转后缀表达式并求值
 */

#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string>
#include <stack>
#include <iostream>

class Calculator {
private:
    static int getLevel(char c);
public:
    Calculator() = default;

    static float calculate(std::string &exp);
    static void handleOperator(std::stack<float> &number,
                                std::stack<char> &opera);

    virtual ~Calculator();
};

#endif
