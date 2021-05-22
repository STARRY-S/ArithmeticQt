#include "arithmetic.hpp"
#include <fstream>
#include <QStringList>

Arithmetic::Arithmetic()
{
    questionNum = 0;
}

Arithmetic::~Arithmetic()
{
    std::cout << "bye!" << std::endl;
}

QString Arithmetic::getQuestion(int i)
{
    if (i >= (int) questionList.size()) {
        std::cerr << "Error: out of range." << std::endl;
        return nullptr;
    }

    QString a = this->questionList[i];
    a.replace("*", " × ");
    a.replace("/", " ÷ ");
    a.replace("+", " + ");
    a.replace("-", " − ");
    // a.append(" =");
    return a;
}

QString Arithmetic::getAnswer(int i)
{
    return answerList[i];
}

int Arithmetic::getQuestionNum()
{
    return questionNum;
}

// 题目数量
void Arithmetic::setQuestionNum(int a)
{
    questionNum = a;
}

// // 难度设定
// void Arithmetic::setDifficulty(int max, int min, bool n, bool p)
// {
//         this->maxNum = max;
//         this->minNum = min;
//         this->hasNegative = n;
//         this->hasPoint = p;
// }

// 通过比较字符串中是否有运算符来判断打开的文件是否合法
bool Arithmetic::checkLineValid(std::string str)
{
    QString tmp = QString::fromUtf8(str.c_str());
    if (!tmp.contains(" = ")) {
        return false;
    }

    if (tmp.contains("×") || tmp.contains("÷")
        || tmp.contains("+") || tmp.contains("−"))
    {
        return true;
    } else {
        return false;
    }
    return true;
}

// 导入文件中的题目和答案
int Arithmetic::openFile(std::string name)
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
        }
    }
    file.close();

    if (!valid) {
        std::cerr << "Error: read file error." << std::endl;
        return -1;
    }

    int size = templist.size();
    questionNum = size;
    questionList.resize(size);
    QStringList listTmp;
    for (int i = 0; i < size; i++) {
        listTmp = QString::fromUtf8(templist[i].c_str()).split(" = ");
        questionList[i] =  listTmp[0];
        answerList[i] = listTmp[1];
    }

    return 0;
}
