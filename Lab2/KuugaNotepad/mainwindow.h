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

    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSavaAs_triggered();

    void on_textEdit_textChanged();

private:
    Ui::MainWindow *ui;

    QLabel statusCursorLabel;   //用于在状态栏中显示信息
    QLabel statusLabel;         //用于在状态栏中显示长度和行数信息

    QString filePath;           // 记录成功打开的文件路径，用于Open操作和Save操作
    bool textChanged;           // 用于记录textEdit是否被改变

    bool userEditConfirmed();   // 在用户点击新建、打开之后弹出MessageBox，让用户选择是否保存当前更改
};
#endif // MAINWINDOW_H
