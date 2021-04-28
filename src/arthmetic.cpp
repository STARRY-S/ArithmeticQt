#include "arthmetic.h"
#include <fstream>
#include <stack>
#include <QStringList>
#include <QDebug>

Arthmetic::Arthmetic()
{
	questionNum = 0;
	maxNum = minNum = 0;
	hasNegative = hasPoint = false;
	set = 0x00;
}

Arthmetic::~Arthmetic()
{
	std::cout << "Arthmetic Finished, bye!" << std::endl;
}

QString Arthmetic::getQuestion(int i)
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

QString Arthmetic::getAnswer(int i)
{
	return answerList[i];
}

// 指定加减乘除生成运算题
QString Arthmetic::generateBySet(int answer_pos)
{
	// 这个函数没想到更好的实现算法
	// 只能一个一个按位与
	// 代码量+++++艹艹艹
	char temp[128] = { 0 };
	int a = getRandNum(minNum, maxNum);
	int b = getRandNum(minNum, maxNum);
	float answer = 0;
	if (!set) {
		// 默认只生成加法
		set = 0x01;
	}

	if (set & 0x30) {
		return generateMulti(answer_pos);
	}

	switch (set) {
	case 0x01:	// 只生成加法
	{
		sprintf(temp, "%d+%d", a, b);
		answer = a + b;
		break;
	}
	case 0x02:	// 只生成减法
	{
		while (!hasNegative && a < b) {	// 负数
			a = getRandNum(minNum, maxNum);
			b = getRandNum(minNum, maxNum);
		}
		sprintf(temp, "%d-%d", a, b);
		answer = a - b;
		break;
	}
	case 0x04:	// 只生成乘法
	{
		sprintf(temp, "%d*%d", a, b);
		answer = a * b;
		break;
	}
	case 0x08:	// 只生成除法
	{
		while ((!hasPoint && a % b != 0) || a == b) {	// 只要求整除
			a = getRandNum(minNum, maxNum);
			b = getRandNum(minNum, maxNum);
		}
		sprintf(temp, "%d/%d", a, b);
		answer = (float) a / b;
		break;
	}
	case 0x03:	// 加减
	{
		int o = getRandNum(1);
		while (!hasNegative && o && a < b) {	// 负数
			a = getRandNum(minNum, maxNum);
			b = getRandNum(minNum, maxNum);
		}
		sprintf(temp, "%d%c%d", a,
			(o) ? '-' : '+', b);
		answer = (o) ? a-b : a+b;
		break;
	}
	case 0b1100:	// 乘除
	{
		int o = getRandNum(1);
		while ((!hasPoint && o == 0 && a % b != 0) || a == b) {
			a = getRandNum(minNum, maxNum);
			b = getRandNum(minNum, maxNum);
		}
		sprintf(temp, "%d%c%d", a,
			(o) ? '/' : '*', b);
		answer = (o) ? (float) a/b : (float) a*b;
		break;
	}
	case 0b0101:	// 加乘
	{
		int o = getRandNum(1);
		sprintf(temp, "%d%c%d", a,
			(o) ? '+' : '*', b);
		answer = (o) ? a+b : (float) a*b;
		break;
	}
	case 0b0110:	// 减乘
	{
		int o = getRandNum(1);
		while (!hasNegative && o && a < b) {	// 负数
			a = getRandNum(minNum, maxNum);
			b = getRandNum(minNum, maxNum);
		}
		sprintf(temp, "%d%c%d", a,
			(o) ? '-' : '*', b);
		answer = (o) ? a-b : (float) a*b;
		break;
	}
	case 0b0111:	// 加减乘
	{
		int o = getRandNum(2);
		char c;
		if (o == 0) {
			c = '+';
		} else if (o == 1) {
			c = '-';
		} else if (o == 2) {
			c = '*';
		}
		while (!hasNegative && o == 1 && a < b) {	// 负数
			a = getRandNum(minNum, maxNum);
			b = getRandNum(minNum, maxNum);
		}
		sprintf(temp, "%d%c%d", a, c, b);
		if (o == 0) {
			answer = a + b;
		} else if (o == 1) {
			answer = a - b;
		} else if (o == 2) {
			answer = (float) a * b;
		}
		break;
	}
	case 0b1001:	// 加除
	{
		int o = getRandNum(1);
		while ((!hasPoint && a % b != 0) || a == b) {	// 只要求整除
			a = getRandNum(minNum, maxNum);
			b = getRandNum(minNum, maxNum);
		}
		sprintf(temp, "%d%c%d", a,
			(o) ? '+' : '/', b);
		answer = (o) ? a+b : (float) a / b;
		break;
	}
	case 0b1010:	// 减除
	{
		int o = getRandNum(1);
		while (!hasNegative && o == 0 && a < b) {	// 负数
			a = getRandNum(minNum, maxNum);
			b = getRandNum(minNum, maxNum);
		}
		while ((!hasPoint && o == 1 && a % b != 0) || a == b) {
			a = getRandNum(minNum, maxNum);
			b = getRandNum(minNum, maxNum);
		}
		sprintf(temp, "%d%c%d", a,
			(o) ? '-' : '/', b);
		answer = (o) ? a-b : (float) a / b;
		break;
	}
	case 0b1011:	// 以此类推
	{
		int o = getRandNum(2);
		char c;
		if (o == 0) {
			c = '+';
		} else if (o == 1) {
			c = '-';
		} else if (o == 2) {
			c = '/';
		}

		while (!hasNegative && o == 1 && a < b) {	// 负数
			a = getRandNum(minNum, maxNum);
			b = getRandNum(minNum, maxNum);
		}
		while ((!hasPoint && o == 2 && a % b != 0) || a == b) {
			a = getRandNum(minNum, maxNum);
			b = getRandNum(minNum, maxNum);
		}
		sprintf(temp, "%d%c%d", a, c, b);
		if (o == 0) {
			answer = a+b;
		} else if (o == 1) {
			answer = a-b;
		} else if (o == 2) {
			answer = (float) a/b;
		}
		break;
	}
	case 0b1101:
	{
		int o = getRandNum(2);
		char c;
		if (o == 0) {
			c = '+';
		} else if (o == 1) {
			c = '*';
		} else if (o == 2) {
			c = '/';
		}

		while ((!hasPoint && o == 2 && a % b != 0) || a == b) {
			a = getRandNum(minNum, maxNum);
			b = getRandNum(minNum, maxNum);
		}
		sprintf(temp, "%d%c%d", a, c, b);
		if (o == 0) {
			answer = a+b;
		} else if (o == 1) {
			answer = (float) a * b;
		} else if (o == 2) {
			answer = (float) a / b;
		}
		break;
	}
	case 0b1110:
	{
		int o = getRandNum(2);
		char c;
		if (o == 0) {
			c = '-';
		} else if (o == 1) {
			c = '*';
		} else if (o == 2) {
			c = '/';
		}
		while (!hasNegative && o == 0 && a < b) {	// 负数
			a = getRandNum(minNum, maxNum);
			b = getRandNum(minNum, maxNum);
		}
		while ((!hasPoint && o == 2 && a % b != 0) || a == b) {
			a = getRandNum(minNum, maxNum);
			b = getRandNum(minNum, maxNum);
		}
		sprintf(temp, "%d%c%d", a, c, b);
		if (o == 0) {
			answer = a-b;
		} else if (o == 1) {
			answer = (float) a * b;
		} else if (o == 2) {
			answer = (float) a / b;
		}
		break;
	}
	case 0b1111:	// 加减乘除,不混合
	{
		int o = getRandNum(3);
		char c;
		if (o == 0) {
			c = '+';
		} else if (o == 1) {
			c = '-';
		} else if (o == 2) {
			c = '*';
		} else if (o == 3) {
			c = '/';
		}

		while (!hasNegative && o == 1 && a < b) {	// 负数
			a = getRandNum(minNum, maxNum);
			b = getRandNum(minNum, maxNum);
		}
		while ((!hasPoint && o == 3 && a % b != 0) || a == b) {
			a = getRandNum(minNum, maxNum);
			b = getRandNum(minNum, maxNum);
		}
		sprintf(temp, "%d%c%d", a, c, b);
		if (o == 0) {
			answer = a+b;
		} else if (o == 1) {
			answer = a-b;
		} else if (o == 2) {
			answer = (float) a * b;
		} else if (o == 3) {
			answer = (float) a / b;
		}
		break;
	}
	default:	// 默认生成加法
		sprintf(temp, "%d+%d", a, b);
		answer = a+b;
		break;
	}

	QString qs(temp);
	QString aw(QString::number(answer));
	qDebug() << "Generated: " << qs << " = " << aw;

	answerList[answer_pos] = aw;
	return qs;
}

