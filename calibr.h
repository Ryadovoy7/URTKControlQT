#ifndef CALIBR_H
#define CALIBR_H

#include <QObject>
#include "operation.h"

class Calibr : public Operation
{
    Q_OBJECT
public:
    Calibr(QVector<int> arguments, QObject *parent = 0);
    void run(byte olddvg0, byte olddvg1);
    void checkCompletion(byte olddvg0, byte olddvg1);

};

#endif // CALIBR_H
