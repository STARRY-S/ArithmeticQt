#include "arithmetic.hpp"
#include <fstream>
#include <iostream>
#include <QStringList>

// 通过比较字符串中是否有运算符来判断打开的文件是否合法
bool Arithmetic::checkLineValid(std::string &str)
{
    QString tmp = QString::fromStdString(str);
    if (!tmp.contains("=")) {
        return false;
    }

    if (tmp.contains("+") || tmp.contains("-")
        || tmp.contains("*") || tmp.contains("/"))
    {
        return true;
    }
    return false;
}

Arithmetic::Arithmetic()
{
    questionNum = 0;
    setMin(10);
    setMax(100);
    setSet(ADD);
    setMode(0x00);
}

Arithmetic::~Arithmetic()
{
    std::cout << "bye!" << std::endl;
}

QString Arithmetic::getQuestion(int i) const
{
    QString a = QString::fromStdString(questionList[i]);
    a.replace("*", " × ");
    a.replace("/", " ÷ ");
    a.replace("+", " + ");
    a.replace("-", " − ");
    return a;
}

float Arithmetic::getAnswer(int i) const
{
    return this->answerList[i];
}

int Arithmetic::getQuestionNum() const
{
    return questionNum;
}

void Arithmetic::generate()
{
    questionList.resize(questionNum);
    answerList.resize(questionNum);

    // much simpler than before.
    for (int i = 0; i < questionNum; i++) {
        genExp(questionList[i]);
        answerList[i] = calculate(questionList[i]);
    }
}

void Arithmetic::setQuestionNum(int n)
{
    this->questionNum = n;
}

// 难度设定
void Arithmetic::setDifficulty(int max, int min, bool neg, bool flt)
{
    setMax(max);
    setMin(min);
    uint8_t mode = 0x00;
    if (neg) {
        mode |= NEG;
    }

    if (flt) {
        mode |= FLT;
    }
    setMode(mode);
}

// 导入文件中的题目和答案
int Arithmetic::openFile(std::string &name)
{
    std::ifstream file;
    std::vector<std::string> templist;
    std::string tmp;
    file.open(name, std::ios::in);
    bool valid = true;
    while (valid && std::getline(file, tmp)) {
        std::cout << "Read Line: " << tmp << std::endl;
        templist.push_back(tmp);
        if (!checkLineValid(tmp)) {
            valid = false;
            break;
        }
    }
    file.close();

    if (!valid) {
        throw "Invalid file.";
        return -1;
    }

    int size = templist.size();
    setQuestionNum(size);
    questionList.resize(size);
    for (int i = 0; i < size; i++) {
        // s.substr(0, s.find("xx"));
        int pos = templist[i].find("=");
        int slen = templist[i].length();
        questionList[i] = templist[i].substr(0, pos);
        answerList[i] = std::stof(templist[i].substr(pos+1, slen));
    }

    return 0;
}
