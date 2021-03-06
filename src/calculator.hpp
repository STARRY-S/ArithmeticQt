/**
 * Calculator: 指定运算表达式并求值
 * 仅支持表达式中的数全部为正数时的运算，
 * 不支持表达式中出现负数的情况
 * Author: STARRT-S
 * License: Apache 2.0
 */

#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string>
#include <stack>

class Calculator {
private:
    static int getLevel(int c);
    static void handleOperator(std::stack<float> &number,
                                std::stack<char> &opera);
public:
    Calculator() = default;

    static float calculate(const std::string &exp);

    virtual ~Calculator() { }
};

#endif
