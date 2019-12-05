#ifndef RUNNER_H
#define RUNNER_H
#include<QObject>
#include<QVector>
#include<QPair>
#include "factory/singleton.h"
#include "factory/factory.h"
class Runner:public QObject
{
    Q_OBJECT
public:
    Runner();

    std::map<QString,QStringList>  GetRegisteredList();
    void SetParametes(QVector<QPair<QString,QStringList>>);
private:
    QVector<QPair<QString,QStringList>> m_cmds;
public slots:
    void Start();
    void SendMsg(QString);
signals:
    void changeSelection(int );
    void finished(int);
    void ShowMsg(QString);

};

#endif // RUNNER_H
