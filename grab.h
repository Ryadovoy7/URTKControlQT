#ifndef GRAB_H
#define GRAB_H

#include <QObject>

class Grab : public Operation
{
public:
    Grab(QVector<int> arguments = nullptr, QObject *parent = nullptr);
};

#endif // GRAB_H
