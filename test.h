#ifndef TEST_H
#define TEST_H

#include <QObject>
#include "Operation.h"
#include <QDebug>

class Test : public Operation
{
public:
    Test(QVector<int> arguments, QObject *parent = 0);
    void run(byte &dvg0, byte &dvg1, URTKPort *port);
    void checkCompletion(byte& dvg0, byte& dvg1, URTKPort* port);
    void timerEvent(QTimerEvent *event);
};

#endif // TEST_H
