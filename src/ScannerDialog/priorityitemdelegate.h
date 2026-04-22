#ifndef CPRIORITYITEMDELEGATE_H
#define CPRIORITYITEMDELEGATE_H

#include <QStyledItemDelegate>

// Делегат для списка с радибуттон
class CPriorityItemDelegate : public QStyledItemDelegate
{
public:
    using QStyledItemDelegate::QStyledItemDelegate;

    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;

    QSize sizeHint(const QStyleOptionViewItem& /*option*/, const QModelIndex& /*index*/) const override;

    bool editorEvent(QEvent* event, QAbstractItemModel* model,
                     const QStyleOptionViewItem& option, const QModelIndex& index) override;
};
#endif // CPRIORITYITEMDELEGATE_H
