#ifndef CALIBR_H
#define CALIBR_H

#include <QObject>
#include "operation.h"

class Calibr : public Operation
{
public:
    Calibr(QVector<int> *arguments, QObject *parent = 0);
};

#endif // CALIBR_H
