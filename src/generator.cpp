#include "generator.hpp"

void Generator::gen_add(std::string &exp)
{
    std::stringstream ss;
    int a = 0, b = 0;
    a = getRandNum(min, max);
    b = getRandNum(min, max);
    ss << a << "+" << b;
    exp = ss.str();
}

void Generator::gen_sub(std::string &exp)
{
    std::stringstream ss;
    int a = 0, b = 0;
    a = getRandNum(min, max);
    b = getRandNum(min, max);
    while (!(mode & 0x01) && a <= b) {
        a = getRandNum(min, max);
        b = getRandNum(min, max);
    }
    ss << a << "-" << b;
    exp = ss.str();
}

void Generator::gen_mul(std::string &exp)
{
    std::stringstream ss;
    int a = 0, b = 0;
    a = getRandNum(min, max);
    b = getRandNum(min, max);
    ss << a << "*" << b;
    exp = ss.str();
}

void Generator::gen_div(std::string &exp)
{
    std::stringstream ss;
    int a = 0, b = 0;
    a = getRandNum(min, max);
    b = getRandNum(min, max);
    while (!(mode & 0x02) && (a % b != 0) ) {
        a = getRandNum(min, max);
        b = getRandNum(min, max);
    }
    ss << a << "/" << b;
    exp = ss.str();
}

void Generator::gen_par(std::string &exp)
{
    std::stringstream ss;
    int a = 0, b = 0, c = 0;
    a = getRandNum(min, max);
    b = getRandNum(min, max);
    c = getRandNum(min, max);
    int par_pos = getRandNum(0, 1);
    if (par_pos == 0) {
        ss << a << getRandoper()
            << "(" << getRandoper()
            << b << getRandoper()
            << c << getRandoper()
            << ")";
    } else {
        ss << "(" << getRandoper()
            << a << getRandoper()
            << b << getRandoper()
            << ")" << getRandoper()
            << c;
    }

    exp = ss.str();
}

void Generator::gen_npa(std::string &exp)
{
    std::stringstream ss;
    int a = 0, b = 0, c = 0;
    a = getRandNum(min, max);
    b = getRandNum(min, max);
    c = getRandNum(min, max);
    ss << a << getRandoper()
        << b << getRandoper()
        << c << getRandoper();
    exp = ss.str();
}

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

int Generator::getRandNum(unsigned int a, unsigned int b)
{
        return QRandomGenerator::global()->generate() % (b-a+1) + a;
}

// 按照设置生成一条表达式到std::string exp中
// TODO: 创建一个线程并发生成表达式
void Generator::generate(std::string &exp)
{
    switch (set) {
        case ADD:
        {
            gen_add(exp);
            break;
        }
        case SUB:
        {
            gen_sub(exp);
            break;
        }
        case MUL:
        {
            gen_mul(exp);
            break;
        }
        case DIV:
        {
            gen_div(exp);
            break;
        }
        case PAR:
        {
            gen_par(exp);
            break;
        }
        case NPA:
        {
            gen_npa(exp);
            break;
        }
        default:
        {
            gen_add(exp);
            break;
        }
    }

}

void Generator::setMin(int _min)
{
    this->min = _min;
}

void Generator::setMax(int _max)
{
    this->max = _max;
}

void Generator::setSet(uint8_t _set)
{
    this->set = _set;
}

void Generator::setMode(uint8_t _mode)
{
    this->mode = _mode;
}
