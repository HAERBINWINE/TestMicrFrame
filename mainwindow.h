#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "./instrument/osc.h"
#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTableWidgetItem>
#include <QModelIndex>
#include <QThread>
#include<QComboBox>
#include "runner.h"
#include <map>
#include<QSignalMapper>
#include<QTreeWidgetItem>
#include"ui/treeitem.h"
#include"ui/treemodel.h"
#include<QVector>
#include<QPair>
#include "3rdparty/rapidjson/document.h"
#include "3rdparty/rapidjson/writer.h"
#include "3rdparty/rapidjson/stringbuffer.h"
#include "ui/mydelegate.h"

using namespace rapidjson;

static const int MAXCOLUMn=4;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    OSC m_osc;
    bool m_connected;
    Runner run;
    std::map <QString,QStringList> ClassNames;
     QSignalMapper* signalMapper;
     Document m_document;
     MyDelegate* delegate;
private:
    void initSignals();
    void initUis();    
    void initVariables();
    void ReadFile(QString);

public slots:
    void showMsg(QString);
    void Init();
    void ReadFile();
    void SelectFile();
    void Run();
    void changeSelection(int);
    void finished(int);
    void setVendor(QString vendorstr);
    void AddItem();
    void ChangeParemeters(int index);
    void InsertChild(QVariant title=QVariant("[No data]"),QVariant discription=QVariant("[No data]"));
    void SetParameters(QString);
    void SetParameters(QWidget* wgt);
    void SaveFile();
    void SaveJson(QString);
    void OpenJson(QString);
    void RemoveRow();
signals:
    void SendChangeSignals(QModelIndex,QAbstractItemModel*);

};

#endif // MAINWINDOW_H
