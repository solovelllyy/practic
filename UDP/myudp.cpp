#include "myudp.h"

MyUDP::MyUDP(QObject *parent) :
    QObject(parent)
{

    socket = new QUdpSocket(this);


    socket->bind(QHostAddress::LocalHost, 2222);

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void MyUDP::HelloUDP()
{
    QByteArray Data;
    Data.append("");

    socket->writeDatagram(Data, QHostAddress::LocalHost, 2222);
}

void MyUDP::readyRead()
{

    QByteArray buffer;
    buffer.resize(socket->pendingDatagramSize());

    QHostAddress sender;
    quint16 senderPort;





    qDebug() << "Message from: " << sender.toString();
    qDebug() << "Message port: " << senderPort;
    qDebug() << "Message: " << buffer;
}
