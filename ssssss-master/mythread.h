#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QMap>
#include <QList>

class mythread : public QThread
{
    Q_OBJECT
public:
    explicit mythread(int ID,QObject *parent = 0);
    void run();
    int socketID;


signals:   
    void UpdateSignal(QString add,int port,QString username,QString password);
    void deleteuser(QString user,int socketID);
public slots:
    void disconnect();
    void handlemessage();
private:

    QTcpSocket *socket;
    QString action;
    QString username;
    QString receiverUser;
    QString password;
    QString usermessage;
    bool UsernameUsed;
    bool bLogin;
    void getstring(QString);
    void regest();
    void login();
    void logout();
    QList <QTcpSocket*> list;



};

#endif // MYTHREAD_H
