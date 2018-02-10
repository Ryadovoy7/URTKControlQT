#ifndef OPERATION_H
#define OPERATION_H

#include <QObject>
#include <QVector>
#include "port.h"

class Operation : public QObject
{
    Q_OBJECT
public:
    explicit Operation(QVector<int> arguments, QObject *parent = 0);
    virtual void run(byte olddvg0, byte olddvg1);
    virtual void checkCompletion(byte olddvg0, byte olddvg1);

    QVector<int> argList;
    QVector<int> runVar;

    bool isCompleted, isStarted;

signals:

public slots:
};

#endif // OPERATION_H
