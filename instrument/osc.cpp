#include "osc.h"
#include <qdebug.h>
#include<QThread>


#ifdef WIN32
#include<windows.h>
#endif

OSC::OSC()
{

}
OSC::~OSC()
{

}
void OSC::setAddress(QString addr)
{
    m_addr=addr;
}

//"TCPIP0::192.168.70.42::5555::SOCKET" address
void OSC::init()
{
    if (m_addr.size()<13)
    {
        qDebug() <<tr("Invalid Ip:")<<m_addr;
        emit ShowMsg(tr("Invalid Ip:")+m_addr);
        return;
    }
    ConnectDevice(m_addr);
    QString ret;
    if(!IDN(ret))
    {
        emit ShowMsg(ret);
    }
    emit setvendor(ret);

    if(RST(ret))
    {
        emit ShowMsg(ret);
    }
#ifdef WIN32

    Sleep(3);
#elif
    sleep(3);
#endif



}
bool  OSC::Read(uint count,QString& ret)
{
    int iret=0;
    if(!ReadDevice(count,ret))
    {
        return false;
    }
    return true;
}
bool  OSC::Write(QString command,QString& ret)
{
    if(!WriteCommand(command,ret))
    {
        return false;
    }
    //emit ShowMsg(result);
    return true;
}
void OSC::init(QString addr)
{
    if (addr.size()<13)
    {
        qDebug() <<tr("Invalid Ip:")<<addr;
        emit ShowMsg(tr("Invalid Ip:")+addr);
        return;
    }
    m_addr=addr;
    ConnectDevice(addr);
    QString ret;
    if(!IDN(ret))
    {
        emit ShowMsg(ret);
    }
    emit setvendor(ret);

    if(RST(ret))
    {
        emit ShowMsg(ret);
    }
#ifdef WIN32

    Sleep(3);
#elif
    sleep(3);
#endif



}
void OSC::SetCmds(QStringList cmds)
{
    m_cmds=cmds;
}

void OSC::Run()
{
    if (m_cmds.size()==0)
    {
        emit finished(-1);
        return;
    }
    QString result;
#if DEBUG
    for (auto cmd:m_cmds)
    {
        emit ShowMsg("Send Msg: "+cmd);
        emit ShowMsg("Recvd Msg:");
    }
#else
    int i=0;
    for (auto cmd:m_cmds)
    {
        emit changeSelection(i);
        Write(cmd,result);
        emit ShowMsg("-->>"+cmd);
        Read(BUFLEN,result);
        emit ShowMsg("<<--"+result);
        i++;
    }
#endif
    moveToThread(qApp->thread());
    emit finished(0);
}

bool  OSC::getBandWidth(int& bandwith,QString &ret) //:ACQuire:BANDwidth?
{
    if(!WriteCommand(":ACQuire:BANDwidth?\n",ret))
    {
        return false;
    }
    if(!ReadDevice(20,ret))
    {
        return false;
    }
    bandwith=ret.toInt();
    return true;

}

bool  OSC::getMaxBandWidth(int& bandwith,QString &ret) //:ACQuire:BANDwidth:FRAMe?
{
    if(!WriteCommand(":ACQuire:BANDwidth:FRAMe?\n",ret))
    {
        return false;
    }
    if(!ReadDevice(20,ret))
    {
        return false;
    }
    bandwith=ret.toInt();
    return true;

}

bool  OSC::measureVmax(int channel,QString& ret) //:MEASure:VMAX CHANnel1;*OPC?
{
    QString cmd=":MEASure:VMAX CHANnel"+QString(channel)+";\n";
    if(!WriteCommand(cmd,ret))
    {
        return false;
    }
    return true;

}

bool  OSC::measureVmin(int channel,QString& ret)//:MEASure:VMIN CHANnel1;*OPC?
{
    QString cmd=":MEASure:VMIN CHANnel"+QString(channel)+";\n";
    if(!WriteCommand(cmd,ret))
    {
        return false;
    }
    return true;

}

bool  OSC::measureVpp(int channel,QString& ret)//:MEASure:VPP CHANnel1;*OPC?
{
    QString cmd=":MEASure:VPP CHANnel"+QString(channel)+";\n";
    if(!WriteCommand(cmd,ret))
    {
        return false;
    }
    return true;

}

bool  OSC::setMark(QString title,QString &ret)//:DISPlay:BOOKmark1:SET NONE,"Vcc";*OPC?
{
    QString cmd=QString(":DISPlay:BOOKmark1:SET NONE,\"%1\";\n").arg(title);
    if(!WriteCommand(cmd,ret))
    {
        return false;
    }
    return true;

}

