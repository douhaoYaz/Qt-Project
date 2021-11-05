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

private slots:
    void on_actionAbout_triggered();

    void on_actionFind_triggered();

    void on_actionReplace_triggered();

private:
    Ui::MainWindow *ui;

    QLabel statusCursorLabel;   //用于在状态栏中显示信息
    QLabel statusLabel;         //用于在状态栏中显示长度和行数信息
};
#endif // MAINWINDOW_H
