#ifndef OSC_H
#define OSC_H

#include<QObject>
#include"basedevice.h"
#include <QApplication>

#define DEBUG 0
static int BUFLEN=256;
static int IDNLEN=56;
class OSC : public BaseDevice
{
    Q_OBJECT
public:
    OSC();
    ~OSC();
    void SetCmds(QStringList);
private:
    QString m_addr;
    QStringList m_cmds;
    enum MODE{
        EDGE=0,
        GLITch=1,
        PATTern=2,
        STATe,
        DELay,
        TIMeout,
        TV,
        COMM,
        RUNT,
        SEQuence,
        SHOLd,
        TRANsition,
        WINDow,
        PWIDth,
        ADVanced,
        SBUS1,
        SBUS2,
        SBUS3,
        SBUS4

    };

public slots:
    void init();
    void init(QString addr);
    void setAddress(QString addr);
    void Run();
    bool Read(uint count,QString&);
    bool Write(QString command,QString&);
    bool getBandWidth(int&,QString &ret); //:ACQuire:BANDwidth?
    bool getMaxBandWidth(int&,QString &ret); //:ACQuire:BANDwidth:FRAMe?
    bool measureVmax(int channel,QString &ret); //:MEASure:VMAX CHANnel1;*OPC?
    bool measureVmin(int channel,QString &ret);//:MEASure:VMIN CHANnel1;*OPC?
    bool measureVpp(int channel,QString &ret);//:MEASure:VPP CHANnel1;*OPC?
    bool setMark(QString title,QString &ret);//:DISPlay:BOOKmark1:SET NONE,"Vcc";*OPC?
    bool SaveScreenShoot(QString filename,bool isInvert,QString& ret);//:DISK:SAVE:IMAGe 'c:\123' , JPEG,SCR,ON,INVERT;*OPC?
    bool getMode(int&,QString& ret);//:ACQuire:MODE?
    bool setMode(int,QString& retE); //:TRIGger:MODE EDGE;
    bool getMaxAmp(int &,QString&);//:MEASure:VMAX?
    bool setTimeScale(double ,QString&);//:TIMebase:SCALE 5e-6;*OPC?
    bool getScale(int channel,double& scale, QString&);//:CHANnel<N>:SCALe?
    bool setAmp(int channel,double amp,QString& ret);//:CHANnel1:SCALe 2E-3;*OPC?
    bool getAmp(int channel,double& amp,QString& ret);//:CHANnel<N>:SCALe?



    void AttributesOSC(void ){
        ViSession vi = GetSesion();
        viSetAttribute(vi,VI_ATTR_SUPPRESS_END_EN, VI_FALSE);
    }
    //    QString IDN(){

    //            WriteCommand("*idn?\n");
    //            int iret=0;
    //            return(ReadDevice(IDNLEN));
    //        }

    //        QString RST(){
    //            return (WriteCommand("*rst\n"));
    //        }
    //        QString WAI(){
    //            return (WriteCommand("*wai\n"));
    //        }

public:
private:


signals:
    void ShowMsg(QString msg);
    void finished(int);
    void changeSelection(int);
    void setvendor(QString);

};

#endif // OSC_H
