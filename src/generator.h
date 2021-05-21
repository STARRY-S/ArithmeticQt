#ifndef GENERATOR_H
#define GENERATOR_H

#include <string>

class Generator {
private:
        uint8_t set = 0;
        uint8_t mode = 0;

        void gen_add();
        void gen_sub();
        void gen_mul();
        void gen_div();
        void gen_par();
        void gen_npa();
public:
        /* sets */
        static const uint8_t ADD = 0x01;
        static const uint8_t SUB = 0x02;
        static const uint8_t MUL = 0x04;
        static const uint8_t DIV = 0x08;
        static const uint8_t PAR = 0x10;        // 括号
        static const uint8_t NPA = 0x20;

        /* modes */
        static const uint8_t NEG = 0x01;
        static const uint8_t FLT = 0x02;

        Generator() = default;
        Generator(int _set) : set(_set) {}
        Generator(int _set, int _mode) : set(_set), mode(_mode) {}

        virtual void generate(std::string &exp);
};

#endif
