#ifndef MOVE_H
#define MOVE_H

#include <QObject>
#include "operation.h"

class Move : public Operation
{
    Q_OBJECT
public:
    Move(QVector<int> arguments, QObject *parent = 0);
    void run(byte olddvg0, byte olddvg1);
    void checkCompletion(byte olddvg0, byte olddvg1);
};

#endif // MOVE_H
