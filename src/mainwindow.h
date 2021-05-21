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
#include <vector>
#include "arithmetic.h"

/*
 * TODO:
 * MainWindow -- 主窗口类
 * [x] 主窗体左边为答题区域，右边为设置、记录显示、一些按钮
 * [x] 状态栏中添加打开文件、导出至文件的功能
 * [x] 一些重要操作(清空作答区域, 清空全部) 需要加一个警告窗
 * [x] 创建帮助弹窗，显示一些使用方法
 * [x] 创建关于弹窗，显示软件版本
 */

static const int DEFAULT_QUESTION_NUM = 20;
static const int DEFAULT_MAX_NUM = 100;
static const int DEFAULT_MIN_NUM = 10;
static const bool HAS_POINT = false;
static const bool HAS_NEGATIVE = false;
static const int DEFAULT_WIDTH = 1280;
static const int DEFAULT_HEIGHT = 720;
static const int MIN_WIDTH = 400;
static const int MIN_HEIGHT = 300;

class MainWindow : public QMainWindow
{
            Q_OBJECT
public:
        explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

private:
        const int PLUS   = 0;
        const int MINUS  = 3;
        const int TIME   = 1;
        const int DIVID  = 4;
        const int PARENT = 2;
        const int NOPAR  = 5;

        Arithmetic *arithmetic;
        int currentGrade;        // 当前选中的年级
        bool answerShowing = false;

        // Main page
        QWidget *startupPage;
        QGridLayout *mainLayout;
        QGroupBox *rightGroupBox;
        QScrollArea *leftScrollArea;
        // QScrollArea *rightScrollArea;

        // left page
        // 题目数量可变
        std::vector<QLabel*> questionLabel;        // 题目
        std::vector<QLineEdit*> calculateLineEdit; // 答题区域
        std::vector<QLabel*> numberLabel;        // 标号
        QGridLayout *calculateLayout;

        // right page
        QCheckBox *checkBoxs[6];
        QSpinBox *numSpinBox;
        QSpinBox *maxNum;                // 生成随机数的最大值
        QSpinBox *minNum;                // 随机数最小值
        QCheckBox *hasNegative;         // 结果是否存在负数运算
        QCheckBox *hasFloat;                // 结果是否可以有浮点数
        QTextEdit *answerTextEdit;        // 作答记录
        // right page buttons
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
        QAction *helpAct;

        void createDefaultPage();
        void createLeftPage();
        void createRightPage();
            void createMenus();
        void createActions();
        void reGenerate(int oldsize, int size);

        void initSetting();

private slots:
        // 重新出题
        void initNew();
        void openFile();
        void saveFile();

        void clearAns();
        void clearLog();
        void clearAll();

        void about();
        void help();

        void settingChanged();        // 设置被修改
        void diffChanged();        // 年级修改
        void checkAnswer();        // 对答案
        void showAnswer();        // 结果显示

protected:

};
#endif // MAINWINDOW_H
