#include "arthmetic.h"

Arthmetic::Arthmetic()
{
	// Arthmetic(10, 1);
}

Arthmetic::~Arthmetic()
{
	std::cout << "Arthmetic Finished, bye!" << std::endl;
}

QString Arthmetic::getQuestion(int i)
{
	if (i >= questionList.size()) {
		std::cerr << "Error: out of range." << std::endl;
		return nullptr;
	}

	QString a = this->questionList[i];
	a.replace("*", " × ");
	a.replace("/", " ÷ ");
	a.replace("+", " + ");
	a.replace("-", " − ");
	a.append(" =");
	return a;
}

QString Arthmetic::generateByGrade(int grade)
{
	unsigned char label = 0x00;

	switch (grade) {
	case 1:
	{
		label = ARTHMETIC_PLUS | ARTHMETIC_MINUS;
		break;
	}
	case 2:
	{
		label = ARTHMETIC_TIMES | ARTHMETIC_DIVID;
		break;
	}
	case 3:
	case 4:
	{
		label = ARTHMETIC_NOPAR;
		break;
	}
	case 5:
	case 6:
	{
		label = ARTHMETIC_PAREN;
		break;
	}
	default:
		label = ARTHMETIC_PAREN;
	}

	return generateBySet(label);
}

QString Arthmetic::generateBySet(unsigned char set)
{
	// 这个函数没想到更好的实现算法
	// 只能一个一个按位与
	// 代码量+++++艹艹艹
	char temp[128];
	int a = getRandNum(10, 100);
	int b = getRandNum(10, 100);
	if (!set) {
		set = 0x01;
	}

	switch (set) {
	case 0x01:	// 只生成加法
	{
		sprintf(temp, "%d+%d", a, b);
		break;
	}
	case 0x02:	// 只生成减法
	{
		// while (a < b) {	// 负数
		// 	a = getRandNum(100);
		// 	b = getRandNum(100);
		// }
		sprintf(temp, "%d-%d", a, b);
		break;
	}
	case 0x04:	// 只生成乘法
	{
		sprintf(temp, "%d*%d", a, b);
		break;
	}
	case 0x08:	// 只生成除法
	{
		// while (a % b != 0) {	// 只要求整除
		// 	a = getRandNum(100);
		// 	b = getRandNum(100);
		// }
		sprintf(temp, "%d/%d", a, b);
		break;
	}

	case 0x03:	// 加减
	{
		int o = getRandNum(1);
		while (o && a < b) {	// 负数
			a = getRandNum(100);
			b = getRandNum(100);
		}
		sprintf(temp, "%d%c%d", a,
			(o) ? '-' : '+', b);
		break;
	}
	case 0b1100:	// 乘除
	{
		printf("乘除\n");
		int o = getRandNum(1);
		// while (o && a % b != 0) {	// 只要求整除
		// 	a = getRandNum(100);
		// 	b = getRandNum(100);
		// }
		sprintf(temp, "%d%c%d", a,
			(o) ? '/' : '*', b);
		break;
	}
	case 0b0101:	// 加乘
	{
		int o = getRandNum(1);
		sprintf(temp, "%d%c%d", a,
			(o) ? '+' : '*', b);
		break;
	}
	case 0b0110:	// 减乘
	{
		int o = getRandNum(1);
		sprintf(temp, "%d%c%d", a,
			(o) ? '-' : '*', b);
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
		sprintf(temp, "%d%c%d", a, c, b);
		break;
	}
	case 0b1001:	// 加除
	{
		int o = getRandNum(1);
		sprintf(temp, "%d%c%d", a,
			(o) ? '+' : '/', b);
		break;
	}
	case 0b1010:	// 减除
	{
		int o = getRandNum(1);
		sprintf(temp, "%d%c%d", a,
			(o) ? '-' : '/', b);
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
		sprintf(temp, "%d%c%d", a, c, b);
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
		sprintf(temp, "%d%c%d", a, c, b);
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
		sprintf(temp, "%d%c%d", a, c, b);
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
		sprintf(temp, "%d%c%d", a, c, b);
		break;
	}
	case 0x10:	// 混合带括号(包括加减乘除)
	{
		;
	}
	case 0x20:	// 混合不带括号(包括加减乘除)
	{
		;
	}
	default:
		sprintf(temp, "生成错误");
		break;
	}

	QString qs(temp);
	std::cout << "Generated: " << qs.toStdString() << std::endl;
	return qs;
}

void Arthmetic::setDifficulty(unsigned char a)
{
	difficulty = a;
}

unsigned char Arthmetic::getDifficulty()
{
	return difficulty;
}

void Arthmetic::firstGenerate(int length)
{
	if (questionList.size() != 0)
		return;

	for (int i = 0; i < length; i++) {
		questionList.push_back(generateBySet(difficulty));
	}
}

void Arthmetic::reGenerate()
{
	int length = questionList.size();
	for (int i = 0; i < length; i++) {
		questionList[i] = generateBySet(difficulty);
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
