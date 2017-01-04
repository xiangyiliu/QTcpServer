#include "mythread.h"
#include "mainwindow.h"
#include "cglobal.h"
#include <QMap>
#include <QDebug>

mythread::mythread(int ID,QObject *parent) :
    QThread(parent)
{
    this->socketID = ID;
    UsernameUsed = false;
    bLogin = false;
    socket = new QTcpSocket;
    if(!socket->setSocketDescriptor(this->socketID))
    {
        return;
    }
    connect(socket,SIGNAL(readyRead()),this,SLOT(handlemessage()));
    socket->waitForReadyRead(100);
    connect(socket,SIGNAL(disconnected()),this,SLOT(disconnect()));
}
void mythread::run()
{

    exec();

}
void mythread::disconnect()
{

    socket->deleteLater();
    exit(0);
}

void mythread::handlemessage()
{
    QString s1 = socket->readAll();
    getstring(s1);//username and socketID
    if (action=="regest")
    {
        regest();
    }
    else if (action=="login")
    {
        login();
        //ui->tableWidget->setItem(0,0,new QTableWidgetItem(username));
        //ui->tableWidget->setItem(0,1,new QTableWidgetItem(s->socketID));
    }
    else if (action=="logout")
    {
        logout();
    }
    else if (action=="chat")
    {
        QByteArray byte = usermessage.toLatin1();
        char * str = byte.data();
        //connectionMap.value("wudi")->state();
        QString str1;
        foreach (str1, connectionMap.keys()){
            //查看接收信息的用户是否在线
            if (str1==receiverUser)
            {
               bLogin=true;
            }
        }
        if (bLogin)
        {
            //发送信息到接收信息的用户
            QString str2 = "chat|"+username +"|" + usermessage;
            connectionMap.value(receiverUser)->write(str2.toLatin1());
        }


    }
    else
    {

    }
}

void mythread::getstring(QString str)
{   int n;
    if(str.indexOf("|")>0)
    {
        n =str.indexOf("|");
        action =str.left(n);
        str =str.mid(n+1);

    }
    if(action=="regest"|action=="login"|action=="logout")
    {
        if(str.indexOf("|")>0)
        {
            n=str.indexOf("|");
            username =str.left(n);
            str=str.mid(n+1);
        }
        if(str.indexOf("|")>0)
        {
            n=str.indexOf("|");
            password =str.left(n);
            str=str.mid(n+1);
        }
    }
    if (action=="chat")
    {
        if(str.indexOf("|")>0)
        {
            n=str.indexOf("|");
            receiverUser =str.left(n);
            str=str.mid(n+1);
        }
        if(str.indexOf("|")>0)
        {
            n=str.indexOf("|");
            usermessage =str.left(n);
            str=str.mid(n+1);
        }
    }

}

void mythread::regest()
{

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName(QString("DRIVER={SQL SERVER};"
                                  "SERVER=%1;"
                                  "DATABASE=%2;"
                                 ).arg("DENGWEI")
                                  .arg("liubing"));
    db.open();
    QSqlQuery query;
    query.prepare("select count(1) from syscolumns where [id]=object_id('userdata') ");
    query.exec();
    if(query.value(0).toInt()==0)
    {
        query.prepare("Create table userdata ([username] char(10), [password] char(16))");
        query.exec();
    }
    query.prepare("select username from userdata");
    query.exec();
    while (query.next())
    {
        QString t=query.value(0).toString().trimmed();
        if (t==username)
        {
            UsernameUsed = true;
            break;
        }
    }
    if (UsernameUsed)
    {
       socket->write("regest|username is used,regest failed!");
    }
    else
    {
        QString sql = "insert into userdata values('";
        sql += username;
        sql += "','";
        sql += password;
        sql += "')";
        query.exec(sql);
        socket->write("regest|success");
    }
}

void mythread::login()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName(QString("DRIVER={SQL SERVER};"
                                  "SERVER=%1;"
                                  "DATABASE=%2;"
                                 ).arg("DENGWEI")
                                  .arg("liubing"));
    db.open();
    QSqlQuery query;
    QString sql = "select username,password from userdata where username='";
    sql += username;
    sql += "'";
    query.exec(sql);
    if(query.next())
    {
        if(query.value(1).toString().trimmed()==password)
        {
            //密码正确
            socket->write("login|login success");
            QString add = socket->peerAddress().toString();
            emit UpdateSignal(add,socket->peerPort(),username,password);
            list.append(socket);
            connectionMap.insert(username,socket);
            //ui->tableWidget->setItem(clientnumber-1,0,new QTableWidgetItem(username));
            //ui->tableWidget->setItem(clientnumber-1,1,new QTableWidgetItem(password));
        }
        else
        {
            socket->write("login|login failed");
        }
    }
    else
    {
        socket->write("login|usename does not exist!");
    }
}

void mythread::logout()
{
 connectionMap.remove(username);
 emit deleteuser(username,socketID);
}
