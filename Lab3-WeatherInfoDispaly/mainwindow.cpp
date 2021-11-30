#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    labelStationInfo = new QLabel("当前气象站点： ");  // 状态栏显示鼠标坐标
    labelStationInfo->setAlignment(Qt::AlignCenter);
    labelStationInfo->setMinimumWidth(400);
    labelStationInfo->setMaximumWidth(400);

    ui->statusbar->addPermanentWidget(labelStationInfo);

    labXYValue = new QLabel("日期=， 温度= ");   // 状态栏显示鼠标坐标
    labXYValue->setAlignment(Qt::AlignCenter);
    labXYValue->setMinimumWidth(400);
    labXYValue->setMaximumWidth(400);

    ui->statusbar->addPermanentWidget(labXYValue);

    QLabel *author = new QLabel(ui->statusbar);
    author->setText(tr("201841510108 符浩扬"));
    ui->statusbar->addPermanentWidget(author);

}

MainWindow::~MainWindow()
{
    delete ui;
}

