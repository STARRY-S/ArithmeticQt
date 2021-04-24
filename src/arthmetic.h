#ifndef ARTHMETIC_H
#define ARTHMETIC_H

#include <iostream>
#include <string>
#include <cstdio>
#include <vector>
#include <QRandomGenerator>
#include <QString>

/*
 * TODO:
 * Arthmetic -- 四则运算类
 * [] 生成指定数量的四则运算题目
 * [] 根据不同难度（年级）生成不同类型的题目
 * [] 生成的题目存储至一个列表中
 * [] 计算答案，将答案单独存储至另一个列表中
 * [] 小数的答案保留两位，并实现四舍五入
 * [] 判断学生做的题目是否正确
 * [] 打开文件导入题目
 * [] 导出题目至文件
 * [] 将生成的题目转换成小学生能看懂的格式，（加减乘除符号转换）
 *    将其存储到字符串数组中
 */

static const unsigned char ARTHMETIC_PLUS  = 0x01;
static const unsigned char ARTHMETIC_MINUS = 0x02;
static const unsigned char ARTHMETIC_TIMES = 0x04;
static const unsigned char ARTHMETIC_DIVID = 0x08;
static const unsigned char ARTHMETIC_PAREN = 0x10;
static const unsigned char ARTHMETIC_NOPAR = 0x20;

class Arthmetic {
public:
        Arthmetic();
        // Arthmetic(int, int);
        ~Arthmetic();

        QString getQuestion(int i);
        void reGenerate();
        void firstGenerate(int length);
        unsigned char getDifficulty();
        void setDifficulty(unsigned char);

private:
        unsigned char difficulty;
        std::vector<QString> questionList;

        QString generateBySet(unsigned char set);
        QString generateByGrade(int grade);
        int getRandNum(unsigned int a);
        int getRandNum(unsigned int a, unsigned int b);
        void checkLabel();

protected:

};

#endif
