#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_scriptwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Создаем таймер, вызывающий выполнение функции onTick() каждые 100 мс
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTick()));
    timer->start(100);

    loadSettings("settings.txt");

    alg = new Algorithm(0);
    connect(alg, SIGNAL(algFinished()), this, SLOT(on_alg_ended()));

    algRunning = false;
    serverRunning = false;
    settingsOpened = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadSettings(QString pathToSettings)
{
    settings.clear();
    if (pathToSettings.size())
    {
        QFile openFile(pathToSettings);
        if (!openFile.open(QIODevice::ReadOnly | QIODevice::Text )) return;
        while (!openFile.atEnd()) {
            QByteArray lineByteArray = openFile.readLine();
            QString line = QTextCodec::codecForUtfText(lineByteArray)->toUnicode(lineByteArray);
            QStringList lineList = line.split('=', QString::SkipEmptyParts);
            if(lineList.length() == 2) { settings.insert(lineList[0],lineList[1]); }
        }
        openFile.close();
    }
}

void MainWindow::on_saveButton_clicked()
{
    // сохраняем содержимое текстового редактора в файл
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
    // загружаем содержимое текстового редактора из файла
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
    if (!algRunning)
    {
        //alg->algWindow->show();
        alg->algInit(settings, this->findChild<QPlainTextEdit*>("scriptEdit")->toPlainText());
        algRunning = true;
    }
    else
    {
        QMessageBox errMsg;
        errMsg.setText("Алгоритм уже выполняется!");
        errMsg.exec();
    }
}

void MainWindow::on_alg_ended()
{
    algRunning = false;
}

void MainWindow::on_pushButton_clicked()
{
    if (algRunning)
    {
        alg->algEnd();
    }
    else
    {
        QMessageBox errMsg;
        errMsg.setText("Алгоритм не выполняется!");
        errMsg.exec();
    }
}
