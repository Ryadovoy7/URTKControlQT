#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_scriptwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTick()));
    timer->start(100);
    //sup
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_saveButton_clicked()
{
    QString savePath;
    savePath = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("Text files (*.txt)"));
    if (savePath.size())
    {
        QPlainTextEdit* edit = this->findChild<QPlainTextEdit*>("scriptEdit");
        QFile saveFile(savePath);
        if (!saveFile.open(QIODevice::WriteOnly | QIODevice::Text )) return;
        QTextStream out(&saveFile);
        out << edit->toPlainText();
        saveFile.close();
    }
}

void MainWindow::on_openButton_clicked()
{
    QString openPath;
    openPath = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Text files (*.txt)"));
    if (openPath.size())
    {
        QPlainTextEdit* edit = this->findChild<QPlainTextEdit*>("scriptEdit");
        QFile openFile(openPath);
        if (!openFile.open(QIODevice::ReadOnly | QIODevice::Text )) return;
        edit->setPlainText("");
        while (!openFile.atEnd()) {
            QByteArray line = openFile.readLine();
            edit->insertPlainText(QTextCodec::codecForUtfText(line)->toUnicode(line));
        }
        openFile.close();
    }
}

void MainWindow::onTick()
{

}

void MainWindow::on_runButton_clicked()
{
    QWidget *testWindow = new QWidget();
    Ui::ScriptWindow uiScript;
    uiScript.setupUi(testWindow);
    testWindow->show();
}
