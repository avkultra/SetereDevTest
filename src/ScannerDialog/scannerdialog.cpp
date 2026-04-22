#include "scannerdialog.h"
#include "ui_scannerdialog.h"
#include <QMenu>
#include <QMessageBox>
#include <QCloseEvent>
#include <QHeaderView>
#include <QRegularExpression>
#include <QButtonGroup>
#include <QApplication>
#include <QPainter>
#include <QStyleOptionButton>
#include <QStyledItemDelegate>
#include <QDebug>
#include "../CommentDlg/commentdlg.h"
#include "icontextdelegate.h"
#include "priorityitemdelegate.h"

//// Делегат для списка с радибуттон
//class CPriorityItemDelegate : public QStyledItemDelegate
//{
//public:
//    using QStyledItemDelegate::QStyledItemDelegate;

//    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override
//    {
//        painter->save();

//        QStyleOptionViewItem opt = option;
//        initStyleOption(&opt, index);

//        opt.state &= ~QStyle::State_Selected;

//        QStyle* style = QApplication::style();
//        style->drawPrimitive(QStyle::PE_PanelItemViewItem, &opt, painter);

//        bool isActive = index.data(Qt::UserRole + 1).toBool();
//        bool isSelected = (option.state & QStyle::State_Selected) != 0;
//        QString text = index.data(Qt::DisplayRole).toString();

//        QStyleOptionButton radioStyle;
//        radioStyle.state = isActive ? QStyle::State_On : QStyle::State_Off;
//        radioStyle.state |= QStyle::State_Enabled;
//        radioStyle.rect = QRect(option.rect.left() + 8,
//                                option.rect.top() + (option.rect.height() - 14) / 2,
//                                14, 14);

//        style->drawPrimitive(QStyle::PE_IndicatorRadioButton, &radioStyle, painter);

//        QRect textRect = option.rect;
//        textRect.setLeft(option.rect.left() + 28);
//        textRect.setRight(option.rect.right() - 10);

//        painter->drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, text);

//        if (isSelected)
//        {
//            QPen pen;
//            pen.setColor(QColor(52, 152, 219));
//            pen.setWidth(1);
//            painter->setPen(pen);

//            // Рисуем полосу внизу ячейки
//            int y = option.rect.bottom() - 1;
//            painter->drawLine(option.rect.left(), y, option.rect.right(), y);
//        }

//        painter->restore();
//    }

//    QSize sizeHint(const QStyleOptionViewItem& /*option*/, const QModelIndex& /*index*/) const override
//    {
//        return QSize(200, 30);
//    }

//    bool editorEvent(QEvent* event, QAbstractItemModel* model,
//                     const QStyleOptionViewItem& option, const QModelIndex& index) override
//    {
//        if (event->type() == QEvent::MouseButtonRelease)
//        {
//            QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);

//            QRect radioRect(option.rect.left() + 8,
//                            option.rect.top() + (option.rect.height() - 14) / 2,
//                            14, 14);

//            if (radioRect.contains(mouseEvent->pos()) || option.rect.contains(mouseEvent->pos()))
//            {
//                model->setData(index, true, Qt::UserRole + 1);
//                return true;
//            }
//        }
//        return QStyledItemDelegate::editorEvent(event, model, option, index);
//    }
//};

