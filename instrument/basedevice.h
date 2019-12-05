/*==================================================================*/
/*!
    \brief Базовый класс связки с приборами через библиотеку visa
    \version 1.0
    \warning Данный класс создан только в учебных целях

    Обычный базовый класс для работы с приборами.
    Все методы возвращают строку. Если ошибок нет - нулевую строку.
*/
/*==================================================================*/
#ifndef BASEDEVICE_H
#define BASEDEVICE_H

#ifndef LINUXBASE


#include <visa.h>
#include <visatype.h>
#include <memory.h>
#include <QString>
#include <QMap>
#include <QByteArray>
#include <QObject>
#include <sys/time.h>


static const int default_timeout=3000; //set default timeout value to 2000 ms
static const int default_terminate_char=0x00; //set default terminate char to '\0'
class BaseDevice:public QObject
{
    Q_OBJECT
public:
/*==================================================================*/

    BaseDevice();
    ~BaseDevice();
/*==================================================================*/

    enum typeConnect{
      USB,
      TCPIP,
      GPIB
    }tC;

    QString ConnectDevice( typeConnect tC , QString typeAdder );
    bool connected();
/*==================================================================*/


    QString ConnectDevice(QString Connect );

    QString DisconnectDevice( );


///Базовые функции. Возвращают  QString. Ежели строка пустая- Успешное выполнение команды, нет- читаем.

    bool IDN(QString&);
    bool RST(QString&);
    bool TST(QString&);
    bool WAI(QString&);
    bool OPC(QString&);
    bool BUSY(QString&);

    //Функция получения номера сессии
    ViSession GetSesion(){
        return(vi);
    }


protected:

    bool flag_connect;  ///<    Флаг проверки подключения прибора
/*==================================================================*/
/*!  \brief
 Метод поиска описания ошибки. Ежели такой нет, то на выходе будет номер.
\param [in] status(переменная типа ViStatus)
\return Строку QString с номером ошибки.
*/

    QString ErrorFunction(ViStatus status);

/*==================================================================*/
/*!  \brief
 Универсальная функция для записи в прибор. Использует viWrite.
\param [in] command - строковая команда, согласно документации на прибор
\return Строку QString. Ежели строка пустая- Успешное выполнение команды, нет- читаем.
*/

    bool WriteCommand(QString command,QString&,int tmo=default_timeout);

/*==================================================================*/
/*!  \brief
        Универсальная функция для чтения из прибора. Использует viRead.
\param  [in] count - Количество символов для чтения
\return Строку QString. Ежели строка пустая- Успеш,kzное выполнение команды, нет- читаем.
*/

    bool ReadDevice(  uint count, QString&,int tmo=default_timeout);
/*==================================================================*/
/*!  \brief
        Универсальная функция для чтения из прибора. Использует viRead.
\param  [in] count - Количество символов для чтения
\return QByteArray - (-1) == Не выполнена функция ConnectDevice
                   - (-2) == Ошибка не определена
*/
QByteArray ReadDevice_Array( uint count,int tmo=default_timeout);



/*==================================================================*/
private:


/*types/*============================================================*/
    ViSession	rm, vi;
    ViStatus	status;
    ViUInt32	retCnt;
    QMap<int, QString> ErrorList;
};

#endif

#ifdef LINUXBASE

#include "QDebug"

#include <../../Загрузки/vxi11_1.10/vxi11_user.h>

#define BUF_LEN 100000

class BaseDevice
{

CLINK* link_;
bool flagConnect_;
int ret_;
//нужен для закрытия соединения
QString deviceIp;
public:
BaseDevice();
~BaseDevice();
CLINK* getLink(){
return link_;
}
//обычно deviceName = inst0
//ежели возвращаемое значение != 0, то ошибка
QString connectDevice( QString ip, QString deviceName);
QString connectDevice(QString ip);
QString disconnectDevice();

//Шаблонные базовые команды
QString IDN();
QString RST();
QString TST();
QString WAI();
QString OPC();
QString BUSY();

QString writeCommand(QString command);
QString readDevice(const int count); //сколько символов принять
QString writeAndRead(QString command, const int count);
void readDevice_Array(const int count, QByteArray& readData);
};


#endif

#endif // BASEDEVICE_H
