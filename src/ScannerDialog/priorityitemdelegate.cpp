#include "priorityitemdelegate.h"
#include <QPainter>
#include <QApplication>
#include <QMouseEvent>

void CPriorityItemDelegate ::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    painter->save();

    QStyleOptionViewItem opt = option;
    initStyleOption(&opt, index);

    opt.state &= ~QStyle::State_Selected;

    QStyle* style = QApplication::style();
    style->drawPrimitive(QStyle::PE_PanelItemViewItem, &opt, painter);

    bool isActive = index.data(Qt::UserRole + 1).toBool();
    bool isSelected = (option.state & QStyle::State_Selected) != 0;
    QString text = index.data(Qt::DisplayRole).toString();

    QStyleOptionButton radioStyle;
    radioStyle.state = isActive ? QStyle::State_On : QStyle::State_Off;
    radioStyle.state |= QStyle::State_Enabled;
    radioStyle.rect = QRect(option.rect.left() + 8,
                            option.rect.top() + (option.rect.height() - 14) / 2,
                            14, 14);

    style->drawPrimitive(QStyle::PE_IndicatorRadioButton, &radioStyle, painter);

    QRect textRect = option.rect;
    textRect.setLeft(option.rect.left() + 28);
    textRect.setRight(option.rect.right() - 10);

    painter->drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, text);

    if (isSelected)
    {
        QPen pen;
        pen.setColor(QColor(52, 152, 219));
        pen.setWidth(1);
        painter->setPen(pen);

        // Рисуем полосу внизу ячейки
        int y = option.rect.bottom() - 1;
        painter->drawLine(option.rect.left(), y, option.rect.right(), y);
    }

    painter->restore();
}

QSize CPriorityItemDelegate ::sizeHint(const QStyleOptionViewItem& /*option*/, const QModelIndex& /*index*/) const
{
    return QSize(200, 30);
}

bool CPriorityItemDelegate ::editorEvent(QEvent* event, QAbstractItemModel* model,
                                         const QStyleOptionViewItem& option, const QModelIndex& index)
{
    if (event->type() == QEvent::MouseButtonRelease)
    {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);

        QRect radioRect(option.rect.left() + 8,
                        option.rect.top() + (option.rect.height() - 14) / 2,
                        14, 14);

        if (radioRect.contains(mouseEvent->pos()) || option.rect.contains(mouseEvent->pos()))
        {
            model->setData(index, true, Qt::UserRole + 1);
            return true;
        }
    }
    return QStyledItemDelegate::editorEvent(event, model, option, index);
}
