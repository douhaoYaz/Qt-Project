#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QObject>
#include <QTcpSocket>

class ChatClient : public QObject
{
    Q_OBJECT
public:
    explicit ChatClient(QObject *parent = nullptr);

signals:
    void connected();
    void messageReceived(const QString &text);

private:
    QTcpSocket *m_clientSocket;

public slots:
    void onReadyRead();
    void sendMessage(const QString &text, const QString &type = "message");
    void connectToServer(const QHostAddress &address, quint16 port);
};

#endif // CHATCLIENT_H
