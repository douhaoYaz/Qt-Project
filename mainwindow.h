#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStack>
#include <QKeyEvent>
#include <QMap>
#include <QPushButton>

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
    QMap<int, QPushButton *> digitBTNs; // 用QMap这种数据结构把键盘按下的数字键与Qt的按键映射起来
    QMap<int, QPushButton *> opertBTNs; // 用QMap这种数据结构把键盘按下的操作符与Qt的按键映射起来

    QString calculation(bool *ok=NULL);

private slots:

    void btnNumClicked();

    void btnBinaryOperatorClicked();
    void btnUnaryOperatorClicked();

    void on_btnPeriod_clicked();

    void on_btnDel_clicked();

    void on_btnClearAll_clicked();

    void on_btnEqual_clicked();

    virtual void keyPressEvent(QKeyEvent *event);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
