#ifndef MASTERVIEW_H
#define MASTERVIEW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MasterView; }
QT_END_NAMESPACE

class MasterView : public QWidget
{
    Q_OBJECT

public:
    MasterView(QWidget *parent = nullptr);
    ~MasterView();

private:
    Ui::MasterView *ui;
};
#endif // MASTERVIEW_H