bool  OSC::SaveScreenShoot(QString filename,bool isInvert,QString& ret)//:DISK:SAVE:IMAGe 'c:\123' , JPEG,SCR,ON,INVERT;*OPC?
{
    QString cmd;
    if(isInvert)
    {
        cmd=":DISK:SAVE:IMAGe '"+filename+"' , JPEG,SCR,ON,INVERT;\n";
    }
    else
    {
        cmd=":DISK:SAVE:IMAGe '"+filename+"' , JPEG,SCR,ON;\n";
    }
    if(!WriteCommand(cmd,ret,6000))
    {
        return false;
    }
    return true;

}

bool  OSC::getMode(int& mode,QString& ret)//:ACQuire:MODE?
{

    if(!WriteCommand(":ACQuire:MODE?\n",ret))
    {
        return false;
    }
    if(!ReadDevice(20,ret))
    {
        return false;
    }
    mode=ret.toInt();
    return true;
}

bool  OSC::setMode(int mode,QString& ret) //:TRIGger:MODE EDGE;
{
    QString cmd;
    switch(mode)
    {
    case  0:
        cmd=":TRIGger:MODE EDGE;\n";
        break;
    case  1:
        cmd=":TRIGger:MODE GLITch;\n";
        break;
    case  2:
        cmd=":TRIGger:MODE PATTern;\n";
        break;
    case  3:
        cmd=":TRIGger:MODE STATe;\n";
        break;
    case  4:
        cmd=":TRIGger:MODE DELay;\n";
        break;
    case  5:
        cmd=":TRIGger:MODE TIMeout;\n";
        break;
    case  6:
        cmd=":TRIGger:MODE TV;\n";
        break;
    case  7:
        cmd=":TRIGger:MODE COMM;\n";
        break;
    case  8:
        cmd=":TRIGger:MODE RUNT;\n";
        break;
    case  9:
        cmd=":TRIGger:MODE SEQuence;\n";
        break;
    case  10:
        cmd=":TRIGger:MODE SHOLd;\n";
        break;
    case  11:
        cmd=":TRIGger:MODE TRANsition;\n";
        break;
    case  12:
        cmd=":TRIGger:MODE WINDow;\n";
        break;
    case  13:
        cmd=":TRIGger:MODE PWIDth;\n";
        break;
    case  14:
        cmd=":TRIGger:MODE ADVanced;\n";
        break;
    case  15:
        cmd=":TRIGger:MODE SBUS1;\n";
        break;
    case  16:
        cmd=":TRIGger:MODE SBUS2;\n";
        break;
    case  17:
        cmd=":TRIGger:MODE SBUS3;\n";
        break;
    case  18:
        cmd=":TRIGger:MODE SBUS4;\n";
        break;
    default:
        ret="Unsupported Acquire Mode!\n";
        return false;

    }
    if(!WriteCommand(cmd,ret))
    {
        return false;
    }
}

bool  OSC::getMaxAmp(int & amp,QString& ret)//:MEASure:VMAX?
{
    if(!WriteCommand(":MEASure:VMAX?\n",ret))
    {
        return false;
    }
    if(!ReadDevice(20,ret))
    {
        return false;
    }
    amp=ret.toInt();
    return true;
}

bool  OSC::setTimeScale(double  scale,QString& ret)//:TIMebase:SCALE 5e-6;*OPC?
{
    QString cmd=QString(":TIMebase:SCALE %1;\n").arg(scale);
    if(!WriteCommand(cmd,ret))
    {
        return false;
    }
    return true;
}

bool  OSC::getScale(int channel,double& scale, QString& ret)//:CHANnel<N>:SCALe?
{
    QString cmd=QString(":CHANnel%1>:SCALe?;\n").arg(channel);
    if(!WriteCommand(cmd,ret))
    {
        return false;
    }
    if(!ReadDevice(20,ret))
    {
        return false;
    }
    scale=ret.toInt();
    return true;
}

bool  OSC::setAmp(int channel,double amp,QString& ret)//:CHANnel1:SCALe 2E-3;*OPC?
{
    QString cmd=QString(":CHANnel%1:SCALe %2;\n").arg(channel,amp);
    if(!WriteCommand(cmd,ret))
    {
        return false;
    }
    return true;

}

bool  OSC::getAmp(int channel,double& amp,QString& ret)//:CHANnel<N>:SCALe?
{
    QString cmd=QString("CHANnel%1:SCALe?;\n").arg(channel);
    if(!WriteCommand(cmd,ret))
    {
        return false;
    }
    if(!ReadDevice(20,ret))
    {
        return false;
    }
    amp=ret.toInt();
    return true;
}



