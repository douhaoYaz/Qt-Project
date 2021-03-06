#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QMap>
#include <QStringListModel>
#include <QtCharts>
#include <QLineSeries>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

typedef struct WeatherRecord{
    QDateTime date;
    QString key{"UNKNOWN"};
    double average_temperature{0};
    double minimum_temperature{0};
    double maximum_temperature{0};
    double rainfall{0};
    double snowfall{0};
    double dew_point{0};
    double relative_humidity{0};
}WeatherRecord;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_action_triggered();

    void on_listView_clicked(const QModelIndex &index);

    void on_actionZoomIn_triggered();

    void on_actionZoomOut_triggered();

    void on_actionResetZoom_triggered();

    void on_LegendMarkerClicked();  // 图例单击槽函数，自定义槽函数
    void on_mouseMovePoint(QPoint point);   // 鼠标移动事件，自定义槽函数

private:

    void processRecord(QString str);
    void createChart();
    Ui::MainWindow *ui;

    QLabel *labXYValue; // 状态栏显示鼠标坐标处的日期和温度
    QLabel *labelStationInfo;   // 状态栏显示鼠标坐标处的气象站点

    QMap<QString, QList<WeatherRecord>> weatherRecordsMap;
    QMap<QString, QLineSeries *> lineSeries;

    QStringListModel *theModel;
    QDateTimeAxis *axisX;
    QValueAxis *axisY;
};
#endif // MAINWINDOW_H
