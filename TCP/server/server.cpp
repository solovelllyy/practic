#include "server.h"

server::server(QWidget *parent)
    : QMainWindow(parent)
{
    if(this->listen(QHostAddress::Any,2323))
     {
     qDebug()<<"Start";
     }
     esle
     {
     qDebug()<<"error";
     }
     nextBlockSize =0;
}

void server:: incomingConnection(qintptr socketDescriptor)
{

    socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescriptor);
    connect(socket, &QTcpSocket::readyRead, this, &server::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
    Sockets.push_back(socket);
    qDebug() << "client connected" << socketDescriptor;
}
void server::slotReadyRead()
{
    socket = (QTcpSocket*) sender();
    QDataStream in (socket);
    in.setVersion (QDAtaStream::Qt_5_6);
    if(in.status() ==QDataStream::Ok)
    {
    qDebug() << "read...";
   /* QString str;
    in >> str;
    qDebug() << str;
    SendToClinet(str);*/
    for(;;)
    {
        if(nextBlockSize ==0)
        {
            qDebug()<<"nextBlockSize = 0";
            if(socket->bytesAvailable()<2)
            {
                break;
            }
            in>>nextBlockSize;
            qDebug()<<"nextBlockSize = " <<nextBlockSize;
        }
        if(socket->bytesAvailable()<nextBlockSize)
        {
            qDebug()<<"Data not full, break";
            break;
        }
        Qsring str;
        in>>str;
        nextBlockSize=0;
        qDebug()<<str;
        SendToClinet(str);
        break;
    }
    }
    else
    {
    qDebug() << "DataStream error";
    }
}
void server::SendToClient (QString str)
{
    Data.clear();
    QDataStream out (&Data, QIODevice::WriteOnly);
    out.setVersion (QDataStream::Qt_5_6);
    out <<quint16(0)<<str;
    out.device()->seek(0);
    out<<quint16(Data.size()-sizeof(quint16));

    //socket->write(Data);
    for(int i=0; i< Sockets.size();i++)
    {
        Sockets[i]->write(Data);
    }

}
