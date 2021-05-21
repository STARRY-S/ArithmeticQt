#include "calculator.hpp"

int Calculator::getLevel(char c)
{
    switch (c) {
        case '+': return 10;
        case '-': return 10;
        case '*': return 20;
        case '/': return 20;
        case '(': return 100;
        case ')': return 1;
        default:
            break;
    }
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
        if (opt == '(' || opt == ')') {
            return;
        }
        a = number.top();
        number.pop();
        b = number.top();
        number.pop();
    } catch (std::string e) {
        std::cerr << e << std::endl;
        return;
    }

    switch (opt) {
        case '+':
        {
            number.push(a + b);
            break;
        }
        case '-':
        {
            number.push(b - a);
            break;
        }
        case '*':
        {
            number.push(a * b);
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
    std::cout << "number.push" << number.top() << std::endl;
}

float Calculator::calculate(std::string &exp)
{
    std::stack<float> number;
    std::stack<char> opera;

    for (int i = 0; (size_t) i < exp.length(); i++) {
        // 如果为数字 直接压栈
        if (exp[i] >= '0' && exp[i] <= '9') {
            number.push(exp[i] - '0');
            continue;
        }

        // 如果是左括号，直接压栈
        if (exp[i] == '(') {
            opera.push(exp[i]);
            continue;
        }

        // if (exp[i] == ')') {
        //     continue;
        // }

        // 如果 运算符栈为空，直接压栈
        if (opera.empty()) {
            opera.push(exp[i]);
        // 表达式的运算符优先级大于栈顶的运算符优先级，也直接压栈
        } else if ( getLevel(exp[i]) >= getLevel(opera.top()) ) {
            opera.push(exp[i]);
        // 栈顶的运算符优先级高，那么先求值
        } else {
            handleOperator(number, opera);
            opera.push(exp[i]);
        }
    }

    while (opera.size() > 0) {
        handleOperator(number, opera);
    }

    std::cout << number.top() << std::endl;
    return 0;
}
