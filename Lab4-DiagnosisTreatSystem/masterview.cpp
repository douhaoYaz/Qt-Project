#include "masterview.h"
#include "ui_masterview.h"
#include <QDebug>

MasterView::MasterView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MasterView)
{
    ui->setupUi(this);

    goLoginView();  // 一打开首先进入login页面
}

MasterView::~MasterView()
{
    delete ui;
}

void MasterView::goLoginView()
{
    qDebug() << "goLoginView";
    loginView = new LoginView();        // 先创建一个loginView页面实例

    pushWidgetToStackView(loginView);   // 将这个loginView页面实例压如stackedWidget的栈中

    connect(loginView, SIGNAL(loginSuccess()), this, SLOT(goWelcomView()));
}

void MasterView::goWelcomView()
{
    qDebug() << "goWelcomView";
    welcomView = new WelcomeView();        // 先创建一个welcomView页面实例

    pushWidgetToStackView(welcomView);      //将这个welcomeView页面实例压入stackedWidget的栈中
}

void MasterView::goDoctorView()
{
    qDebug() << "goDoctorView";
    doctorView = new DoctorView();        // 先创建一个doctorView页面实例

    pushWidgetToStackView(doctorView);      //将这个doctorView页面实例压入stackedWidget的栈中
}

void MasterView::goDepartmentView()
{
    qDebug() << "goDepartmentView";
    departmentView = new DepartmentView();        // 先创建一个departmentView页面实例

    pushWidgetToStackView(departmentView);      //将这个departmentView页面实例压入stackedWidget的栈中
}

void MasterView::goPatientEditView()
{
    qDebug() << "goPatientEditView";
    patientEditView = new PatientEditView();        // 先创建一个patientEditView页面实例

    pushWidgetToStackView(patientEditView);      //将这个patientEditView页面实例压入stackedWidget的栈中
}

void MasterView::goPatientView()
{
    qDebug() << "goPatientView";
    patientView = new PatientView();        // 先创建一个patientView页面实例

    pushWidgetToStackView(patientView);      //将这个patientView页面实例压入stackedWidget的栈中
}

void MasterView::goPreviousView()
{
    int count = ui->stackedWidget->count();     // 获取当前栈中页面个数

    if (count > 1){
        ui->stackedWidget->setCurrentIndex(count-2);    // 显示上一个页面（count-1是当前页面，count-2是上一个页面）
        ui->labelTitle->setText(ui->stackedWidget->currentWidget()->windowTitle());     // 设置页面上方标题

        QWidget *widget = ui->stackedWidget->widget(count-1);    // 获取栈顶页面
        ui->stackedWidget->removeWidget(widget);        // 将栈顶页面从栈中移出
        delete widget;      // 在内存中删除栈顶页面
    }
}

void MasterView::pushWidgetToStackView(QWidget *widget)
{
    ui->stackedWidget->addWidget(widget);    // 将这个页面实例压入stackedWidget的栈

    int count = ui->stackedWidget->count();     // 获得stackedWidget栈里的页面个数
    ui->stackedWidget->setCurrentIndex(count-1);    // 将最新压如stackedWidget栈的页面设置为当前页面
    ui->labelTitle->setText(widget->windowTitle());  // 设置页面上方标题
}


void MasterView::on_btBack_clicked()
{
    goPreviousView();
}

