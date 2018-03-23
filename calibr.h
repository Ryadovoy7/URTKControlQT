#ifndef CALIBR_H
#define CALIBR_H

#include <QObject>
#include "operation.h"
#include "port.h"

class Calibr : public Operation
{
    Q_OBJECT
public:
    Calibr(QVector<int> arguments, QObject *parent = 0);
    void run(byte& dvg0, byte& dvg1, URTKPort* port);
    void checkCompletion(byte& dvg0, byte& dvg1, URTKPort* port);
    void resetOperation();

};

#endif // CALIBR_H
