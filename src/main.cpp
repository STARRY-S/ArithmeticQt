#include "mainwindow.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
        QApplication a(argc, argv);
#ifdef _MSC_BUILD
        a.setFont(QFont("Microsoft YaHei", 11));
#else
        a.setFont(QFont("Noto Sans CJK SC", 11));
#endif
        a.setWindowIcon(QIcon("images/favicon.ico"));
        MainWindow w;
        w.show();
        return a.exec();
}
