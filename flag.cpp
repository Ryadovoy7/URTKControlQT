#include "flag.h"

Flag::Flag(QVector<int> arguments, QObject *parent) : Operation(arguments, parent), tcpSocket(new QTcpSocket(this))
{
    connect(tcpSocket, SIGNAL(connected()), this, SLOT(sendFlag()));
    connect(tcpSocket, SIGNAL(error()), this, SLOT(handleError()));
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(recvFlag()));
}

void Flag::run(byte &dvg0, byte &dvg1, URTKPort *port)
{
    if ((argList.size() >= 2) &&  (argList[0] >= 0) && (argList[0] <= 255)
            && (argList[1] >= 0) && (argList[1] <= 255))
    {
        isStarted = 1;
        qDebug() << "flag starts!";
    }
    else
    {
        isStarted = 1;
        isCompleted = 1;
    }
}

void Flag::checkCompletion(byte &dvg0, byte &dvg1, URTKPort *port)
{
    qDebug() << "flag checking completion " << tcpSocket->state();
    if (tcpSocket->state() == QAbstractSocket::UnconnectedState)
    {
        tcpSocket->abort();
        tcpSocket->connectToHost(serverAddress, serverPort.toInt());
        qDebug() << "connecting to host";
    }
}

void Flag::setServer(QString adr, QString prt)
{
    serverAddress = adr;
    serverPort = prt;
}

void Flag::sendFlag()
{

    QByteArray dataBlock;
    QDataStream bufStream(&dataBlock, QIODevice::WriteOnly);
    QVector<int> bufBlock;
    bufBlock.append(0);
    bufBlock.append(argList[0]);
    qDebug() << "flag arg0: ";
    bufBlock.append(argList[1]);
    qDebug() << "flag arg1: ";
    bufStream << bufBlock;

    tcpSocket->write(dataBlock);
    qDebug() << "flag sent!";

}

void Flag::recvFlag()
{
    int flagStatus;
    QByteArray bufByteArray;
    bufByteArray = tcpSocket->read(sizeof(int));
    QDataStream bufByteStream(bufByteArray);
    bufByteStream >> flagStatus;
    qDebug() << "flag status recieved: " << flagStatus;

    if (flagStatus == 1) {
        tcpSocket->abort();
        isCompleted = 1;
        qDebug() << "flag completed!";
    }
    else
    {
        tcpSocket->abort();
    }


}

void Flag::handleError()
{
    tcpSocket->abort();
    qDebug() << "flag error happeed";
}

void Flag::resetOperation()
{
    isStarted = 0; isCompleted = 0;
}
