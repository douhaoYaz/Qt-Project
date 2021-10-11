#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <math.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    digitBTNs = {{Qt::Key_0, ui->btnNum0},
                {Qt::Key_1, ui->btnNum1},
                {Qt::Key_2, ui->btnNum2},
                {Qt::Key_3, ui->btnNum3},
                {Qt::Key_4, ui->btnNum4},
                {Qt::Key_5, ui->btnNum5},
                {Qt::Key_6, ui->btnNum6},
                {Qt::Key_7, ui->btnNum7},
                {Qt::Key_8, ui->btnNum8},
                {Qt::Key_9, ui->btnNum9}
              };

    foreach(auto btn, digitBTNs)
        connect(btn, SIGNAL(clicked()), this, SLOT(btnNumClicked()));

//    connect(ui->btnNum0, SIGNAL(clicked()), this, SLOT(btnNumClicked()));
//    connect(ui->btnNum1, SIGNAL(clicked()), this, SLOT(btnNumClicked()));
//    connect(ui->btnNum2, SIGNAL(clicked()), this, SLOT(btnNumClicked()));
//    connect(ui->btnNum3, SIGNAL(clicked()), this, SLOT(btnNumClicked()));
//    connect(ui->btnNum4, SIGNAL(clicked()), this, SLOT(btnNumClicked()));
//    connect(ui->btnNum5, SIGNAL(clicked()), this, SLOT(btnNumClicked()));
//    connect(ui->btnNum6, SIGNAL(clicked()), this, SLOT(btnNumClicked()));
//    connect(ui->btnNum7, SIGNAL(clicked()), this, SLOT(btnNumClicked()));
//    connect(ui->btnNum8, SIGNAL(clicked()), this, SLOT(btnNumClicked()));
//    connect(ui->btnNum9, SIGNAL(clicked()), this, SLOT(btnNumClicked()));

    opertBTNs = {{Qt::Key_Plus, ui->btnPlus},
                 {Qt::Key_Minus, ui->btnMinus},
                 {Qt::Key_Asterisk, ui->btnMultiple},
                 {Qt::Key_Slash, ui->btnDivide}
                };

    foreach(auto btn, opertBTNs)
        connect(btn, SIGNAL(clicked()), this, SLOT(btnBinaryOperatorClicked()));

//    // 双操作数操作符处理
//    connect(ui->btnPlus, SIGNAL(clicked()), this, SLOT(btnBinaryOperatorClicked()));
//    connect(ui->btnMinus, SIGNAL(clicked()), this, SLOT(btnBinaryOperatorClicked()));
//    connect(ui->btnMultiple, SIGNAL(clicked()), this, SLOT(btnBinaryOperatorClicked()));
//    connect(ui->btnDivide, SIGNAL(clicked()), this, SLOT(btnBinaryOperatorClicked()));

    // 单操作数操作符处理
    connect(ui->btnPercentage, SIGNAL(clicked()), this, SLOT(btnUnaryOperatorClicked()));
    connect(ui->btnInverse, SIGNAL(clicked()), this, SLOT(btnUnaryOperatorClicked()));
    connect(ui->btnSquare, SIGNAL(clicked()), this, SLOT(btnUnaryOperatorClicked()));
    connect(ui->btnSqrt, SIGNAL(clicked()), this, SLOT(btnUnaryOperatorClicked()));
    connect(ui->btnSign, SIGNAL(clicked()), this, SLOT(btnUnaryOperatorClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::calculation(bool *ok)
{
    double result = 0;
    if(operands.size() == 2 && opcodes.size() > 0){
        // 从堆栈operands获取操作数
        double operand1 = operands.front().toDouble();
        operands.pop_front();
        double operand2 = operands.front().toDouble();
        operands.pop_front();

        // 从堆栈opcodes获取操作符
        QString op = opcodes.front();
        opcodes.pop_front();

        if(op == "+"){
            result = operand1 + operand2;
        }
        else if(op == "-"){
            result = operand1 - operand2;
        }
        else if(op == "×"){
            result = operand1 * operand2;
        }
        else if(op == "÷"){
            result = operand1 / operand2;
        }

        ui->statusbar->showMessage(QString("calculation is progress: operands is %1, opcodes is %2").arg(
                                       operands.size()).arg(opcodes.size()));

        // 保存当前结果作为操作数
        operands.push_back(QString::number(result));
        return QString::number(result);
    }
    else{
        ui->statusbar->showMessage(QString("operands is %1, opcodes is %2").arg(operands.size()).arg(opcodes.size()));
        return operands.front();
    }



}


void MainWindow::btnNumClicked()
{
    // 获取按键数
    QString digit = qobject_cast<QPushButton *>(sender())->text();
    // 防止display栏出现多个0开头的，如0002084
//    if(digit == "0" && operand == "0")
//        digit = "";
//    // 防止display栏出现以0开头的，如02084
//    if(operand == "0" && digit != "0")
//        operand = "";

    // 防止display栏出现诸如0002084或02084的情况
    if(operand == "0"){
        if(digit == "0")
            digit = "";
        else
            operand = "";
    }

    operand += digit;

    ui->display->setText(operand);
}



void MainWindow::on_btnPeriod_clicked()
{
    if(!operand.contains("."))
        operand += qobject_cast<QPushButton *>(sender())->text();
    ui->display->setText(operand);
}


void MainWindow::on_btnDel_clicked()
{
    operand = operand.left(operand.length()-1);
    ui->display->setText(operand);
}


void MainWindow::on_btnClearAll_clicked()
{
    operand.clear();
    operands.clear();
    ui->display->setText(operand);
}


void MainWindow::btnBinaryOperatorClicked()
{
    ui->statusbar->showMessage("last operand " + operand);
    // 获取操作符
    QString opcode = qobject_cast<QPushButton *>(sender())->text();

    // 如果操作数非空，即display里有数
    if(operand != ""){
        operands.push_back(operand);
        operand = "";

        opcodes.push_back(opcode);
        QString result = calculation();

        ui->display->setText(result);
    }


}

void MainWindow::btnUnaryOperatorClicked()
{
    if(operand != ""){
        double result = operand.toDouble();
        QString opcode = qobject_cast<QPushButton *>(sender())->text();
        if(opcode == "%")
            result /= 100;
        else if(opcode == "1/x")
            result = 1/result;
        else if(opcode == "x^2")
            result *= result;
        else if(opcode == "√")
            result = sqrt(result);
        else if(opcode == "+/-")
            result = -result;

        operand = QString::number(result);
        ui->display->setText(QString::number(result));
    }
}


void MainWindow::on_btnEqual_clicked()
{
    if(operand != ""){
            operands.push_back(operand);
            operand = "";
    }

    QString result = calculation();
    ui->display->setText(result);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    foreach(auto btnKey, digitBTNs.keys()){
        if(event->key() == btnKey)
            digitBTNs[btnKey]->animateClick(100);
    }

    foreach(auto btnKey, opertBTNs.keys()){
        if(event->key() == btnKey)
            opertBTNs[btnKey]->animateClick(100);
    }

    if(event->key() == Qt::Key_Equal)
        ui->btnEqual->animateClick(100);
    else if(event->key() == Qt::Key_Period)
        ui->btnPeriod->animateClick(100);
    else if(event->key() == Qt::Key_Percent)
        ui->btnPercentage->animateClick(100);
    else if(event->key() == Qt::Key_Backspace)
        ui->btnDel->animateClick(100);
}

