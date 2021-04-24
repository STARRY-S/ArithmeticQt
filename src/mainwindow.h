#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>

#include <QLayout>
#include <QMainWindow>
#include <QPushButton>
#include <QGroupBox>
#include <QCheckBox>
#include <QRadioButton>
#include <QLineEdit>
#include <QLabel>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QToolBar>
#include <QtWidgets>
#include "arthmetic.h"

/*
 * TODO:
 * MainWindow -- 主窗口类
 * [x] 主窗体左边为答题区域，右边为设置、记录显示、一些按钮
 * [x] 状态栏中添加打开文件、导出至文件的功能
 * [] 一些重要操作(清空作答区域, 清空全部) 需要加一个警告窗
 * [] 创建帮助弹窗，显示一些使用方法
 * [] 创建关于弹窗，显示软件版本
 */

class MainWindow : public QMainWindow
{
    	Q_OBJECT
public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private:
	Arthmetic *arthmetic;

	// Main page
	QWidget *startupPage;
	QGridLayout *mainLayout;
	QGroupBox *rightGroupBox;
	QGroupBox *leftGroupBox;

	// left page
	QLabel *questionLabel[10];
	QLineEdit *calculateLineEdit[10];
	// right page
	QCheckBox *checkBoxs[6];
	QRadioButton *gradeRbutton[6];
	QTextEdit *answerTextEdit;
	QPushButton *calcButton;
	QPushButton *answerButton;
	QPushButton *recalcButton;
	QPushButton *exitButton;

	// Menu
	QMenu *startMenu;
	QMenu *editMenu;
	QMenu *aboutMenu;

	// Menu Actions
	QAction *initAct;
    	QAction *openAct;
	QAction *saveAct;
	QAction *exitAct;
	QAction *clearAnsAct;
	QAction *clearLogAct;
	QAction *clearAllAct;
	QAction *aboutAct;
	QAction *aboutQtAct;

	void createDefaultPage();
	void createLeftPage();
	void createRightPage();
    	void createMenus();
	void createActions();

	void init();

private slots:
	// 重新出题
	void initNew();
	void openFile();
	void saveFile();

	void clearAns();
	void clearLog();
	void clearAll();

	void about();
	void aboutQt();

	void settingChanged();	// 设置被修改
	void gradeChanged();	// 年级修改
	void checkAnswer();	// 对答案
	void showAnswer();	// 结果显示

protected:

};
#endif // MAINWINDOW_H
