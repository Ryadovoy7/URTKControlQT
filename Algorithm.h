#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "port.h"
#include <QtCore>
#include <QObject>
#include <QVector>
#include <QRegExp>
#include <QMetaEnum>

#include "operation.h"
#include "calibr.h"
#include "grab.h"
#include "move.h"
#include "test.h"

class Algorithm : public QObject
{
    Q_OBJECT
    Q_ENUMS(opEnum)

public:
    Algorithm(QObject *parent = 0);
    ~Algorithm();
    URTKPort* LPTPort;

    void algInit(const QMap<QString,QString> &settings, QString algText);
    void algEnd();

    void timerEvent(QTimerEvent *event);
    int timerID;

    QWidget* algWindow;

    enum opEnum
    {
        GRAB,
        MOVE,
        CALIBR,
        BEGIN,
        END,
        FLAG,
        CHECK,
        TEST
    };
	
private:

    QVector<QVector<Operation*>*> opVec;
    int opVecIterator;

    byte olddvg0, olddvg1;

    void readAlgorithm(QString algText);

    void portInit(const QMap<QString,QString> &settings);

    void clearOpVec();

signals:

    void algFinished();

public slots:
};

#endif

