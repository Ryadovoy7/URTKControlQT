#ifndef CHECK_H
#define CHECK_H

#include <QObject>
#include <QDebug>
#include "operation.h"
#include "port.h"

class Check : public Operation
{
public:
    Check(QVector<int> arguments, QObject *parent = 0);
    void run(byte& dvg0, byte& dvg1, URTKPort* port);
    void checkCompletion(byte& dvg0, byte& dvg1, URTKPort* port);
};

#endif // CHECK_H
