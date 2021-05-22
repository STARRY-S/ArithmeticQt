/**
 * Generator: 生成运算符表达式
 * 静态方法: 生成随机运算符、生成随机数
 * 静态变量: 难度、模式
 * 类成员：难度、模式、随机数范围
 * Created by STARRY-S - hxstarrs@gmail.com
 * LICENSE Apache 2.0
 */

#ifndef GENERATOR_H
#define GENERATOR_H

#include <QRandomGenerator>
#include <string>
#include <sstream>

class Generator {
private:
    uint8_t set = 0;
    uint8_t mode = 0;
    int min = 0;        // min random number
    int max = 100;      // max randrom number

    char getOperaByLabel(uint8_t label) const;
    void genNumByMode(int &a, int &b, uint8_t label) const;
    void gen_normal(std::string &exp) const;
    void gen_par(std::string &exp) const;
    void gen_npa(std::string &exp) const;


public:
    /* sets */
    static const uint8_t ADD = 0x01;    // 加法
    static const uint8_t SUB = 0x02;    // 减法
    static const uint8_t MUL = 0x04;    // 乘法
    static const uint8_t DIV = 0x08;    // 除法
    static const uint8_t PAR = 0x10;    // 括号
    static const uint8_t NPA = 0x20;    // 没有括号
    /* modes */
    static const uint8_t NEG = 0x01;    // 有负数
    static const uint8_t FLT = 0x02;    // 有小数

    Generator() = default;
    Generator(int _set)
        : set(_set) { }
    Generator(int _set, int _mode)
        : set(_set), mode(_mode) { }
    Generator(int _set, int _mode, int _min, int _max)
        : set(_set), mode(_mode), min(_min), max(_max) { }

    virtual ~Generator() { }

    void genExp(std::string &exp) const;
    void setMin(int _min);
    void setMax(int _max);
    void setSet(uint8_t _set);
    uint8_t getSet() const;
    void setMode(uint8_t _mode);

    static char getRandoper();
    static int getRandNum();
    static int getRandNum(unsigned int a, unsigned int b);
};

#endif