// Конструктор
CScannerDialog::CScannerDialog(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::CScannerDialog),
    m_settings("Setere", "ScannerSelector"),
    m_pAvailableModel(new QStandardItemModel(this)),
    m_pPriorityModel(new QStandardItemModel(this))
{

    Qt::WindowFlags flags = Qt::Dialog;
    flags |= Qt::WindowTitleHint;
    flags |= Qt::WindowSystemMenuHint;
    flags |= Qt::WindowCloseButtonHint;

    flags &= ~Qt::WindowMinMaxButtonsHint;
    flags &= ~Qt::WindowContextHelpButtonHint;

    ui->setupUi(this);

    QDialog::setWindowTitle(tr("Choose scaner"));

    // Установка моделей
    setupModels();
    // Инициализация сканеров
    initScannersList();
    // Загрузка настроек
    loadSettings();

    // Подключение сигналов
    connect(ui->availableTableView, &QTableView::customContextMenuRequested,
            this, &CScannerDialog::showAvailableContextMenu);
    connect(ui->availableTableView, &QTableView::clicked,
            this, &CScannerDialog::onAvailableItemClicked);
    connect(m_pPriorityModel, &QStandardItemModel::itemChanged,
            this, &CScannerDialog::onPriorityItemChanged);

}

// Деструктор
CScannerDialog::~CScannerDialog()
{
    delete ui;
}

// Инициализация моделей и настройка таблиц
void CScannerDialog::setupModels()
{
    m_pAvailableModel->setColumnCount(1);

    ui->availableTableView->setModel(m_pAvailableModel);
    ui->availableTableView->horizontalHeader()->setVisible(false);
    ui->availableTableView->verticalHeader()->setVisible(false);

    ui->availableTableView->setSelectionMode(QAbstractItemView::NoSelection);
    ui->availableTableView->setFocusPolicy(Qt::NoFocus);

    ui->availableTableView->setShowGrid(false);
    ui->availableTableView->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->availableTableView->horizontalHeader()->setStretchLastSection(true);
    ui->availableTableView->setItemDelegate(new CIconTextDelegate(this));

    m_pPriorityModel->setColumnCount(1);

    ui->priorityTableView->setModel(m_pPriorityModel);
    ui->priorityTableView->horizontalHeader()->setVisible(false);
    ui->priorityTableView->verticalHeader()->setVisible(false);

     ui->priorityTableView->setSelectionMode(QAbstractItemView::NoSelection);
    // ui->priorityTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    // ui->priorityTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->priorityTableView->setFocusPolicy(Qt::NoFocus);

    ui->priorityTableView->setShowGrid(false);
    ui->priorityTableView->horizontalHeader()->setStretchLastSection(true);

    ui->priorityTableView->setItemDelegate(new CPriorityItemDelegate(this));
    ui->availableTableView->verticalHeader()->setDefaultSectionSize(32);
    ui->priorityTableView->verticalHeader()->setDefaultSectionSize(30);

    QString tableStyle =
        "QTableView"
        "{   background-color: transparent;"
        "    alternate-background-color: palette(alternate-base);"
        "    border: 1px solid palette(mid);"
        "    outline: 1px solid palette(mid);"
        "    outline-offset: 1px;"
        "    border-radius: 0px;"
        "    padding: 2px;"
        "}"
        "QTableView::item"
        "{   border: none;"
        "    padding: 0px;"
        "}"
        "QTableView::item:selected"
        "{   background-color: transparent;"
        "    color: palette(text);"
        "}"
        "QTableView::item:hover"
        "{   background-color: rgba(0, 0, 0, 0.05);"
        "}"
        "QTableView::item:focus"
        "{   outline: none;"
        "    border: none;"
        "}"
        "QTableView:focus"
        "{   outline: none;"
        "    border: none;"
        "}"
        "QHeaderView::section:focus"
        "{   outline: none;"
        "    border: none;"
        "}";

    ui->availableTableView->setStyleSheet(tableStyle);
    ui->priorityTableView->setStyleSheet(tableStyle);
}

