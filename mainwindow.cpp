#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include<QStandardItemModel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initVariables();
    initUis();
    initSignals();

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
    ClassNames=run.GetRegisteredList();
}
void MainWindow::initSignals()
{

    signalMapper= new QSignalMapper(this);
    connect(&run,SIGNAL(ShowMsg(QString)),this,SLOT(showMsg(QString)));
    connect(ui->open_btn,SIGNAL(clicked()),this,SLOT(SelectFile()));
    connect(ui->run_btn,SIGNAL(clicked()),this,SLOT(Run()));
    connect(&run,SIGNAL(setvendor(QString)),this,SLOT(setVendor(QString)));
    connect(ui->add_btn,SIGNAL(clicked()),this,SLOT(AddItem()));
    connect(ui->save_btn,SIGNAL(clicked(bool)),this,SLOT(SaveFile()));
    connect(ui->del_btn,SIGNAL(clicked(bool)),this,SLOT(RemoveRow()));

}

void MainWindow::initUis()
{
    //ui->run_btn->setDisabled(true);
    this->setWindowTitle("Xconnect");
    ui->file->setAcceptDrops(true);


    this->ui->content->setStyleSheet("QtreeWidget{background-color:rgb(255,255,255);font:font(\"Microsoft YaHei\")}");//
    QStringList headers;
    headers << tr("Title") << tr("Description");

    TreeModel *model = new TreeModel(headers, "");

    ui->content->setModel(model);
    delegate = new MyDelegate;
    connect(delegate,SIGNAL(closeEditor(QWidget*,QAbstractItemDelegate::EndEditHint)),this,SLOT(SetParameters(QWidget*)));
    connect(delegate->signalMapper,SIGNAL(mapped(QString)),this,SLOT(SetParameters(QString)));
    QStringList tem;
    for(auto item :ClassNames)
    {
        tem.append(item.first);
    }
    delegate->setOptionalData(tem);
    ui->content->setItemDelegate(delegate);


    QStringList header;
    header<<"Item"<<"arg1"<<"arg2"<<"arg3";



}
void MainWindow::SetParameters(QString paList)
{
    QAbstractItemModel *model =ui->content->model();
    QStringList parames=paList.split("$");
    QModelIndex child = model->index(parames.at(1).toInt(), 1);
    model->setData(child,parames.at(0)+" component " , Qt::EditRole);
}
void MainWindow::SetParameters(QWidget* wgt)
{
    QComboBox* comb=(QComboBox*)wgt;
    QStandardItemModel  *model =static_cast<QStandardItemModel *>(ui->content->model());
    QString cur_compName=comb->currentText();
    qDebug()<<comb->currentText();
    QRect rect=wgt->contentsRect();
    //QModelIndex index=ui->content->indexAt(rect.center());
    QModelIndex index = ui->content->selectionModel()->currentIndex();
    int rcnt=model->rowCount(index);
    do
    {
        if(!model->removeRow(0,index))
        {break;}
    }while(rcnt--);
    QStringList aaa;
//    foreach (auto item, ClassNames[cur_compName]) {
//        InsertChild(QVariant(item),QVariant(item));
//    }
    for(int i=ClassNames[cur_compName].size()-1;i>=0;i--)
    {
        InsertChild(QVariant(ClassNames[cur_compName].at(i)),ClassNames[cur_compName].at(i));
    }


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
        //QString addr="TCPIP0::"+ui->Ip->text()+"::"+ui->port->text()+"::SOCKET";
        //m_osc.init(addr);

        if(m_osc.connected()||DEBUG)
        {
            ui->run_btn->setDisabled(false);
            // ui->connect_btn->setText("Disconnect");
            m_connected=true;        }
    }
    else
    {

        m_osc.DisconnectDevice();
        ui->run_btn->setDisabled(true);
        //ui->connect_btn->setText("Connect");
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
    file.setNameFilter(tr("Text Files(*.json)"));
    if(file.exec()==QDialog::Accepted)
    {
        QString filename(file.selectedFiles()[0]);
        ui->file->setText(filename);
        OpenJson(filename);
    }
}
void MainWindow::ReadFile()
{



}

