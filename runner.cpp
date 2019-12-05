#include "runner.h"
#include "component/ibase.h"
#include<QApplication>
//#include "component/init.h"
//#include "component/vdd_test.h"
Runner::Runner()
{
    m_cmds.clear();
    //connect()
}

std::map<QString,QStringList> Runner::GetRegisteredList()
{
    return ClassFactory::instance()->ReturnClassNames();
}

void Runner::Start()
{
//    IBase * Init_ = (IBase*)ClassFactory::instance()->CreateItem("Init");
//    Init_->setParameter(1,QString("TCPIP0::127.0.0.1::5025::SOCKET"));
//    Init_->start();
//    IBase * VDD_test_ = (IBase*)ClassFactory::instance()->CreateItem("VDD_test");
//    VDD_test_->start();
//    delete Init_;
//    Init_=NULL;
//    delete VDD_test_;
//    VDD_test_=nullptr;

    QVector<IBase*> classContainers;
    int i=0;
    foreach (auto item, m_cmds) {
        emit changeSelection(i);
        IBase * base=(IBase*)ClassFactory::instance()->CreateItem(item.first);
        connect(base,SIGNAL(ShowMsg(QString)),this,SLOT(SendMsg(QString)));
        base->setParameter(1,item.second);
        emit ShowMsg(QString("Start Component :%1").arg(base->GetClassName()));
        base->start();
        emit ShowMsg(QString("Complete Component :%1").arg(base->GetClassName()));
        classContainers.append(base);
        i++;
    }
    foreach (auto item, classContainers){
        delete item;
        item=nullptr;

    }
    moveToThread(qApp->thread());
    emit finished(1);
}

void  Runner::SetParametes(QVector<QPair<QString,QStringList>> cmds)
{
    m_cmds=cmds;
}

//https://www.cnblogs.com/qiuhongli/p/9019062.html
void Runner::SendMsg(QString msg)
{
    emit ShowMsg(msg);
}
