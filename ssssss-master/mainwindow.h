#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include "myserver.h"
#include "mythread.h"
#include <QMap>
#include <QtSql>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QMap<int,QHostAddress>  map;
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    //QTcpServer *server;
    myserver *s;
    void getstring(QString);
    void regest(QTcpSocket *socket);
    void login();
    void logout();
    QString action;
    QString username;
    QString password;
    bool UsernameUsed;
    int clientnumber;
    int i;
    QTcpSocket *socket;
private slots:
    //void opennewconnection();
public slots:
    //void handlemessage();
     void updatetable(QString add,int por,QString username2,QString password2);
     void deleteuser(QString ,int);
};

#endif // MAINWINDOW_H
