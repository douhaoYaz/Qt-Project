#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QDialog>
#include <QPlainTextEdit>

namespace Ui {
class SearchDialog;
}

class SearchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SearchDialog(QWidget *parent = nullptr, QPlainTextEdit * textEdit=nullptr);
    ~SearchDialog();

private slots:
    void on_btFindNext_clicked();

    void on_btCancel_clicked();

private:
    Ui::SearchDialog *ui;

    QPlainTextEdit *pTextEdit;  // 用来保存指向Mainwindow中的TextEdit的指针（因为查找功能需要查找的是这个TextEdit文本输入框中的文本）
};

#endif // SEARCHDIALOG_H
