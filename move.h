#ifndef MOVE_H
#define MOVE_H

#include <QObject>
#include "operation.h"

class Move : public Operation
{
public:
    Move(QVector<int> *arguments, QObject *parent = 0);
};

#endif // MOVE_H
