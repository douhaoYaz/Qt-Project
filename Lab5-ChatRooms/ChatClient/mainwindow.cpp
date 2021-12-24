#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHostAddress>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 初始化，使启动程序后首先进入的是登录界面
    ui->stackedWidget->setCurrentWidget(ui->loginPage);

    m_chatClient = new ChatClient(this);

    connect(m_chatClient, &ChatClient::connected, this, &MainWindow::connectedToServer);
    connect(m_chatClient, &ChatClient::messageReceived, this, &MainWindow::messageReceived);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_loginButton_clicked()
{
    m_chatClient->connectToServer(QHostAddress(ui->serverEdit->text()), 1967);
}


void MainWindow::on_sayButton_clicked()
{
    if (!ui->sayLineEdit->text().isEmpty())
        m_chatClient->sendMessage(ui->sayLineEdit->text());
}


void MainWindow::on_logoutButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->loginPage);
}

void MainWindow::connectedToServer()
{
    ui->stackedWidget->setCurrentWidget(ui->chatPage);
    m_chatClient->sendMessage(ui->usernameEdit->text(), "login");
}

void MainWindow::messageReceived(const QString &text)
{
    ui->roomTextEdit->append(text);
}

