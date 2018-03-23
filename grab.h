#ifndef GRAB_H
#define GRAB_H

#include <QObject>
#include "operation.h"
#include "port.h"
#include <QDebug>

class Grab : public Operation
{
    Q_OBJECT
public:
    Grab(QVector<int> arguments, QObject *parent = 0);
    void run(byte& dvg0, byte& dvg1, URTKPort* port);
    void checkCompletion(byte& dvg0, byte& dvg1, URTKPort* port);
    void resetOperation();
};

#endif // GRAB_H
