#ifndef GRAB_H
#define GRAB_H

#include <QObject>
#include "operation.h"

class Grab : public Operation
{
public:
    Grab(QVector<int> *arguments, QObject *parent = 0);
};

#endif // GRAB_H
