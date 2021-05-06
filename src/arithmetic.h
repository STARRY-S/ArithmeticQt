#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include <iostream>
#include <string>
#include <cstdio>
#include <vector>
#include <QRandomGenerator>
#include <QString>

/*
 * TODO:
 * Arithmetic -- 四则运算类
 * [x] 生成指定数量的四则运算题目
 * [x] 选择生成题是否包含负数、小数
 * [x] 设定随机数最大值
 * [x] 生成的题目存储至一个列表中
 * [x] 计算答案，将答案单独存储至另一个列表中
 * [x] 小数的答案保留两位，并实现四舍五入
 * [x] 判断学生做的题目是否正确
 * [x] 打开文件导入题目
 * [x] 导出题目至文件(由主窗口类实现)
 * [x] 将生成的题目转换成小学生能看懂的格式，（加减乘除符号转换）
 */

static const unsigned char ARITHMETIC_PLUS  = 0x01;
static const unsigned char ARITHMETIC_MINUS = 0x02;
static const unsigned char ARITHMETIC_TIMES = 0x04;
static const unsigned char ARITHMETIC_DIVID = 0x08;
static const unsigned char ARITHMETIC_PAREN = 0x10;
static const unsigned char ARITHMETIC_NOPAR = 0x20;

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
	int questionNum;	// 题目数量
	int maxNum;		// 随机数最大值
	int minNum;		// 最小值
	bool hasNegative;	// 结果是否有正负
	bool hasPoint;		// 结果是否有小数
        unsigned char set;	// 当前设置（加减乘除、混合）
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
