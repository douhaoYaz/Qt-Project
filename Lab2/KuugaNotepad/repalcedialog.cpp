#include "repalcedialog.h"
#include "ui_repalcedialog.h"

RepalceDialog::RepalceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RepalceDialog)
{
    ui->setupUi(this);
}

RepalceDialog::~RepalceDialog()
{
    delete ui;
}