// Извлечение имени сканера из полной строки
QString CScannerDialog::extractScannerName(const QString& fullString) const
{
    // Извлекаем имя сканера
    QRegularExpression nameRegex(R"(\]\s+\[[^\]]+\]\s+\[([^\]]+)\])");
    QRegularExpressionMatch nameMatch = nameRegex.match(fullString);
    QString name = nameMatch.hasMatch() ? nameMatch.captured(1).trimmed() : "Unknown";

    // Извлекаем IP и порт
    QRegularExpression ipPortRegex(R"((\d+\.\d+\.\d+\.\d+):(\d+))");
    QRegularExpressionMatch ipPortMatch = ipPortRegex.match(fullString);

    if (ipPortMatch.hasMatch())
    {
        QString ip = ipPortMatch.captured(1);
        QString port = ipPortMatch.captured(2);
        return QString("%1 [%2:%3]").arg(name, ip, port);
    }

    return name;
}

// Извлечение IP-адреса из полной строки
QString CScannerDialog::extractIpAddress(const QString& fullString) const
{
    QRegularExpression regex(R"(\d+\.\d+\.\d+\.\d+)");
    QRegularExpressionMatch match = regex.match(fullString);
    if (match.hasMatch())
    {
        return match.captured(0);
    }
    return "Unknown";
}

// Получение отображаемого текста для доступного сканера
QString CScannerDialog::getAvailableDisplayText(const QString& scannerFullName) const
{
    if (m_availableScannerComments.contains(scannerFullName))
    {
        return m_availableScannerComments[scannerFullName];
    }
    return extractScannerName(scannerFullName);
}

// Получение отображаемого текста для приоритетного сканера
QString CScannerDialog::getPriorityDisplayText(const QString& scannerFullName) const
{
    if (m_availableScannerComments.contains(scannerFullName))
    {
        return m_availableScannerComments[scannerFullName];
    }
    return extractScannerName(scannerFullName);
}

// Инициализация списка доступных сканеров
void CScannerDialog::initScannersList()
{
    std::vector<std::string> scannersList;
    scannersList.push_back("[escl:https://192.168.77.235:9096] [ESCL]  [Kyocera ECOSYS M5526cdw111]  [flatbed scanner]");
    scannersList.push_back("[escl:https://192.168.66.235:9096] [ESCL]  [Cannon ECOSYS M5526cdw222]  [flatbed scanner]");
    scannersList.push_back("[escl:https://192.168.77.21:9096] [ESCL]  [Plustek OpticSlim 2610 Pro]  [flatbed scanner]");
    scannersList.push_back("[escl:https://192.168.66.23:9096] [ESCL]  [Epson Perfection V19]  [flatbed scanner]");
    scannersList.push_back("[escl:https://192.168.77.25:9096] [ESCL]  [HP ScanJet Pro 2000 s2]  [flatbed scanner]");
    scannersList.push_back("[escl:https://192.168.66.35:9096] [ESCL]  [Canon CanoScan LiDE 400 2996C010]  [flatbed scanner]");
    scannersList.push_back("[escl:https://192.168.77.205:9096] [ESCL]  [Epson WorkForce DS-7500]  [flatbed scanner]");
    scannersList.push_back("[escl:https://192.168.66.203:9096] [ESCL]  [Canon/Duplex Color Image Reader Unit-M2]  [flatbed scanner]");
    scannersList.push_back("[escl:https://192.168.77.123:9096] [ESCL]  [Kyocera ECOSYS M5526cdw333]  [flatbed scanner]");
    scannersList.push_back("[escl:https://192.168.66.135:9096] [ESCL]  [Cannon ECOSYS M5526cdw]  [flatbed scanner]");

    m_pAvailableModel->removeRows(0, m_pAvailableModel->rowCount());

    for (const auto& scanner : scannersList)
    {
        QString scannerStr = QString::fromStdString(scanner);
        QString name = getAvailableDisplayText(scannerStr);
        QString ip = extractIpAddress(scannerStr);

        QStandardItem* pItem = new QStandardItem();
        pItem->setEditable(false);
        pItem->setData(name, Qt::DisplayRole);
        pItem->setData(scannerStr, Qt::UserRole);
        pItem->setData(ip, Qt::UserRole + 2);
        pItem->setData(false, Qt::UserRole + 1);
        pItem->setData(QIcon(":/icons/pennant.png"), Qt::DecorationRole);

        pItem->setSizeHint(QSize(0, 32));

        m_pAvailableModel->appendRow(pItem);
    }
}

