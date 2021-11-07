#include "searchdialog.h"
#include "ui_searchdialog.h"
#include <QMessageBox>
#include <QDebug>

SearchDialog::SearchDialog(QWidget *parent, QPlainTextEdit * textEdit) :
    QDialog(parent),
    ui(new Ui::SearchDialog)
{
    ui->setupUi(this);

    pTextEdit = textEdit;
    ui->rdDown->setChecked(true);
}

SearchDialog::~SearchDialog()
{
    delete ui;
}

void SearchDialog::on_btFindNext_clicked()
{
    QString target = ui->searchText->text();    // 获取对话框输入的文本，即要查找的文本

    if(target == "" || pTextEdit == nullptr)
        return;

    QString text = pTextEdit->toPlainText();
    QTextCursor c = pTextEdit->textCursor();
    int index = -1;

    if(ui->rdDown->isChecked()){
        index = text.indexOf(target, c.position(), ui->cbCaseSensetive->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive);
        if(index >= 0){
            c.setPosition(index);
            c.setPosition(index + target.length(), QTextCursor::KeepAnchor);

            pTextEdit->setTextCursor(c);
        }
    }
    else if(ui->rdUp->isChecked()){
        index = text.lastIndexOf(target, c.position() - text.length() - 1,
                ui->cbCaseSensetive->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive);
        if(index >= 0){
            c.setPosition(index + target.length());
            c.setPosition(index, QTextCursor::KeepAnchor);

            pTextEdit->setTextCursor(c);
        }
    }

    if(index < 0){
        QMessageBox msg(this);
        msg.setWindowTitle("Notepad");
        msg.setText(QString("找不到" + target));
        msg.setWindowFlag(Qt::Drawer);
        msg.setIcon(QMessageBox::Information);
        msg.setStandardButtons(QMessageBox::Ok);
        msg.exec();
    }
}


void SearchDialog::on_btCancel_clicked()
{
    accept();
}

