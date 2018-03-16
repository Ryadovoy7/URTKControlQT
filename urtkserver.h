#ifndef URTKSERVER_H
#define URTKSERVER_H

#include <QtCore>
#include <QObject>
#include <QDialog>
#include <QString>
#include <QVector>
#include <QLabel>
#include <QIODevice>
#include <QMessageBox>
#include <QDebug>
#include <QtNetwork>
#include <QPushButton>
#include <QHBoxLayout>
#include <QGuiApplication>
#include <QStyleHints>
#include <QGroupBox>


class QLabel;
class QTcpServer;
class QNetworkSession;

class URTKServer : public QDialog
{
    Q_OBJECT

public:
    explicit URTKServer(QWidget *parent = nullptr);

private slots:
    void sessionOpened();
    void newConnect();
    void sendFlag();

private:
    QLabel *statusLabel = nullptr;
    QTcpServer *tcpServer = nullptr;
    QMap<int, int> flags;
    QNetworkSession *networkSession = nullptr;
    QVector<QTcpSocket*> socketVector;
    QTcpSocket *clientConnection;
};

#endif // URTKSERVER_H
