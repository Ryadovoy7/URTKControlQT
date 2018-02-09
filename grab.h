#ifndef GRAB_H
#define GRAB_H

#include <QObject>
#include "operation.h"

class Grab : public Operation
{
    Q_OBJECT
public:
    Grab(QVector<int> arguments, QObject *parent = 0);
    void run(byte olddvg0, byte olddvg1);
    void checkCompletion(byte olddvg0, byte olddvg1);
};

#endif // GRAB_H
