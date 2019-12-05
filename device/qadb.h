#ifndef QADB_H
#define QADB_H

#include <QObject>
#include <QtCore/QProcess>
#include <QThread>
#include <QMutex>
#include <QtGlobal>
#ifdef Q_OS_WIN32
// win
static const QString SepSimbol="\\";
static const QString NextSimbol="\r\n";
#else
static const QString SepSimbol="/";
static const QString NextSimbol="\r\n";
#endif

class QAdb:public QObject
{
    Q_OBJECT
public:
    QAdb();
    QAdb(QString SN);
    ~QAdb();
    bool devices(QString& devices);
    bool push(QString from,QString dst);
    bool pull(QString from,QString dst);
    bool reboot();
    bool shell_write(QString);
    bool shell_read(QString&);
    bool shell_writeThenread(QString,QString&);


private:
    QString m_SN;
    QProcess *m_shell_process;
    QMutex m_pull_mutex;
    QString m_response;
    enum ADB_EXEC_RESULT {
            AER_SUCCESS_START,
            AER_ERROR_START,
            AER_SUCCESS_EXEC,
            AER_ERROR_EXEC,
            AER_ERROR_MISSING_BINARY,
        };


private:
    bool executeCmd(QStringList);
    bool startshell();
    bool excuteCmd_sync(QStringList Args,QString &resp);

private slots:
    void batchErr(QProcess::ProcessError);

    void Finished(int,QProcess::ExitStatus);
    //void Unlock(QMutex mutex);
    void pull_exit();

signals:
    //void Unlock_sig(QMutex mutex);
    void finishShell();
};

#endif // QADB_H
