#include "mainwindow.h"
#include <QApplication>
#include "inpout32.h"


int main(int argc, char *argv[])
{
    // Оставляем здесь путь к qwindows.dll
    // Теперь программа запустится на XP!
    QStringList paths = QCoreApplication::libraryPaths();
    paths.append(".");
    paths.append("imageformats");
    paths.append("platforms");
    paths.append("sqldrivers");
    QCoreApplication::setLibraryPaths(paths);

    // Создаем экземпляр класса QApplication - необходимо для работы QT-приложения
    QApplication a(argc, argv);
    // Создаем основное окно приложения
    MainWindow w;
    // По умолчанию оно скрыто
    w.show();

    // Запускаем функцию exec() - она вернет значение, когда мы закроем программу
    return a.exec();
}
