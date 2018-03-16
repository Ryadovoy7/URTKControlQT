#ifndef MOVE_H
#define MOVE_H

#include <QObject>
#include <QDebug>
#include "operation.h"
#include "port.h"

class Move : public Operation
{
    Q_OBJECT
public:
    Move(QVector<int> arguments, QObject *parent = 0);
    void run(byte& dvg0, byte& dvg1, URTKPort* port);
    void checkCompletion(byte& dvg0, byte& dvg1, URTKPort* port);
    void timerEvent(QTimerEvent *event);
};

#endif // MOVE_H
