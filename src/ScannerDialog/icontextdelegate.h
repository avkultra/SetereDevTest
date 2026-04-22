#ifndef CICONTEXTDELEGATE_H
#define CICONTEXTDELEGATE_H

#include <QStyledItemDelegate>

// Делегат для списка с иконкой
class CIconTextDelegate : public QStyledItemDelegate
{
public:
    using QStyledItemDelegate::QStyledItemDelegate;
    void paint(QPainter *painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    QSize sizeHint(const QStyleOptionViewItem& /*option*/, const QModelIndex& /*index*/) const override;
};

#endif // CICONTEXTDELEGATE_H
