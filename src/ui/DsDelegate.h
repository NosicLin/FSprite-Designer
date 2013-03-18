#ifndef DSDELEGATE_H
#define DSDELEGATE_H
#include <QItemDelegate>
#include <QModelIndex>
#include <QObject>
#include <QSize>
#include <QSpinBox>
#include <QDoubleSpinBox>

class DsPropertyDisplay;

class DsDelegate:public QItemDelegate
{
    Q_OBJECT
public:
    DsDelegate(DsPropertyDisplay* view,QObject* parent = 0);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const;

    void setEditorData(QWidget *editor, const QModelIndex &index) const;

    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const;

    void updateEditorGeometry(QWidget *editor,
        const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QSize sizeHint ( const QStyleOptionViewItem & option,const QModelIndex & index ) const ;

private:
    static double m_preData;
    DsPropertyDisplay* m_view;
};
#endif // DSDELEGATE_H