void MainWindow::AddItem()
{
    //QModelIndex index = ui->content->selectionModel()->currentIndex();
    //ui->content->
    QAbstractItemModel *model = ui->content->model();
    int currentNod=model->rowCount();
    QModelIndex index=model->index(currentNod-1,0);
    //ui->content->indexAt()


    if (!model->insertRow(index.row()+1, index.parent()))
        return;

    QString default_String;
    QStringList default_Parameter;
    for(auto item :ClassNames)
    {
        default_String=item.first;
        default_Parameter=item.second;
        break;
    }


    QModelIndex child = model->index(index.row()+1, 0, index.parent());
    model->setData(child, QVariant(default_String), Qt::EditRole);
    child = model->index(index.row()+1, 1, index.parent());
    model->setData(child, QVariant(default_String+" component "), Qt::EditRole);

    ui->content->selectionModel()->setCurrentIndex(model->index(index.row()+1, 0, index.parent()),
                                                   QItemSelectionModel::ClearAndSelect);
    for(int i=default_Parameter.size()-1;i>=0;i--)
    {
        InsertChild(default_Parameter.at(i),default_Parameter.at(i));
    }
    connect(signalMapper, SIGNAL(mapped(const int &)),
            this, SLOT(ChangeParemeters(const int )));

    //ui->content->expandAll();
    ui->content->expand(model->index(index.row()+1,0,index.parent()));
    for (int column = 0; column < model->columnCount(); ++column)
        ui->content->resizeColumnToContents(column);
    ui->content->show();
}

void MainWindow::InsertChild(QVariant title,QVariant discription)
{

    QModelIndex index=ui->content->selectionModel()->currentIndex();
    QAbstractItemModel *model = ui->content->model();
    if (model->columnCount(index) == 0) {
        if (!model->insertColumn(0, index))
            return;
    }

    if (!model->insertRow(0, index))
        return;


        QModelIndex child = model->index(0, 0, index);
        QModelIndex child_discription = model->index(0, 1, index);
        model->setData(child, title, Qt::EditRole);
        model->setData(child_discription,discription,Qt::EditRole);
        if (!model->headerData(0, Qt::Horizontal).isValid())
            model->setHeaderData(0, Qt::Horizontal, QVariant("[No header]"), Qt::EditRole);
        if (!model->headerData(1, Qt::Horizontal).isValid())
            model->setHeaderData(1, Qt::Horizontal, QVariant("[No header]"), Qt::EditRole);


}
void MainWindow::ChangeParemeters(int index)
{

}
void MainWindow::Run()
{
    QAbstractItemModel *model = ui->content->model();
    if(model->rowCount()==0)
    {
        QMessageBox message(QMessageBox::NoIcon, "Err","No Valid Phrases" );
        message.exec();
        return;
    }

    //QModelIndex index=ui->content->selectionModel()->currentIndex();
    QVector<QPair<QString,QStringList>> cmds;
    for(int i=0;i<model->rowCount();i++)
    {
        QStringList parameters;
        QModelIndex idx=model->index(i,0);
        QMap<int,QVariant> mmmmmp=model->itemData(idx);
        int rcnt=idx.model()->rowCount(idx);
        for(int j=0;j<rcnt;j++)
        {
            parameters.append(model->index(j,1,idx).data().toString());
        }
        QPair<QString,QStringList> tempair(idx.data().toString(),parameters);

        cmds.push_back(tempair);
    }
    run.SetParametes(cmds);
    //m_osc.SetCmds(cmds);
    QThread * thread=new QThread();
    run.moveToThread(thread);

    connect(&run,SIGNAL(changeSelection(int)),this,SLOT(changeSelection(int)));


    connect(thread,SIGNAL(started()),&run,SLOT(Start()));
    connect(&run,SIGNAL(finished(int)),thread,SLOT(quit()));
    connect(&run,SIGNAL(finished(int)),this,SLOT(finished(int)));
    connect(thread,SIGNAL(finished()),thread,SLOT(deleteLater()));//😱
    ui->run_btn->setDisabled(true);
    thread->start();





}
void MainWindow::changeSelection(int index)
{
    QAbstractItemModel *model = ui->content->model();
    QModelIndex selIndex = model->index(index,0);
    ui->content->setCurrentIndex(selIndex);


}
void MainWindow::finished(int retcode)
{
    ui->run_btn->setDisabled(false);
}
void MainWindow::setVendor(QString vendorstr)
{
    this->setWindowTitle(vendorstr);
}
void MainWindow::SaveFile()
{
    QFileDialog file(this);
    file.setWindowTitle("Save");
    file.setAcceptMode(QFileDialog::AcceptSave);
    file.setFileMode(QFileDialog::ExistingFile);
    file.setViewMode(QFileDialog::Detail);
    file.setDirectory(".");
    file.setNameFilter(tr("Json Files(*.json)"));
    if(file.exec()==QDialog::Accepted)
    {
        QString filename(file.selectedFiles()[0]);
        ui->file->setText(filename);
        SaveJson(filename);
    }
}
void MainWindow::SaveJson(QString filename)
{
    rapidjson::StringBuffer buf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buf);
    writer.StartObject();

    QAbstractItemModel *model = ui->content->model();
    for(int i=0;i<model->rowCount();i++)
    {
        QModelIndex idx=model->index(i,0);
        writer.Key(model->data(idx).toString().toStdString().data());
        //Value parameters(kObjectType);
        writer.StartObject();
        for(int j=0;j<model->rowCount(idx);j++)
        {
            writer.Key(model->data(model->index(j,0,idx)).toString().toStdString().data());
            writer.String(model->data(model->index(j,1,idx)).toString().toStdString().data());
            //parameters.AddMember(model->data(model->index(j,0,idx)).toString(),model->index(j,1,idx)).toString(),writer.);
        }
        writer.EndObject();
    }
    writer.EndObject();
    QString json_content(buf.GetString());
    QFile file;
    file.setFileName(filename);
    file.open(QIODevice::WriteOnly|QIODevice::Text);
    file.write(json_content.toUtf8());
    file.flush();
    file.close();
}

