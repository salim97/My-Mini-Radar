#ifndef MYNETWORK_H
#define MYNETWORK_H

#include <QObject>
#include <QUdpSocket>
#include "mypropertyhelper.h"

#define enable_debug_udp true

class MyNetwork : public QObject
{
    Q_OBJECT
public:
    explicit MyNetwork(QObject *parent = nullptr);
    AUTO_PROPERTY(int, angle)
    AUTO_PROPERTY(int, distance_CM)
    AUTO_PROPERTY(bool, rightToLeft)

signals:

public slots:
        void sendUDP(QString msg);
private slots:
    void readyReadUDP();
    void proccessData(QString data);
private:
    int udpPort = 5551 ;
    QUdpSocket *m_udpSocket = nullptr;

};

#endif // MYNETWORK_H
