#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 初始化，使启动程序后首先进入的是登录界面
    ui->stackedWidget->setCurrentWidget(ui->loginPage);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_loginButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->chatPage);
}


void MainWindow::on_sayButton_clicked()
{

}


void MainWindow::on_logoutButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->loginPage);
}

