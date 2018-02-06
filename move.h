#ifndef MOVE_H
#define MOVE_H

#include <QObject>

class Move : public Operation
{
public:
    Move(QVector<int> arguments = nullptr, QObject *parent = nullptr);
};

#endif // MOVE_H
