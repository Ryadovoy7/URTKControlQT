#include "Algorithm.h"


Algorithm::Algorithm(QObject *parent) : QObject(parent)
{
    opVec.clear();
    opVec.squeeze();
}

Algorithm::~Algorithm()
{
}

void Algorithm::algInit(const QMap<QString, QString> &settings, QString algText)
{

    // На всякий случай очищаем вектор операций
    opVec.clear();
    opVec.squeeze();

    // Инициализируем LPTPort
    portInit(settings);

    // Читаем алгоритм из файла и собираем вектор операций
    readAlgorithm(algText);

    // Создаем таймер
    timerID = startTimer(50);
}

void Algorithm::algEnd()
{
    // Останавливаем таймер
    killTimer(timerID);
    timerID = 0;

    // Удаляем инициализированный порт
    delete LPTPort;
    LPTPort = 0;

    // Очищаем вектор операций
    clearOpVec();
}

void Algorithm::timerEvent(QTimerEvent *event)
{

}

void Algorithm::readAlgorithm(QString algText)
{
    // Делим полученный текст по строчкам
    QStringList algTextList = algText.split(QRegExp("[\r\n]"),QString::SkipEmptyParts);
    // Теперь для каждой строчки
    QStringListIterator algIterator(algTextList);
    while(algIterator.hasNext())
    {
        QString bufString = algIterator.next();
        QPair<QString,QString> sepBufString;
    }
}

void Algorithm::portInit(const QMap<QString, QString> &settings)
{
    bool ok;
    byte data = (byte)settings["LptData"].toUInt(&ok,0);
    byte status = (byte)settings["LptStatus"].toUInt(&ok,0);
    byte config = (byte)settings["LptConfig"].toUInt(&ok,0);

    if(data && status && config)
    {
        LPTPort = new URTKPort(data, status, config, this);
    }
    else
    {
        LPTPort = new URTKPort(this);
    }
}

void Algorithm::clearOpVec()
{
    // Сначала удаляем операции из векторов ступеней
    for (QVector<Operation*> i : opVec)
    {
        for (Operation* j : i)
        {
            delete j;
        }

        i.clear();
        i.squeeze();
    }

    // Затем удаляем весь вектор алгоритма
    opVec.clear();
    opVec.squeeze();
}
