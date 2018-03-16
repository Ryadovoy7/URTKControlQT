#ifndef FLAG_H
#define FLAG_H

#include <QObject>
#include <QDebug>
#include "operation.h"
#include "port.h"

class Flag : public Operation
{
public:
    Flag(QVector<int> arguments, QObject *parent = 0);
    void run(byte& dvg0, byte& dvg1, URTKPort* port);
    void checkCompletion(byte& dvg0, byte& dvg1, URTKPort* port);
};

#endif // FLAG_H
