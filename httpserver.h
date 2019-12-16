#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <QObject>
#include <QTimer>

#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>

class HttpServer : public QObject
{
    Q_OBJECT

public:
    HttpServer(QObject* parent = nullptr);

    Q_PROPERTY(QString                      message
        READ                                message
        NOTIFY                              messageChanged)

    QString message() const;

private:
    void _newConnection();
    void _launchReset();
    void _reset();

private slots:
    void _read();

private:
    QTcpServer* m_tcpServer;
    QHostAddress m_adress;
    QTimer m_resetTimer;
    quint16 m_port;
    QString m_message;
    int m_resetDelta;

    QList<QTcpSocket*> m_clients;

signals:
    void messageChanged();
    void startAnimation();
    void stopAnimation();
};

#endif // HTTPSERVER_H
