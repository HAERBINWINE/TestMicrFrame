#ifndef MYDELEGATE_H
#define MYDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>
#include <QSignalMapper>

class MyDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    MyDelegate(QObject *parent = 0);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;

    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const override;
    void setOptionalData(QStringList );

    void updateEditorGeometry(QWidget *editor,
        const QStyleOptionViewItem &option, const QModelIndex &index) const override;
private:
    QStringList m_optional;
public:

    QSignalMapper* signalMapper;
signals:
    void CombSlectedChanged(QString);
public slots:
    void EmitEndEditSignal(QModelIndex,QAbstractItemModel*);
};


#endif // MYDELEGATE_H
