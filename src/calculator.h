#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string>

class Calculator {
private:
public:
        Calculator() = default;

        virtual float calculate(std::string exp);
};

#endif
