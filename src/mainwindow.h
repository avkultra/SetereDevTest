#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class CScannerDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onOpenScanner();
    void onSettings();
    void onAbout();
    void onExit();

private:
    void setupSquareToolButtons();  // Новый метод для настройки квадратных кнопок

private:
    Ui::MainWindow *ui;
    CScannerDialog *m_pScannerDialog;
};

#endif // MAINWINDOW_H
