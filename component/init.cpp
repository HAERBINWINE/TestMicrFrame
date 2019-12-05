#include "init.h"
#include <QDebug>

#ifdef WIN32
#include<windows.h>
#endif

REGISTERCLASS(Init,(Init::getParemeterList()))
Init::Init()
{
    m_addr="";
    className="Init";
}
Init::~Init()
{

}
void Init::setParameter(int i,QStringList parameters)
{
    //setParameter(int i,...)
    //va_list ap;
    //va_start(ap, i);
    //m_addr=va_arg(ap,QString);
    if(parameters.size()!=2)
    {
        return;
    }
    m_ip=parameters.at(0);
    m_port=parameters.at(1);
    m_addr=QString("TCPIP0::%1::%2::SOCKET").arg(m_ip,m_port);


}
void Init::start()
{
    if (m_addr.size()<13)
    {
        qDebug() <<tr("Invalid Ip:")<<m_addr;
        emit ShowMsg(tr("Invalid Ip:")+m_addr);
        return;
    }
    OSC* m_osc=Base::getOSC();
    m_osc->ConnectDevice(m_addr);
    QString ret;
    if(!m_osc->IDN(ret))
    {
        emit ShowMsg(ret);

    }
    qDebug()<<ret;
    emit ShowMsg(ret);
    emit setvendor(ret);

    if(!m_osc->RST(ret))
    {
        emit ShowMsg(ret);
    }
#ifdef WIN32

    Sleep(3);
#elif
    sleep(3);
#endif
}

QStringList Init::getParemeterList()
{
    return QStringList()<<"IP Adress"<<"Port";
}