// Добавление сканера в приоритетную модель
void CScannerDialog::addToPriorityModel(const QString& scannerFullName, bool isActive)
{
    QString name = getPriorityDisplayText(scannerFullName);

    QStandardItem* pItem = new QStandardItem();
    pItem->setEditable(false);
    pItem->setData(name, Qt::DisplayRole);
    pItem->setData(scannerFullName, Qt::UserRole);
    pItem->setData(isActive, Qt::UserRole + 1);

    pItem->setSizeHint(QSize(0, 30));

    m_pPriorityModel->insertRow(0, pItem);

    if (isActive)
    {
        for (int i = 1; i < m_pPriorityModel->rowCount(); ++i)
        {
            QStandardItem* pOtherItem = m_pPriorityModel->item(i);
            pOtherItem->setData(false, Qt::UserRole + 1);
        }
    }
}

// Проверяет, есть ли уже сканер в приоритетном списке
bool CScannerDialog::isScannerInPriorityList(const QString& scannerFullName) const
{
    for (int i = 0; i < m_pPriorityModel->rowCount(); ++i)
    {
        QString existingScanner = m_pPriorityModel->item(i)->data(Qt::UserRole).toString();
        if (existingScanner == scannerFullName)
        {
            return true;
        }
    }
    return false;
}

// Обработчик клика по доступному сканеру
void CScannerDialog::onAvailableItemClicked(const QModelIndex& index)
{
    if (!index.isValid())
    {
         return;
    }

    QStandardItem* pItem = m_pAvailableModel->itemFromIndex(index);
    QString scannerFullName = pItem->data(Qt::UserRole).toString();

    if (isScannerInPriorityList(scannerFullName))
    {
        removeFromPriorityModel(scannerFullName);
        updateIconAvailableScaner(pItem);
        return;
    }

    addToPriorityModel(scannerFullName, true);

    updateIconAvailableScaner(pItem, true);

    if (m_pPriorityModel->rowCount() > 0)
    {
        QModelIndex firstIndex = m_pPriorityModel->index(0, 0);
        ui->priorityTableView->scrollTo(firstIndex);
    }

    qDebug() << "Сканер добавлен в приоритетные:"
             << getPriorityDisplayText(scannerFullName);
}

// Обновление иконки доступных сканеров
void CScannerDialog::updateIconAvailableScaner(QStandardItem* pCurrItem, bool show /*= false*/)
{
    if (!pCurrItem)
    {
        return;
    }

    if (pCurrItem)
    {
        if(show)
        {
            pCurrItem->setData(show, Qt::UserRole + 1);
            pCurrItem->setData(QIcon(":/icons/pennant_on.png"), Qt::DecorationRole);
        }
        else
        {
            pCurrItem->setData(show, Qt::UserRole + 1);
            pCurrItem->setData(QIcon(":/icons/pennant.png"), Qt::DecorationRole);
        }
    }
}

//  Удаление сканера из приоритетной модели
void CScannerDialog::removeFromPriorityModel(const QString& scannerFullName)
{
    for (int i = 0; i < m_pPriorityModel->rowCount(); ++i)
    {
        QStandardItem *pItem = m_pPriorityModel->item(i);
        if (pItem->data(Qt::UserRole).toString() == scannerFullName)
        {
            m_pPriorityModel->removeRow(i);
            break;
        }
    }
     qDebug() << "Сканер удалён в приоритетные:" << getPriorityDisplayText(scannerFullName);
}

