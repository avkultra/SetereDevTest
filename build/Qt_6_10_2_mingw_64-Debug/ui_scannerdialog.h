/********************************************************************************
** Form generated from reading UI file 'scannerdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCANNERDIALOG_H
#define UI_SCANNERDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CScannerDialog
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QPushButton *pbClear;
    QTableView *priorityTableView;
    QFrame *frame_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLabel *label_3;
    QTableView *availableTableView;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QPushButton *m_pbScan;
    QPushButton *m_pbSetup;
    QPushButton *m_pbCancel;

    void setupUi(QDialog *CScannerDialog)
    {
        if (CScannerDialog->objectName().isEmpty())
            CScannerDialog->setObjectName("CScannerDialog");
        CScannerDialog->resize(695, 371);
        verticalLayout = new QVBoxLayout(CScannerDialog);
        verticalLayout->setObjectName("verticalLayout");
        frame_2 = new QFrame(CScannerDialog);
        frame_2->setObjectName("frame_2");
        frame_2->setFrameShape(QFrame::Shape::NoFrame);
        frame_2->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame_2);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(frame_2);
        label->setObjectName("label");

        horizontalLayout_2->addWidget(label);

        pbClear = new QPushButton(frame_2);
        pbClear->setObjectName("pbClear");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pbClear->sizePolicy().hasHeightForWidth());
        pbClear->setSizePolicy(sizePolicy);
        pbClear->setMaximumSize(QSize(25, 25));
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::ViewRestore));
        pbClear->setIcon(icon);
        pbClear->setFlat(false);

        horizontalLayout_2->addWidget(pbClear);


        verticalLayout->addWidget(frame_2);

        priorityTableView = new QTableView(CScannerDialog);
        priorityTableView->setObjectName("priorityTableView");
        priorityTableView->setShowGrid(false);

        verticalLayout->addWidget(priorityTableView);

        frame_3 = new QFrame(CScannerDialog);
        frame_3->setObjectName("frame_3");
        frame_3->setFrameShape(QFrame::Shape::NoFrame);
        frame_3->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout_3 = new QHBoxLayout(frame_3);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, -1, 0);
        label_2 = new QLabel(frame_3);
        label_2->setObjectName("label_2");

        horizontalLayout_3->addWidget(label_2);

        label_3 = new QLabel(frame_3);
        label_3->setObjectName("label_3");

        horizontalLayout_3->addWidget(label_3);


        verticalLayout->addWidget(frame_3);

        availableTableView = new QTableView(CScannerDialog);
        availableTableView->setObjectName("availableTableView");
        availableTableView->setShowGrid(false);

        verticalLayout->addWidget(availableTableView);

        frame = new QFrame(CScannerDialog);
        frame->setObjectName("frame");
        frame->setFrameShape(QFrame::Shape::NoFrame);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        m_pbScan = new QPushButton(frame);
        m_pbScan->setObjectName("m_pbScan");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/device_scanner_icon.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        m_pbScan->setIcon(icon1);

        horizontalLayout->addWidget(m_pbScan);

        m_pbSetup = new QPushButton(frame);
        m_pbSetup->setObjectName("m_pbSetup");
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/setup_utility_tools.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        m_pbSetup->setIcon(icon2);

        horizontalLayout->addWidget(m_pbSetup);

        m_pbCancel = new QPushButton(frame);
        m_pbCancel->setObjectName("m_pbCancel");
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/cancel_icon.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        m_pbCancel->setIcon(icon3);

        horizontalLayout->addWidget(m_pbCancel);


        verticalLayout->addWidget(frame);


        retranslateUi(CScannerDialog);

        QMetaObject::connectSlotsByName(CScannerDialog);
    } // setupUi

    void retranslateUi(QDialog *CScannerDialog)
    {
        CScannerDialog->setWindowTitle(QCoreApplication::translate("CScannerDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("CScannerDialog", "Favotite scanners", nullptr));
        pbClear->setText(QString());
        label_2->setText(QCoreApplication::translate("CScannerDialog", "Avalible Scanners", nullptr));
        label_3->setText(QCoreApplication::translate("CScannerDialog", "dpi 300 page format A4 portrait", nullptr));
        m_pbScan->setText(QCoreApplication::translate("CScannerDialog", "Scan", nullptr));
        m_pbSetup->setText(QCoreApplication::translate("CScannerDialog", "Setup && Scan", nullptr));
        m_pbCancel->setText(QCoreApplication::translate("CScannerDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CScannerDialog: public Ui_CScannerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCANNERDIALOG_H
