#include "mainwindow.h"
#include <fstream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
	// 默认生成加减乘除
	arthmetic = new Arthmetic();
	// 初始化预设为加减乘除
	arthmetic->setSet( ARTHMETIC_PLUS
				| ARTHMETIC_MINUS
		      		| ARTHMETIC_TIMES
				| ARTHMETIC_DIVID);
	// 初始化题目数量为20
	arthmetic->setQuestionNum(DEFAULT_QUESTION_NUM);
	// 初始化难度
	arthmetic->setDifficulty(DEFAULT_MAX_NUM,
				DEFAULT_MIN_NUM,
				HAS_NEGATIVE,
				HAS_POINT);
	// 生成指定数量的题目
	arthmetic->generate();
	this->setWindowTitle(tr("四则运算计算器"));
	this->resize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
	setMinimumSize(MIN_WIDTH, MIN_HEIGHT);
	createActions();
	createMenus();
	createDefaultPage();
	setCentralWidget(startupPage);
	initSetting();
}

void MainWindow::initSetting()
{
	unsigned char level = arthmetic->getSet();
	if (level == 0) {
		checkBoxs[NOPAR]->setChecked(true);
	} else {
		checkBoxs[NOPAR]->setChecked(false);
	}

	if (level & 0x01) {
		checkBoxs[PLUS]->setChecked(true);
	} else {
		checkBoxs[PLUS]->setChecked(false);
	}

	if (level & 0x02) {
		checkBoxs[MINUS]->setChecked(true);
	} else {
		checkBoxs[MINUS]->setChecked(false);
	}

	if (level & 0x04) {
		checkBoxs[TIME]->setChecked(true);
	} else {
		checkBoxs[TIME]->setChecked(false);
	}

	if (level & 0x08) {
		checkBoxs[DIVID]->setChecked(true);
	} else {
		checkBoxs[DIVID]->setChecked(false);
	}

	if (level & 0x10) {
		checkBoxs[PARENT]->setChecked(true);
	} else {
		checkBoxs[PARENT]->setChecked(false);
	}

	if (level & 0x20) {
		checkBoxs[NOPAR]->setChecked(true);
	} else {
		checkBoxs[NOPAR]->setChecked(false);
	}

	// 暂不支持混合
	checkBoxs[PARENT]->setCheckable(false);
	checkBoxs[NOPAR]->setCheckable(false);
}

void MainWindow::createDefaultPage()
{
	createRightPage();
	createLeftPage();

	startupPage = new QWidget;
	mainLayout = new QGridLayout;
	mainLayout->addWidget(leftScrollArea, 0, 0, 1, 5);
	mainLayout->addWidget(rightGroupBox, 0, 5, 1, 1);
	startupPage->setLayout(mainLayout);
}

