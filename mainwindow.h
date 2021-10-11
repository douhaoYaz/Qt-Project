#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStack>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString operand;    // 暂存操作数
    QString opcode;     // 暂存操作符
    QStack<QString> operands;   // 用堆栈存储操作数
    QStack<QString> opcodes;    // 用堆栈存储操作符

    QString calculation(bool *ok=NULL);

private slots:

    void btnNumClicked();

    void btnBinaryOperatorClicked();

    void on_btnPeriod_clicked();

    void on_btnDel_clicked();

    void on_btnClearAll_clicked();

    void on_btnEqual_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
