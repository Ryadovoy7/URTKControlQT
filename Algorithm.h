#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "port.h"
#include <QtCore>
#include <QObject>
#include <QMap>
#include <QVector>
#include <QPair>
#include <QRegExp>

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

    void algInit(const QMap<QString,QString> &settings, QString algText);
    void algEnd();



    void timerEvent(QTimerEvent *event);
    int timerID;
	
private:

    QVector<QVector<Operation*>> opVec;
    void readAlgorithm(QString algText);

    void portInit(const QMap<QString,QString> &settings);

    void clearOpVec();

signals:

public slots:
};

#endif

