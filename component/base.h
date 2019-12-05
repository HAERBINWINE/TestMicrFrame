#ifndef BASE_H
#define BASE_H
#include "ibase.h"
#include "factory/registerclass.h"
#include "../instrument/osc.h"


class Base:public IBase
{
    Q_OBJECT
public:
    Base();
    virtual ~Base(){
        Base::DecreaseRefCnt();
        if(!Base::getRefCnt())
        {
            delete m_osc;
            m_osc=new OSC();
        }
    }
    QString GetClassName() override {return className;}




    static int getRefCnt()
    {
        return Base::reference_cnt;
    }

    static void IncreaseRefCnt()
    {
        Base::reference_cnt++;
    }
    static void DecreaseRefCnt()
    {
        Base::reference_cnt--;
    }
    static OSC* getOSC()
    {
        return Base::m_osc;
    }

private:
    static OSC* m_osc;
    static int reference_cnt;
public:
    QString className;
signals:
    void ShowMsg(QString msg);
    void finished(int);
    void changeSelection(int);
    void setvendor(QString);
public slots:

};




#endif // BASE_H

