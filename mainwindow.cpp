#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
	this->setWindowTitle(tr("四则运算计算器"));
	this->resize(1000, 500);
	setMinimumSize(700, 400);
	createDefaultPage();
	setCentralWidget(startupPage);
}

void MainWindow::createDefaultPage()
{
	createActions();
	createMenus();
	createRightPage();
	createLeftPage();

	startupPage = new QWidget;
	mainLayout = new QGridLayout;
	mainLayout->addWidget(leftGroupBox, 0, 0);
	mainLayout->addWidget(rightGroupBox, 0, 1);
	startupPage->setLayout(mainLayout);
}

void MainWindow::createMenus()
{
	startMenu = menuBar()->addMenu(tr("开始"));
	startMenu->addAction(initAct);
	startMenu->addAction(openAct);
	startMenu->addAction(saveAct);
	startMenu->addSeparator();
	startMenu->addAction(exitAct);

	editMenu = menuBar()->addMenu(tr("编辑"));
	editMenu->addAction(clearAnsAct);
	editMenu->addAction(clearLogAct);
	editMenu->addSeparator();
	editMenu->addAction(clearAllAct);

	// helpMenu = menuBar()->addMenu(tr("帮助"));
	aboutMenu = menuBar()->addMenu(tr("关于"));
	aboutMenu->addAction(aboutAct);
	aboutMenu->addAction(aboutQtAct);
}

void MainWindow::createActions()
{
	// 开始
	initAct = new QAction(tr("生成新的题目"));
	openAct = new QAction(tr("打开文件"));
	saveAct = new QAction(tr("导出题目至文件"));
	exitAct = new QAction(tr("退出"));
	connect(initAct, &QAction::triggered, this, &MainWindow::initNew);
	connect(openAct, &QAction::triggered, this, &MainWindow::openFile);
	connect(saveAct, &QAction::triggered, this, &MainWindow::saveFile);
	connect(exitAct, &QAction::triggered, this, &MainWindow::close);


	// 编辑
	clearAnsAct = new QAction(tr("清空作答区域"));
	clearLogAct = new QAction(tr("清空历史记录"));
	clearAllAct = new QAction(tr("清空全部"));
	connect(clearAnsAct, &QAction::triggered, this, &MainWindow::clearAns);
	connect(clearLogAct, &QAction::triggered, this, &MainWindow::clearLog);
	connect(clearAllAct, &QAction::triggered, this, &MainWindow::clearAll);

	aboutAct = new QAction(tr("四则运算"));
	aboutQtAct = new QAction(tr("About Qt"));
	connect(aboutAct, &QAction::triggered, this, &MainWindow::about);
	connect(aboutQtAct, &QAction::triggered, this, &MainWindow::aboutQt);

}

void MainWindow::createLeftPage()
{
	// calculation
	leftGroupBox = new QGroupBox;
	QGridLayout *calculateLayout = new QGridLayout;
	// TODO: remove char
	char question[50];
	for (int i = 0; i < 10; i++) {
		calculateLineEdit[i] = new QLineEdit;
		questionLabel[i] = new QLabel;
		// TODO: 在此处将出的题转换格式显示在屏幕上
		sprintf(question, "（%d） 100 + 334 / 11 * 33 =", i+1);
		questionLabel[i]->setText(question);
		calculateLineEdit[i]->setMaxLength(3);
		calculateLayout->addWidget(
			questionLabel[i],
			i % 5,
			(i / 5 == 0) ? 0 : 2
		);
		calculateLayout->addWidget(
			calculateLineEdit[i],
			i % 5,
			(i / 5) ? 1 : 3
		);

	}

	leftGroupBox->setLayout(calculateLayout);
}

