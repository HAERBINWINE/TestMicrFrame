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
signals:

};

#endif // MAINWINDOW_H
