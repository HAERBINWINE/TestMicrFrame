#include <QDebug>
#include "devices.h"

REGISTERCLASS(Devices,(Devices::getParemeterList()))
Devices::Devices()
{
    className="Devices";

}
Devices::~Devices()
{

}

void Devices::start()
{
    m_adb=BaseADB::getADB();
    QString Devices;
    m_adb->devices(Devices);
    qDebug()<<Devices;

    emit ShowMsg(Devices);

}
void Devices::setParameter(int i, QStringList parameters)
{

}

QStringList Devices::getParemeterList()
{
    return QStringList();
}
