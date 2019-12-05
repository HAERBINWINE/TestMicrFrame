#ifndef IBASE_H
#define IBASE_H

#include <QObject>
#include <stdarg.h>
#include <QStringList>


#define DEBUG 0

class IBase : public QObject
{
    Q_OBJECT
public:
    //explicit IBase(QObject *parent = nullptr){}
    virtual void start()=0;
    virtual void setParameter(int i,QStringList)=0;
    //virtual QStringList getParemeterList() const=0;
    //virtual ~IBase()=0;
    virtual QString GetClassName()=0;
signals:
    void ShowMsg(QString msg);
};

#endif // IBASE_H
