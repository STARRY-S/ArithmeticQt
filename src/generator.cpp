#include "generator.hpp"

char Generator::getOperaByLabel(uint8_t label) const
{
    switch (label) {
        case ADD: return '+';
        case SUB: return '-';
        case MUL: return '*';
        case DIV: return '/';
    }

    throw "invalid label";
}

void Generator::genNumByMode(int &a, int &b, uint8_t label) const
{
    a = getRandNum(min, max);
    b = getRandNum(min, max);

    if (label & SUB && !(mode & NEG) ) {
        while (a < b) {
            a = getRandNum(min, max);
            b = getRandNum(min, max);
        }
    }

    if (label & DIV && !(mode & FLT) ) {
        while (b == 0 || a % b) {
            a = getRandNum(min, max);
            b = getRandNum(min, max);
        }
    }
}

void Generator::gen_normal(std::string &exp) const
{
    int rand = getRandNum(0, 3);
    uint8_t optLabel = 0x01;
    while ( !((optLabel << rand) & set) ) {
        rand = getRandNum(0, 3);
    }
    optLabel <<= rand;
    char opt = getOperaByLabel(optLabel);
    std::stringstream ss;
    int a = 0, b = 0;
    genNumByMode(a, b, optLabel);
    ss << a << opt << b;
    exp = ss.str();
}

void Generator::gen_par(std::string &exp) const
{
    std::stringstream ss;
    int a = 0, b = 0, c = 0;
    // 避免分母为0
    int tmin = (min == 0) ? min + 1 : min;
    a = getRandNum(tmin, max);
    b = getRandNum(tmin, max);
    c = getRandNum(tmin, max);
    int par_pos = getRandNum(0, 1);
    if (par_pos == 0) {
        ss << a << getRandoper()
            << "("
            << b << getRandoper()
            << c
            << ")";
    } else {
        ss << "("
            << a << getRandoper()
            << b
            << ")" << getRandoper()
            << c;
    }

    exp = ss.str();
}

void Generator::gen_npa(std::string &exp) const
{
    std::stringstream ss;
    int a = 0, b = 0, c = 0;
    int tmin = (min == 0) ? min + 1 : min;
    a = getRandNum(tmin, max);
    b = getRandNum(tmin, max);
    c = getRandNum(tmin, max);
    ss << a << getRandoper()
        << b << getRandoper()
        << c;
    exp = ss.str();
}

// 按照设置生成一条表达式到exp中
// TODO: std::thread 创建一个线程并发生成表达式
void Generator::generate(std::string &exp) const
{
    if (set & NPA) {
        gen_npa(exp);
    } else if (set & PAR) {
        gen_par(exp);
    } else {
        gen_normal(exp);
    }
}

void Generator::setMin(int _min)
{
    if (_min >= max) {
        throw "min should less than max.";
    }

    if (_min < 0) {
        throw "min should larger tham zero.";
    }
    this->min = _min;
}

void Generator::setMax(int _max)
{
    if (_max >= min) {
        throw "max should larger than min";
    }

    if (_max <= 0) {
        throw "max should larger than zero.";
    }
    this->max = _max;
}

void Generator::setSet(uint8_t _set)
{
    if (_set == 0x00) {
        this->set = 0x01;
    }
    this->set = _set;
}

void Generator::setMode(uint8_t _mode)
{
    this->mode = _mode;
}

/* static */
char Generator::getRandoper()
{
    int num = getRandNum(0, 3);
    switch (num) {
        case 0: return '+';
        case 1: return '-';
        case 2: return '*';
        case 3: return '/';
    }
    return '+';
}

// TODO: Use std random generator.
int Generator::getRandNum()
{
        return QRandomGenerator::global()->generate();
}

int Generator::getRandNum(unsigned int a, unsigned int b)
{
        return QRandomGenerator::global()->generate() % (b-a+1) + a;
}
