#include "vdd_test.h"
#include <QDebug>

REGISTERCLASS(VDD_test,VDD_test::getParemeterList())
VDD_test::VDD_test()
{
    className="VDD_test";
}

VDD_test::~VDD_test()
{

}

void VDD_test::setParameter(int i, QStringList parameters)
{
    if(parameters.size()!=3)
    {
        return;
    }
    m_ampl=parameters.at(0).toDouble();
    m_timescale=parameters.at(1).toDouble();
    m_savepath=parameters.at(2);


}

QStringList VDD_test::getParemeterList()
{
    return QStringList()<<"ampl"<<"timescale"<<"savepath";
}
void VDD_test::start()
{
    OSC* m_osc=Base::getOSC();
    if(!m_osc->connected())
    {
        emit ShowMsg("Connected to device failed\n");
        qDebug()<<"Connected to device failed\n";
        return;
    }
    int bandwt=0;
    QString ret;
    if(!m_osc->getBandWidth(bandwt,ret))
    {
        emit ShowMsg(ret);
        qDebug()<<ret;
        return ;
    }
    if(!m_osc->getMaxAmp(bandwt,ret))
    {
        emit ShowMsg(ret);
        return ;
    }
    int mode;
    if(!m_osc->getMode(mode,ret))
    {
        emit ShowMsg(ret);
        return;
    }
    if(!m_osc->setMode(0,ret))
    {
        emit ShowMsg(ret);
        return;
    }
    if(!m_osc->setTimeScale(m_timescale,ret))
    {
        emit ShowMsg(ret);
        return;
    }
    double scale;
    if(!m_osc->getScale(1,scale,ret))
    {
        emit ShowMsg(ret);
        return;
    }
    double amp;
    if(!m_osc->getAmp(1,amp,ret))
    {
        emit ShowMsg(ret);
        return;
    }
    if(!m_osc->setAmp(1,m_ampl,ret))
    {   emit ShowMsg(ret);
        return;
    }
    if(!m_osc->setMark("VDD",ret))
    {
        emit ShowMsg(ret);
        return;
    }
    if(!m_osc->measureVmax(1,ret))
    {
        emit ShowMsg(ret);
        return;
    }
    if(!m_osc->measureVmin(1,ret))
    {
        emit ShowMsg(ret);
        return;
    }
    if(!m_osc->measureVpp(1,ret))
    {
        emit ShowMsg(ret);
        return;
    }
    if(!m_osc->SaveScreenShoot(m_savepath,true,ret))
    {
        emit ShowMsg(ret);
        return;
    }
}