void MainWindow::createLeftPage()
{
	// calculation
	leftScrollArea = new QScrollArea;
	calculateLayout = new QGridLayout;
	QGroupBox *leftGroupBox = new QGroupBox;
	for (int i = 0; i < 20; i++) {
		calculateLineEdit.push_back(new QLineEdit);
		questionLabel.push_back(new QLabel);
		numberLabel.push_back(new QLabel(tr("（%1）").arg(i+1)));
		QString a = arthmetic->getQuestion(i);
		questionLabel[i]->setText(a);
		calculateLayout->addWidget(
			numberLabel[i],
			i % 10,
			(i / 10 == 0) ? 0 : 3
		);
		calculateLayout->addWidget(
			questionLabel[i],
			i % 10,
			(i / 10 == 0) ? 1 : 4
		);
		calculateLayout->addWidget(
			calculateLineEdit[i],
			i % 10,
			(i / 10) ? 2 : 5
		);

	}

	leftGroupBox->setLayout(calculateLayout);
	leftScrollArea->setWidgetResizable(true);
	leftScrollArea->setWidget(leftGroupBox);
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

	QGridLayout *operationsLayout = new QGridLayout;
	for (int i = 0; i < 6; i++) {
		operationsLayout->addWidget(checkBoxs[i], i / 3, i % 3);
		connect(checkBoxs[i], SIGNAL(clicked()), this,
			SLOT(settingChanged()));
	}
	operationsGroupBox->setLayout(operationsLayout);
	rightLayout->addWidget(operationsGroupBox, 0, 0, 1, 4);

	QGroupBox *selectDiffBox = new QGroupBox("难度设定");
	QGridLayout *selectDiffLayout = new QGridLayout;

	QLabel *numberHint = new QLabel("题目数量:");
	numSpinBox = new QSpinBox;
	numSpinBox->setRange(10, 100);
	numSpinBox->setSingleStep(1);
	numSpinBox->setValue(arthmetic->getQuestionNum());
	selectDiffLayout->addWidget(numberHint, 0, 0, 1, 1);
	selectDiffLayout->addWidget(numSpinBox, 0, 1, 1, 4);
	connect(numSpinBox, SIGNAL(valueChanged(int)), this, SLOT(diffChanged()));

	QLabel *maxHint = new QLabel("最大值：");
	maxNum = new QSpinBox;
	maxNum->setRange(1, 10000);
	maxNum->setValue(100);
	QLabel *minHint = new QLabel("最小值：");
	minNum = new QSpinBox;
	minNum->setRange(0, 9999);
	minNum->setValue(10);
	selectDiffLayout->addWidget(maxHint, 1, 0, 1, 1);
	selectDiffLayout->addWidget(maxNum, 1, 1, 1, 1);
	selectDiffLayout->addWidget(minHint, 1, 3, 1, 1);
	selectDiffLayout->addWidget(minNum, 1, 4, 1, 1);
	connect(maxNum, SIGNAL(valueChanged(int)), this, SLOT(diffChanged()));
	connect(minNum, SIGNAL(valueChanged(int)), this, SLOT(diffChanged()));

	hasNegative = new QCheckBox("结果是否存在负数");
	hasFloat = new QCheckBox("结果是否存在小数");
	selectDiffLayout->addWidget(hasNegative, 2, 0, 1, 2);
	selectDiffLayout->addWidget(hasFloat, 2, 3, 1, 2);
	connect(hasNegative, SIGNAL(clicked()), this, SLOT(diffChanged()));
	connect(hasFloat, SIGNAL(clicked()), this, SLOT(diffChanged()));

	selectDiffBox->setLayout(selectDiffLayout);
	rightLayout->addWidget(selectDiffBox, 1, 0, 1, 4);

	QLabel *answerLabel = new QLabel("作答记录");
	rightLayout->addWidget(answerLabel, 2, 0, 1, 1);

	answerTextEdit = new QTextEdit;
	answerTextEdit->setReadOnly(true);
	rightLayout->addWidget(answerTextEdit, 3, 0, 1, 4);

	// button
	calcButton = new QPushButton("对答案");
	answerButton = new QPushButton("结果显示");
	recalcButton = new QPushButton("重新出题");
	exitButton = new QPushButton("退出");

	rightLayout->addWidget(calcButton, 4, 0, 1, 1);
	rightLayout->addWidget(answerButton, 4, 1, 1, 1);
	rightLayout->addWidget(recalcButton, 4, 2, 1, 1);
	rightLayout->addWidget(exitButton, 4, 3, 1, 1);

	connect(calcButton, SIGNAL(clicked()), this, SLOT(checkAnswer()));
	connect(answerButton, SIGNAL(clicked()), this, SLOT(showAnswer()));
	connect(recalcButton, SIGNAL(clicked()), this, SLOT(initNew()));
	connect(exitButton, SIGNAL(clicked()), this, SLOT(close()));
	rightGroupBox->setLayout(rightLayout);
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
	aboutMenu->addAction(helpAct);
}

