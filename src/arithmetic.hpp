#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include "generator.hpp"
#include "calculator.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <QString>

class Arithmetic : public Generator, public Calculator {
private:
    int questionNum;                // 题目数量
    std::vector<QString> questionList;
    std::vector<QString> answerList;

    bool checkLineValid(std::string str);

public:
    Arithmetic();
    ~Arithmetic();

    QString getQuestion(int i);
    QString getAnswer(int i);
    void generate();
    unsigned char getSet();
    void setSet(unsigned char);
    int getQuestionNum();
    void setQuestionNum(int);
    void setDifficulty(int max, int min, bool n, bool p);
    int openFile(std::string name);
};

#endif