// Обработчик изменения элемента в приоритетном списке
void CScannerDialog::onPriorityItemChanged(QStandardItem* pItem)
{
    if (!pItem) return;

    bool isActive = pItem->data(Qt::UserRole + 1).toBool();
    QString scannerName = pItem->data(Qt::DisplayRole).toString();

    if (isActive)
    {
        for (int i = 0; i < m_pPriorityModel->rowCount(); ++i)
        {
            if (i != pItem->row())
            {
                QStandardItem *pOtherItem = m_pPriorityModel->item(i);
                bool wasActive = pOtherItem->data(Qt::UserRole + 1).toBool();
                if (wasActive)
                {
                    qDebug() << "  Деактивируем:" << pOtherItem->data(Qt::DisplayRole).toString();
                }
                pOtherItem->setData(false, Qt::UserRole + 1);
            }
        }
    }
}

//  Показывает контекстное меню
void CScannerDialog::showAvailableContextMenu(const QPoint& pos)
{
    QModelIndex index = ui->availableTableView->indexAt(pos);
    if (!index.isValid()) return;

    // Устанавливаем current index без изменения режима выделения
    ui->availableTableView->setCurrentIndex(index);

    QMenu contextMenu(tr("Context menu"), this);
    QAction action1(tr("Add comment"), this);
    connect(&action1, &QAction::triggered, this, &CScannerDialog::setAvailableScannerComment);
    contextMenu.addAction(&action1);
    contextMenu.exec(ui->availableTableView->mapToGlobal(pos));
}

void CScannerDialog::setAvailableScannerComment()
{
    QModelIndex index = ui->availableTableView->currentIndex();
    if (!index.isValid()) return;

    int row = index.row();
    QStandardItem *pItem = m_pAvailableModel->item(row);
    QString scannerFullName = pItem->data(Qt::UserRole).toString();
    QString currentComment = m_availableScannerComments.value(scannerFullName, "");
    QString currentName = extractScannerName(scannerFullName);

    QString comment;
    bool bOk = CCommentDlg::getComment(this, comment,
                                       tr("Enter some comments:"),
                                       currentComment);
    if (bOk)
    {
        if (!comment.isEmpty())
        {
            m_availableScannerComments[scannerFullName] = comment;
            pItem->setData(comment, Qt::DisplayRole);

            for (int priorityRow = 0; priorityRow < m_pPriorityModel->rowCount(); ++priorityRow)
            {
                QStandardItem* pPriorityItem = m_pPriorityModel->item(priorityRow);
                if (pPriorityItem->data(Qt::UserRole).toString() == scannerFullName)
                {
                    pPriorityItem->setData(comment, Qt::DisplayRole);
                    break;
                }
            }
            qDebug() << "Комментарий добавлен для сканера:" << scannerFullName << "->" << comment;
        }
        else if (!currentComment.isEmpty())
        {
            m_availableScannerComments.remove(scannerFullName);
            pItem->setData(currentName, Qt::DisplayRole);

            for (int priorityRow = 0; priorityRow < m_pPriorityModel->rowCount(); ++priorityRow)
            {
                QStandardItem* pPriorityItem = m_pPriorityModel->item(priorityRow);
                if (pPriorityItem->data(Qt::UserRole).toString() == scannerFullName)
                {
                    pPriorityItem->setData(currentName, Qt::DisplayRole);
                    break;
                }
            }
            qDebug() << "Комментарий удален для сканера:" << scannerFullName;
        }
    }
}

