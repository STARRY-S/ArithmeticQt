/**
 * Arithmetic: 四则运算类
 * 存储题目、答案、题目数量信息
 * 继承自Generator和Calculator
 * 拥有生成表达式和计算表达式的功能
 * Written by STARRY-S
 * License: Apache 2.0
 */

#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include "generator.hpp"
#include "calculator.hpp"

#include <string>
#include <vector>
#include <QString>

class Arithmetic : public Generator, public Calculator {
private:
    int questionNum;                // 题目数量
    std::vector<std::string> questionList;
    std::vector<float> answerList;
    static bool checkLineValid(std::string &str);

public:
    Arithmetic();
    virtual ~Arithmetic();

    QString getQuestion(int i) const;
    float getAnswer(int i) const;
    int getQuestionNum() const;

    void generate();
    void setQuestionNum(int n);
    void setDifficulty(int max, int min, bool neg, bool flt);
    int openFile(std::string &name);
};

#endif