void MainWindow::RemoveRow()
{
    QModelIndex index = ui->content->selectionModel()->currentIndex();
    if(index.row()==-1)
    {return;}
    while(index.parent().column()!=-1)
    {index=index.parent();}
    QAbstractItemModel *model = ui->content->model();
    model->removeRow(index.row(), index.parent());
}
void MainWindow::OpenJson(QString filename)
{
    QAbstractItemModel *model = ui->content->model();
    if(model->hasChildren())
    {
        model->removeRows(0,model->rowCount());
    }
    //QModelIndex selIndex = ui->content->rootIndex();
    QModelIndex selIndex = model->index(0,0);

    QFile file;
    file.setFileName(filename);
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QString json_content(file.readAll());
    Document doc;
    doc.Parse(json_content.toUtf8());
    qDebug()<<json_content;
    if(doc.HasParseError())
    {
        return;
    }
    int i=0;
    for (rapidjson::Value::ConstMemberIterator iter = doc.MemberBegin(); iter != doc.MemberEnd(); ++iter)
        // {		qDebug()<<QString("iter json name: %1, type: ").arg(iter->name.GetString())<<iter->value.GetType();	}
    {
        QString name(iter->name.GetString());
        qDebug()<<tr("ComponentName:")<<name;
        AddItem();
        QModelIndex curInd=model->index(i,0,selIndex.parent());
        QStyleOptionViewItem option;
        QWidget* wdt=delegate->createEditor(ui->content,option,curInd);
        QModelIndex curInd_Dis=model->index(i,1,selIndex.parent());


        bool isOk=model->setData(curInd,QVariant(name));
        isOk=model->setData(curInd_Dis,QVariant(name+" component"));

        int rcnt=model->rowCount(curInd);
        do
        {
            if(!model->removeRow(0,curInd))
            {break;}
        }while(rcnt--);

//        foreach (auto item, ClassNames[name]) {
//            InsertChild(QVariant(item));
//        }

        i++;

        if(3==iter->value.GetType())
        {
            for(rapidjson::Value::ConstMemberIterator sub_iter = iter->value.MemberBegin(); sub_iter != iter->value.MemberEnd(); ++sub_iter)
            {
                qDebug()<<tr("Parameters: ")<<sub_iter->name.GetString()<<tr(", value:")<<sub_iter->value.GetString();
                 InsertChild(QVariant(sub_iter->name.GetString()),QVariant(sub_iter->value.GetString()));
            }
        }


    }



}
