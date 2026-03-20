#include "commentdlg.h"
#include "ui_commentdlg.h"
#include <QLabel>
#include <QTextEdit>
#include <QDialogButtonBox>
#include <QPushButton>

CCommentDlg::CCommentDlg(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::CCommentDlg)
{
    ui->setupUi(this);
}

CCommentDlg::~CCommentDlg()
{
    delete ui;
}

void CCommentDlg::setWindowTitle(const QString& title)
{
    QDialog::setWindowTitle(title);
}

void CCommentDlg::setCommentText(const QString& text)
{
    if (ui->m_pTextEdit)
    {
        ui->m_pTextEdit->setText(text);
    }
}

QString CCommentDlg::getCommentText() const
{
    return ui->m_pTextEdit ? ui->m_pTextEdit->text() : QString();
}

bool CCommentDlg::getComment(QWidget* parent, QString& comment, const QString& title,
                             const QString& initialText)
{
    CCommentDlg dlg(parent);
    dlg.setWindowTitle(title);
    dlg.setCommentText(initialText);

    if (dlg.exec() == QDialog::Accepted)
    {
        comment = dlg.getCommentText();
        return true;
    }
    return false;
}
