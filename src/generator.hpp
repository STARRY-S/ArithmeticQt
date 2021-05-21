/**
 * Generator: 生成运算符表达式
 * 类中存储难度、模式、随机数范围信息
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
    int min;        // min random number
    int max;        // max randrom number

    void gen_add(std::string &exp);
    void gen_sub(std::string &exp);
    void gen_mul(std::string &exp);
    void gen_div(std::string &exp);
    void gen_par(std::string &exp);
    void gen_npa(std::string &exp);

    char getRandoper();
    int getRandNum(unsigned int a, unsigned int b);

public:
    /* sets */
    static const uint8_t ADD = 0x01;
    static const uint8_t SUB = 0x02;
    static const uint8_t MUL = 0x04;
    static const uint8_t DIV = 0x08;
    static const uint8_t PAR = 0x10;    // 括号
    static const uint8_t NPA = 0x20;    // 没有括号

    /* modes */
    static const uint8_t NEG = 0x01;    // has negative
    static const uint8_t FLT = 0x02;    // has float number

    Generator() = default;
    Generator(int _set)
        : set(_set) { }
    Generator(int _set, int _mode)
        : set(_set), mode(_mode) { }
    Generator(int _set, int _mode, int _min, int _max)
        : set(_set), mode(_mode), min(_min), max(_max) { }

    virtual ~Generator() { }

    void generate(std::string &exp);
    void setMin(int _min);
    void setMax(int _max);
    void setSet(uint8_t _set);
    void setMode(uint8_t _mode);
};

#endif
