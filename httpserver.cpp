#include "httpserver.h"
#include <QDebug>

#include <QTextCodec>

HttpServer::HttpServer(QObject* parent):
    QObject(parent),
    m_tcpServer(new QTcpServer(this)),
    m_adress(QHostAddress::Any),
    m_port(8080),
    m_message(QString("")),
    m_resetDelta(10000)
{
    m_tcpServer->listen(m_adress, m_port);
    connect(m_tcpServer, &QTcpServer::newConnection, this, &HttpServer::_newConnection);
    qDebug() << tr("The server is running on IP: %1 port: %2.")
              .arg(m_tcpServer->serverAddress().toString()).arg(m_tcpServer->serverPort());
}

void HttpServer::_newConnection()
{
    QTcpSocket *clientConnection = m_tcpServer->nextPendingConnection();
    QObject::connect(clientConnection, &QAbstractSocket::readyRead, this, &HttpServer::_read);
    m_clients.append(clientConnection);
}

void HttpServer::_launchReset()
{
    m_resetTimer.stop();
    m_resetTimer.singleShot(m_resetDelta, this, &HttpServer::_reset);
}

void HttpServer::_reset()
{
    m_message = "";
    messageChanged();
}

void HttpServer::_read()
{
    auto sender = this->sender();
    auto clientConnection = qobject_cast<QTcpSocket*>(sender);
    auto res = clientConnection->readAll();
    qDebug() << "received " << res;

    //UTF-8 106
    QString data = QTextCodec::codecForMib(106)->toUnicode(res);
    QString token = "obione";
    QString start = "startAnimation";
    QString stop = "stopAnimation";

    if(data.contains(token)){
        data = data.section(token, 1, 1);
    }
    if(data.contains(start)){
        m_resetTimer.stop();
        startAnimation();
    } else if(data.contains(stop)){
        m_resetTimer.stop();
        stopAnimation();
    }
    else {
        _launchReset();
        m_message = data;
        messageChanged();
    }

    clientConnection->write("Hello client\r\n");
    clientConnection->flush();
    clientConnection->waitForBytesWritten(3000);
    clientConnection->disconnectFromHost();
}

QString HttpServer::message() const
{
    return m_message;
}


