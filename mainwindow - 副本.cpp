#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initSignals();
    initUis();
    initVariables();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete signalMapper;
    signalMapper=nullptr;
}

void MainWindow::initVariables()
{
    m_connected=false;
}
void MainWindow::initSignals()
{

    signalMapper= new QSignalMapper(this);
    connect(ui->connect_btn,SIGNAL(clicked()),this,SLOT(Init()));
    connect(&m_osc,SIGNAL(ShowMsg(QString)),this,SLOT(showMsg(QString)));
    connect(ui->open_btn,SIGNAL(clicked()),this,SLOT(SelectFile()));
    connect(ui->run_btn,SIGNAL(clicked()),this,SLOT(Run()));
    connect(&m_osc,SIGNAL(setvendor(QString)),this,SLOT(setVendor(QString)));
    connect(ui->add_btn,SIGNAL(clicked()),this,SLOT(AddItem()));
}
void MainWindow::initUis()
{
    ui->run_btn->setDisabled(true);
    this->setWindowTitle("Xconnect");
    ui->file->setAcceptDrops(true);
    ui->Ip->setText("127.0.0.1");
    ui->port->setText("5025");

    this->ui->content->setStyleSheet("QtableWidget{background-color:rgb(255,255,255);font:font(\"Microsoft YaHei\")}");//
        //ui->tableWidget->setModel(model);
    ui->content->clearSpans();
    //ui->tableWidget->verticalHeader()->hide();
    ui->content->horizontalHeader()->setStretchLastSection(true);
    ui->content->setColumnCount(MAXCOLUMn);
    QStringList header;
    header<<"Item"<<"arg1"<<"arg2"<<"arg3";
    ui->content->setHorizontalHeaderLabels(header);


}

void MainWindow::showMsg(QString msg)
{
    ui->output->append(msg);
    //ui->output->append("\n");
}
void MainWindow::Init()
{
    if(!m_connected)
    {
        QString addr="TCPIP0::"+ui->Ip->text()+"::"+ui->port->text()+"::SOCKET";
        m_osc.init(addr);

        if(m_osc.connected()||DEBUG)
        {
            ui->run_btn->setDisabled(false);
            ui->connect_btn->setText("Disconnect");
            m_connected=true;        }
    }
    else
    {

        m_osc.DisconnectDevice();
        ui->run_btn->setDisabled(true);
        ui->connect_btn->setText("Connect");
        this->setWindowTitle("Xconnect");
        m_connected=false;
    }




}

void MainWindow::SelectFile()
{
    QFileDialog file(this);
    file.setWindowTitle("Open");
    file.setAcceptMode(QFileDialog::AcceptOpen);
    file.setFileMode(QFileDialog::ExistingFile);
    file.setViewMode(QFileDialog::Detail);
    file.setDirectory(".");
    file.setNameFilter(tr("Text Files(*.txt *.log)"));
    if(file.exec()==QDialog::Accepted)
    {
        ui->file->setText(file.selectedFiles()[0]);
        ReadFile();
    }
}
void MainWindow::ReadFile()
{
    QString Filename=ui->file->text();
    if (Filename.length()<1)
    {
        QMessageBox message(QMessageBox::NoIcon, "Attention","File Not valid" );
        message.exec();
        return;
    }

    QFile file;
    file.setFileName(Filename);
    file.open(QFile::ReadOnly);
    char content[512]={'\0'};



}

void MainWindow::AddItem()
{
    int rowcnt=ui->content->rowCount();
    ui->content->insertRow(rowcnt);
    QComboBox* cob=new QComboBox;
    cob->setAcceptDrops(true);
    ClassNames=run.GetRegisteredList();
    for(auto item :ClassNames)
    {
        cob->addItem(item.first);

    }
    //connect(cob,SIGNAL(activated(QString)),this,SLOT(ChangeParemeters(QString)));
    //connect(cob,SIGNAL(currentIndexChanged(QString)))
    connect(cob, SIGNAL(currentIndexChanged(QString)), signalMapper, SLOT(map()));
    signalMapper->setMapping(cob, rowcnt);
    connect(signalMapper, SIGNAL(mapped(const int &)),
             this, SLOT(ChangeParemeters(const int )));

    ui->content->setCellWidget(rowcnt,0,cob);
    ui->content->show();
}
void MainWindow::ChangeParemeters(int index)
{
    //QStringList Params=index.split("-");

    QComboBox* combo=(QComboBox*)ui->content->cellWidget(index, 0);
    QString key=combo->currentText();
    QStringList parlist=ClassNames[key];
    //int row =Params[0].toInt();
    for(int i=0;i<parlist.size();i++)
    {
        ui->content->setItem(index,1+i,new QTableWidgetItem(parlist.at(i)));
    }
    for(int i=parlist.size();i<MAXCOLUMn;i++)
    {
        QTableWidgetItem* twi=new QTableWidgetItem("");
        twi->setFlags(twi->flags() & ~Qt::ItemIsEnabled & ~Qt::ItemIsSelectable);
        ui->content->setItem(index,1+i,twi);

    }
    ui->content->show();
}
void MainWindow::Run()
{
    if(0==0)
    {
        QMessageBox message(QMessageBox::NoIcon, "Err","No Valid Phrases" );
        message.exec();
        return;
    }

    QStringList cmds;
    for(int i=0;i<5;i++)
    {
       // QModelIndex moIndx= m_model->index(i,0);
        //QVariant data=m_model->data(moIndx);
        //cmds.append(data.toString()+'\n');
    }
    m_osc.SetCmds(cmds);
    QThread * thread=new QThread();
    m_osc.moveToThread(thread);

    connect(&m_osc,SIGNAL(changeSelection(int)),this,SLOT(changeSelection(int)));


    connect(thread,SIGNAL(started()),&m_osc,SLOT(Run()));
    connect(&m_osc,SIGNAL(finished(int)),thread,SLOT(quit()));
    connect(&m_osc,SIGNAL(finished(int)),this,SLOT(finished(int)));
    connect(thread,SIGNAL(finished()),thread,SLOT(deleteLater()));//😱
    ui->run_btn->setDisabled(true);
    thread->start();





}
void MainWindow::changeSelection(int index)
{

    //QModelIndex moIndx= m_model->index(index,0);
   // ui->content->clicked(moIndx);
    //ui->content->setCurrentIndex(moIndx);


}
void MainWindow::finished(int retcode)
{
    ui->run_btn->setDisabled(false);
}
void MainWindow::setVendor(QString vendorstr)
{
    this->setWindowTitle(vendorstr);
}
