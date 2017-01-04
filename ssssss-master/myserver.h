#ifndef MYSERVER_H
#define MYSERVER_H

#include <QTcpServer>
#include "mythread.h"

class myserver : public QTcpServer
{
    Q_OBJECT
public:
    explicit myserver(QObject *parent = 0);
    void serverstart();
    int socketID;
    mythread *thread;
signals:
   void senddatatoMainWindow(QString add,int por,QString username2,QString password2);
   void sdeleteuser(QString ,int);
public slots:
    void sendData(QString add,int por,QString username2,QString password2);
    void deleteuser(QString,int);
protected:
    void incomingConnection(int socketDescriptor);
private:



};

#endif // MYSERVER_H