char getOperatorInMulti(int i)
{
	switch (i) {
	case 0:
		return '+';
	case 1:
		return '-';
	case 2:
		return '*';
	case 3:
		return '/';
	default:
		return '+';
	}
}

QString Arthmetic::generateMulti(int answer_pos)
{
	int operaNum = getRandNum(0, 1);
	QString tmp;
	int a, b, c;
	float answer = 0.0;

	a = getRandNum(minNum, maxNum);
	b = getRandNum(minNum, maxNum);
	c = getRandNum(minNum, maxNum);

	int op1 = getRandNum(0, 3);
	int op2 = getRandNum(0, 3);

	if ((set & 0x10) && operaNum == 0) {
		tmp = '(' + QString::number(a)
			+ getOperatorInMulti(op1)
			+ QString::number(b) + ')'
			+ getOperatorInMulti(op2)
			+ QString::number(c);
		if (op1 == 0) {
			answer = a + b;
		} else if (op1 == 1) {
			answer = a - b;
 		} else if (op1 == 2) {
			answer = a * b;
		} else if (op1 == 3) {
			answer = (float) a / b;
		}

		if (op2 == 0) {
			answer += c;
		} else if (op2 == 1) {
			answer -= c;
 		} else if (op2 == 2) {
			answer *= c;
		} else if (op2 == 3) {
			answer /= c;
		}
	}else if ((set & 0x10) && operaNum == 1) {
		tmp = QString::number(a)
			+ getOperatorInMulti(op1) + '('
			+ QString::number(b)
			+ getOperatorInMulti(op2)
			+ QString::number(c) + ')';
		;
		if (op2 == 0) {
			answer = b + c;
		} else if (op2 == 1) {
			answer = b - c;
 		} else if (op2 == 2) {
			answer = b * c;
		} else if (op2 == 3) {
			answer = (float) b / c;
		}

		if (op1 == 0) {
			answer = a + answer;
		} else if (op1 == 1) {
			answer = a - answer;
 		} else if (op1 == 2) {
			answer = a * answer;
		} else if (op1 == 3) {
			answer = a / answer;
		}
	} else {
		tmp = QString::number(a)
			+ getOperatorInMulti(op1)
			+ QString::number(b)
			+ getOperatorInMulti(op2)
			+ QString::number(c);
		;
		// 优先级相同
		if (op1 > 1 && op2 > 1) {
			if (op1 == 0) {
				answer = a + b;
			} else if (op1 == 1) {
				answer = a - b;
	 		} else if (op1 == 2) {
				answer = a * b;
			} else if (op1 == 3) {
				answer = (float) a / b;
			}

			if (op2 == 0) {
				answer += c;
			} else if (op2 == 1) {
				answer -= c;
	 		} else if (op2 == 2) {
				answer *= c;
			} else if (op2 == 3) {
				answer /= c;
			}
		// 优先级不同
		} else if (op2 > 1) {
			if (op2 == 0) {
				answer = b + c;
			} else if (op2 == 1) {
				answer = b - c;
	 		} else if (op2 == 2) {
				answer = b * c;
			} else if (op2 == 3) {
				answer = (float) b / c;
			}

			if (op1 == 0) {
				answer = a + answer;
			} else if (op1 == 1) {
				answer = a - answer;
	 		} else if (op1 == 2) {
				answer = c * answer;
			} else if (op1 == 3) {
				answer = c / answer;
			}
		} else {
			if (op1 == 0) {
				answer = a + b;
			} else if (op1 == 1) {
				answer = a - b;
	 		} else if (op1 == 2) {
				answer = a * b;
			} else if (op1 == 3) {
				answer = (float) a / b;
			}

			if (op2 == 0) {
				answer += c;
			} else if (op2 == 1) {
				answer -= c;
	 		} else if (op2 == 2) {
				answer *= c;
			} else if (op2 == 3) {
				answer /= c;
			}
		}
	}

	qDebug() << "Generated: " << tmp << " = " << answer;
	answerList[answer_pos] = QString::number(answer);
	return tmp;
}

