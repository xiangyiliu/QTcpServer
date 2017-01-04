#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTcpSocket>
#include "cglobal.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    clientnumber = 0;
    socket = new QTcpSocket;
    s = new myserver ;
    s->serverstart();
    UsernameUsed = false;
    connect(s,SIGNAL(senddatatoMainWindow(QString,int,QString,QString)),this,SLOT(updatetable(QString,int,QString,QString)));
    connect(s,SIGNAL(sdeleteuser(QString,int)),this,SLOT(deleteuser()));
    //connect(socket,SIGNAL(readyRead()),this,SLOT(handlemessage()));
}

MainWindow::~MainWindow()
{
    delete ui;
    connectionMap.clear();
    map.clear();
}

void MainWindow::updatetable(QString add,int por,QString username2,QString password2)
{
    clientnumber += 1;
    ui->tableWidget->setRowCount(clientnumber);
    ui->tableWidget->setItem(clientnumber-1,3,new QTableWidgetItem(add));
    ui->tableWidget->setItem(clientnumber-1,4,new QTableWidgetItem(QString::number(por)));
    ui->tableWidget->setItem(clientnumber-1,0,new QTableWidgetItem(username2));
    ui->tableWidget->setItem(clientnumber-1,1,new QTableWidgetItem(password2));
}

void MainWindow::deleteuser(QString user, int ID)
{
    QList<QTableWidgetItem*> itemVec=ui->tableWidget->findItems(user,Qt::MatchExactly);
    for(int i=0;i<itemVec.count();i++)
    {
        if(ui->tableWidget->item(itemVec.at(i)->row(),0)==user)
        {
                ui->tableWidget->removeRow(itemVec.at(i)->row());
        }
    }

}

/*void MainWindow::opennewconnection()
{
   //ui->listWidget->addItem(QString::number(s->socketID));
   QTcpSocket *socket1 = new QTcpSocket;

   //socket1 = s->socketID);

   //socket->setSocketDescriptor(s->socketID);
   connect(socket1,SIGNAL(readyRead()),this,SLOT(handlemessage()));
   //int i = socket1->state();
   socket1->write("connected");

   clientnumber += 1;
   //ui->tableWidget->setRowCount(clientnumber);
  // ui->tableWidget->setItem(clientnumber-1,2,new QTableWidgetItem(QString::number(s->socketID)));
  // ui->tableWidget->setItem(clientnumber-1,3,new QTableWidgetItem(socket1->peerAddress().toString()));
   //ui->tableWidget->setItem(clientnumber-1,4,new QTableWidgetItem(QString::number(socket1->peerPort())));
   //cloum 0 for username, 1 for password, 2 for socketID, 3 for IP, 4 for port
   if (!map.contains(s->socketID)){
   map.insert(s->socketID,socket->peerAddress());
   }

}

void MainWindow::getstring(QString str)
{   int n;
    if(str.indexOf("|")>0)
    {
        n =str.indexOf("|");
        action =str.left(n);
        str =str.mid(n+1);

    }
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

void MainWindow::regest(QTcpSocket *socket3)
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
       socket3->write("regest|username is used,regest failed!");
    }
    else
    {
        QString sql = "insert into userdata values('";
        sql += username;
        sql += "','";
        sql += password;
        sql += "')";
        query.exec(sql);
        socket3->write("regest|success");
    }
}

void MainWindow::login()
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
            //QTcpSocket *socket1 = new QTcpSocket;
            socket->setSocketDescriptor(s->socketID);
            socket->write("ffdsfdsfds");
            ui->tableWidget->setItem(clientnumber-1,0,new QTableWidgetItem(username));
            ui->tableWidget->setItem(clientnumber-1,1,new QTableWidgetItem(password));
        }
    }
}

void MainWindow::logout()
{

}

void MainWindow::handlemessage()
{
   // QTcpSocket *socket2 = new QTcpSocket;
    i =s->socketID;
    socket->setSocketDescriptor(i);
    QString s1 = socket->readAll();
    getstring(s1);//username and socketID
    if (action=="regest")
    {
        regest(socket);
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
    else
    {

    }
}
*/
