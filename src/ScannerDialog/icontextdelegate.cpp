#include "icontextdelegate.h"
#include <QPainter>
#include <QApplication>

void CIconTextDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    painter->save();

    QStyleOptionViewItem opt = option;
    initStyleOption(&opt, index);

    QStyle* style = QApplication::style();
    style->drawPrimitive(QStyle::PE_PanelItemViewItem, &opt, painter);

    // Получаем данные
    QIcon icon = index.data(Qt::DecorationRole).value<QIcon>();
    QString text = index.data(Qt::DisplayRole).toString();

    if (!icon.isNull())
    {
        QRect iconRect = option.rect;
        iconRect.setLeft(option.rect.left() + 8);
        iconRect.setWidth(16);
        iconRect.setHeight(16);
        iconRect.moveTop(option.rect.top() + (option.rect.height() - 16) / 2);

        icon.paint(painter, iconRect, Qt::AlignCenter,
                   index.data(Qt::UserRole + 1).toBool() ? QIcon::Selected : QIcon::Normal);
    }

    QRect textRect = option.rect;
    textRect.setLeft(option.rect.left() + 32);
    textRect.setRight(option.rect.right() - 10);

    QFont font = painter->font();
    if (index.data(Qt::FontRole).value<QFont>() != font)
    {
        font = index.data(Qt::FontRole).value<QFont>();
    }
    painter->setFont(font);

    painter->drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, text);

    painter->restore();
}

QSize CIconTextDelegate::sizeHint(const QStyleOptionViewItem& /*option*/, const QModelIndex& /*index*/) const
{
    return QSize(200, 32);
}
