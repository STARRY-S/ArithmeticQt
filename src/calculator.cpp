#include "calculator.hpp"
#include <iostream>

int Calculator::getLevel(int c)
{
    switch (c) {
        case '+': return 10;
        case '-': return 10;
        case '*': return 20;
        case '/': return 20;
        case '(': return 100;
        case ')': return 1;
    }

    throw "invalid operator";
    return 0;
}

void Calculator::handleOperator(std::stack<float> &number,
                                std::stack<char> &opera)
{
    char opt;
    float a, b;
    try {
        opt = opera.top();
        opera.pop();
        // 处理过程中如果遇到括号直接丢弃
        if (opt == '(' || opt == ')') { return; }
        a = number.top();
        number.pop();
        b = number.top();
        number.pop();
    } catch (const char *const e) {
        std::cerr << e << std::endl;
        return;
    }

    // std::cout << "opt = " << (int) opt << ' ' << opt << std::endl;

    switch (opt) {
        case '+':
        {
            number.push(b + a);
            break;
        }
        case '-':
        {
            number.push(b - a);
            break;
        }
        case '*':
        {
            number.push(b * a);
            break;
        }
        case '/':
        {
            number.push(b / a);
            break;
        }
        default:
            break;
    }

    // if (number.size()) {
    //     std::cout << "number.push " << number.top() << std::endl;
    // }
}

float Calculator::calculate(const std::string &exp)
{
    std::stack<float> number;
    std::stack<char> opera;

    const int length = exp.length();
    for (int i = 0; i < length; ++i) {
        // 如果为数字 直接压栈
        if (exp[i] >= '0' && exp[i] <= '9') {
            int temp = 0;
            while (exp[i] >= '0' && exp[i] <= '9') {
                temp *= 10;
                temp += exp[i] - '0';
                ++i;
            }
            number.push(temp);

            // avoid '\0'
            if (i >= length) {
                break;
            }
        }

        // 如果是左括号，直接压栈
        if (exp[i] == '(') {
            opera.push(exp[i]);
            continue;
        }

        try {
            // 如果 运算符栈为空，直接压栈
            if (opera.empty()) {
                opera.push(exp[i]);
            // 表达式的运算符优先级大于栈顶的运算符优先级，也直接压栈
            } else if ( getLevel(exp[i]) > getLevel(opera.top()) ) {
                opera.push(exp[i]);
            // 栈顶的运算符优先级大于等于表达式的优先级，那么先求值
            } else {
                handleOperator(number, opera);
                opera.push(exp[i]);
            }
        } catch(const char *const e) {
            std::cerr << e << std::endl;
            return -1;
        }
    }

    while (opera.size() > 0) {
        handleOperator(number, opera);
    }

    float answer = 0;
    if (number.size() > 0) {
        answer = number.top();
    }

    return answer;
}
