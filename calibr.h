#ifndef CALIBR_H
#define CALIBR_H

#include <QObject>

class Calibr : public Operation
{
public:
    Calibr(QVector<int> arguments = nullptr, QObject *parent = nullptr);
};

#endif // CALIBR_H