void CScannerDialog::loadSettings()
{
    QByteArray geometry = m_settings.value("dialog_geometry").toByteArray();
    if (!geometry.isEmpty())
    {
        restoreGeometry(geometry);
    }

    int availableCommentSize = m_settings.beginReadArray("available_comments");
    for (int i = 0; i < availableCommentSize; ++i)
    {
        m_settings.setArrayIndex(i);
        QString scanner = m_settings.value("scanner").toString();
        QString comment = m_settings.value("comment").toString();
        m_availableScannerComments[scanner] = comment;
    }
    m_settings.endArray();

    QStringList priorityScanners = m_settings.value("priority_scanners").toStringList();
    QString activeScanner = m_settings.value("active_scanner").toString();

    m_pPriorityModel->removeRows(0, m_pPriorityModel->rowCount());

    for (int i = priorityScanners.size() - 1; i >= 0; --i)
    {
        const QString &scanner = priorityScanners.at(i);
        bool isActive = (scanner == activeScanner);
        addToPriorityModel(scanner, isActive);
    }

    for (int row = 0; row < m_pAvailableModel->rowCount(); ++row)
    {
        QStandardItem* pItem = m_pAvailableModel->item(row);
        QString scannerFullName = pItem->data(Qt::UserRole).toString();
        if(isScannerInPriorityList(scannerFullName))
        {
            updateIconAvailableScaner(pItem, true);
        }
        if (m_availableScannerComments.contains(scannerFullName))
        {
            pItem->setData(m_availableScannerComments[scannerFullName], Qt::DisplayRole);
        }
    }
}

void CScannerDialog::saveSettings()
{
    m_settings.setValue("dialog_geometry", saveGeometry());

    m_settings.beginWriteArray("available_comments");
    int i = 0;
    for (auto it = m_availableScannerComments.begin(); it != m_availableScannerComments.end(); ++it)
    {
        m_settings.setArrayIndex(i);
        m_settings.setValue("scanner", it.key());
        m_settings.setValue("comment", it.value());
        ++i;
    }
    m_settings.endArray();

    QStringList priorityScanners;
    QString activeScanner;

    for (int row = 0; row < m_pPriorityModel->rowCount(); ++row)
    {
        QStandardItem* pItem = m_pPriorityModel->item(row);
        QString scanner = pItem->data(Qt::UserRole).toString();
        priorityScanners.append(scanner);

        if (pItem->data(Qt::UserRole + 1).toBool())
        {
            activeScanner = scanner;
            qDebug() << "Активный сканер сохранен:" << scanner;
        }
    }

    m_settings.setValue("priority_scanners", priorityScanners);
    m_settings.setValue("active_scanner", activeScanner);

    qDebug() << "Сохранено приоритетных сканеров:" << priorityScanners.size();
    qDebug() << "Активный сканер:" << activeScanner;
}

// Обработчик события закрытия окна
void CScannerDialog::closeEvent(QCloseEvent *event)
{
    saveSettings();
    event->accept();
}

// Очищаем весь список приоритетных сканеров
void CScannerDialog::on_pbClear_released()
{
    if (m_pPriorityModel->rowCount() == 0)
    {
        QMessageBox::information(this, "Информация",
                                 "Список приоритетных сканеров уже пуст");
        return;
    }

    QStringList scannersToClear;
    for (int row = 0; row < m_pPriorityModel->rowCount(); ++row)
    {
        QStandardItem* pItem = m_pPriorityModel->item(row);
        scannersToClear.append(pItem->data(Qt::UserRole).toString());
    }

    m_pPriorityModel->removeRows(0, m_pPriorityModel->rowCount());

    for (const QString& scanner : scannersToClear)
    {
        for (int row = 0; row < m_pAvailableModel->rowCount(); ++row)
        {
            QStandardItem* pItem = m_pAvailableModel->item(row);
            if (pItem->data(Qt::UserRole).toString() == scanner)
            {
                updateIconAvailableScaner(pItem, false);
                break;
            }
        }
    }

    qDebug() << "Список приоритетных сканеров очищен";
}
// Очищает все выбранные сканеры
void CScannerDialog::clearAvailableScane()
{
    for (int row = 0; row < m_pAvailableModel->rowCount(); ++row)
    {
        QStandardItem* pCurrItem = m_pAvailableModel->item(row);
        updateIconAvailableScaner(pCurrItem);
    }
}

// Выход из диалога
void CScannerDialog::on_m_pbCancel_released()
{
     reject();
}

