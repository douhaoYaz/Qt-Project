#ifndef REPALCEDIALOG_H
#define REPALCEDIALOG_H

#include <QDialog>

namespace Ui {
class RepalceDialog;
}

class RepalceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RepalceDialog(QWidget *parent = nullptr);
    ~RepalceDialog();

private:
    Ui::RepalceDialog *ui;
};

#endif // REPALCEDIALOG_H
