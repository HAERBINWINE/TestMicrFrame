#ifndef INIT_H
#define INIT_H

#include <QObject>
#include "base.h"
class Init : public Base
{
public:
    Init();
    ~Init();
    void start();
    void setParameter(int i,QStringList);
    static QStringList getParemeterList();
private:
    QString m_addr;
    QString m_port;
    QString m_ip;
};

#endif // INIT_H
