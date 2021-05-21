#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include <iostream>
#include <string>
#include <vector>
#include <QRandomGenerator>
#include <QString>

class Arithmetic {
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

private:
        int questionNum;                // 题目数量
        int maxNum;                     // 随机数最大值
        int minNum;                     // 最小值
        bool hasNegative;               // 结果是否有正负
        bool hasPoint;                  // 结果是否有小数
        unsigned char set;              // 当前设置（加减乘除、混合）
        std::vector<QString> questionList;
        std::vector<QString> answerList;

        QString generateBySet(int answer_pos);
        QString generateMulti(int answer_pos);
        int getRandNum(unsigned int a);
        int getRandNum(unsigned int a, unsigned int b);
        void checkLabel();
        QString calculateAnswer(int i);
        bool checkLineValid(std::string str);
};

#endif
