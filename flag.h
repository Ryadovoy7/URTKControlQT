#ifndef FLAG_H
#define FLAG_H

#include <QObject>
#include <QDebug>
#include "operation.h"
#include "port.h"
#include <QDataStream>
#include <QtNetwork>

class Flag : public Operation
{
    Q_OBJECT
public:
    Flag(QVector<int> arguments, QObject *parent = 0);
    void run(byte& dvg0, byte& dvg1, URTKPort* port);
    void checkCompletion(byte& dvg0, byte& dvg1, URTKPort* port);
    void setServer(QString adr, QString prt);
    void handleError();
    void resetOperation();

public slots:

    void sendFlag();
    void recvFlag();

private:
    QTcpSocket *tcpSocket = nullptr;
    QNetworkSession *networkSession = nullptr;

    QDataStream in;
    QString serverAddress = "127.0.0.1", serverPort = "51000";
};

#endif // FLAG_H
