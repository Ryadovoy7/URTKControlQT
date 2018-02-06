#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWindow>
#include <QFile>
#include <QTextStream>
#include <QDialog>
#include <QFileDialog>
#include <QTextCodec>
#include <QTimer>
#include "Algorithm.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void loadSettings(QString pathToSettings);
    QMap<QString, QString> settings;

    Algorithm* alg;

private slots:
    void on_saveButton_clicked();

    void on_openButton_clicked();

    void onTick();

    void on_runButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