void MainWindow::createActions()
{
	// 开始
	initAct = new QAction(tr("生成新的题目"));
	openAct = new QAction(tr("打开文件"));
	saveAct = new QAction(tr("导出题目至文件"));
	exitAct = new QAction(tr("退出"));
	connect(initAct, SIGNAL(triggered()), this, SLOT(initNew()));
	connect(openAct, SIGNAL(triggered()), this, SLOT(openFile()));
	connect(saveAct, SIGNAL(triggered()), this, SLOT(saveFile()));
	connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

	// 编辑
	clearAnsAct = new QAction(tr("清空作答区域"));
	clearLogAct = new QAction(tr("清空历史记录"));
	clearAllAct = new QAction(tr("清空全部"));
	connect(clearAnsAct, SIGNAL(triggered()), this, SLOT(clearAns()));
	connect(clearLogAct, SIGNAL(triggered()), this, SLOT(clearLog()));
	connect(clearAllAct, SIGNAL(triggered()), this, SLOT(clearAll()));

	// About
	aboutAct = new QAction(tr("关于本软件"));
	helpAct = new QAction(tr("使用说明"));
	connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));
	connect(helpAct, SIGNAL(triggered()), this, SLOT(help()));

}

MainWindow::~MainWindow()
{
	delete arthmetic;
}

void MainWindow::reGenerate(int oldsize, int size) {
	// 如果用户修改了题目数量
	// 需要重新生成作答区域
	for (int i = 0; i < oldsize; i++) {
		calculateLayout->removeWidget(calculateLineEdit[i]);
		calculateLayout->removeWidget(numberLabel[i]);
		calculateLayout->removeWidget(questionLabel[i]);
		calculateLineEdit[i]->deleteLater();
		numberLabel[i]->deleteLater();
		questionLabel[i]->deleteLater();
	}

	questionLabel.resize(size);
	calculateLineEdit.resize(size);
	numberLabel.resize(size);
	// char number[10];
	int l = (size % 2) ? size / 2 + 1 : size / 2;
	for (int i = 0; i < size; i++) {
		calculateLineEdit[i] = (new QLineEdit);
		questionLabel[i] = (new QLabel);
		numberLabel[i] = new QLabel(tr("（%1）").arg(i+1));
		questionLabel[i]->setText(arthmetic->getQuestion(i));
		calculateLayout->addWidget(
			numberLabel[i],
			i % l,
			(i / l == 0) ? 0 : 3
		);
		calculateLayout->addWidget(
			questionLabel[i],
			i % l,
			(i / l == 0) ? 1 : 4
		);
		calculateLayout->addWidget(
			calculateLineEdit[i],
			i % l,
			(i / l == 0) ? 2 : 5
		);
	}
}

void MainWindow::initNew()
{
	std::cout<< "SLOT_LOG: 生成新的题目" << std::endl;
	int oldsize = calculateLineEdit.size();
	int size = arthmetic->getQuestionNum();
	arthmetic->generate();
	// 如果题目数量没有改变，仅修改Label即可
	if (oldsize == size) {
		for (int i = 0; i < size; i++) {
			questionLabel[i]->setText(
				arthmetic->getQuestion(i));
		}
	} else {
		reGenerate(oldsize, size);
	}
}

void MainWindow::openFile()
{
	std::cout<< "SLOT_LOG: 打开文件" << std::endl;
	QString fileName = QFileDialog::getOpenFileName(this, tr("打开文件"),
		tr(".txt"));
	std::cout << "Open file: " << fileName.toStdString() << std::endl;

	arthmetic->openFile(fileName.toStdString());
	reGenerate(questionLabel.size(), arthmetic->getQuestionNum());
}

void MainWindow::saveFile()
{
	std::cout<< "SLOT_LOG: 保存题目至文件" << std::endl;
	QString fileName = QFileDialog::getSaveFileName(this, tr("导出至文件"),
		"四则运算.txt", tr("*.txt"));

	std::ofstream outstream;
	outstream.open(fileName.toStdString(), std::ios::out | std::ios::trunc);
	int size = questionLabel.size();
	for (int i = 0; i < size; i++) {
		outstream << arthmetic->getQuestion(i).toStdString()
				<< std::endl;
	}
	outstream.close();

	std::cout << "Exported to file:" << fileName.toStdString() << std::endl;
}

