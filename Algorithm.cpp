#include "Algorithm.h"


Algorithm::Algorithm(QObject *parent) : QObject(parent)
{
    LPTPort = new URTKPort();
}

Algorithm::Algorithm(const QMap<QString, QString> &settings, QObject *parent) : QObject(parent)
{
    bool ok;
    byte data = (byte)settings["LptData"].toUInt(&ok,0);
    byte status = (byte)settings["LptStatus"].toUInt(&ok,0);
    byte config = (byte)settings["LptConfig"].toUInt(&ok,0);
    if(data && status && config)
    {
        LPTPort = new URTKPort(data, status, config);
    }
    else
    {
        LPTPort = new URTKPort();
    }
}


Algorithm::~Algorithm()
{
}
