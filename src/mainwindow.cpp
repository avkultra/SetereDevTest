#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ScannerDialog/scannerdialog.h"
#include <QMessageBox>
#include <QStyle>
#include <QToolButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_pScannerDialog(nullptr)
{
    ui->setupUi(this);

    setWindowTitle(tr("Scanner Selector"));

    setupSquareToolButtons();

    connect(ui->actionOpenScanner, &QAction::triggered, this, &MainWindow::onOpenScanner);
    connect(ui->actionSettings, &QAction::triggered, this, &MainWindow::onSettings);
    connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::onAbout);
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::onExit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupSquareToolButtons()
{
    ui->toolBar->setStyleSheet(
        "QToolBar QToolButton"
        "{   width: 48px;"
        "    height: 48px;"
        "    border: 1px solid #cccccc;"
        "    border-radius: 4px;"
        "    margin: 2px;"
        "}"
        "QToolBar QToolButton:hover"
        "{   background-color: #e6e6e6;"
        "    border: 1px solid #999999;"
        "}"
        "QToolBar QToolButton:pressed"
        "{   background-color: #cccccc;"
        "}"
        );

    QList<QToolButton*> buttons = ui->toolBar->findChildren<QToolButton*>();
    for (int i = 0; i < buttons.size(); ++i)
    {
        buttons[i]->setToolButtonStyle(Qt::ToolButtonIconOnly);
        buttons[i]->setAutoRaise(false);
        buttons[i]->setIconSize(QSize(32, 32));
    }
}

void MainWindow::onOpenScanner()
{
    if (!m_pScannerDialog)
    {
        m_pScannerDialog = new CScannerDialog(this);
    }
    m_pScannerDialog->show();
    m_pScannerDialog->raise();
    m_pScannerDialog->activateWindow();

    statusBar()->showMessage(tr("Scanner dialog opened"), 2000);
}

void MainWindow::onSettings()
{
    statusBar()->showMessage(tr("Settings dialog"), 2000);
    QMessageBox::information(this, tr("Settings"), tr("Settings dialog will be implemented here"));
}

void MainWindow::onAbout()
{
    QMessageBox::about(this, tr("About Scanner Selector"),
                       tr("<h2>Scanner Selector</h2>"
                       "<p>Version 1.0</p>"
                       "<p>Setere test application</p>"
                       "<p>© 2026 Setetre </p>"));
}

void MainWindow::onExit()
{
    close();
}
