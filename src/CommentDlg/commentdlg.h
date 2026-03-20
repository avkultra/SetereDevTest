#ifndef COMMENTDLG_H
#define COMMENTDLG_H

#include <QDialog>
#include <QString>

namespace Ui {
class CCommentDlg;
}

class QLabel;
class QTextEdit;
class QDialogButtonBox;

class CCommentDlg : public QDialog
{
    Q_OBJECT

public:
    explicit CCommentDlg(QWidget* parent = nullptr);
    ~CCommentDlg();

    void setWindowTitle(const QString& title);
    void setCommentText(const QString& text);

    QString getCommentText() const;

    static bool getComment(QWidget* parent, QString& comment, const QString& title = "Enter some comments:",
                           const QString& initialText = "");

private:
    Ui::CCommentDlg* ui;
};

#endif // COMMENTDLG_H
