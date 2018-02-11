#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "port.h"
#include <QtCore>
#include <QObject>
#include <QMap>
#include <QVector>

#include "operation.h"
#include "calibr.h"
#include "grab.h"
#include "move.h"

class Algorithm : public QObject
{
    Q_OBJECT
public:
    Algorithm(QObject *parent = 0);
    ~Algorithm();
    URTKPort* LPTPort;

    void algInit(const QMap<QString,QString> &settings);
    void algEnd();

    void timerEvent(QTimerEvent *event);
    int timerID;
	
private:

    QVector<QVector<Operation*>> opVec;
    void readAlgorithm();
    void portInit(const QMap<QString,QString> &settings);

signals:

public slots:
};

#endif

