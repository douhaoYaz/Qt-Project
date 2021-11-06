#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutdialog.h"
#include "searchdialog.h"
#include "replacedialog.h"
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // TODO 一运行程序，WindowTitle就有个*号，即textEdit以发生变化，为什么会出现这种情况，需要debug一下

    textChanged = false;    // 将textEdit的是否被修改状态初始化为False
    on_actionNew_triggered();

    // 设置编辑器右下角状态栏要显示的信息
    // 显示长度和行数
    statusLabel.setMaximumWidth(150);   // 设置最大宽度为150
    statusLabel.setText("length: " + QString::number(0) + "    lines: " + QString::number(1));   // 设置Label内容
    ui->statusbar->addPermanentWidget(&statusLabel);    // 把该Lable添加到状态栏中
    // 显示当前光标所在行列位置
    statusCursorLabel.setMaximumWidth(150);   // 设置最大宽度为150
    statusCursorLabel.setText("Ln: " + QString::number(0) + "    Col: " + QString::number(1));   // 设置Label内容
    ui->statusbar->addPermanentWidget(&statusCursorLabel);    // 把该Lable添加到状态栏中
    // 显示编辑者
    QLabel *author = new QLabel(ui->statusbar);
    author->setText(tr("符浩扬"));
    ui->statusbar->addPermanentWidget(author);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionAbout_triggered()
{
    aboutDialog dlg;
    dlg.exec();
}


void MainWindow::on_actionFind_triggered()
{
    SearchDialog dlg;
    dlg.exec();
}





void MainWindow::on_actionReplace_triggered()
{
    ReplaceDialog dlg;
    dlg.exec();
}


void MainWindow::on_actionNew_triggered()
{
    // 在新建文件之前，先让用户确认一下
    if(!userEditConfirmed())
        return;

    filePath = "";
    ui->textEdit->clear();
    this->setWindowTitle(tr("新建文本文件 - 编辑器"));

    // 新建文件后，还需要把textChanged重置为false，，因为上面的操作会使textEdit改变，引起textChanged信号
    // textEdit的textChanged槽函数会把textChanged全局变量置为true
    textChanged = false;
}


void MainWindow::on_actionOpen_triggered()
{
    // 在打开文件之前，先让用户确认一下
    if(!userEditConfirmed())
        return;

    QString filename = QFileDialog::getOpenFileName(this, "打开文件", ".", tr("Text files (*.txt) ;; All (*.*)"));
    QFile file(filename);

    if(!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, "..", "打开文件失败");
        return;
    }

    filePath = filename;

    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->insertPlainText(text);
    file.close();

    this->setWindowTitle(QFileInfo(filename).absoluteFilePath());

    // 打开文件后，还需要把textChanged重置为false，因为上面的操作会使textEdit改变，引起textChanged信号
    // textEdit的textChanged槽函数会把textChanged全局变量置为true
    textChanged = false;
}


void MainWindow::on_actionSave_triggered()
{
    QFile file(filePath);

    if(filePath == ""){
        QString filename = QFileDialog::getSaveFileName(this, "保存文件", ".", tr("Text files (*.txt) "));

        QFile file(filename);
        if(!file.open(QFile::WriteOnly | QFile::Text)){
            QMessageBox::warning(this, "..", "打开保存文件失败");
            return;
        }
        file.close();
        filePath = filename;
    }
    else if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "..", "打开文件失败");

        QString filename = QFileDialog::getSaveFileName(this, "保存文件", ".", tr("Text files (*.txt) "));

        QFile file(filename);
        if(!file.open(QFile::WriteOnly | QFile::Text)){
            QMessageBox::warning(this, "..", "打开保存文件失败");
            return;
        }
        filePath = filename;
    }

    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out<<text;
    file.flush();
    file.close();

    this->setWindowTitle(QFileInfo(filePath).absoluteFilePath());

    textChanged = false;

    // TODO 保存的函数还需要改进补充逻辑：没有新建文件的情况下按保存的逻辑
}


void MainWindow::on_actionSavaAs_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, "保存文件", ".", tr("Text files (*.txt) "));

    QFile file(filename);
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "..", "打开保存文件失败");
        return;
    }

    filePath = filename;
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out<<text;
    file.flush();
    file.close();

    this->setWindowTitle(QFileInfo(filePath).absoluteFilePath());
}


void MainWindow::on_textEdit_textChanged()
{
    if(!textChanged){
        this->setWindowTitle("*" + this->windowTitle());
        textChanged = true;
    }
}

bool MainWindow::userEditConfirmed()
{
    if(textChanged){

        QString path = (filePath != "") ? filePath : "无标题.txt";

        QMessageBox msg(this);
        msg.setIcon(QMessageBox::Question);
        msg.setWindowTitle("...");
        msg.setWindowFlag(Qt::Drawer);
        msg.setText(QString("是否将更改保存到\n") + "\"" + path + "\" ?");
        msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

        int r = msg.exec();
        switch(r){
        case QMessageBox::Yes:
            on_actionSave_triggered();
            break;
        case QMessageBox::No:
            textChanged = false;
            break;
        case QMessageBox::Cancel:
            return false;
        }
    }

    return true;

}