void Arthmetic::setSet(unsigned char a)
{
	set = a;
}

unsigned char Arthmetic::getSet()
{
	return set;
}

/*
 * generate -- 生成题目
 * 生成questionNum数量的题目
 * 将题目以QString格式保存在questionList中
 * 将答案以QString格式保存在answerList中
 */
void Arthmetic::generate()
{
	questionList.resize(questionNum);
	answerList.resize(questionNum);
	for (int i = 0; i < questionNum; i++) {
		questionList[i] = generateBySet(i);
		// answerList[i] = calculateAnswer(i);
	}
}

int Arthmetic::getRandNum(unsigned int a)
{
	return getRandNum(0, a);
}

int Arthmetic::getRandNum(unsigned int a, unsigned int b)
{
	return QRandomGenerator::global()->generate() % (b-a+1) + a;
}

int Arthmetic::getQuestionNum()
{
	return questionNum;
}

// 题目数量
void Arthmetic::setQuestionNum(int a)
{
	questionNum = a;
}

// 难度设定
void Arthmetic::setDifficulty(int max, int min, bool n, bool p)
{
	this->maxNum = max;
	this->minNum = min;
	this->hasNegative = n;
	this->hasPoint = p;
}

// 通过比较字符串中是否有运算符来判断打开的文件是否合法
bool Arthmetic::checkLineValid(std::string str)
{
	QString tmp = QString::fromUtf8(str.c_str());
	if (!tmp.contains(" = ")) {
		return false;
	}

	if (tmp.contains("×") || tmp.contains("÷") || tmp.contains("+")
		|| tmp.contains("−")) {
		return true;
	} else {
		return false;
	}
	return true;
}

// 导入文件中的题目和答案
int Arthmetic::openFile(std::string name)
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
