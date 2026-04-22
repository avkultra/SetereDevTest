#ifndef CSCANNERDIALOG_H
#define CSCANNERDIALOG_H

#include <QDialog>
#include <QSettings>
#include <QMap>
#include <QStandardItemModel>

class QMenu;
class QStandardItem;

namespace Ui {
class CScannerDialog;
}

/**
 * @brief Класс диалога для выбора и управления сканерами
 *
 * Предоставляет интерфейс с двумя списками:
 * - Список доступных сканеров
 * - Список приоритетных сканеров
 */
class CScannerDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Конструктор
     * @param parent Родительский виджет
     */
    explicit CScannerDialog(QWidget* parent = nullptr);

    /**
     * @brief Деструктор
     */
    ~CScannerDialog();

protected:
    /**
     * @brief Обработчик события закрытия окна
     * @param event Событие закрытия
     */
    void closeEvent(QCloseEvent* event) override;

private slots:
    /**
     * @brief Обработчик изменения элемента в приоритетном списке
     * @param pItem Измененный элемент
     */
    void onPriorityItemChanged(QStandardItem* pItem);

    /**
     * @brief Обработчик клика по доступному сканеру
     * @param index Индекс выбранного элемента
     */
    void onAvailableItemClicked(const QModelIndex& index);

    /**
     * @brief Показывает контекстное меню
     * @param pos Позиция курсора
     */
    void showAvailableContextMenu(const QPoint& pos);

    /**
     * @brief Устанавливает комментарий для выбранного доступного сканера
     */
    void setAvailableScannerComment();


    /**
     * @brief Очищаем весь список приоритетных сканеров
     */
    void on_pbClear_released();

    /**
     * @brief Выход из диалога
     */
    void on_m_pbCancel_released();

private:
    /**
     * @brief Инициализация моделей и настройка таблиц
     */
    void setupModels();

    /**
     * @brief Инициализация списка доступных сканеров
     */
    void initScannersList();

    /**
     * @brief Настройка контекстных меню
     */
   // void setupContextMenus();

    /**
     * @brief Загрузка настроек из QSettings
     */
    void loadSettings();

    /**
     * @brief Сохранение настроек в QSettings
     */
    void saveSettings();

    /**
     * @brief Извлечение имени сканера из полной строки
     * @param fullString Полная строка сканера
     * @return Имя сканера
     */
    QString extractScannerName(const QString& fullString) const;

    /**
     * @brief Извлечение IP-адреса из полной строки
     * @param fullString Полная строка сканера
     * @return IP-адрес
     */
    QString extractIpAddress(const QString& fullString) const;

    /**
     * @brief Получение отображаемого текста для доступного сканера
     * @param scannerFullName Полная строка сканера
     * @return Текст для отображения (с учетом комментария)
     */
    QString getAvailableDisplayText(const QString& scannerFullName) const;

    /**
     * @brief Получение отображаемого текста для приоритетного сканера
     * @param scannerFullName Полная строка сканера
     * @return Текст для отображения (с учетом комментария)
     */
    QString getPriorityDisplayText(const QString& scannerFullName) const;

    /**
     * @brief Добавление сканера в приоритетную модель
     * @param scannerFullName Полная строка сканера
     * @param isActive Флаг активности (выбран ли радиокнопкой)
     */
    void addToPriorityModel(const QString& scannerFullName, bool isActive);

    /**
     * @brief Удаление сканера из приоритетной модели
     * @param scannerFullName Полная строка сканера
     */
    void removeFromPriorityModel(const QString& scannerFullName);

    /**
     * @brief Обновление элемента в приоритетной модели
     * @param pItem Элемент для обновления
     * @param scannerFullName Полная строка сканера
     * @param isActive Флаг активности
     */
    void updatePriorityItem(QStandardItem* pItem, const QString& scannerFullName, bool isActive);

    /**
     * @brief Проверяет, есть ли уже сканер в приоритетном списке
     * @param scannerFullName Полная строка сканера
     * @return true если сканер уже есть в приоритетном списке
     */
    bool isScannerInPriorityList(const QString& scannerFullName) const;

    /**
     * @brief Обновление иконки доступных сканеров
     * @param pItem Выбранный элемент
     * @param show Показать да или нет
     */
    void updateIconAvailableScaner(QStandardItem* pItem, bool show = false);

    /**
     * @brief Очищает все выбранные сканеры
     */
    void clearAvailableScane();

private:
    Ui::CScannerDialog* ui;
    QSettings m_settings;

    // Модели данных
    QStandardItemModel* m_pAvailableModel;
    QStandardItemModel* m_pPriorityModel;
    // Комментарии
    QMap<QString, QString> m_availableScannerComments;
};

#endif // CSCANNERDIALOG_H
