#include "qadb.h"
#include <QMetaType>
#include <QDebug>
#include <QFileInfo>

QAdb::QAdb()
{
      m_SN.clear();
      m_shell_process=NULL;
      //connect(this,SIGNAL(finishShell(int)),m_shell_process,SLOT(deleteLater()));
}
QAdb::QAdb(QString SN)
{
    m_SN=SN;m_shell_process=NULL;

}

QAdb::~QAdb()
{

    if(m_shell_process!=NULL)
    {

        if(m_shell_process->isOpen())
        {
            //emit(finishShell());
            shell_write("exit");
            m_shell_process->close();
        }
        delete m_shell_process;
        m_shell_process=NULL;
    }
}
bool QAdb::devices(QString &devices)
{
    QStringList Args;
    Args.append("devices");
    return excuteCmd_sync(Args,devices);
}
bool QAdb::excuteCmd_sync(QStringList Args,QString &resp)
{
    QProcess process;
    process.start("adb",Args);
    process.waitForFinished();
    resp=process.readAllStandardOutput();
    QString errmsg=process.readAllStandardError();
    qDebug()<<tr("Msg:")<<resp<<tr("Errmsg:")<<errmsg;
    if (errmsg.size())
    {
        resp=errmsg;
        return false;
    }
    return true;
}

bool QAdb::pull(QString from, QString dst)
{
    QStringList Args;
    //m_pull_mutex.lock();

    if(from.size()<2)
    {
        return false;
    }

    if(m_SN.size())
    {
        Args.append("-s");
        Args.append(m_SN);
    }
    Args.append("pull");
    Args.append(from);
    Args.append(dst);
    QString response;
    QFileInfo file(dst);
    excuteCmd_sync(Args,response);
    if (!file.exists())
    {
        return false;
    }
    return true;
}

void QAdb::pull_exit()
{
    //m_pull_mutex.unlock();
}

bool QAdb::push(QString from, QString dst)
{
    QStringList Args;
    if(from.size()<2)
    {
        return false;
    }
    QFileInfo file(from);
    if(!file.exists())
    {return false;}

    if(m_SN.size())
    {
        Args.append("-s");
        Args.append(m_SN);
    }
    Args.append("push");
    Args.append(from);
    Args.append(dst);
    QString response;
    excuteCmd_sync(Args,response);
    if(response.toLower().contains("permission denied"))
    {
        return false;}
    else if(response.toLower().contains(" no "))
    {
        return false;}
    return true;

}

void QAdb::batchErr(QProcess::ProcessError ecode)
{
    qDebug()<<tr("The exit code is :")<<QString::number(ecode);
    if (ecode<0)
    {

    }
}

void QAdb::Finished(int n,QProcess::ExitStatus ECode)
{
    if(n)
    {
        qDebug()<<tr("The process crashed, exit code is :")<<QString::number(n);
        return;
    }
    qDebug()<<tr("The process exit, code is :")<<QString::number(n);
}

bool QAdb::reboot()
{
    QStringList Args;
    if(m_SN.size())
    {
        Args.append("-s");
        Args.append(m_SN);
    }
    Args.append("reboot");
    return executeCmd(Args);

}

bool QAdb::executeCmd(QStringList Args)
{
    QProcess process;
    int iRet=0;
    iRet=process.execute("adb",Args);
    if(iRet<0)
    {
        return false;
    }
    return true;

}

bool QAdb::startshell()
{
    if (m_shell_process!=NULL)
    {
        if(m_shell_process->isOpen())
        {
            return true;
        }
        m_shell_process=NULL;
    }
    m_shell_process=new QProcess();
    QStringList Args;
    if(m_SN.size())
    {
        Args.append("-s");
        Args.append(m_SN);
    }
    Args.append("shell");
    m_shell_process->setProcessChannelMode(QProcess::MergedChannels);
    qRegisterMetaType<QProcess::ExitStatus>("QProcess::ExitStatus");
    connect(m_shell_process,SIGNAL(error(QProcess::ProcessError)),this,SLOT(batchErr(QProcess::ProcessError)));
    connect(m_shell_process,SIGNAL(finished(int,QProcess::ExitStatus)),this,SLOT(Finished(int,QProcess::ExitStatus)));
    m_shell_process->start("adb",Args);

    return true;
}

bool QAdb::shell_write(QString cmd)
{
    if(m_shell_process==NULL)
    {
        startshell();
    }
    int iRet=m_shell_process->write((cmd+NextSimbol).toLatin1());
    if(iRet<-1)
    {
        return false;
    }
    return true;
}

bool QAdb::shell_read(QString & resp)
{
    resp.clear();
    if(m_shell_process==NULL)
    {
        return false;
    }
    QString temString;
    while(m_shell_process->waitForReadyRead(1000))
    {

        temString=QString::fromUtf8(this->m_shell_process->readAll());
        int i;

        for (i = 0; i < temString.length(); i++)
        {
            if (temString.at(i).unicode() == 13)
                temString[i] = ' ';
            if (temString.at(i).unicode() == 10)
                temString[i] = '\n';
        }

         resp.append(temString);
    }
    //temString.remove(0,temString.indexOf("\n"));
    qDebug()<<tr("mythread QThread::currentThreadId()==")<<QThread::currentThreadId()<<resp;
    return true;
}

bool QAdb::shell_writeThenread(QString cmd, QString &resp)
{
    if(!shell_write(cmd))
    {
        return false;
    }
    if(!shell_read(resp))
    {
        return false;
    }
    //resp=resp.replace(cmd,"");
    return true;
}
