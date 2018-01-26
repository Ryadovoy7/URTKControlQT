#include "mainwindow.h"
#include <QApplication>
#include "inpout32.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
