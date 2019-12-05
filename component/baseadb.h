#ifndef BASEADB_H
#define BASEADB_H
#include "base.h"
#include "device/qadb.h"

class BaseADB : public Base
{
    Q_OBJECT
public:
    BaseADB();
    virtual ~BaseADB(){
        BaseADB::DecreaseRefCnt();
        if(!BaseADB::getRefCnt())
        {
            delete m_adb;
            m_adb=new QAdb();
        }
    }
    QString GetClassName() const{return className;}




    static int getRefCnt()
    {
        return BaseADB::reference_cnt;
    }

    static void IncreaseRefCnt()
    {
        BaseADB::reference_cnt++;
    }
    static void DecreaseRefCnt()
    {
        BaseADB::reference_cnt--;
    }
    static QAdb* getADB()
    {
        return BaseADB::m_adb;
    }

private:
    static QAdb* m_adb;
    static int reference_cnt;
public:
    QString className;
signals:
    void ShowMsg(QString msg);

};

#endif // BASEADB_H
