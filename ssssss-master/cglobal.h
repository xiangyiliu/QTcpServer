#ifndef CGLOBAL_H
#define CGLOBAL_H
#include <QMap>
#include <QTcpSocket>

extern QMap<QString,QTcpSocket*> connectionMap;
#endif // CGLOBAL_H
