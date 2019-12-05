#ifndef DEVICES_H
#define DEVICES_H
#include<QObject>
#include"baseadb.h"

class Devices : public BaseADB
{
public:
    Devices();
    ~Devices();
    void start();
    void setParameter(int i,QStringList);
    static QStringList getParemeterList();
private:
    QAdb *m_adb;

};

#endif // DEVICES_H
