#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "port.h"
#include <QtCore>
#include <QObject>
#include <QQueue>

class Algorithm : public QObject
{
    Q_OBJECT
public:
    Algorithm(QObject *parent = 0);
    Algorithm(const QMap<QString,QString> &settings, QObject *parent = 0);
    ~Algorithm();
    URTKPort* LPTPort;

    void onTick();
	
private:

signals:

public slots:
};

#endif

