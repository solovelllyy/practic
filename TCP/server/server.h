#ifndef SERVER_H
#define SERVER_H

#ifndef <QTspServer>
#ifndef <QTspSocket>
#ifndef <QVector>
class Server666 : public QTcpServer
{
    Q_OBJECT

public:
    Server666();
    QTcpSocket *socket;

private:
    QVector <QTcpSocket*> Sockets;
    QByteArray Data;
    void SendTOClient(QString str);
    quint16 nextBlockSize;

public slots:
    void incomingConnection(qintptr socketDescriptor);
    void slotReadyRead();

};
#endif // SERVER666_H

