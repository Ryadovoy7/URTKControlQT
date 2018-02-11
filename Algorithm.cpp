#include "Algorithm.h"


Algorithm::Algorithm(QObject *parent) : QObject(parent)
{
}

Algorithm::~Algorithm()
{
}

void Algorithm::algInit(const QMap<QString, QString> &settings)
{

    // Инициализируем LPTPort
    portInit(settings);

    // Читаем алгоритм из файла и собираем вектор операций

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

    // Сначала удаляем операции из векторов ступеней
    for (QVector<Operation*> i : opVec)
    {
        for (Operation* j : i)
        {
            delete j;
        }

        while (i.size())
        {
            i.pop_back();
            i.squeeze(); //?
        }
    }

    // Затем удаляем весь вектор алгоритма
    while(opVec.size())
    {
        opVec.pop_back();
        opVec.squeeze();
    }
}

void Algorithm::timerEvent(QTimerEvent *event)
{

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