void MainWindow::clearAns()
{
	std::cout<< "SLOT_LOG: 清空答案" << std::endl;
	QMessageBox msgBox;
	msgBox.setText("清空答题区域:");
	msgBox.setInformativeText("确定要清空答题区域么?\n此操作不可逆!");
	msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
	msgBox.setDefaultButton(QMessageBox::Cancel);
	int ret = msgBox.exec();
	if (ret == QMessageBox::Ok) {
		int size = calculateLineEdit.size();
		for (int i = 0; i < size; i++) {
			calculateLineEdit[i]->setText("");
		}
	}

}

void MainWindow::clearLog()
{
	std::cout<< "SLOT_LOG: 清空答题记录" << std::endl;
	QMessageBox msgBox;
	msgBox.setText("清空作答记录:");
	msgBox.setInformativeText("确定要清空答题记录么?\n此操作不可逆!");
	msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
	msgBox.setDefaultButton(QMessageBox::Cancel);
	int ret = msgBox.exec();
	if (ret == QMessageBox::Ok) {
		answerTextEdit->setText("");
	}
}

void MainWindow::clearAll()
{
	std::cout<< "SLOT_LOG: 清除全部" << std::endl;
	clearAns();
	clearLog();
}

void MainWindow::about()
{
	std::cout<< "SLOT_LOG: 关于此软件" << std::endl;
	QMessageBox msgBox;
	msgBox.setText("四则运算生成器\n版本号: v1.0.0.");
	msgBox.exec();
}

void MainWindow::help()
{
	std::cout<< "SLOT_LOG: 帮助" << std::endl;
	QMessageBox msg;
	msg.setText("使用说明：\n"
		    "左侧为答题区域，将运算结果填写在题目后方文本框中\n"
	    	    "右侧为设置区域，可以设置难度，运算模式等\n"
	            "作答记录中保留了学生每次答题的记录和得分情况\n"
	    	    "默认答对为1分，答错不得分\n"
	    	    "小数运算时保留小数点后2位");
        msg.exec();
}

void MainWindow::settingChanged()
{
	std::cout<< "SLOT_LOG: 设置被修改" << std::endl;
	unsigned char oldLevel = arthmetic->getSet();
	unsigned char newLevel = 0x00;

	if (checkBoxs[PLUS]->isChecked()) {
		newLevel |= ARTHMETIC_PLUS;
	}
	if (checkBoxs[MINUS]->isChecked()) {
		newLevel |= ARTHMETIC_MINUS;
	}
	if (checkBoxs[TIME]->isChecked()) {
		newLevel |= ARTHMETIC_TIMES;
	}
	if (checkBoxs[DIVID]->isChecked()) {
		newLevel |= ARTHMETIC_DIVID;
	}
	if (checkBoxs[PARENT]->isChecked()) {
		newLevel |= ARTHMETIC_PAREN;
	}
	if (checkBoxs[NOPAR]->isChecked()) {
		newLevel |= ARTHMETIC_NOPAR;
	}
	printf("Change state from 0X%2X to 0X%2X\n", oldLevel, newLevel);
	arthmetic->setSet(newLevel);
}

void MainWindow::diffChanged()
{
	std::cout<< "SLOT_LOG: 难度被修改" << std::endl;
	int max, min;
	bool hp, hn;
	int qnum;
	qnum = numSpinBox->value();
	max = maxNum->value();
	min = minNum->value();
	hp = hasFloat->isChecked();
	hn = hasNegative->isChecked();
	arthmetic->setQuestionNum(qnum);
	arthmetic->setDifficulty(max, min, hn, hp);
}

void MainWindow::checkAnswer()
{
	std::cout<< "SLOT_LOG: 对答案" << std::endl;
}

void MainWindow::showAnswer()
{
	std::cout<< "SLOT_LOG: 显示答案" << std::endl;
}
