#include "connservice.h"

void connService::disConnectService()
{
    if(socket)
    {
        socket->disconnectFromHost();
        socket->close();
        socket->abort();
    }
}
connService::connService(QObject *parent):
    QObject(parent)
{
    tport = 6666;
    hostAddr = QHostAddress::LocalHost;
    sizeTotal = 0;
    sizeGet = 0;
    fileNameSize = 0;
    fileName.clear();
    file = NULL;
    isFile = false;
    buf.resize(0);
    //file = new QFile(QCoreApplication::applicationDirPath());
    socket = new QTcpSocket;
    socket->abort();
    socket->connectToHost(("127.0.0.1"), 6666);
    connect(socket, SIGNAL(connected()), this, SLOT(slotConnetion()));
    //connect(socket, SIGNAL(disconnected()), this, SLOT(slotDisConnection()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(dataRead()));
}
connService::~connService()
{
    if(socket != NULL)
    {
        socket->disconnectFromHost();
        socket->close();
        socket->abort();
        delete socket;
    }
}
void connService::slotConnetion()
{
}
//void connService::slotDisConnection()
//{
//    socket->abort();
//    socket->connectToHost(("127.0.0.1"), 6666);
//    connect(socket, SIGNAL(connected()), this, SLOT(connService::slotConnetion()));
//    connect(socket, SIGNAL(disconnected()), this, SLOT(connService::slotDisConnection()));
//    connect(socket, SIGNAL(readyRead()), this, SLOT(connService::dataRead()));
//}
void connService::dataWrite(const QString &str)
{
    socket->write(str.toLatin1(),str.length() + 1);
}
void connService::dataRead()
{
    if(!isFile) {
        while(socket->bytesAvailable() > 0)
        {
            buf.resize(0);
            buf = socket->readAll();
        }
        if(static_cast<QString>(buf) == "file"){
            isFile = true;
        }
    } else {
        QDataStream in(socket);
        in.setVersion(QDataStream::Qt_5_8);
        if(sizeGet <= sizeof(qint64) * 2) { //接收文件头（包大小+文件名大小+文件名）
            if((socket->bytesAvailable() >= sizeof(qint64) * 2)&&(fileNameSize == 0))
            {
                in >> sizeTotal >> fileNameSize;
                sizeGet += sizeof(qint64) * 2;
            }
            if((socket->bytesAvailable() >= fileNameSize)&&(fileNameSize != 0))
            {
                in >> fileName;
                fileName = "Files\\" + fileName;
                sizeGet += fileNameSize;
                file = new QFile(fileName);
                if(!file->open(QFile::WriteOnly))
                {
                    qDebug() << "无法写文件";
                    return;
                }
            } else {
                return; //没有成功接收到文件头
            }
        }
        if(sizeGet < sizeTotal)
        {
            sizeGet += socket->bytesAvailable();
            buf = socket->readAll();
            file->write(buf);
            buf.resize(0);
        }
        if(sizeGet == sizeTotal)
        {
            file->close();
            file = NULL;
            sizeGet = 0;
            sizeTotal = 0;
            fileNameSize = 0;
            fileName.clear();
            isFile = false;
        }
    }
}
QByteArray  connService::getBuf()
{
    //阻塞等待socket获取到服务器的数据
    socket->waitForReadyRead();
    return buf;
}
bool connService::isConnected()
{
    return (socket->state() == QTcpSocket::ConnectedState);
}

