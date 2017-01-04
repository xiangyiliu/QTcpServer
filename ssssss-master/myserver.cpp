#include "myserver.h"


myserver::myserver(QObject *parent) :
    QTcpServer(parent)
{
}
void myserver::serverstart()
{
    if(!this->listen(QHostAddress::Any,1234))
    {

    }
}

void myserver::sendData(QString add,int por,QString username2,QString password2)
{
    emit senddatatoMainWindow(add,por,username2,password2);
}

void myserver::deleteuser(QString str, int ID)
{
    emit sdeleteuser(str,ID);
}
void myserver::incomingConnection(int socketDescriptor)
{
  thread = new mythread(socketDescriptor,this);
  socketID = socketDescriptor;
  connect(thread,SIGNAL(UpdateSignal(QString ,int,QString,QString)),this,SLOT(sendData(QString,int,QString,QString)));
  connect(thread,SIGNAL(deleteuser(QString,int)),this,SLOT(deleteuser(QString,int)));
  thread->start();
}
