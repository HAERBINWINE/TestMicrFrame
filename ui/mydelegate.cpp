#include "mydelegate.h"
#include <QSpinBox>
#include <QComboBox>
#include <QLineEdit>
MyDelegate::MyDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
    m_optional.clear();
    signalMapper=new QSignalMapper(this);
}

QWidget *MyDelegate::createEditor(QWidget *parent,
                                  const QStyleOptionViewItem & option ,
                                  const QModelIndex & index ) const
{
    if(index.column() == 0&&index.parent().column()==-1) //只对第4列采用此方法编辑
    {
        //QModelIndex xx=;
        QComboBox* box = new QComboBox(parent);
        box->addItems(m_optional);
        connect(box, SIGNAL(currentIndexChanged(QString)), signalMapper, SLOT(map()));
        signalMapper->setMapping(box, box->currentText()+"$"+index.row());
        return box;
    }
    else if(index.column()==0&&index.parent().column()!=-1)
    {
        return nullptr;
    }
    else
    {
        return QStyledItemDelegate::createEditor(parent,option,index);
    }
}


void MyDelegate::setEditorData(QWidget *editor,
                               const QModelIndex &index) const
{
    QString value = index.model()->data(index, Qt::EditRole).toString();
    if(index.column() == 0&&index.parent().column()==-1) //只对第4列采用此方法编辑
    {

        QComboBox* box = static_cast<QComboBox*>(editor);
        box->setCurrentText(value);
    }
    else{
        QStyledItemDelegate::setEditorData(editor,index);

    }
}

void MyDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                              const QModelIndex &index) const
{
    if(index.column() == 0&&index.parent().column()==-1) //只对第4列采用此方法编辑
    {
        QComboBox* box = static_cast<QComboBox*>(editor);
        model->setData(index, box->currentText(), Qt::EditRole);
        model->setData(model->index(index.row(),index.column()+1,index.parent()),box->currentText()+" component ",Qt::EditRole);
    }
    else
    {
        QLineEdit* edt = static_cast<QLineEdit*>(editor);
        model->setData(index,edt->text(),Qt::EditRole);
    }
}

void MyDelegate::updateEditorGeometry(QWidget *editor,
                                      const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
    editor->setGeometry(option.rect);
}
void MyDelegate::setOptionalData(QStringList list)
{
    m_optional=list;
}

void MyDelegate::EmitEndEditSignal(QModelIndex index,QAbstractItemModel *model)
{
    //QComboBox* box = static_cast<QComboBox*>(editor);
    if(index.column() == 0&&index.parent().column()==-1) //只对第4列采用此方法编辑
    {
        //QModelIndex xx=;
        //QComboBox* box = new QComboBox(parent);
        //box->addItems(m_optional);
        //box->setCurrentText();
    }
}