void MainWindow::createRightPage()
{
	rightGroupBox = new QGroupBox;
	QGridLayout *rightLayout = new QGridLayout;

	// operations
	QGroupBox *operationsGroupBox = new QGroupBox(tr("手动设置"));
	checkBoxs[0] = new QCheckBox("加法");
	checkBoxs[1] = new QCheckBox("乘法");
	checkBoxs[2] = new QCheckBox("混合运算（带括号）");
	checkBoxs[3] = new QCheckBox("减法");
	checkBoxs[4] = new QCheckBox("除法");
	checkBoxs[5] = new QCheckBox("混合运算（无括号）");

	// QCheckBox *selectAll = new QCheckBox("全选");

	QGridLayout *operationsLayout = new QGridLayout;
	for (int i = 0; i < 6; i++) {
		// checkBoxs[i]->setStyleSheet("color: rgb(169,157,157)");
		// checkBoxs[i]->setFont(QFont("楷体", 18));
		operationsLayout->addWidget(checkBoxs[i], i / 3, i % 3);
	}
	// operationsLayout->addWidget(selectAll, 2, 2);
	// operationsLayout->addWidget(selectOff, 2, 1);
	operationsGroupBox->setLayout(operationsLayout);

	QGroupBox *selectGradeBox = new QGroupBox("难度");
	QGridLayout *selectGradeLayout = new QGridLayout;
	gradeRbutton[0] = new QRadioButton("一年级");
	gradeRbutton[1] = new QRadioButton("二年级");
	gradeRbutton[2] = new QRadioButton("三年级");
	gradeRbutton[3] = new QRadioButton("四年级");
	gradeRbutton[4] = new QRadioButton("五年级");
	gradeRbutton[5] = new QRadioButton("六年级");
	for (int i = 0; i < 6; i++)
	{
		selectGradeLayout->addWidget(gradeRbutton[i], i / 3, i % 3);
	}
	selectGradeBox->setLayout(selectGradeLayout);
	rightLayout->addWidget(selectGradeBox, 1, 0, 1, 4);

	rightLayout->addWidget(operationsGroupBox, 0, 0, 1, 4);
	rightLayout->addWidget(answerTextEdit, 2, 0, 1, 4);

	// button
	calcButton = new QPushButton("对答案");
	answerButton = new QPushButton("结果显示");
	recalcButton = new QPushButton("重新出题");
	exitButton = new QPushButton("退出");
	// QPushButton *exitButton = new QPushButton("退出");

	rightLayout->addWidget(calcButton, 3, 0, 1, 1);
	rightLayout->addWidget(answerButton, 3, 1, 1, 1);
	rightLayout->addWidget(recalcButton, 3, 2, 1, 1);
	rightLayout->addWidget(exitButton, 3, 3, 1, 1);

	connect(calcButton, &QPushButton::clicked, this,
		&MainWindow::checkAnswer);
	connect(answerButton, &QPushButton::clicked, this,
		&MainWindow::showAnswer);
	connect(recalcButton, &QPushButton::clicked, this,
		&MainWindow::initNew);
	connect(exitButton, &QPushButton::clicked, this,
		&MainWindow::close);
	rightGroupBox->setLayout(rightLayout);
}


MainWindow::~MainWindow()
{
	;
}

void MainWindow::initNew()
{
	std::cout << "生成新的题目" << std::endl;
}

void MainWindow::openFile()
{
	std::cout << "打开文件" << std::endl;
}

void MainWindow::saveFile()
{
	std::cout << "保存题目至文件" << std::endl;
}

void MainWindow::clearAns()
{
	std::cout << "清空答案" << std::endl;
}

void MainWindow::clearLog()
{
	std::cout << "清空做题记录" << std::endl;
}

void MainWindow::clearAll()
{
	std::cout << "清除全部" << std::endl;
}

void MainWindow::about()
{
	std::cout << "关于此软件" << std::endl;
}

void MainWindow::aboutQt()
{
	std::cout << "关于Qt" << std::endl;
}

void MainWindow::settingChanged()
{
	std::cout << "设置被修改" << std::endl;
}

void MainWindow::gradeChanged()
{
	std::cout << "年级被修改" << std::endl;
}

void MainWindow::checkAnswer()
{
	std::cout << "对答案" << std::endl;
}

void MainWindow::showAnswer()
{
	std::cout << "显示答案" << std::endl;
}
