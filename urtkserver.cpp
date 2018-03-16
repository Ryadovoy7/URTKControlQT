#include "urtkserver.h"

URTKServer::URTKServer(QWidget *parent) : QDialog(parent), statusLabel(new QLabel)
{
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    statusLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);

    QNetworkConfigurationManager manager;
    if (manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired)
    {
        // Get saved network configuration
        QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
        settings.beginGroup(QLatin1String("QtNetwork"));
        const QString id = settings.value(QLatin1String("DefaultNetworkConfiguration")).toString();
        settings.endGroup();

        // If the saved network configuration is not currently discovered use the system default
        QNetworkConfiguration config = manager.configurationFromIdentifier(id);
        if ((config.state() & QNetworkConfiguration::Discovered) !=
                QNetworkConfiguration::Discovered) {
            config = manager.defaultConfiguration();
        }

        networkSession = new QNetworkSession(config, this);
        connect(networkSession, SIGNAL(opened()), this, SLOT(sessionOpened()));

        statusLabel->setText(tr("Opening network session."));
        networkSession->open();
    } else {
        sessionOpened();
    }


    auto quitButton = new QPushButton(tr("Quit"));
    quitButton->setAutoDefault(false);
    connect(quitButton, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(quitButton, SIGNAL(clicked(bool)), tcpServer, SLOT(deleteLater()));
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(newConnect()));

    auto buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(quitButton);
    buttonLayout->addStretch(1);

    QVBoxLayout *mainLayout = nullptr;
    if (QGuiApplication::styleHints()->showIsFullScreen()) {
        auto outerVerticalLayout = new QVBoxLayout(this);
        outerVerticalLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding));
        auto outerHorizontalLayout = new QHBoxLayout;
        outerHorizontalLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::Ignored));
        auto groupBox = new QGroupBox(QGuiApplication::applicationDisplayName());
        mainLayout = new QVBoxLayout(groupBox);
        outerHorizontalLayout->addWidget(groupBox);
        outerHorizontalLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::Ignored));
        outerVerticalLayout->addLayout(outerHorizontalLayout);
        outerVerticalLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding));
    } else {
        mainLayout = new QVBoxLayout(this);
    }

    mainLayout->addWidget(statusLabel);
    mainLayout->addLayout(buttonLayout);

    setWindowTitle(QGuiApplication::applicationDisplayName());
    show();
}

void URTKServer::sessionOpened()
{
    // Save the used configuration
    if (networkSession) {
        QNetworkConfiguration config = networkSession->configuration();
        QString id;
        if (config.type() == QNetworkConfiguration::UserChoice)
            id = networkSession->sessionProperty(QLatin1String("UserChoiceConfiguration")).toString();
        else
            id = config.identifier();

        QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
        settings.beginGroup(QLatin1String("QtNetwork"));
        settings.setValue(QLatin1String("DefaultNetworkConfiguration"), id);
        settings.endGroup();
    }

    tcpServer = new QTcpServer(this);
    qDebug() << "new tcpserver created";
    if (!tcpServer->listen(QHostAddress::Any, 56655)) {
        QMessageBox::critical(this, tr("Server"),
                              tr("Unable to start the server: %1.")
                              .arg(tcpServer->errorString()));
        close();
        return;
    }
    qDebug() << "listening!";
    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // use the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
                ipAddressesList.at(i).toIPv4Address()) {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }
    qDebug() << "searched for addresses";
    // if we did not find one, use IPv4 localhost
    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
    qDebug() << "ipAddress set";
    statusLabel->setText(tr("The server is running on\n\nIP: %1\nport: %2\n\n" ).arg(ipAddress).arg(tcpServer->serverPort()));
    qDebug() << "labelCreated";
    qDebug() << "constructor exits";
}

void URTKServer::newConnect()
{
    clientConnection = tcpServer->nextPendingConnection();
    connect(clientConnection, SIGNAL(disconnected()), clientConnection, SLOT(deleteLater()));
    connect(clientConnection, SIGNAL(readyRead()), this, SLOT(sendFlag()));
    qDebug() << "new connection in town";
}

void URTKServer::sendFlag()
{
    int flagNum = 0;
    int flagMode = 0;
    int flagVal = 0;
    QByteArray recv, snd;

    recv.resize(sizeof(int)*4);
    recv = clientConnection->read(sizeof(int)*4);

    QDataStream bufByteStream(recv);
    int pckt;

    bufByteStream >> pckt;
    bufByteStream >> flagMode;
    bufByteStream >> flagNum;
    bufByteStream >> flagVal;

    qDebug() << "flagMode: " << flagMode;
    qDebug() << "flagNum: " << flagNum;
    qDebug() << "flagVal: " << flagVal;

    QDataStream out(&snd, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);

    int sendInt;

    if (1 == flagMode)
    {
        if(flags.contains(flagNum))
        {
            sendInt = flags[flagNum];
            out << sendInt;
        }
        else
        {
            sendInt = -1;
            out << sendInt;
        }
    }
    else
    {
        flags[flagNum] = flagVal;
        sendInt = 1;
        out << sendInt;
    }

    clientConnection->write(snd);
    qDebug() << "writing to client!";
    clientConnection->disconnectFromHost();
}



