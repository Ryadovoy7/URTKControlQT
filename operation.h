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
    virtual void run(byte& dvg0, byte& dvg1, URTKPort* port);
    virtual void checkCompletion(byte& dvg0, byte& dvg1, URTKPort* port);
    virtual void resetOperation();

    QVector<int> argList;
    QVector<int> runVar;

    bool isCompleted, isStarted;

signals:

public slots:

};

#endif // OPERATION_H
