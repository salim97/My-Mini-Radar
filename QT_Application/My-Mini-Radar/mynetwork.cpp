#include "mynetwork.h"

MyNetwork::MyNetwork(QObject *parent) : QObject(parent)
{
    angle(0);
    m_udpSocket = new QUdpSocket(this);
    if(!m_udpSocket->bind(udpPort, QUdpSocket::ShareAddress))
        qDebug() << "m_udpSocket : " + m_udpSocket->errorString() ;
    else
        qDebug() << "UDP 127.0.0.1:" +QString::number(udpPort)+" LISTENING." ;

    connect(m_udpSocket, SIGNAL(readyRead()), this, SLOT(readyReadUDP()));

}

void MyNetwork::sendUDP(QString msg)
{
    qDebug() << "msg: " << msg  ;
    QByteArray datagram = msg.toUtf8() ;
    m_udpSocket->writeDatagram(datagram.data(), datagram.size(),
                               //QHostAddress::Broadcast, udpPort);
                              QHostAddress("255.255.255.255"), udpPort);
}

void MyNetwork::readyReadUDP()
{
    while (m_udpSocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(m_udpSocket->pendingDatagramSize());
        m_udpSocket->readDatagram(datagram.data(), datagram.size());

        QString data = datagram;
        if(enable_debug_udp)
            qDebug() << "readyReadUDP: " << data ;

        proccessData(data) ;

    }
}

void MyNetwork::proccessData(QString data)
{
        if(data.contains("<angle>"))
        {
            data.replace("<angle>","");
            angle(data.toInt());
        }
        else if(data.contains("<distance_CM>"))
        {
            data.replace("<distance_CM>","");
            distance_CM(data.toInt());
        }
        else if(data.contains("<rightToLeft>"))
        {
            data.replace("<rightToLeft>","");
            if(data == "1")
                rightToLeft(true);
            else
                rightToLeft(false);
        }
}
