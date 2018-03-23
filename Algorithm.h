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
#include "flag.h"
#include "check.h"
#include "test.h"

#include "urtkserver.h"

class Algorithm : public QObject
{
    Q_OBJECT
    Q_ENUMS(opEnum)

public:
    Algorithm(QObject *parent = 0);
    ~Algorithm();
    URTKPort* LPTPort;
    URTKServer* serv;

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
        TEST,
        REPEAT
    };
	
private:

    QVector<QVector<Operation*>*> opVec;
    int opVecIterator;

    byte olddvg0, olddvg1;

    void readAlgorithm(QString algText, const QMap<QString,QString> &settings);

    void portInit(const QMap<QString,QString> &settings);

    void clearOpVec();

    int repeatCount;

signals:

    void algFinished();

public slots:
};

#endif

