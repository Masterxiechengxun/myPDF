#ifndef CONNSERVICE_H
#define CONNSERVICE_H

#include <QObject>
#include <QTcpSocket>
#include <QDataStream>
#include <QHostAddress>
#include <QFile>
#include <QCoreApplication>

class connService :public  QObject
{
    Q_OBJECT
public:
    static connService *getService()
    {
        static connService instance;
        return &instance;
    }
    ~connService();
    void dataWrite(const QString &str);
    void disConnectService();
    QByteArray getBuf();
    bool isConnected();
private:
    connService(QObject *parent = 0);
    QTcpSocket *socket;
    QHostAddress hostAddr;
    qint16 tport;
    QByteArray buf;
    bool isFile;
    qint64 sizeTotal;
    qint64 sizeGet;
    qint64 fileNameSize;
    QFile *file;
    QString fileName;
private slots:
    void slotConnetion();
    //void slotDisConnection();
    void dataRead();
};
#endif // CONNSERVICE_H
