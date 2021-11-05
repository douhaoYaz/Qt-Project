#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutdialog.h"
#include "searchdialog.h"
#include "replacedialog.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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

