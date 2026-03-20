/********************************************************************************
** Form generated from reading UI file 'commentdlg.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMMENTDLG_H
#define UI_COMMENTDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CCommentDlg
{
public:
    QVBoxLayout *verticalLayout;
    QLineEdit *m_pTextEdit;
    QDialogButtonBox *m_pButtonBox;

    void setupUi(QDialog *CCommentDlg)
    {
        if (CCommentDlg->objectName().isEmpty())
            CCommentDlg->setObjectName("CCommentDlg");
        CCommentDlg->resize(410, 76);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(CCommentDlg->sizePolicy().hasHeightForWidth());
        CCommentDlg->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(CCommentDlg);
        verticalLayout->setObjectName("verticalLayout");
        m_pTextEdit = new QLineEdit(CCommentDlg);
        m_pTextEdit->setObjectName("m_pTextEdit");

        verticalLayout->addWidget(m_pTextEdit);

        m_pButtonBox = new QDialogButtonBox(CCommentDlg);
        m_pButtonBox->setObjectName("m_pButtonBox");
        m_pButtonBox->setOrientation(Qt::Orientation::Horizontal);
        m_pButtonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);

        verticalLayout->addWidget(m_pButtonBox);


        retranslateUi(CCommentDlg);
        QObject::connect(m_pButtonBox, &QDialogButtonBox::accepted, CCommentDlg, qOverload<>(&QDialog::accept));
        QObject::connect(m_pButtonBox, &QDialogButtonBox::rejected, CCommentDlg, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(CCommentDlg);
    } // setupUi

    void retranslateUi(QDialog *CCommentDlg)
    {
        CCommentDlg->setWindowTitle(QCoreApplication::translate("CCommentDlg", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CCommentDlg: public Ui_CCommentDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMMENTDLG_H
