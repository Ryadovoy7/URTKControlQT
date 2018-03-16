#include "check.h"

Check::Check(QVector<int> arguments, QObject *parent) : Operation(arguments, parent), tcpSocket(new QTcpSocket(this))
{
    in.setDevice(tcpSocket);
    in.setVersion(QDataStream::Qt_4_0);

    connect(tcpSocket, SIGNAL(connected()), this, SLOT(sendCheck()));
    connect(tcpSocket, SIGNAL(error()), this, SLOT(handleError()));
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(recvCheck()));
}

void Check::run(byte &dvg0, byte &dvg1, URTKPort *port)
{
    if ((argList.size() >= 2) &&  (argList[0] >= 0) && (argList[0] <= 255)
           && (argList[1] >= 0) && (argList[1] <= 255))
    {
        isStarted = 1;
    }
    else
    {
        isStarted = 1;
        isCompleted = 1;
    }
}

void Check::checkCompletion(byte &dvg0, byte &dvg1, URTKPort *port)
{
    if (tcpSocket->state() == 0)
    {
        tcpSocket->abort();
        tcpSocket->connectToHost(serverAddress, serverPort.toInt());
    }
}

void Check::setServer(QString adr, QString prt)
{
    serverAddress = adr;
    serverPort = prt;
}

void Check::sendCheck()
{

    QByteArray dataBlock;
    QDataStream bufStream(&dataBlock, QIODevice::WriteOnly);
    QVector<int> bufBlock;
    bufBlock.append(1);
    bufBlock.append(argList[0]);
    bufBlock.append(argList[1]);
    bufStream << bufBlock;

    tcpSocket->write(dataBlock);

}

void Check::recvCheck()
{
    int flagStatus;
    QByteArray bufByteArray;
    bufByteArray = tcpSocket->read(sizeof(int));
    QDataStream bufByteStream(bufByteArray);
    bufByteStream >> flagStatus;
    qDebug() << "check status recieved: " << flagStatus;

    if (flagStatus != argList[1]) {
        tcpSocket->abort();
    }
    else
    {
        tcpSocket->abort();
        isCompleted = 1;
        qDebug() << "check completed!";
    }

}

void Check::handleError()
{
    tcpSocket->abort();
    qDebug() << "check error happeed";
}
