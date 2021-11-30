#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTextStream>
#include <QDebug>

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

    // 创建模型
    theModel = new QStringListModel(this);
    // 把模型和view关联起来
    ui->listView->setModel(theModel);

    createChart();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_action_triggered()
{
    //打开文件
    QString curPath=QCoreApplication::applicationDirPath(); //获取应用程序的路径
    //调用打开文件对话框打开一个文件
    QString aFileName=QFileDialog::getOpenFileName(this,"打开一个文件",curPath,
                 "气象数据文件(*.csv);;所有文件(*.*)");
    if (aFileName.isEmpty())
        return; //如果未选择文件，退出

    QFile aFile(aFileName);  //以文件方式读出
    if (aFile.open(QIODevice::ReadOnly | QIODevice::Text)) //以只读文本方式打开文件
    {
        QTextStream aStream(&aFile); //用文本流读取文件
        while (!aStream.atEnd())
        {
            QString str=aStream.readLine();//读取文件的一行
//            qDebug() << str;
            processRecord(str);
        }

        QStringList strList;
        for(auto key: weatherRecordsMap.keys())
        {
            qDebug() << key << ":" << weatherRecordsMap[key].size();
            strList << key;
        }

        theModel->setStringList(strList);

        aFile.close();//关闭文件
    }
}

void MainWindow::processRecord(QString recordStr)
{
    // 一个或多个空格、TAB等分隔符隔开的字符串， 分解为一个StringList
    QStringList tmpList=recordStr.split(QRegExp(","));
    WeatherRecord record;

    // 简单的数据有效性检测
    if(tmpList.size() != 9){
        qDebug() << "wrong format" << recordStr;
        return;
    }

    record.date = tmpList[0];
    record.key = tmpList[1];
    record.average_temperature = tmpList[2].toDouble();
    record.minimum_temperature = tmpList[3].toDouble();
    record.maximum_temperature = tmpList[4].toDouble();
    record.rainfall = tmpList[5].toDouble();
    record.snowfall = tmpList[6].toDouble();
    record.dew_point = tmpList[7].toDouble();
    record.relative_humidity = tmpList[8].toDouble();

    weatherRecordsMap[record.key].append(record);
}


void MainWindow::on_listView_clicked(const QModelIndex &index)
{
    QString stationKey = theModel->data(index).toString();
    labelStationInfo->setText(QString("当前气象站点：%1").arg(stationKey));
    ui->chartView->chart()->setTitle(QString("气象信息：%1").arg(stationKey));

    // 每次点击listView的项时先清除右边chart的内容，然后再显示数据
    lineSeries["average_temperature"]->clear();
    lineSeries["minimum_temperature"]->clear();
    lineSeries["maximum_temperature"]->clear();
    int count = 0;

    for(auto record : weatherRecordsMap[stationKey]){
        lineSeries["average_temperature"]->append(count, record.average_temperature);
        lineSeries["minimum_temperature"]->append(count, record.minimum_temperature);
        lineSeries["maximum_temperature"]->append(count, record.maximum_temperature);
        count++;
    }


}

void MainWindow::createChart()
{ //创建图表
    QChart *chart = new QChart();
    ui->chartView->setChart(chart);
    ui->chartView->setRenderHint(QPainter::Antialiasing);
    ui->chartView->setCursor(Qt::CrossCursor); //设置鼠标指针为十字星

    axisX = new QValueAxis;
    axisX->setRange(0, 360); //设置坐标轴范围
    axisX->setLabelFormat("%.1f"); //标签格式
    axisX->setTickCount(10); //主分隔个数
    axisX->setMinorTickCount(2);//4
    axisX->setTitleText("日期"); //标题

    axisY = new QValueAxis;
    axisY->setRange(-30, 50);
    axisY->setTitleText("温度");
    axisY->setTickCount(9);
    axisY->setLabelFormat("%.2f"); //标签格式
    axisY->setMinorTickCount(2);//4

//另外一种添加坐标轴的方式，Qt 5.12.1中编译没问题
    chart->addAxis(axisX,Qt::AlignBottom); //坐标轴添加到图表，并指定方向
    chart->addAxis(axisY,Qt::AlignLeft);

    lineSeries["average_temperature"] = new QLineSeries();
    lineSeries["average_temperature"]->setName("平均温度");
    lineSeries["minimum_temperature"] = new QLineSeries();
    lineSeries["minimum_temperature"]->setName("最低温度");
    lineSeries["maximum_temperature"] = new QLineSeries();
    lineSeries["maximum_temperature"]->setName("最高温度");

    for(auto key : lineSeries.keys()){
        chart->addSeries(lineSeries[key]);
        lineSeries[key]->attachAxis(axisX); // 序列 series1 附加坐标轴
        lineSeries[key]->attachAxis(axisY);
    }

}
