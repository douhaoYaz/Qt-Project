#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QLabel *labXYValue; // 状态栏显示鼠标坐标处的日期和温度
    QLabel *labelStationInfo;   // 状态栏显示鼠标坐标处的气象站点
};
#endif // MAINWINDOW_H
